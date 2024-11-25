#include "Client.hpp"

Client::Client() : client(nullptr), peer(nullptr), running(false), lastRollResult(0) , turnopermitido(0), conteoturn(0){}

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

	std::cout << "\nInicia";
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

	std::cout << "\nInicia0";
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
	std::cout << "\nIniciaConec";
	enet_address_set_host(&enetAddress, address.c_str());
	enetAddress.port = port;

	// Conectar al servidor
	peer = enet_host_connect(client, &enetAddress, 2, 0);
	if (!peer) {
		std::cerr << "No available peers for initiating an ENet connection!" << std::endl;
		return false;
	}
	std::cout << "\nIniciaConec 0";
	ENetEvent event;
	const int maxRetries = 10;  // Reducir el número de reintentos
	const int retryDelay = 10;  // Reducir el tiempo de espera entre reintentos
	int totalTimeWaited = 0;

	// Intentar conectar
	for (int i = 0; i < maxRetries; ++i) {
		if (enet_host_service(client, &event, retryDelay) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
			std::cout << "Connected to server!" << std::endl;
			isConnected = true;
			clientThread = std::thread(&Client::run, this);  // Iniciar el hilo
			casasCargadas = false;
			return true;
		}
		totalTimeWaited += retryDelay;
		if (totalTimeWaited >= 100) break;
	}

	std::cerr << "Failed to connect to server within 0.1 seconds." << std::endl;
	enet_peer_reset(peer);  // Limpiar la conexión si falla
	return false;
}


void Client::disconnect() {
	if (!isConnected) return;  // Si no está conectado, no hace nada

	// Desconectar y liberar recursos
	if (peer) {
		enet_peer_disconnect(peer, 0);
		peer = nullptr;
	}

	running = false;  // Detener el hilo de ejecución
	if (clientThread.joinable()) {
		clientThread.join();  // Esperar a que termine el hilo
	}

	// Destruir el cliente y liberar recursos
	if (client) {
		enet_host_destroy(client);
		client = nullptr;
	}

	isConnected = false;  // Actualizar estado de la conexión
	std::cout << "Disconnected from server!" << std::endl;
}



std::string Client::createRoom(const std::string& username) {
	if (!peer) {
		std::cerr << "Client is not connected to a server!" << std::endl;
		return ""; // Retornar una cadena vacía en caso de error
	}

	// Generar el código de la sala
	std::string roomCode = generateRoomCode();
	std::cout << "Room created with code: " << roomCode << std::endl;

	// Establecer el índice del jugador como 0 (creador)
	playerIndex = 0;

	// Crear el mensaje para el paquete
	std::string message = "CREATE_ROOM:" + roomCode + ":" + username + ":";


	// Crear y enviar el paquete ENet
	ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);

	// Asegurar que el paquete se envíe inmediatamente
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

	// Asegurar que el paquete se envíe inmediatamente
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

	// Asegurar que el paquete se envíe inmediatamente
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

// Nueva función para solicitar tirada de dados
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

	std::string message = "OPCION_CAMINO:" + std::to_string(opcionCami);
	ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	enet_host_flush(client);

}

void Client::endTurn() {
	if (!peer) {
		std::cerr << "Client is not connected to a server!" << std::endl;
	}
	std::cout << "\nTurno de " << IndexTurn << "finalizo";
	std::string message = "END_TURN";
	ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	enet_host_flush(client);

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

	//std::cout << "Spin initiated!" << std::endl;
}

void Client::ruleteGame(float angulo) {
	if (!peer) {
		std::cerr << "Client is not connected to a server!" << std::endl;
		return;
	}

	std::string message = "RULETE_GAME:" + std::to_string(angulo);
	ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	enet_host_flush(client);


	std::cout << "Spin initiated!" << std::endl;
	enet_packet_destroy(packet);
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



void Client::moneyActu(int money) {


	std::string message = "MONEY_ACTU:" + std::to_string(money);

	ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);	
	enet_host_flush(client);


}


