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
#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#endif

#include <unordered_map>
class ServerMessageHandler
{
public:
	

	explicit ServerMessageHandler(ClientData* cData);
	int calcularNumeroDeLineas(const sf::Text& text);
	void Enetpeer(ENetPeer* Peer);
	void handleServerMessage(const ENetPacket* preprocces);
	void MONEYSALARIO(std::string message, int usuario);

	std::unordered_map<uint32_t, std::map<uint32_t, std::vector<uint8_t>>> playerImageFragments;
	std::unordered_map<uint32_t, uint32_t> expectedChunksPerPlayer;

private:
	ClientData* clientData;
	ENetPeer* peer;
	sf::FloatRect globalBounds;
};

