#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "ResourceGameO.hpp"
#include "Bot.hpp"
#include <vector>
#include <memory>  

class GameManager {
public:
	GameManager();

	Bot bot;
	void CasasAleatorias();
	void GenerarBot(int BotN);
	void startGame();
	void nextTurn();
	void impuesto();
	void processTurn(int playerId);
	void addPlayer(bool isBot);
	bool isGameOver();
	int turnopermitido = 0;
	bool juegoTerminadoo = false;
	bool giroActivo = false;
private:
	int currentTurn;

	bool gameOver;
};

#endif
