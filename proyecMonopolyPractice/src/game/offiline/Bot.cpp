#include "Bot.hpp"
#include <iostream>

Bot::Bot(int id) : id(id), score(0) {}

void Bot::playTurn() {
    std::cout << "Bot " << id << " jugando su turno..." << std::endl;
}
