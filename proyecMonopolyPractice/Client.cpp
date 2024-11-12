#include "Client.hpp"

Client::Client() : client(nullptr), peer(nullptr), running(false), lastRollResult(0) {}

std::string generateRoomCode() {
	std::string code;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, 9);

	for (int i = 0; i < 5; ++i) {
		code += std::to_string(dist(mt));
	}

	return code;
}

Client::~Client() {
	disconnect();
	if (client) {
		enet_host_destroy(client);
	}
	enet_deinitialize();
}

bool Client::initialize() {
	static bool enetInitialized = false;
	if (!enetInitialized) {
		if (enet_initialize() != 0) {
			std::cerr << "Error initializing ENet!" << std::endl;
			return false;
		}
		enetInitialized = true;
	}

	// Solo crear cliente si no existe
	if (!client) {
		client = enet_host_create(nullptr, 1, 2, 0, 0);
		if (!client) {
			std::cerr << "Error creating ENet client!" << std::endl;
			return false;
		}
	}
	return true;
}

void Client::run() {
	running = true;
	while (running) {
		ENetEvent event;
		while (enet_host_service(client, &event, 100) > 0) {
			switch (event.type) {
			case ENET_EVENT_TYPE_RECEIVE: {
				std::string message(reinterpret_cast<char*>(event.packet->data), event.packet->dataLength);
				handleServerMessage(message);  // Manejar el mensaje recibido
				enet_packet_destroy(event.packet);
				break;
			}
			case ENET_EVENT_TYPE_DISCONNECT:
				//      std::cout << "Disconnected from server!" << std::endl;
				running = false;
				break;
			default:
				break;
			}
		}
	}
}

bool Client::connectToServer(const std::string& address, uint16_t port) {
	ENetAddress enetAddress;
	enet_address_set_host(&enetAddress, address.c_str());
	enetAddress.port = port;

	// Conectar al servidor
	peer = enet_host_connect(client, &enetAddress, 2, 0);
	if (!peer) {
		std::cerr << "No available peers for initiating an ENet connection!" << std::endl;
		return false;
	}

	ENetEvent event;
	const int maxRetries = 10;  // Reducir el n�mero de reintentos
	const int retryDelay = 10;  // Reducir el tiempo de espera entre reintentos
	int totalTimeWaited = 0;

	// Intentar conectar
	for (int i = 0; i < maxRetries; ++i) {
		if (enet_host_service(client, &event, retryDelay) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
			std::cout << "Connected to server!" << std::endl;
			isConnected = true;
			clientThread = std::thread(&Client::run, this);  // Iniciar el hilo
			return true;
		}
		totalTimeWaited += retryDelay;
		if (totalTimeWaited >= 100) break;
	}

	std::cerr << "Failed to connect to server within 0.1 seconds." << std::endl;
	enet_peer_reset(peer);  // Limpiar la conexi�n si falla
	return false;
}


void Client::disconnect() {
	if (!isConnected) return;  // Si no est� conectado, no hace nada

	// Desconectar y liberar recursos
	if (peer) {
		enet_peer_disconnect(peer, 0);
		peer = nullptr;
	}

	running = false;  // Detener el hilo de ejecuci�n
	if (clientThread.joinable()) {
		clientThread.join();  // Esperar a que termine el hilo
	}

	// Destruir el cliente y liberar recursos
	if (client) {
		enet_host_destroy(client);
		client = nullptr;
	}

	isConnected = false;  // Actualizar estado de la conexi�n
	std::cout << "Disconnected from server!" << std::endl;
}



std::string Client::createRoom(const std::string& username) {
	if (!peer) {
		std::cerr << "Client is not connected to a server!" << std::endl;
		return ""; // Retornar una cadena vac�a en caso de error
	}

	// Generar el c�digo de la sala
	std::string roomCode = generateRoomCode();
	std::cout << "Room created with code: " << roomCode << std::endl;

	// Establecer el �ndice del jugador como 0 (creador)
	playerIndex = 0;

	// Crear el mensaje para el paquete
	std::string message = "CREATE_ROOM:" + roomCode + ":" + username + ":";


	// Crear y enviar el paquete ENet
	ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);

	// Asegurar que el paquete se env�e inmediatamente
	enet_host_flush(client);

	return roomCode;
}




