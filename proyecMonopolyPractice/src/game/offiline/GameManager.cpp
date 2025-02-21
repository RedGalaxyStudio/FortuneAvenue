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
    //playerGameOff nextPlayer = playerGameOff[IndexTurn1];

    if (IndexTurn1==0) {

        if (playerGameInfo[ActiveUsers[0]].final) {

            nextTurn();
            return;
        }

       // conteoturn += 1;
        //conteosuel += 1;

        //if (turnopermitido != 0) {
         //   nular = false;
     //       return;
       // }

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

    //    if (indexPos != std::string::npos) {
        //
         //   std::string playerIndexStr = message.substr(indexPos + 13);
          //  int playerIndexTurn = std::stoi(playerIndexStr);
           // IndexTurn = playerIndexTurn;

//            MONEYSALARIO(message, playerIndexTurn);

  //      }
    }

}

void GameManager::processTurn(int playerId) {
    std::cout << "Procesando el turno para el jugador con ID: " << playerId << std::endl;
    // Aquí iría la lógica del evento específico (mover piezas, hacer compras, lanzar dados, etc.)
    if (playerId < players.size()) {
        players[playerId]->playTurn();  // Llamar a la función del bot si es un bot
    }
}

void GameManager::addPlayer(bool isBot) {
    if (isBot) {
        players.push_back(std::make_shared<Bot>(players.size()));
        std::cout << "Bot añadido al juego." << std::endl;
    }
    else {
        // Aquí agregas la lógica para añadir jugadores humanos, si corresponde
        std::cout << "Jugador humano añadido al juego." << std::endl;
    }
}

bool GameManager::isGameOver() {
    // Aquí puedes agregar condiciones de fin del juego, como si los jugadores perdieron o alcanzaron un objetivo.
    return gameOver;
}
