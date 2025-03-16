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
#include "ClientData.hpp"
#include <winsock2.h>
#include <windows.h>
class ServerMessageHandler
{
public:
	

	ServerMessageHandler(ClientData* cData);
	int calcularNumeroDeLineas(const sf::Text& text);
	void Enetpeer(ENetPeer* Peer);
	void moneyActu(int money);
	void handleServerMessage(const ENetPacket* preprocces);
	void MONEYSALARIO(std::string message, int usuario);

private:
	ClientData* clientData;
	ENetPeer* peer;
	sf::FloatRect globalBounds;
};

