#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "ResourceGameO.hpp"
#include "Bot.hpp"
#include <vector>
#include <memory>  

class GameManager {
public:
    GameManager();


    void GenerarBot(int BotN);
    void startGame();  
    void nextTurn();   
    void processTurn(int playerId); 
    void addPlayer(bool isBot);  
    bool isGameOver();  
  int turnopermitido = 0;
  bool juegoTerminado = false;
  bool giroActivo = false;
private: 
    int currentTurn;
  
    bool gameOver;
};

#endif
