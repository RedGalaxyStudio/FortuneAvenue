#include "GameManager.hpp"
#include <iostream>

GameManager::GameManager() : currentTurn(0), gameOver(false) {}

void GameManager::startGame() {
    std::cout << "El juego ha comenzado!" << std::endl;
    IndexTurn1 = 0;
    turn_dice = true;
    firstTurn = true;
    activeEvent = false;
    turn_roulette = true;
    turn_house = true;
    turn_Tax = true;
    turn_Move = true;

    secondTurn = false;
}

void GameManager::nextTurn() {
    size_t currentTurn = IndexTurn1;
    IndexTurn1 = (currentTurn + 1) % ActiveUsers.size();

    if (IndexTurn1 == 0) {

        if (playerGameInfo[ActiveUsers[0]].final) {

            nextTurn();
            return;
        }

        turn_dice = true;
        firstTurn = true;
        activeEvent = false;
        turn_roulette = true;
        turn_house = true;
        turn_Tax = true;
        turn_Move = true;

        secondTurn = false;
    }
    else {
        secondTurn = true;
        activeEvent = false;
        turn_roulette = true;
        turn_house = true;
        turn_Tax = true;
        turn_Move = true;
    }
}

void GameManager::processTurn(int playerId) {
    std::cout << "Procesando el turno para el jugador con ID: " << playerId << std::endl;
    if (playerId < players.size()) {
        players[playerId]->playTurn();  
    }
}

void GameManager::addPlayer(bool isBot) {
    if (isBot) {
        players.push_back(std::make_shared<Bot>(players.size()));
        std::cout << "Bot añadido al juego." << std::endl;
    }
    else {
        std::cout << "Jugador añadido al juego." << std::endl;
    }
}

bool GameManager::isGameOver() {
    return gameOver;
}
