#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <enet/enet.h>
#include <vector>
#include <thread>
#include <atomic>
#include <string>
#include <sstream>
#include <random>
#include <condition_variable>
#include <mutex>

struct ClientData {

	int lastRollResult;

	bool Nmsg = false;
	bool casasCargadas;

	bool agregardor = false;
	bool eventOccurred = false;
	bool disconnecte;
	bool disActiv;


	std::atomic<bool> running;
	bool isConnected;
	bool ruletaMessageReceived = false;	
	bool impuestoMessageReceived = false;
	float anguloActualrule;


	std::mutex ruletaMutex;
	std::condition_variable ruletaCondVar;
	std::mutex mtxExisting;
	std::condition_variable cvExisting;
	std::mutex mtxx;
	std::condition_variable cvv;
	std::mutex mtex;
	std::condition_variable cvDis;
	std::mutex impuestoMutex;
	std::condition_variable impuestoCondVar;
	std::mutex mtx;
	std::condition_variable cv;
	std::mutex casasMutex;
};