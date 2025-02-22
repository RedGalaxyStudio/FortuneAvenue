#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "ResourceGameO.hpp"
#include "Bot.hpp"
#include <vector>
#include <memory>  // Para usar smart pointers si es necesario

class GameManager {
public:
    GameManager();
    void startGame();  // Inicia el juego, creando los jugadores y configurando el juego
    void nextTurn();   // Cambia al siguiente turno
    void processTurn(int playerId);  // Procesa el turno de un jugador específico
    void addPlayer(bool isBot);  // Añade un jugador (bot o humano)
    bool isGameOver();  // Comprueba si el juego ha terminado
  int turnopermitido = 0;
  bool juegoTerminado = false;
  bool giroActivo = false;
private:
    std::vector<std::shared_ptr<Bot>> players;  // Lista de jugadores (humanos o bots)
    int currentTurn;
  
    bool gameOver;
};

#endif
