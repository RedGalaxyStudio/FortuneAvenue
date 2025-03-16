#ifndef CLIENT_HPP
#define CLIENT_HPP
#define WIN32_LEAN_AND_MEAN

//#include "ResourceGlobal.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <winsock2.h>
#include "NetworkMessage.hpp"
#include "ServerMessageHandler.hpp"
#include <windows.h>
#include <enet/enet.h>
#include <vector>
#include <thread>
#include <atomic>
#include <string>
#include <sstream>
#include <random>
#include <condition_variable>
#include <mutex>
#include "ClientData.hpp"

class Client {
public:
	struct Nodo {
		ENetPacket* dato;
		Nodo* siguiente;
	};
	void process();
	void insertC(Nodo*& frente, Nodo*& fin, ENetPacket* n);
	Nodo* frente = nullptr;
	Nodo* fin = nullptr;
	Client();
	bool c_empty(Nodo* frente);
	~Client();
	void run();
	bool initialize();
	std::string createRoom(const std::string& username, const std::string& filename);
	bool joinRoom(const std::string& roomCode, const std::string& username, const std::string& filename);
	bool connectToServer(const std::string& address, uint16_t port);
	void disconnect();
	ENetPeer* peer;
	ENetHost* client;
	void suprim(Nodo*& frente, Nodo*& fin);

	NetworkMessage networkMessage;
	ClientData* clientData;
private:
	ServerMessageHandler* SMessageHandler;
	sf::FloatRect globalBounds;
	std::thread clientThread;
	std::thread clientMensThread;

};

#endif