// Manejar mensajes recibidos del servidor
void Client::handleServerMessage(const std::string& message) {


	std::cout << "Mensaje recibido: " << message << std::endl;

	std::cout << "\n mensage:" << message;

	

	if (message.rfind("YOUR_TURN", 0) == 0) {
		std::cout << "It's your turn!" << std::endl;
		// Aquí el jugador puede decidir llamar a `rollDice`
		conteoturn += 1;
		std::cout << "\n\nTurno numero:" << conteoturn;
		size_t moneyPos = message.find(":MONEYSALARIO:");
		if (moneyPos != std::string::npos) {
			// Extraer el valor de dinero después de ":MONEYSALARIO:"
			size_t moneyStart = moneyPos + 14; // 13 es la longitud de ":MONEYSALARIO:"
			std::string moneyStr = message.substr(moneyStart);
			std::cout << "\n\nel dinero en teoria es este:" <<moneyStr;
			int playerMoney = std::stoi(moneyStr);  // Convertirlo a entero
			std::cout << "Player's current money: " << playerMoney << std::endl;  // Depuración
			playerInfos[0].money = playerMoney;
			playersGame[0].Money.setString(std::to_string(playerInfos[0].money));

			// Aquí puedes usar la variable playerMoney según sea necesario
		}
		else {
			std::cout << "No salary information found in the message." << std::endl;
			// Puedes manejar este caso si no hay dinero, por ejemplo, asignando un valor predeterminado o no haciendo nada
		}


		if(turnopermitido==0){
			turn_dado = true;
			turn = true;
			eventoActivo = false;
			turn_ruleta = true;
			turn_casa = true;
			turn_impuesto = true;
			turn_Moviendo = true;
			IndexTurn = 0;
		}
		else {

			turnopermitido++;
			endTurn();
		}
		std::cout << "It's your turn!2" << std::endl;
	}
	else 	if (message.rfind("TURN_START", 0) == 0) {
		std::cout << "\nReceived message: " << message << std::endl;  // Depuración

		eventoActivo = false;
		turn_ruleta = true;
		turn_casa = true;
		turn_impuesto = true;
		// Buscar el inicio de "PLAYER_INDEX:" y extraer el valor numérico después
		size_t indexPos = message.find("PLAYER_INDEX:");  // Encontrar el índice donde empieza "PLAYER_INDEX:"
		if (indexPos != std::string::npos) {
			// Extraer la parte después de "PLAYER_INDEX:"
			std::string playerIndexStr = message.substr(indexPos + 13); // 13 es la longitud de "PLAYER_INDEX:"

			std::cout << "Extracted player index string: " << playerIndexStr << std::endl;  // Depuración

			// Convertir la cadena extraída a entero
			int playerIndexTurn = std::stoi(playerIndexStr);

			std::cout << "Converted player index: " << playerIndexTurn << std::endl;  // Depuración

			// Ajustar el turno
			playerIndexTurn = (playerIndexTurn - playerIndex + 4) % 4;

			IndexTurn = playerIndexTurn;
			std::cout << "Turn has started for player: " << playerIndexTurn << std::endl;

			std::cout << "le toca a: " << playerIndexStr << std::endl;  // Depuración



			size_t moneyPos = message.find(":MONEYSALARIO:");
			if (moneyPos != std::string::npos) {
				size_t moneyStart = moneyPos + 13;
				std::string moneyStr = message.substr(moneyStart);
				int playerMoney = std::stoi(moneyStr);
				std::cout << "Player's current money: " << playerMoney << std::endl;  // Depuración
				playerInfos[playerIndexTurn].money = playerMoney;
				playersGame[playerIndexTurn].Money.setString(std::to_string(playerInfos[playerIndexTurn].money));

				// Aquí puedes usar la variable playerMoney según sea necesario
			}
			else {
				std::cout << "No salary information found in TURN_START message." << std::endl;
			}

		}
		else {
			std::cout << "Invalid message format for TURN_START." << std::endl;
		}
	}



	else if (message.rfind("ROLL_RESULT:", 0) == 0) {
		std::cout << "\nEjecución de ROLL_RESULT";

		size_t playerIndexPos = message.find(":PLAYER_INDEX:") + std::string(":PLAYER_INDEX:").length();
		size_t dicePos = message.find(":DICE:", playerIndexPos);

		if (playerIndexPos != std::string::npos && dicePos != std::string::npos) {
			int currentPlayerIndex = std::stoi(message.substr(playerIndexPos, dicePos - playerIndexPos));
			int diceRoll = std::stoi(message.substr(dicePos + std::string(":DICE:").length()));

			currentPlayerIndex = (currentPlayerIndex - playerIndex + 4) % 4;
			lastRollResult = diceRoll; // Asigna el resultado del dado aquí
			IndexTurn = currentPlayerIndex;
			if (turn) {
				std::cout << "resultado " << lastRollResult << " de :" << IndexTurn << std::endl;  // Depuración

				{
					std::lock_guard<std::mutex> lock(mtx);
					espera = true; // Cambia espera a true
				}

				cv.notify_one(); // Notifica al hilo principal para continuar
			}
			else {
				std::cout << "resultado " << lastRollResult<<" de :"<< IndexTurn << std::endl;  // Depuración


				{
					std::lock_guard<std::mutex> lock(mtx);
					rolldiceJugador = true; // Cambia rolldiceJugador a true
				}

				cv.notify_one(); // Notifica al hilo principal para continuar


				std::cout << "resultado finalizo"<< std::endl;  // Depuración

			}

			std::cout << "\nResultado en clase cliente:" << lastRollResult;
			std::cout << "\nDice roll result: " << diceRoll << " para jugador con índice: " << currentPlayerIndex << std::endl;
		}
		else {
			std::cerr << "Formato del mensaje ROLL_RESULT incorrecto" << std::endl;
		}
	}

	else if (message == "NOT_YOUR_TURN") {

		std::cout << "Wait for your turn!" << std::endl;

	}

	else if (message.rfind("OPCION_CAMINO:", 0) == 0) {
		// Encuentra el primer ":" para asegurarse de que haya algo después
		size_t pos = message.find(":");
		if (pos != std::string::npos && pos + 1 < message.size()) {
			// Extrae la parte numérica del mensaje
			std::string opcionCami = message.substr(pos + 1);

			// Puedes convertir opcionCami a un número si es necesario
			try {
				int opcion = std::stoi(opcionCami);  // Convierte el string a int
				std::cout << "Opción recibida: " << opcion << std::endl;


				Opcioncami = opcion;





			}
			catch (const std::invalid_argument& e) {
				std::cerr << "Error al convertir la opción: " << e.what() << std::endl;
			}
			catch (const std::out_of_range& e) {
				std::cerr << "Número fuera de rango: " << e.what() << std::endl;
			}
		}
		else {
			std::cerr << "Mensaje mal formado: falta valor después de los dos puntos." << std::endl;
		}
	}
	else if (message.rfind("RULETE_GAME:", 0) == 0) {
		// Extraer el ángulo de la cadena, después de "RULETE_GAME:"
		float angulo = std::stof(message.substr(12));  // Convertir la parte del ángulo en float
	
		std::cout << "\n Llegooooooooooooooooooooooooooooooooooooooo";
		{
			std::lock_guard<std::mutex> lock(ruletaMutex);
			anguloActualrule = angulo;
			ruletaMessageReceived = true;
		}

		// Notificar al hilo principal que el mensaje ha sido recibido
		ruletaCondVar.notify_one();

	}else if (message.rfind("START_SPIN", 0) == 0) {
		// Dividir el mensaje en partes
		std::cout << "aaaaaaaaayyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy";
		std::istringstream stream(message);
		std::string segment;
		std::vector<std::string> parts;

		while (std::getline(stream, segment, ':')) {
			parts.push_back(segment);
		}

		// Validar si tiene suficientes partes
		if (parts.size() == 5 && parts[0] == "START_SPIN") {
			try {
				// Extraer los valores
				float initialSpeed = std::stof(parts[2]); // Valor después de "initialSpeed"
				float decelerationRate = std::stof(parts[4]); // Valor después de "decelerationRate"


				initialSpeedActi = initialSpeed;
				decelerationRateActi = decelerationRate;


				// Utilizar los valores como sea necesario
				std::cout << "Initial Speed: " << initialSpeed << std::endl;
				std::cout << "Deceleration Rate: " << decelerationRate << std::endl;
				giroActivo = true;
				// Aquí puedes actualizar la lógica del juego con estos valores
				// Por ejemplo: iniciar la animación de la ruleta con initialSpeed y decelerationRate
			}
			catch (const std::exception& e) {
				std::cerr << "Error al procesar el mensaje START_SPIN: " << e.what() << std::endl;
			}
		}
		else {
			std::cerr << "Mensaje START_SPIN mal formateado: " << message << std::endl;
		}

	}
	else if (message.rfind("PLAYER_INDEX:", 0) == 0) {

		std::cout << "\nEJEcuto playerindex1";
		// Extraer el índice del jugador
		std::string indexStr = message.substr(std::string("PLAYER_INDEX:").length());
		playerIndex = std::stoi(indexStr);


		// Aquí puedes realizar la lógica que necesites con el índice del jugador
		std::cout << "Tu índice de jugador es: " << playerIndex << std::endl;
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
			// Todos los valores se han leído correctamente
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


		try {
			index = std::stoi(indexStr);
			money = std::stoi(moneyStr);
			isSelecting = (isSelectingStr == "true");
			isInGame = (isInGameStr == "true");
		}
		catch (const std::invalid_argument&) {

			return;
		}
		catch (const std::out_of_range&) {

			return;
		}




		if (playerIndex != 0) {

			index = (index - playerIndex + 4) % 4;

		}



		if (index >= 0 && index < playerInfos.size()) {

			playerInfos[index].username = username;
			playerInfos[index].money = money;
			playerInfos[index].isSelectingPiece = isSelecting;
			playerInfos[index].isInGame = isInGame;


			playersGame[index].NamePlayer.setString(playerInfos[index].username);


			std::cout << "Player " << index << ": " << username
				<< " | Money: " << money
				<< " | Is Selecting: " << (isSelecting ? "Yes" : "No")
				<< " | Is In Game: " << (isInGame ? "Yes" : "No")
				<< std::endl;


		}
		else {
			std::cerr << "Error: Index out of bounds for player information." << std::endl;
		}


		std::cout << "\nEJEcuto existen2";
	}
	else if (message.rfind("EXISTING_PLAYER:", 0) == 0) {
		// Elimina el prefijo "EXISTING_PLAYER:"
		std::cout << "\nEXISTING_PLAYER";

		if (message.length() < 16) {

			return;
		}

		std::string data = message.substr(16);

		// para dividir la cadena de datos en partes usando ":" como delimitador :)
		std::istringstream iss(data);
		std::string username, indexStr, moneyStr, isSelectingStr, isInGameStr, imagePath, indexPieceStr;

		if (std::getline(iss, username, ':') &&
			std::getline(iss, indexStr, ':') &&
			std::getline(iss, moneyStr, ':') &&
			std::getline(iss, isSelectingStr, ':') &&
			std::getline(iss, isInGameStr, ':') &&
			std::getline(iss, imagePath, ':') && // Leer hasta el último campo (image)
			std::getline(iss, indexPieceStr)) {


			// Todos los valores se han leído correctamente
		}
		else {
			std::cout << "\nEJEcuto toy remal";

		}

		int index;
		int money;
		bool isSelecting;
		bool isInGame;
		std::string image;
		int indexPiece;
		std::cout << "indexStr: '" << indexStr << "', moneyStr: '" << moneyStr << "'\n";

		try {
			index = std::stoi(indexStr);
			money = std::stoi(moneyStr);
			isSelecting = (isSelectingStr == "true");
			isInGame = (isInGameStr == "true");
			image = imagePath; // Guarda la dirección de la imagen eso uwu
			indexPiece = std::stoi(indexPieceStr);
		}
		catch (const std::invalid_argument&) {

			return;
		}
		catch (const std::out_of_range&) {

			return;
		}
		std::cout << "\nEJEcuto existen3";



		if (playerIndex != 0) {

			index = (index - playerIndex + 4) % 4;

		}

		// Asegurarse de que el índice esté dentro de los límites
		if (index >= 0 && index < playerInfos.size()) {
			std::cout << "\nEJEcuto existen6";
			// Actualizar la información del jugador en la posición correspondiente
			playerInfos[index].username = username;
			playerInfos[index].money = money;
			playerInfos[index].isSelectingPiece = isSelecting;
			playerInfos[index].isInGame = isInGame;
			playerInfos[index].image = image;
			index = (index - playerIndex + 4) % 4;
			CplayerIndex = index;
			playerInfos[index].indexPiece = indexPiece; // Actualizar el índice de la pieza



			if (!playersGame[index].textureAvatarPLayer.loadFromFile(playerInfos[index].image)) {
				std::cerr << "Error loading image!" << std::endl;
			}
			playersGame[index].NamePlayer.setString(playerInfos[index].username);

			// Imprimir la información del jugador
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
		// Extraer el índice y el nombre del archivo
		size_t firstColon = message.find(":", 11); // Buscar el primer ':' después de "SEND_IMAGE:"
		int IIndex = std::stoi(message.substr(11, firstColon - 11)); // Extraer el índice
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
			size_t firstColon = message.find(":", 20);   // Buscar el primer ":" después del prefijo
			size_t secondColon = message.find(":", firstColon + 1); // Buscar el segundo ":" después del primero

			if (firstColon == std::string::npos || secondColon == std::string::npos) {
				std::cerr << "Error: Formato de mensaje inesperado. Faltan delimitadores." << std::endl;
				return;
			}

			// Extraer las subcadenas correspondientes al índice del jugador y al índice de la pieza
			indexStr = message.substr(firstColon + 1, secondColon - firstColon - 1);
			pieceIndexStr = message.substr(secondColon + 1);

			// Mostrar los valores extraídos para depuración
			std::cout << "\nindexStr: '" << indexStr << "', pieceIndexStr: '" << pieceIndexStr << "'";

			// Convertir los valores a enteros
			int Index = std::stoi(indexStr);
			int indexselectinpiece = std::stoi(pieceIndexStr);

			// Ajustar el índice del jugador
			Index = (Index - playerIndex + 4) % 4;
			CplayerIndex = Index;

			// Actualizar la información en el cliente
			std::cout << "Player " << playerIndex << " seleccionó la pieza con índice " << indexselectinpiece << std::endl;
			playerInfos[Index].indexPiece = indexselectinpiece;
			std::cout << "\nEJEcuto index 2";
		}
		catch (const std::invalid_argument&) {

		}
		catch (const std::out_of_range&) {

		}
	}
	else if (message.rfind("PLAYER_READY:", 0) == 0) {
		// Extraer el `indexPlayer` del mensaje
		std::cout << "\n PLAYER READY" << std::endl;
		int indexPlayer = std::stoi(message.substr(13)); // "PLAYER_READY:" tiene 13 caracteres
		indexPlayer = (indexPlayer - playerIndex + 4) % 4;
		playerInfos[indexPlayer].isSelectingPiece = true;

		// Ahora puedes usar `indexPlayer` para actualizar el estado del jugador en el cliente
		std::cout << "Jugador " << indexPlayer << " está listo." << std::endl;

		// Realiza cualquier acción adicional para indicar que este jugador está listo,
		// como actualizar el estado en la interfaz de usuario.
		std::cout << "\n PLAYER fin" << std::endl;
	}
	else if (message.rfind("START_GAME", 0) == 0) {
		// Comprueba si empieza con "START_GAME"
		std::cout << "Mensaje de inicio recibido: " << message << std::endl;

		// Encuentra la posición de "Casas:"
		size_t casasPos = message.find("Casas:");
		if (casasPos != std::string::npos) {
			// Extrae todo después de "Casas:"
			std::string casasData = message.substr(casasPos + 6); // +6 para saltar "Casas:"

			// Convertir los números de cada jugador en vectores separados
			std::istringstream iss(casasData);
			std::string palabra;
			std::vector<std::vector<int>> casasPorJugador;
			std::vector<int> indicesJugadores;



			while (iss >> palabra) {
				if (palabra == "Jugador") {
					// Encontramos un nuevo jugador, inicializamos su vector de casas
					int jugadorIndex;
					iss >> jugadorIndex; // Lee el número del jugador

					indicesJugadores.push_back(jugadorIndex); // Guarda el índice
					iss.ignore(256, ':'); // Ignora hasta el próximo ':'
					casasPorJugador.emplace_back();
					// Encontramos un nuevo jugador

				}
				else {
					// Convertimos los números de casas
					try {
						int casa = std::stoi(palabra);
						casasPorJugador.back().push_back(casa); // Añadimos al último jugador
					}
					catch (...) {
						// Ignoramos los caracteres que no son números (por ejemplo, ";")
					}
				}

			}

			// Mostrar las casas de cada jugador
			// Transferir los datos a PlayerInfo
			// Transferir los datos a PlayerInfo
			
				
				for (size_t i = 0; i < indicesJugadores.size(); ++i) {

					for (int j = 0; j < 17; ++j) {
						playerInfos[i].casasPorJugador[j] = casasPorJugador[i][j];
					}

					// Muestra las casas asignadas
					std::cout << "Jugador " << indicesJugadores[i] << " casas asignadas: ";
					for (int casa : playerInfos[i].casasPorJugador) {
						std::cout << casa << " ";
					}
					std::cout << std::endl;
				} 
				
				{
					std::lock_guard<std::mutex> lock(casasMutex);
					casasCargadas = true; // Actualiza la bandera	
				}
				cv.notify_one(); // Notifica al hilo principal para continuar
		}
		else {
			std::cerr << "Error: no se encontró 'Casas:' en el mensaje." << std::endl;
		}
		}
		else {
			std::cerr << "Unknown message received from server: " << message << std::endl;
		}



		std::cout << "\nfinal mensaje!" << std::endl;
	}//START_GAMECasas: Jugador 0 : 7 12 15 3 0 4 2 11 8 16 1 9 5 14 13 10 6;
