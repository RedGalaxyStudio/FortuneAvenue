#include "Client.hpp"
#include "../game/online/ResourceGame.hpp"
#include "../game/online/OnlineVars.hpp"
#include <fstream>
#include <iostream>


Client::Client() : client(nullptr), peer(nullptr){
	clientData = new ClientData();
	SMessageHandler = new ServerMessageHandler(clientData);
	clientData->running=false;
    clientData->isConnected=false;
	clientData->lastRollResult = 0;
	turnopermitido = 0;
	accionCompra = false;
	clientData->anguloActualrule=0.f;
	clientData->casasCargadas = false;
	decelerationRateActi = 0.f;
	clientData->disActiv = false;
	clientData->disconnecte = false;
	giroActivo = false;
	initialSpeedActi=0.f;
	//std::cout << "\n[DEBUG] Constructor: Dirección de client: " << std::hex << reinterpret_cast<uintptr_t>(client);
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
bool Client::c_empty(Nodo* frente) {
	return (frente == NULL) ? true : false;
}
void Client::suprim(Nodo*& frente, Nodo*& fin) {
	ENetPacket* n = frente->dato;
	Nodo* aux = frente;

	SMessageHandler->handleServerMessage(n);
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

	static bool enetInitialized = false;
	if (!enetInitialized) {
		if (enet_initialize() != 0) {
			std::cerr << "Error initializing ENet!" << std::endl;
			return false;
		}
		enetInitialized = true;

	}

	if (reinterpret_cast<uintptr_t>(client) < 0x1000) {  // Detectar valores raros

		client = nullptr;
	}
	if (!client) {

		client = enet_host_create(nullptr, 1, 2, 0, 0);

		if (!client) {
			std::cerr << "Error creating ENet client!" << std::endl;

			return false;
		}
	}


	return true;
}
void Client::insertC(Nodo*& frente, Nodo*& fin, ENetPacket* n) {
	Nodo* nuevo_nodo = new Nodo();

	nuevo_nodo->dato = n;
	nuevo_nodo->siguiente = NULL;

	if (c_empty(frente)) {
		frente = nuevo_nodo;
	}
	else {
		fin->siguiente = nuevo_nodo;
	}

	fin = nuevo_nodo;
}
void Client::run() {
	clientData->running = true;
	while (clientData->running) {
		ENetEvent event;
		while (enet_host_service(client, &event, 100) > 0) {
			switch (event.type) {
			case ENET_EVENT_TYPE_RECEIVE: {

				insertC(frente, fin, event.packet);
				enet_packet_destroy(event.packet);
				break;
			}
			case ENET_EVENT_TYPE_DISCONNECT:
				clientData->running = false;
				break;
			default:
				break;
			}
		}
	}
}
void Client::process() {
	clientData->running = true;
	while (clientData->running) {
		if (frente != NULL) {
			suprim(frente, fin);
		}

	}
}
bool Client::connectToServer(const std::string& address, uint16_t port) {

	if (!client) {
		std::cerr << "Client not initialized!" << std::endl;
		return false;
	}

	// introduce direccion
	ENetAddress enetAddress;
	enet_address_set_host(&enetAddress, address.c_str());
	enetAddress.port = port;

	// intenta conectarse
	peer = enet_host_connect(client, &enetAddress, 2, 0);
	if (!peer) {
		std::cerr << "No available peers for initiating an ENet connection!" << std::endl;
		return false;
	}

	// Espera respuesta del servidor
	ENetEvent event;
	const int maxRetries = 50;
	const int retryDelay = 50;
	for (int i = 0; i < maxRetries; ++i) {
		if (enet_host_service(client, &event, retryDelay) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {

			clientData->isConnected = true;
			clientThread = std::thread(&Client::run, this);
			clientMensThread = std::thread(&Client::process, this);
			networkMessage.Enetpeer(peer);
			SMessageHandler->Enetpeer(peer);
			return true;
		}
	}

	std::cerr << "Failed to connect to server after " << maxRetries << " retries." << std::endl;
	enet_peer_reset(peer);
	return false;
}
void Client::disconnect() {
	if (!clientData->isConnected) return;


	std::string message = "DISCONNNECT";
	ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	enet_host_flush(client);


	if (peer) {
		enet_peer_disconnect(peer, 0);
		peer = nullptr;
	}

	clientData->running = false;
	if (clientThread.joinable()) {
		clientThread.join();
	}

	// destruye cliente y libera los recursos
	if (client) {
		enet_host_destroy(client);
		client = nullptr;
	}

	if (clientMensThread.joinable()) {
		clientMensThread.join();
	}

	clientData->isConnected = false;

}
std::string Client::createRoom(const std::string& username, const std::string& filename) {
	if (!peer) {
		std::cerr << "Client is not connected to a server!" << std::endl;
		return "";
	}


	std::string roomCode = generateRoomCode();

	playerIndex = 0;

	std::string message = "CREATE_ROOM:" + roomCode + ":" + username + ":" + filename;


	ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	PlayerInfo playerInfoNew;
	PlayerGame playerGameNew;
	playerInfoNew.username = nameUser;
	playerInfoNew.PiecUserme = true;
	playerInfos.push_back(playerInfoNew);

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

	enet_host_flush(client);

	return roomCode;
}
bool Client::joinRoom(const std::string& roomCode, const std::string& username, const std::string& filename) {
	if (!peer) {
		return false;
	}

	std::string message = "JOIN_ROOM:" + roomCode + ":" + username + ":" + filename;

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
