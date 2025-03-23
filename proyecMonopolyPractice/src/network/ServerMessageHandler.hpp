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
#include <unordered_map>
class ServerMessageHandler
{
public:
	

	ServerMessageHandler(ClientData* cData);
	int calcularNumeroDeLineas(const sf::Text& text);
	void Enetpeer(ENetPeer* Peer);
	void moneyActu(int money);
	void handleServerMessage(const ENetPacket* preprocces);
	void MONEYSALARIO(std::string message, int usuario);
	std::unordered_map<uint32_t, std::map<uint32_t, std::vector<uint8_t>>> playerImageFragments;

	//std::unordered_map<uint32_t, std::vector<uint8_t>> playerImageFragments;
	std::unordered_map<uint32_t, uint32_t> expectedChunksPerPlayer;
private:
	ClientData* clientData;
	ENetPeer* peer;
	sf::FloatRect globalBounds;
};

