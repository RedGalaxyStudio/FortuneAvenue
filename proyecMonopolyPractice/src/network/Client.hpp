#ifndef CLIENT_HPP
#define CLIENT_HPP
#define WIN32_LEAN_AND_MEAN

//#include "ResourceGlobal.hpp"
#include <winsock2.h>
#include "NetworkMessage.hpp"
#include <windows.h>
#include <enet/enet.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <string>
#include <sstream>
#include <random>
#include <condition_variable>
#include <mutex>

class Client {
public:


	struct Nodo {
		std::string dato;
		Nodo* siguiente;
	};

	void process();
	void insertarCola(Nodo*& frente, Nodo*& fin, std::string n);
	Nodo* frente = nullptr;
	Nodo* fin = nullptr;
	Client();
	bool cola_vacia(Nodo* frente);
	~Client();
	void run();
	bool initialize();
	std::string createRoom(const std::string& username, const std::string& filename);
	bool joinRoom(const std::string& roomCode, const std::string& username, const std::string& filename);
	bool connectToServer(const std::string& address, uint16_t port);
	void disconnect();
	void moneyActu(int money);
	void handleServerMessage(const std::string& message);
	int lastRollResult;
	ENetPeer* peer;
	std::atomic<bool> running;
	bool isConnected;
	ENetHost* client;
	std::mutex mtx;
	std::condition_variable cv;
	std::mutex casasMutex;        // Para proteger el acceso a las casas
	bool casasCargadas;
	int conteoturn;
	float anguloActualrule;
	float initialSpeedActi;
	float decelerationRateActi;
	bool giroActivo;
	int turnopermitido;
	std::mutex ruletaMutex;
	std::condition_variable ruletaCondVar;
	bool ruletaMessageReceived = false;

	std::mutex impuestoMutex;
	std::condition_variable impuestoCondVar;
	bool impuestoMessageReceived = false;

	bool agregardor = false;
	void suprimirCola(Nodo*& frente, Nodo*& fin);
	std::mutex mtxExisting;
	std::condition_variable cvExisting;
	bool accionCompra;
	void llegadaFinal();
	void MONEYSALARIO(std::string message, int usuario);
	std::mutex mtxx;
	std::condition_variable cvv;
	int playerIndex;
	std::mutex mtex;
	std::condition_variable cvDis;
	bool eventOccurred = false;
	bool disconnecte;
	bool disActiv;
	bool juegoTerminado = false;


	NetworkMessage networkMessage;
	int calcularNumeroDeLineas(const sf::Text& text);
private:
	
	sf::FloatRect globalBounds;
	std::thread clientThread;
	std::thread clientMensThread;

};

#endif
