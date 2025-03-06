#include "Client.hpp"
#include "../game/online/ResourceGame.hpp"

Client::Client() : client(nullptr),peer(nullptr), running(false),
lastRollResult(0), turnopermitido(0), conteoturn(0), accionCompra(false),
anguloActualrule(0.f), casasCargadas(false), decelerationRateActi(0.f),
disActiv(false), disconnecte(false), giroActivo(false), initialSpeedActi(0.f),
isConnected(false),playerIndex(-1) {
	std::cout << "\n[DEBUG] Constructor: Dirección de client: " << std::hex << reinterpret_cast<uintptr_t>(client);
}

int Client::calcularNumeroDeLineas(const sf::Text& text) {
	// Obtener el rectángulo delimitador (bounding box) del texto
	sf::FloatRect bounds = text.getGlobalBounds();

	// Dividir la altura del rectángulo entre la altura de la fuente
	// Esto nos da el número de líneas
	float alturaLinea = text.getCharacterSize();  // El tamaño de la fuente
	int numeroDeLineas = static_cast<int>(bounds.height / alturaLinea);

	return numeroDeLineas;
}
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
bool Client::cola_vacia(Nodo* frente) {
	return (frente == NULL) ? true : false;
}
void Client::suprimirCola(Nodo*& frente, Nodo*& fin) {
	std::string n = frente->dato;
	Nodo* aux = frente;
	std::cout << "\n" << n;
	handleServerMessage(n);
	if (frente == fin) {
		frente = NULL;
		fin = NULL;
	}
	else {
		frente = frente->siguiente;
	}
	delete aux;
}
Client::~Client() {
	disconnect();
	if (client) {
		enet_host_destroy(client);
	}
	enet_deinitialize();
}
bool Client::initialize() {
	std::cout << "\n[DEBUG] Dirección de client al inicio de initialize: " << std::hex << reinterpret_cast<uintptr_t>(client);

	//std:: << "\nInicia";
	std::cout << "\nHola";
	static bool enetInitialized = false;
	if (!enetInitialized) {
		std::cout << "\nHola1";
		if (enet_initialize() != 0) {
			std::cerr << "Error initializing ENet!" << std::endl;
			std::cout << "\nHola11";
			return false;
		}
		enetInitialized = true;
		std::cout << "\nHola111";
	}

	// Solo crear cliente si no existe
	std::cout << "\nHola32422222222222";
	std::cout << "\nValor de client antes del if: " << client;
	if (reinterpret_cast<uintptr_t>(client) < 0x1000) {  // Detectar valores raros
		std::cout << "\nClient tiene un valor inesperado, reiniciándolo...";
		client = nullptr;
	}
	if (!client) {
		std::cout << "\nHola324";
		client = enet_host_create(nullptr, 1, 2, 0, 0);
		std::cout << "\nHola3224";
		if (!client) {
			std::cerr << "Error creating ENet client!" << std::endl;
			std::cout << "\nHo2la";
			return false;
		}
	}

	//std:: << "\nInicia0";
	std::cout << "\nHola";
	return true;
}
void Client::insertarCola(Nodo*& frente, Nodo*& fin, std::string n) {
	Nodo* nuevo_nodo = new Nodo();

	nuevo_nodo->dato = n;
	nuevo_nodo->siguiente = NULL;

	if (cola_vacia(frente)) {
		frente = nuevo_nodo;
	}
	else {
		fin->siguiente = nuevo_nodo;
	}

	fin = nuevo_nodo;
}
void Client::run() {
	running = true;
	while (running) {
		ENetEvent event;
		while (enet_host_service(client, &event, 100) > 0) {
			switch (event.type) {
			case ENET_EVENT_TYPE_RECEIVE: {
				std::string message(reinterpret_cast<char*>(event.packet->data), event.packet->dataLength);
				insertarCola(frente, fin, message);
				std::cout << "\nMensaje recibido: " << message << std::endl;
				enet_packet_destroy(event.packet);
				break;
			}
			case ENET_EVENT_TYPE_DISCONNECT:
				//      //std::cout << "Disconnected from server!" << std::endl;
				running = false;
				break;
			default:
				break;
			}
		}
	}
}
void Client::process() {
	running = true;
	while (running) {
		if (frente != NULL) {
			suprimirCola(frente, fin);
		}

	}
}
bool Client::connectToServer(const std::string& address, uint16_t port) {

	if (!client) {
		std::cerr << "Client not initialized!" << std::endl;
		return false;
	}

	// Configurar dirección
	ENetAddress enetAddress;
	enet_address_set_host(&enetAddress, address.c_str());
	enetAddress.port = port;

	// Intentar conexión
	peer = enet_host_connect(client, &enetAddress, 2, 0);
	if (!peer) {
		std::cerr << "No available peers for initiating an ENet connection!" << std::endl;
		return false;
	}

	// Esperar respuesta del servidor
	ENetEvent event;
	const int maxRetries = 50;
	const int retryDelay = 50;
	for (int i = 0; i < maxRetries; ++i) {
		if (enet_host_service(client, &event, retryDelay) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
			////std::cout << "Connected to server!" << std::endl;
			isConnected = true;
			clientThread = std::thread(&Client::run, this);
			clientMensThread = std::thread(&Client::process, this);
			networkMessage.Enetpeer(peer);
			return true;
		}
	}

	std::cerr << "Failed to connect to server after " << maxRetries << " retries." << std::endl;
	enet_peer_reset(peer);
	return false;
}
void Client::disconnect() {
	if (!isConnected) return;  // Si no está conectado, no hace nada


	std::string message = "DISCONNNECT";
	ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	enet_host_flush(client);

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

	if (clientMensThread.joinable()) {
		clientMensThread.join();
	}

	isConnected = false;  // Actualizar estado de la conexión
	//	//std::cout << "Disconnected from server!" << std::endl;
}
std::string Client::createRoom(const std::string& username,const std::string& filename) {
	if (!peer) {
		std::cerr << "Client is not connected to a server!" << std::endl;
		return ""; // Retornar una cadena vacía en caso de error
	}

	// Generar el código de la sala
	std::string roomCode = generateRoomCode();
	////std::cout << "Room created with code: " << roomCode << std::endl;

	// Establecer el índice del jugador como 0 (creador)
	playerIndex = 0;

	// Crear el mensaje para el paquete
	std::string message = "CREATE_ROOM:" + roomCode + ":" + username + ":"+ filename;


	// Crear y enviar el paquete ENet
	ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	PlayerInfo playerInfoNew;
	PlayerGame playerGameNew;
	playerInfoNew.username = nameUser;
	playerInfoNew.PiecUserme = true;
	playerInfos.push_back(playerInfoNew);
	std::cout << "\n" << playerInfos[0].username;

	playerGameNew.CashSprite.setTexture(TextureCash);
	playerGameNew.Home.setTexture(TextureHome);
	playerGameNew.NamePlayer.setCharacterSize(17);
	playerGameNew.NamePlayer.setFont(fontUserPerfil);
	playerGameNew.NamePlayer.setFillColor(sf::Color::White);
	playerGameNew.NamePlayer.setOutlineThickness(2);
	playerGameNew.NamePlayer.setOutlineColor(sf::Color(135, 135, 135));
	playerGameNew.NamePlayer.setString(playerInfos[0].username);

	globalBounds = playerGameNew.NamePlayer.getGlobalBounds();


	playerGameNew.NamePlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
	playerGameNew.boxPlayer.setTexture(textureBoxPerfil);
	playerGameNew.boxPlayer.setOrigin(125, 40);
	playerGameNew.boxPlayer.setScale(0.9f, 0.9f);
	playerGameNew.Check.setTexture(CheckTexturesOff);
	playerGameNew.Check.setOrigin(50.0f, 46.5f);
	playersGame.push_back(playerGameNew);
	UsuariosActivos.push_back(0);



	// Asegurar que el paquete se envíe inmediatamente
	enet_host_flush(client);

	return roomCode;
}
bool Client::joinRoom(const std::string& roomCode, const std::string& username, const std::string& filename) {
	if (!peer) {
		return false;
	}

	std::string message = "JOIN_ROOM:" + roomCode + ":" + username + ":"+ filename;

	ENetPacket* packet = enet_packet_create(message.c_str(), message.size(), ENET_PACKET_FLAG_RELIABLE);
	if (!packet) {
		return false;
	}

	if (enet_peer_send(peer, 0, packet) < 0) {
		return false;
	}

	enet_host_flush(client);

	return true;
}
void Client::moneyActu(int money) {
	std::string message = "MONEY_ACTU:" + std::to_string(money);

	ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	enet_host_flush(client);


}
void Client::llegadaFinal() {
	if (!peer) {
		std::cerr << "Client is not connected to a server!" << std::endl;
	}

	std::string message = "LLEGUEFINAL";
	ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	enet_host_flush(client);


}
void Client::MONEYSALARIO(std::string message, int usuario) {
	size_t moneyPos = message.find(":MONEYSALARIO:");
	if (moneyPos != std::string::npos) {
		size_t moneyStart = moneyPos + 14;
		std::string moneyStr = message.substr(moneyStart);
		int playerMoney = std::stoi(moneyStr);
		playerInfos[usuario].money = playerMoney;
		playersGame[usuario].Money.setString(std::to_string(playerInfos[usuario].money));

	}
}
void Client::handleServerMessage(const std::string& message) {
	std::cout << "\nMensaje recibido procesando: " << message << std::endl;

	if (message.rfind("YOUR_TURN", 0) == 0) {

		MONEYSALARIO(message, playerIndex);

		if (playerInfos[UsuariosActivos[0]].final) {

			networkMessage.endTurn();
			return;
		}

		conteoturn += 1;
		conteosuel += 1;

		if (turnopermitido != 0) {
			nular = false;
			return;
		}

		turn_dado = true;
		turn = true;
		eventoActivo = false;
		turn_ruleta = true;
		turn_casa = true;
		turn_impuesto = true;
		turn_Moviendo = true;
		IndexTurn = playerIndex;
		otherturn = false;
	}
	else if (message.rfind("TURN_START", 0) == 0) {

		otherturn = true;
		eventoActivo = false;
		turn_ruleta = true;
		turn_casa = true;
		turn_impuesto = true;
		turn_Moviendo = true;

		size_t indexPos = message.find("PLAYER_INDEX:");
		if (indexPos != std::string::npos) {

			std::string playerIndexStr = message.substr(indexPos + 13);
			int playerIndexTurn = std::stoi(playerIndexStr);
			IndexTurn = playerIndexTurn;

			MONEYSALARIO(message, playerIndexTurn);

		}

	}
	else if (message.rfind("ROLL_RESULT:", 0) == 0) {

		size_t playerIndexPos = message.find(":PLAYER_INDEX:") + std::string(":PLAYER_INDEX:").length();
		size_t dicePos = message.find(":DICE:", playerIndexPos);

		if (playerIndexPos != std::string::npos && dicePos != std::string::npos) {
			int currentPlayerIndex = std::stoi(message.substr(playerIndexPos, dicePos - playerIndexPos));
			int diceRoll = std::stoi(message.substr(dicePos + std::string(":DICE:").length()));

		//	currentPlayerIndex = (currentPlayerIndex - playerIndex + 4) % 4;
			lastRollResult = diceRoll;
			IndexTurn = currentPlayerIndex;
			if (turn) {

				{
					std::lock_guard<std::mutex> lock(mtx);
					espera = true;
				}

				cv.notify_one();
			}
			else {

				{
					std::lock_guard<std::mutex> lock(mtx);
					rolldiceJugador = true;
				}

				cv.notify_one();

			}

		}

	}
	else if (message.rfind("OPCION_CAMINO:", 0) == 0) {

		size_t pos = message.find(":");
		if (pos != std::string::npos && pos + 1 < message.size()) {
			int opcion = std::stoi(message.substr(pos + 1));
			Opcioncami = opcion;
		}

	}
	else if (message.find("COMPRADA:") == 0) {
		std::string data = message.substr(9);
		size_t delimiterPos = data.find(':');
		if (delimiterPos != std::string::npos) {
			int indexPlayerr = std::stoi(data.substr(0, delimiterPos));
		//	indexPlayerr = (indexPlayerr - playerIndex + 4) % 4;
			int moneyy = std::stoi(data.substr(delimiterPos + 1));
			playerInfos[indexPlayerr].money = moneyy;
			playersGame[indexPlayerr].Money.setString(std::to_string(playerInfos[indexPlayerr].money));
			accionCompra = true;
		}
	}
	else if (message.rfind("RULETE_GAME:", 0) == 0) {
		float angulo = std::stof(message.substr(12));

		{
			std::lock_guard<std::mutex> lock(ruletaMutex);
			anguloActualrule = angulo;
			ruletaMessageReceived = true;
		}

		ruletaCondVar.notify_one();

	}
	else if (message.rfind("START_SPIN", 0) == 0) {
		std::istringstream stream(message);
		std::string segment;
		std::vector<std::string> parts;

		while (std::getline(stream, segment, ':')) {
			parts.push_back(segment);
		}

		if (parts.size() == 5 && parts[0] == "START_SPIN") {

			initialSpeedActi = std::stof(parts[2]);
			decelerationRateActi = std::stof(parts[4]);
			giroActivo = true;

		}

	}
	else if (message.rfind("GANAR150:", 0) == 0) {
		size_t firstColon = message.find(':');
		size_t secondColon = message.find(':', firstColon + 1);

		if (firstColon != std::string::npos && secondColon != std::string::npos) {

			int indexjugador = std::stoi(message.substr(firstColon + 1, secondColon - firstColon - 1));
			//if (playerIndex != 0) {
			//	indexjugador = (indexjugador - playerIndex + 4) % 4;
			//}

			playerInfos[indexjugador].money = std::stoi(message.substr(secondColon + 1));
			playersGame[indexjugador].Money.setString(std::to_string(playerInfos[indexjugador].money));

		}

	}
	else if (message.rfind("INVERCIONSEGURA", 0) == 0) {
		
		std::string data = message.substr(15 + 1);
		std::cout << "\n entra en inversion:"<<data;
		std::istringstream iss(data);
		std::string  indexStr, moneyStr;
		std::cout << "\n entra en inversion";
		if (!(std::getline(iss, indexStr, ':') &&
			std::getline(iss, moneyStr, ':'))
			) {
			return;
		}
		std::cout << "\nindexStr:" << indexStr << " moneyStr:" << moneyStr<<".:.";
		int indext = std::stoi(indexStr);
		playerInfos[indext].money = std::stoi(moneyStr);

		playersGame[indext].Money.setString(std::to_string(playerInfos[indext].money));

	}
	else if (message.rfind("TODOSPIERDEN:", 0) == 0) {
		std::string data = message.substr(13);

		std::vector<std::string> tokens;
		size_t start = 0;
		size_t end = data.find(':');
		while (end != std::string::npos) {
			tokens.push_back(data.substr(start, end - start));
			start = end + 1;
			end = data.find(':', start);
		}

		for (size_t i = 0; i < tokens.size(); i += 2) {
			if (i + 1 < tokens.size()) { // Asegurarse de que hay un par índice/dinero
				int indexjugador = std::stoi(tokens[i]);
				int moneyAmount = std::stoi(tokens[i + 1]);

			
				playerInfos[indexjugador].money = moneyAmount;
				playersGame[indexjugador].Money.setString(std::to_string(playerInfos[indexjugador].money));

			}
		}
	}
	else if (message.rfind("PLAYER_INDEX:", 0) == 0) {

			playerIndex = std::stoi(message.substr(std::string("PLAYER_INDEX:").length()));
			agregardor = true;

		PlayerInfo playerInfoNew;
		PlayerGame playerGameNew;
		playerInfoNew.username = nameUser;
		playerInfoNew.PiecUserme = true;
		playerGameNew.NamePlayer.setCharacterSize(17);
		playerGameNew.NamePlayer.setFont(fontUserPerfil);
		playerGameNew.NamePlayer.setFillColor(sf::Color::White);
		playerGameNew.NamePlayer.setOutlineThickness(2);
		playerGameNew.NamePlayer.setOutlineColor(sf::Color(135, 135, 135));
		playerGameNew.NamePlayer.setString(playerInfoNew.username);
		playerGameNew.CashSprite.setTexture(TextureCash);
		playerGameNew.Home.setTexture(TextureHome);
		globalBounds = playerGameNew.NamePlayer.getGlobalBounds();
		playerGameNew.NamePlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
		playerGameNew.Check.setTexture(CheckTexturesOff);
		playerGameNew.Check.setOrigin(50.0f, 46.5f);
		playerGameNew.boxPlayer.setTexture(textureBoxPerfil);
		playerGameNew.boxPlayer.setOrigin(125, 40);
		playerGameNew.boxPlayer.setScale(0.9f, 0.9f);
		playersGame.push_back(playerGameNew);
		playerInfos.push_back(playerInfoNew);
		UsuariosActivos.insert(UsuariosActivos.begin(), playerIndex);

		std::cout << "\nPLAYER_INDEX "<< playerIndex <<" UsuariosActivos:" << UsuariosActivos.size();

	}
	else if (message.rfind("NEW_PLAYER:", 0) == 0) {

		std::istringstream iss(message.substr(11));
		std::string username, indexStr, moneyStr, isSelectingStr, isInGameStr,isimageStr;

		if (!(std::getline(iss, username, ':') &&
			std::getline(iss, indexStr, ':') &&
			std::getline(iss, moneyStr, ':') &&
			std::getline(iss, isSelectingStr, ':') &&
			std::getline(iss, isInGameStr, ':') &&
			std::getline(iss, isimageStr, ':')
			)
			) {

			return;

		}

		int index = std::stoi(indexStr);
		PlayerInfo playerInfoNew;
		PlayerGame playerGameNew;
		

		playerInfoNew.image = isimageStr;
		playerGameNew.NamePlayer.setCharacterSize(17);
		playerGameNew.NamePlayer.setFont(fontUserPerfil);
		playerGameNew.NamePlayer.setFillColor(sf::Color::White);
		playerGameNew.NamePlayer.setOutlineThickness(2);
		playerGameNew.NamePlayer.setOutlineColor(sf::Color(135, 135, 135));
		playerInfoNew.username = username;
		playerGameNew.CashSprite.setTexture(TextureCash);
		playerGameNew.Home.setTexture(TextureHome);
		playerInfoNew.money = std::stoi(moneyStr);
		playerInfoNew.isSelectingPiece = (isSelectingStr == "true");
		playerInfoNew.isInGame = (isInGameStr == "true");
		playerGameNew.textureAvatarPLayer.loadFromFile(playerInfoNew.image);
		playerGameNew.NamePlayer.setString(playerInfoNew.username);
		globalBounds = playerGameNew.NamePlayer.getGlobalBounds();
		playerGameNew.NamePlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
		playerGameNew.Check.setTexture(CheckTexturesOff);
		playerGameNew.Check.setOrigin(50.0f, 46.5f);
		playerGameNew.boxPlayer.setTexture(textureBoxPerfil);
		playerGameNew.boxPlayer.setOrigin(125, 40);
		playerGameNew.boxPlayer.setScale(0.9f, 0.9f);
		playersGame.push_back(playerGameNew);
		playerInfos.push_back(playerInfoNew);
		UsuariosActivos.push_back(index);

		std::cout << "\n NEW_PLAYER " << index << " UsuariosActivos:" << UsuariosActivos.size();
	}
	else if (message.rfind("EXISTING_PLAYER:", 0) == 0) {

		std::string data = message.substr(16);
		std::istringstream iss(data);
		std::string username, indexStr, moneyStr, isSelectingStr, isInGameStr, imagePath, indexPieceStr;

		if (!(std::getline(iss, username, ':') &&
			  std::getline(iss, indexStr, ':') &&
			  std::getline(iss, moneyStr, ':') &&
			  std::getline(iss, isSelectingStr, ':') &&
			  std::getline(iss, isInGameStr, ':') &&
			  std::getline(iss, imagePath, ':') && 
			  std::getline(iss, indexPieceStr))
			){
			return;
		}

		int index = std::stoi(indexStr);

		std::unique_lock<std::mutex> lock(mtxExisting);
		PlayerInfo playerInfoNew;
		PlayerGame playerGameNew;
		playerGameNew.NamePlayer.setCharacterSize(17);
		playerGameNew.NamePlayer.setFont(fontUserPerfil);
		playerGameNew.NamePlayer.setFillColor(sf::Color::White);
		playerGameNew.NamePlayer.setOutlineThickness(2);
		playerGameNew.NamePlayer.setOutlineColor(sf::Color(135, 135, 135));
		playerInfoNew.username = username;
		playerInfoNew.money = std::stoi(moneyStr);
		playerInfoNew.isSelectingPiece = (isSelectingStr == "true");
		playerInfoNew.isInGame = (isInGameStr == "true");
		playerInfoNew.image = imagePath;
		int indexPiece = std::stoi(indexPieceStr);
		playerGameNew.CashSprite.setTexture(TextureCash);
		playerGameNew.Home.setTexture(TextureHome);
		playerGameNew.Check.setTexture(CheckTexturesOff);
		playerGameNew.Check.setOrigin(50.0f, 46.5f);
		playerGameNew.textureAvatarPLayer.loadFromFile(playerInfoNew.image);
		playerGameNew.NamePlayer.setString(playerInfoNew.username);
		globalBounds = playerGameNew.NamePlayer.getGlobalBounds();
		playerGameNew.NamePlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
		playerGameNew.boxPlayer.setTexture(textureBoxPerfil);
		playerGameNew.boxPlayer.setOrigin(125, 40);
		playerGameNew.boxPlayer.setScale(0.9f, 0.9f);
		playerInfos.push_back(playerInfoNew);
		playersGame.push_back(playerGameNew);
		UsuariosActivos.push_back(index);

		if (indexPiece >= 0) {
			
			std::cout << "\n pieza:" << indexPiece << " CplayerIndex:" << CplayerIndex;
			playerInfos[index].indexPiece = indexPiece;
			int newPieceIndex = playerInfos[index].indexPiece;

			pieces[previousSelectionIndex[index]].setColor(sf::Color::White); // Color original
			pieces[newPieceIndex].setColor(sf::Color(248, 134, 255)); // Resaltar la nueva pieza
			std::cout << "\nplayersGame" << playersGame.size();
			// Actualizar el sprite del jugador con la nueva textura de la pieza seleccionada
			playersGame[index].PieceSelect.setTexture(piecesTextures[newPieceIndex], true);
			playersGame[index].PieceSelect.setScale(pieces[newPieceIndex].getScale());
			playersGame[index].PieceSelect.setOrigin(pieces[newPieceIndex].getOrigin());
			playersGame[index].PieceSelect.setColor(sf::Color::White); // Asegurar el color correcto
			previousSelectionIndex[index] = newPieceIndex;
			CplayerIndex = -1;

	
		}


	}
	else if (message.rfind("PLAYER_COUNT:", 0) == 0) {

		NumPlayers = std::stoi(message.substr(13));

	}
	else if (message.rfind("XCASA:", 0) == 0) {

		accionCompra = true;

	}
	else if (message.rfind("SMG", 0) == 0) {
	
		int num = message[3] - '0';  // Convertir el 4to carácter a int
		std::string rest = message.substr(4);  // Obtener el resto del string
		PlantillaMensajeR.SMSEnviado.setString(rest);

		int In = calcularNumeroDeLineas(PlantillaMensajeR.SMSEnviado) + 1;

		if (In == 1) {
			sf::FloatRect altura = PlantillaMensajeR.SMSEnviado.getGlobalBounds();

			PlantillaMensajeR.ContenidoEnviado.setSize(sf::Vector2f(altura.width + 20, 40));
			PlantillaMensajeR.ContenidoEnviado.setPosition(970, 600);
			PlantillaMensajeR.SMSEnviado.setPosition(970 + 10, 618);
			PlantillaMensajeR.AvatarEnviado.setPosition(920, 600);
			PlantillaMensajeR.positionContenidoEnviado = PlantillaMensajeR.ContenidoEnviado.getPosition();;
			PlantillaMensajeR.positionSMSEnviado = PlantillaMensajeR.SMSEnviado.getPosition();
			PlantillaMensajeR.positionAvatarEnviado = PlantillaMensajeR.AvatarEnviado.getPosition();

		}

		else if (In > 1) {

			sf::FloatRect altura = PlantillaMensajeR.SMSEnviado.getGlobalBounds();
			PlantillaMensajeR.AvatarEnviado.setPosition(920, 600);
			PlantillaMensajeR.ContenidoEnviado.setSize(sf::Vector2f(altura.width + 20, altura.height + 22));
			PlantillaMensajeR.ContenidoEnviado.setPosition(sf::Vector2f(970, 640 - PlantillaMensajeR.ContenidoEnviado.getGlobalBounds().height));
			PlantillaMensajeR.SMSEnviado.setPosition(sf::Vector2f(970 + 10, PlantillaMensajeR.ContenidoEnviado.getPosition().y + 18));
			PlantillaMensajeR.positionContenidoEnviado = PlantillaMensajeR.ContenidoEnviado.getPosition();
			PlantillaMensajeR.positionSMSEnviado = PlantillaMensajeR.SMSEnviado.getPosition();
			PlantillaMensajeR.positionAvatarEnviado = PlantillaMensajeR.AvatarEnviado.getPosition();
		}

		PlantillaMensajeR.positionContenidoEnviado = PlantillaMensajeR.ContenidoEnviado.getPosition();
		PlantillaMensajeR.positionSMSEnviado = PlantillaMensajeR.SMSEnviado.getPosition();

		Mensajes.push_back(PlantillaMensajeR);
		float aux = PlantillaMensajeR.ContenidoEnviado.getGlobalBounds().height;

		 aux += 20;

		for (int i = 0; i < Mensajes.size() - 1; i++)
		{
			Mensajes[i].ContenidoEnviado.setPosition(Mensajes[i].ContenidoEnviado.getPosition().x, Mensajes[i].ContenidoEnviado.getPosition().y - aux);
			Mensajes[i].AvatarEnviado.setPosition(Mensajes[i].AvatarEnviado.getPosition().x, Mensajes[i].AvatarEnviado.getPosition().y - aux);
			Mensajes[i].SMSEnviado.setPosition(Mensajes[i].ContenidoEnviado.getPosition().x + 10, Mensajes[i].ContenidoEnviado.getPosition().y + 20);
			Mensajes[i].positionContenidoEnviado = Mensajes[i].ContenidoEnviado.getPosition();
			Mensajes[i].positionSMSEnviado = Mensajes[i].SMSEnviado.getPosition();
			Mensajes[i].positionAvatarEnviado = Mensajes[i].AvatarEnviado.getPosition();

		

		}
		std::cout << "uuuuu: " << Mensajes.size();
	}
	else if (message.rfind("PLAYER_CHANGED_PIECE:", 0) == 0) {

	 	size_t firstColon = message.find(":", 20);   
		size_t secondColon = message.find(":", firstColon + 1); 

		int Index = std::stoi(message.substr(firstColon + 1, secondColon - firstColon - 1));
		playerInfos[Index].indexPiece = std::stoi(message.substr(secondColon + 1));
		CplayerIndex = Index;
		

	}
	else if (message.rfind("PLAYER_READY:", 0) == 0) {

		int indexPlayer = std::stoi(message.substr(13));

		playerInfos[indexPlayer].isSelectingPiece = true;

	}
	else if (message.rfind("START_GAME", 0) == 0) {

		size_t casasPos = message.find("Casas:");
		if (casasPos != std::string::npos) {
			
			std::string casasData = message.substr(casasPos + 6); 

			std::istringstream iss(casasData);
			std::string palabra;
			std::vector<std::vector<int>> casasPorJugador;
			std::vector<int> indicesJugadores;

			while (iss >> palabra){
				if (palabra == "Jugador") {
					
					int jugadorIndex;
					iss >> jugadorIndex;
					indicesJugadores.push_back(jugadorIndex); 
					iss.ignore(256, ':');
					casasPorJugador.emplace_back();

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

			for (size_t i = 0; i < indicesJugadores.size(); ++i) {

				for (int j = 0; j < 17; ++j) {
					playerInfos[i].casasPorJugador[j] = casasPorJugador[i][j];
				}

			}

			{
				std::lock_guard<std::mutex> lock(casasMutex);
				casasCargadas = true; 	
			}
			cv.notify_one(); 

		}

	}
	else if (message.rfind("ROBARPLAYER:", 0) == 0) {

		std::string datos = message.substr(11);
		std::stringstream ss(datos);
		std::string token;

		std::vector<std::pair<int, int>> jugadores;

		while (std::getline(ss, token, ':')) {

			int indice = std::stoi(token); 
			if (std::getline(ss, token, ':')) {
				int dinero = std::stoi(token); 

				playerInfos[indice].money = dinero;
				playersGame[indice].Money.setString(std::to_string(playerInfos[indice].money));

			}
		}
	}
	else if (message.rfind("EVENTOCASA", 0) == 0) {
		userCasa = true;
	}
	else if (message.rfind("EVENTOIMPUEST", 0) == 0) {
		
		std::string data = message.substr(15);
		std::istringstream iss(data);
		std::string impuesto, indexStr, moneyStr;

		if (!(std::getline(iss, impuesto, ':') &&
			std::getline(iss, indexStr, ':') &&
			std::getline(iss, moneyStr, ':'))
			) {
			return;
		}
		std::cout << "\nImpuesto:" << impuesto << ":indexStr:" << indexStr << " moneyStr:" << moneyStr;
		int indext = std::stoi(indexStr);
		playerInfos[indext].money = std::stoi(moneyStr);
		playerInfos[indext].impuesto = std::stoi(impuesto);

		playersGame[indext].Money.setString(std::to_string(playerInfos[indext].money));
		{
			std::lock_guard<std::mutex> lock(impuestoMutex);
			if(IndexTurn!= playerIndex){
				userImpuesto = true;
		
			}
			impuestoMessageReceived = true;
		}

		impuestoCondVar.notify_one();
        
	}
	else if (message.rfind("EVENTORULETA", 0) == 0) {

		userRuleta = true;

	}
	else if (message.rfind("JUEGOTERMINADO", 0) == 0) {

		juegoTerminado =  true;

	}
	else if(message.rfind("PLAYER_DISCONNECTED", 0) == 0) {

		disconnecte = true;

		while (!disActiv) {
		}

		{
			std::lock_guard<std::mutex> lock(mtex);
			int index = std::stoi(message.substr(20));

			if (playerIndex == 0){

				UsuariosActivos.erase(UsuariosActivos.begin() + index);
				for (int i = index; i < UsuariosActivos.size(); i++) {


					UsuariosActivos[i] -= 1;

				}
			}
			else if (playerIndex >= index ) {

				UsuariosActivos.erase(UsuariosActivos.begin() + (index + 1));
				for (int i = index; i < UsuariosActivos.size(); i++) {


					UsuariosActivos[i] -= 1;

				}
				playerIndex -= 1;
			}
			else if (playerIndex < index) {
				UsuariosActivos.erase(UsuariosActivos.begin() + index);
				for (int i = index; i < UsuariosActivos.size(); i++) {


					UsuariosActivos[i] -= 1;

				}
			}	
		
			playerInfos.erase(playerInfos.begin() + index);
			playersGame.erase(playersGame.begin() + index);



			for (int i=0; i < UsuariosActivos.size(); i++) {

				std::cout << "\n UsuariosActivos:" << UsuariosActivos[i]<< "\n Usuarios:"<<playerInfos.size();


			}
			eventOccurred = true;
		}
		cvDis.notify_one(); // Notifica al hilo principal que puede continuar.





	}

	std::cout << "\nmensaje final";
}