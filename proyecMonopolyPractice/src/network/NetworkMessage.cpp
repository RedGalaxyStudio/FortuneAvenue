#include "NetworkMessage.hpp"


NetworkMessage::NetworkMessage() :peer(nullptr){}
    

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

     void NetworkMessage::stealPlayer( int stolenPlayer) {
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
