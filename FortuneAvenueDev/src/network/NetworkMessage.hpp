#ifndef NETWORKMESSAGE_HPP
#define NETWORKMESSAGE_HPP
#include <SFML/Graphics.hpp>
#include <string>
#include <enet/enet.h>
#include <vector>

class NetworkMessage {

private:
    ENetPeer* peer;

public:

    NetworkMessage();
     void Enetpeer(ENetPeer* Peer);
     static void sendMessage(ENetPeer* Peer, const std::string& message);
     void cargarImagen(const std::string& ruta);
     void sendSafeInvestment();
     void sendSmg(const std::string mensaje);
     void sendXHouse();
     void sendEventHouse();
     void sendEventTax();
     void sendEventSpin();
     void stealPlayer( int stolenPlayer);
     void buyHouse(int houseIndex);
     void rollDice();
     void sendPathOption(int option);
     void endTurn();
     void startSpin();
     void everyoneLoses();
     void win150();
     void sendRouletteGame(float angle);
     void playerChangedPiece(int pieceIndex);
     void playerReady();
     void llegadaFinal();
};

#endif 
