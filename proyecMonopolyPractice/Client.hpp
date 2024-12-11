#ifndef CLIENT_HPP
#define CLIENT_HPP
#define WIN32_LEAN_AND_MEAN
#include "ResourceGame.hpp"
#include <winsock2.h>
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
	Client();
	~Client();
	void run();
	bool initialize();
	std::string createRoom(const std::string& username);
	bool joinRoom(const std::string& roomCode, const std::string& username);
	bool connectToServer(const std::string& address, uint16_t port);
	bool sendImage(const std::string& filename);
	void disconnect();
	void rollDice();
	void endTurn();
	void todospierden();
	void ganas150();

	void moneyActu(int money);
	void handleServerMessage(const std::string& message);
	int lastRollResult;
	void playerChangedPiece();
	void opcionCaminoenvio(int opcionCami);
	void ReadyPlayer();
	void startSpin();
	void ruleteGame(float angulo);
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
	void casasX();
	void invercionSegura();
	void robarUser(int usuariorobao);
	void casacomprada(int compra);

	std::mutex mtxExisting;
	std::condition_variable cvExisting;
	bool accionCompra;


	std::mutex mtxx;
	std::condition_variable cvv;
private:


	int playerIndex;
	std::vector<char> loadImage(const std::string& filename);

	std::thread clientThread;

};

#endif
