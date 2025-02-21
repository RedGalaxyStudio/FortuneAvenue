#include "Bot.hpp"
#include <iostream>

Bot::Bot(int id) : id(id), score(0) {}

void Bot::playTurn() {
    // Lógica para que el bot realice su turno
    std::cout << "Bot " << id << " jugando su turno..." << std::endl;
    // Implementar el comportamiento del turno
}