bool Client::joinRoom(const std::string& roomCode, const std::string& username) {
	if (!peer) {
		std::cerr << "Client is not connected to a server!" << std::endl;
		return false;
	}

	// Crear el mensaje que incluye roomCode y username
	std::string message = "JOIN_ROOM:" + roomCode + ":" + username + ":";

	// Crear el paquete ENet
	ENetPacket* packet = enet_packet_create(message.c_str(), message.size(), ENET_PACKET_FLAG_RELIABLE);
	if (!packet) {
		std::cerr << "Failed to create ENet packet for JOIN_ROOM." << std::endl;
		return false;
	}

	// Enviar el paquete y verificar errores
	if (enet_peer_send(peer, 0, packet) < 0) {
		std::cerr << "Failed to send JOIN_ROOM packet to server." << std::endl;
		return false;
	}

	// Asegurar que el paquete se env�e inmediatamente
	enet_host_flush(client);

	return true;
}




bool Client::sendImage(const std::string& filename) {
	if (!peer) {
		std::cerr << "Client is not connected to a server!" << std::endl;
		return false;
	}



	std::string message = "SEND_IMAGE:" + filename;


	// Crear y enviar el paquete ENet
	ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);

	// Asegurar que el paquete se env�e inmediatamente
	enet_host_flush(client);

	std::cout << "Filename sent:" << message << std::endl;
	return true;
}




std::vector<char> Client::loadImage(const std::string& filename) {
	std::ifstream file(filename, std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Failed to open the image file!" << std::endl;
		return {};
	}

	std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();
	return buffer;
}

// Nueva funci�n para solicitar tirada de dados
void Client::rollDice() {
	if (!peer) {
		std::cerr << "Client is not connected to a server!" << std::endl;
	}
	std::cout << "\nUYYYyy";
	std::string message = "ROLL_DICE";
	ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	enet_host_flush(client);
	std::cout << "\neYYYyy";
}


void Client::opcionCaminoenvio(int opcionCami) {
	if (!peer) {
		std::cerr << "Client is not connected to a server!" << std::endl;
	}
	
	std::string message = "OPCION_CAMINO:"+ std::to_string(opcionCami);
	ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	enet_host_flush(client);
	
}

void Client::endTurn() {
	if (!peer) {
		std::cerr << "Client is not connected to a server!" << std::endl;
	}
	std::cout << "\nUYYyy";
	std::string message = "END_TURN";
	ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	enet_host_flush(client);
	std::cout << "\neYYyy";
}

void Client::startSpin() {
	if (!peer) {
		std::cerr << "Client is not connected to a server!" << std::endl;
		return;
	}

	std::string message = "START_SPIN";
	ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	enet_host_flush(client);

	std::cout << "Spin initiated!" << std::endl;
}

void Client::ruleteGame(float angulo) {
	if (!peer) {
		std::cerr << "Client is not connected to a server!" << std::endl;
		return;
	}

	std::string message = "RULETE_GAME:";
	ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	enet_host_flush(client);

	std::cout << "Spin initiated!" << std::endl;

}


void Client::playerChangedPiece() {
	std::string message = "SELECTING_PIECE:" + std::to_string(playerInfos[0].indexPiece);
	std::cout << "\nSELECTING_PIECE:" << playerInfos[0].indexPiece;
	ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	enet_host_flush(client);
}


void Client::ReadyPlayer() {
	if (!peer) {
		std::cerr << "Client is not connected to a server!" << std::endl;
	}

	std::string message = "PLAYER_READY";
	ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	enet_host_flush(client);

}






