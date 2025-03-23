#include "NetworkMessage.hpp"
#include "../game/online/ResourceGame.hpp"
#include <fstream>


NetworkMessage::NetworkMessage() :peer(nullptr) {}


void NetworkMessage::Enetpeer(ENetPeer* Peer) {
	this->peer = Peer;
}
void NetworkMessage::sendMessage(ENetPeer* Peer, const std::string& message) {
	if (!Peer) return;
	ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
	if (!packet) return;
	if (enet_peer_send(Peer, 0, packet) < 0) return;
	enet_host_flush(Peer->host);
}
void NetworkMessage::cargarImagen(const std::string& ruta) {
	
	if (ruta.find("personal") != std::string::npos) {

		//std::cout << "JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN";
		sf::Image imagen;
		if (!imagen.loadFromFile(ruta)) {
			throw std::runtime_error("No se pudo cargar la imagen");
		}

		std::vector<uint8_t> buffer;

		if (!imagen.saveToMemory(buffer, "png")) {
			throw std::runtime_error("No se pudo convertir la imagen a PNG");
		}
		
		size_t chunkSize = 1024;
		size_t totalSize = buffer.size();
		uint32_t numChunks = (totalSize + chunkSize - 1) / chunkSize;

		for (uint32_t i = 0; i < numChunks; ++i) {
			size_t offset = i * chunkSize;
			size_t size = std::min(chunkSize, totalSize - offset);

			// Crear el paquete con identificador de imagen
			std::vector<uint8_t> packetData(sizeof(uint32_t) * 3 + 5 + size); // "IMG|" + datos
			memcpy(packetData.data(), "IMG|", 4); // Prefijo de imagen
			uint32_t* header = reinterpret_cast<uint32_t*>(packetData.data() + 4);
			header[0] = UsuariosActivos[0];
			header[1] = i;
			header[2] = numChunks;
			memcpy(packetData.data() + 4 + sizeof(uint32_t) * 3, buffer.data() + offset, size);

			ENetPacket* packet = enet_packet_create(packetData.data(), packetData.size(), ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet);
		}

		/*std::string header = "image1;" + std::to_string(UsuariosActivos[0]) + ";";

		// Crear un buffer que contenga la cabecera + imagen
		std::vector<uint8_t> paquete(header.begin(), header.end());
		paquete.insert(paquete.end(), buffer.begin(), buffer.end());

		// Crear el paquete ENet
		ENetPacket* packet = enet_packet_create(paquete.data(), paquete.size(), ENET_PACKET_FLAG_RELIABLE);

		enet_peer_send(peer, 0, packet);
		enet_host_flush(peer->host);
		std::cout << "Bytes de imagen enviados: ";
		for (size_t i = 0; i < std::min(buffer.size(), size_t(10)); i++) {
			std::cout << std::hex << static_cast<int>(buffer[i]) << " ";
		}
		std::cout << std::dec << std::endl;*/
	}
	else {
		std::string avatarspre="image0;"+ std::to_string(UsuariosActivos[0]) + ";"+ruta;
		ENetPacket* packet = enet_packet_create(avatarspre.c_str(), avatarspre.size() + 1, ENET_PACKET_FLAG_RELIABLE);

		// Enviar el paquete al servidor o cliente
		enet_peer_send(peer, 0, packet);

		// Asegurar que los datos se envíen
		enet_host_flush(peer->host);
	}



}
void NetworkMessage::sendSafeInvestment() {
	std::string message = "INVERCIONSEGURA";
	sendMessage(peer, message);
}
void NetworkMessage::sendSmg(std::string mensaje) {
	std::string message = "SMG" + mensaje;
	sendMessage(peer, message);
}
void NetworkMessage::sendXHouse() {
	std::string message = "XCASA";
	sendMessage(peer, message);
}
void NetworkMessage::sendEventHouse() {
	std::string message = "EVENTOCASA";
	sendMessage(peer, message);
}
void NetworkMessage::sendEventTax() {
	std::string message = "EVENTOIMPUEST";
	sendMessage(peer, message);
}
void NetworkMessage::sendEventSpin() {
	std::string message = "EVENTORULETA";
	sendMessage(peer, message);
}
void NetworkMessage::stealPlayer(int stolenPlayer) {
	std::string message = "ROBARPLAYER:" + std::to_string(stolenPlayer);
	sendMessage(peer, message);
}
void NetworkMessage::buyHouse(int houseIndex) {
	std::string message = "CASACOMPRA:" + std::to_string(houseIndex);
	sendMessage(peer, message);
}
void NetworkMessage::rollDice() {
	std::string message = "ROLL_DICE";
	sendMessage(peer, message);
}
void NetworkMessage::sendPathOption(int option) {
	std::string message = "OPCION_CAMINO:" + std::to_string(option);
	sendMessage(peer, message);
}
void NetworkMessage::endTurn() {
	std::string message = "END_TURN";
	sendMessage(peer, message);
}
void NetworkMessage::startSpin() {
	std::string message = "START_SPIN";
	sendMessage(peer, message);
}
void NetworkMessage::everyoneLoses() {
	std::string message = "TODOSPIERDEN";
	sendMessage(peer, message);
}
void NetworkMessage::win150() {
	std::string message = "GANAS150";
	sendMessage(peer, message);
}
void NetworkMessage::sendRouletteGame(float angle) {
	std::string message = "RULETE_GAME:" + std::to_string(angle);
	sendMessage(peer, message);
}
void NetworkMessage::playerChangedPiece(int pieceIndex) {
	std::string message = "SELECTING_PIECE:" + std::to_string(pieceIndex);
	sendMessage(peer, message);
}
void NetworkMessage::playerReady() {
	std::string message = "PLAYER_READY";
	sendMessage(peer, message);
}
void NetworkMessage::llegadaFinal() {

	std::string message = "LLEGUEFINAL";
	ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	enet_host_flush(peer->host);


}