// Manejar mensajes recibidos del servidor
void Client::handleServerMessage(const std::string& message) {



	std::cout << "\n mensage:" << message;




	if (message.rfind("YOUR_TURN", 0) == 0) {
		std::cout << "It's your turn!" << std::endl;
		// Aqu� el jugador puede decidir llamar a `rollDice`
		turn_dado = true;
		turn = true;
		turn_ruleta = true;
		IndexTurn = 0;
	}else 	if (message.rfind("TURN_START", 0) == 0) {
		std::cout << "\nReceived message: " << message << std::endl;  // Depuraci�n

		// Buscar el inicio de "PLAYER_INDEX:" y extraer el valor num�rico despu�s
		size_t indexPos = message.find("PLAYER_INDEX:");  // Encontrar el �ndice donde empieza "PLAYER_INDEX:"
		if (indexPos != std::string::npos) {
			// Extraer la parte despu�s de "PLAYER_INDEX:"
			std::string playerIndexStr = message.substr(indexPos + 13); // 13 es la longitud de "PLAYER_INDEX:"

			std::cout << "Extracted player index string: " << playerIndexStr << std::endl;  // Depuraci�n

			// Convertir la cadena extra�da a entero
			int playerIndexTurn = std::stoi(playerIndexStr);

			std::cout << "Converted player index: " << playerIndexTurn << std::endl;  // Depuraci�n

			// Ajustar el turno
			playerIndexTurn = (playerIndexTurn - playerIndex + 4) % 4;

			IndexTurn = playerIndexTurn;
			std::cout << "Turn has started for player: " << playerIndexTurn << std::endl;
		}
		else {
			std::cout << "Invalid message format for TURN_START." << std::endl;
		}
	}



	else if (message.rfind("ROLL_RESULT:", 0) == 0) {
		std::cout << "\nEjecuci�n de ROLL_RESULT";

		size_t playerIndexPos = message.find(":PLAYER_INDEX:") + std::string(":PLAYER_INDEX:").length();
		size_t dicePos = message.find(":DICE:", playerIndexPos);

		if (playerIndexPos != std::string::npos && dicePos != std::string::npos) {
			int currentPlayerIndex = std::stoi(message.substr(playerIndexPos, dicePos - playerIndexPos));
			int diceRoll = std::stoi(message.substr(dicePos + std::string(":DICE:").length()));

			lastRollResult = diceRoll; // Asigna el resultado del dado aqu�

			if (turn) {
				{
					std::lock_guard<std::mutex> lock(mtx);
					espera = true; // Cambia espera a true
				}

				cv.notify_one(); // Notifica al hilo principal para continuar
			}
			else {
				{
					std::lock_guard<std::mutex> lock(mtx);
					rolldiceJugador = true; // Cambia rolldiceJugador a true
				}

				cv.notify_one(); // Notifica al hilo principal para continuar
			}

			std::cout << "\nResultado en clase cliente:" << lastRollResult;
			std::cout << "\nDice roll result: " << diceRoll << " para jugador con �ndice: " << currentPlayerIndex << std::endl;
		}
		else {
			std::cerr << "Formato del mensaje ROLL_RESULT incorrecto" << std::endl;
		}
	}

	else if (message == "NOT_YOUR_TURN") {

		std::cout << "Wait for your turn!" << std::endl;

	}

	else if(message.rfind("OPCION_CAMINO:", 0) == 0) {
		// Encuentra el primer ":" para asegurarse de que haya algo despu�s
		size_t pos = message.find(":");
		if (pos != std::string::npos && pos + 1 < message.size()) {
			// Extrae la parte num�rica del mensaje
			std::string opcionCami = message.substr(pos + 1);

			// Puedes convertir opcionCami a un n�mero si es necesario
			try {
				int opcion = std::stoi(opcionCami);  // Convierte el string a int
				std::cout << "Opci�n recibida: " << opcion << std::endl;


				Opcioncami = opcion;





			}
			catch (const std::invalid_argument& e) {
				std::cerr << "Error al convertir la opci�n: " << e.what() << std::endl;
			}
			catch (const std::out_of_range& e) {
				std::cerr << "N�mero fuera de rango: " << e.what() << std::endl;
			}
		}
		else {
			std::cerr << "Mensaje mal formado: falta valor despu�s de los dos puntos." << std::endl;
		}
	}

	else if (message.rfind("PLAYER_INDEX:", 0) == 0) {

		std::cout << "\nEJEcuto playerindex1";
		// Extraer el �ndice del jugador
		std::string indexStr = message.substr(std::string("PLAYER_INDEX:").length());
		playerIndex = std::stoi(indexStr);


		// Aqu� puedes realizar la l�gica que necesites con el �ndice del jugador
		std::cout << "Tu �ndice de jugador es: " << playerIndex << std::endl;
		std::cout << "\nEJEcuto playerindex2";

	}

	else if (message.rfind("NEW_PLAYER:", 0) == 0) {
		std::cout << "\nNEW_PLAYER";

		// Eliminar el prefijo "NEW_PLAYER:"
		if (message.length() < 11) { // 11 es la longitud de "NEW_PLAYER:"
			std::cout << "\nEJEcuto toy mal";
			return;
		}
		std::cout << "\nEJEcuto existen1";
		std::string data = message.substr(11); // Obtener los datos sin el prefijo

		// Dividir la cadena de datos en partes usando ":" como delimitador
		std::istringstream iss(data);
		std::string username, indexStr, moneyStr, isSelectingStr, isInGameStr;

		if (std::getline(iss, username, ':') &&
			std::getline(iss, indexStr, ':') &&
			std::getline(iss, moneyStr, ':') &&
			std::getline(iss, isSelectingStr, ':') &&
			std::getline(iss, isInGameStr, ':')) {
			//&&std::getline(iss, imageStr)
			// Todos los valores se han le�do correctamente
		}
		else {
			std::cout << "\nEJEcuto toy remal";
			return;
		}

		int index;
		int money;
		bool isSelecting;
		bool isInGame;

		std::cout << "indexStr: '" << indexStr << "', moneyStr: '" << moneyStr << "'\n";

		// Convertir el �ndice y el dinero a sus tipos apropiados
		try {
			index = std::stoi(indexStr);
			money = std::stoi(moneyStr);
			isSelecting = (isSelectingStr == "true");
			isInGame = (isInGameStr == "true");
		}
		catch (const std::invalid_argument& e) {
			// Manejar el error (el valor no es un n�mero)
			std::cout << "\nEJEcuto no sirvo";
			return;
		}
		catch (const std::out_of_range& e) {
			// Manejar el error (el n�mero est� fuera del rango)
			std::cout << "\nEJEcuto no 98989";
			return;
		}
		std::cout << "\nEJEcuto existen3";



		if (playerIndex != 0) {

			index = (index - playerIndex + 4) % 4;

		}


		// Asegurarse de que el �ndice est� dentro de los l�mites
		if (index >= 0 && index < playerInfos.size()) {
			std::cout << "\nEJEcuto existen6";
			// Actualizar la informaci�n del jugador en la posici�n correspondiente
			playerInfos[index].username = username;
			playerInfos[index].money = money;
			playerInfos[index].isSelectingPiece = isSelecting;
			playerInfos[index].isInGame = isInGame;

			// Procesar la imagen
			//std::vector<char> image(imageStr.begin(), imageStr.end());
			//playerInfos[index].image = image;

			// Cargar la textura del avatar
		  //  playersGame[index].textureAvatarPLayer.loadFromMemory(image.data(), image.size());
			playersGame[index].NamePlayer.setString(playerInfos[index].username);

			// Imprimir la informaci�n del jugador
			std::cout << "Player " << index << ": " << username
				<< " | Money: " << money
				<< " | Is Selecting: " << (isSelecting ? "Yes" : "No")
				<< " | Is In Game: " << (isInGame ? "Yes" : "No")
				<< std::endl;

			std::cout << "\nEJEcuto existen4";
		}
		else {
			std::cerr << "Error: Index out of bounds for player information." << std::endl;
		}


		std::cout << "\nEJEcuto existen2";
	}
	else if (message.rfind("EXISTING_PLAYER:", 0) == 0) {
		// Eliminar el prefijo "EXISTING_PLAYER:"
		std::cout << "\nEXISTING_PLAYER";

		if (message.length() < 16) {
			std::cout << "\nEJEcuto toy mal";
			return;
		}
		std::cout << "\nEJEcuto existen1";
		std::string data = message.substr(16);

		// Dividir la cadena de datos en partes usando ":" como delimitador
		std::istringstream iss(data);
		std::string username, indexStr, moneyStr, isSelectingStr, isInGameStr, imagePath;

		if (std::getline(iss, username, ':') &&
			std::getline(iss, indexStr, ':') &&
			std::getline(iss, moneyStr, ':') &&
			std::getline(iss, isSelectingStr, ':') &&
			std::getline(iss, isInGameStr, ':') &&
			std::getline(iss, imagePath)) { 
			

			   // Todos los valores se han le�do correctamente
		}
		else {
			std::cout << "\nEJEcuto toy remal";

		}

		int index;
		int money;
		bool isSelecting;
		bool isInGame;
		std::string image;
		std::cout << "indexStr: '" << indexStr << "', moneyStr: '" << moneyStr << "'\n";

		// Convertir el �ndice y el dinero a sus tipos apropiados
		try {
			index = std::stoi(indexStr);
			money = std::stoi(moneyStr);
			isSelecting = (isSelectingStr == "true");
			isInGame = (isInGameStr == "true");
			image = imagePath; // Guardar la direcci�n de la imagen
		}
		catch (const std::invalid_argument& e) {
			// Manejar el error (el valor no es un n�mero)
			std::cout << "\nEJEcuto no sirvo";
			return;
		}
		catch (const std::out_of_range& e) {
			// Manejar el error (el n�mero est� fuera del rango)
			std::cout << "\nEJEcuto no 98989";
			return;
		}
		std::cout << "\nEJEcuto existen3";



		if (playerIndex != 0) {

			index = (index - playerIndex + 4) % 4;

		}


		//std::vector<char> image(imageStr.begin(), imageStr.end());


		// Asegurarse de que el �ndice est� dentro de los l�mites
		if (index >= 0 && index < playerInfos.size()) {
			std::cout << "\nEJEcuto existen6";
			// Actualizar la informaci�n del jugador en la posici�n correspondiente
			playerInfos[index].username = username;
			playerInfos[index].money = money;
			playerInfos[index].isSelectingPiece = isSelecting;
			playerInfos[index].isInGame = isInGame;
			playerInfos[index].image = image;



			if (!playersGame[index].textureAvatarPLayer.loadFromFile(playerInfos[index].image)) {
				std::cerr << "Error loading image!" << std::endl;
			}
			playersGame[index].NamePlayer.setString(playerInfos[index].username);


			// Imprimir la informaci�n del jugador
			std::cout << "Player " << index << ": " << username
				<< " | Money: " << money
				<< " | Is Selecting: " << (isSelecting ? "Yes" : "No")
				<< " | Is In Game: " << (isInGame ? "Yes" : "No")
				<< std::endl;

			std::cout << "\nEJEcuto existen4";
		}
		else {
			std::cerr << "Error: Index out of bounds for player information." << std::endl;
		}

		std::cout << "\nEJEcuto existen2";
	}
	else if (message.rfind("PLAYER_COUNT:", 0) == 0) {
		std::cout << "\nPLAYER_COUNT" << std::endl;
		// Extraer la cantidad de jugadores de la mensaje
		std::string playerCountStr = message.substr(13); // "PLAYER_COUNT:".length() == 13
		int playerCount = std::stoi(playerCountStr);
		NumPlayers = playerCount;

	}
	else if (message.rfind("SEND_IMAGE:", 0) == 0) {
		// Extraer el �ndice y el nombre del archivo
		size_t firstColon = message.find(":", 11); // Buscar el primer ':' despu�s de "SEND_IMAGE:"
		int IIndex = std::stoi(message.substr(11, firstColon - 11)); // Extraer el �ndice
		std::string filename = message.substr(firstColon + 1); // Extraer el nombre del archivo

		std::cout << "Received image info - Player Index: " << playerIndex << ", Filename: " << filename << std::endl;


		IIndex = (IIndex - playerIndex + 4) % 4;

		if (!playersGame[IIndex].textureAvatarPLayer.loadFromFile(filename)) {
			std::cerr << "Error loading image!" << std::endl;
		}


		// Guardar la imagen recibida (opcional)


		std::cout << "Received image from player " << IIndex << std::endl;
	}
	else if (message.rfind("PLAYER_CHANGED_PIECE:", 0) == 0) {
			std::cout << "\nEJEcuto index1";
			std::cout << "\nMensaje recibido: " << message;
			std::string indexStr;
			std::string pieceIndexStr;
			try {
				// Encontrar las posiciones de los delimitadores ":" en el mensaje
				size_t firstColon = message.find(":", 20);   // Buscar el primer ":" despu�s del prefijo
				size_t secondColon = message.find(":", firstColon + 1); // Buscar el segundo ":" despu�s del primero

				if (firstColon == std::string::npos || secondColon == std::string::npos) {
					std::cerr << "Error: Formato de mensaje inesperado. Faltan delimitadores." << std::endl;
					return;
				}

				// Extraer las subcadenas correspondientes al �ndice del jugador y al �ndice de la pieza
				indexStr = message.substr(firstColon + 1, secondColon - firstColon - 1);
				pieceIndexStr = message.substr(secondColon + 1);

				// Mostrar los valores extra�dos para depuraci�n
				std::cout << "\nindexStr: '" << indexStr << "', pieceIndexStr: '" << pieceIndexStr << "'";

				// Convertir los valores a enteros
				int Index = std::stoi(indexStr);
				int indexselectinpiece = std::stoi(pieceIndexStr);

				// Ajustar el �ndice del jugador
				Index = (Index - playerIndex + 4) % 4;
				CplayerIndex = Index;

				// Actualizar la informaci�n en el cliente
				std::cout << "Player " << playerIndex << " seleccion� la pieza con �ndice " << indexselectinpiece << std::endl;
				playerInfos[Index].indexPiece = indexselectinpiece;
				std::cout << "\nEJEcuto index 2";
			}
			catch (const std::invalid_argument& e) {
				std::cerr << "\nError: Argumento no v�lido al intentar convertir a entero. indexStr: '" << indexStr << "', pieceIndexStr: '" << pieceIndexStr << "'" << std::endl;
			}
			catch (const std::out_of_range& e) {
				std::cerr << "\nError: N�mero fuera de rango al intentar convertir a entero. indexStr: '" << indexStr << "', pieceIndexStr: '" << pieceIndexStr << "'" << std::endl;
			}
	}
	else if (message.rfind("PLAYER_READY:", 0) == 0) {
			// Extraer el `indexPlayer` del mensaje
			std::cout << "\n PLAYER READY" << std::endl;
			int indexPlayer = std::stoi(message.substr(13)); // "PLAYER_READY:" tiene 13 caracteres
			indexPlayer = (indexPlayer - playerIndex + 4) % 4;
			playerInfos[indexPlayer].isSelectingPiece = true;

			// Ahora puedes usar `indexPlayer` para actualizar el estado del jugador en el cliente
			std::cout << "Jugador " << indexPlayer << " est� listo." << std::endl;

			// Realiza cualquier acci�n adicional para indicar que este jugador est� listo,
			// como actualizar el estado en la interfaz de usuario.
			std::cout << "\n PLAYER fin" << std::endl;
	}
	else {
			std::cerr << "Unknown message received from server: " << message << std::endl;
	}
}
