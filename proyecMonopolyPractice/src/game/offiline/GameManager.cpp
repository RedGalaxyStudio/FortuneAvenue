#include "GameManager.hpp"
#include <iostream>
#include "ResourceGameO.hpp"
#include <random>
GameManager::GameManager() : currentTurn(0), gameOver(false) {


}



void GameManager::CasasAleatorias() {
	int numJugadores = ActiveUsers.size();
	int numCasas = 17;
	std::vector<std::vector<int>> casasR;
	casasR.resize(numJugadores);
	std::cout << "COta";
	// Lista de todas las casas (suponiendo que son números del 1 al 68)
	std::vector<int> casas;
	for (int i = 0; i < numCasas; ++i) {
		casas.push_back(i);
	}
	for (int i = 0; i < numJugadores; i++) {
		casasR[i].resize(numCasas);
	}
	// Barajar la lista de casas una sola vez
	std::random_device rd;
	std::mt19937 g(rd());
	std::cout << "COta";
	// Asignar las casas a los jugadores
	for (int i = 0; i < numJugadores; ++i) {
		std::shuffle(casas.begin(), casas.end(), g);
		std::cout << "\niiii:  " << i;
		for (int j = 0; j < numCasas; ++j) {
			std::cout << "\nJJJJJ:  " << i;
			casasR[i][j] = casas[j];
		}
	}
	std::cout << "COta";
	for (int i = 0; i < numJugadores; ++i) {
		playerGameInfo[i].casasPorJugador = casasR[i];
	}
	std::cout << "COta";
}
void GameManager::GenerarBot(int BotN) {

	std::vector<std::string> NamesBots = CreatorB::getRandomBotNames(BotN);

	std::vector<int> PiecesBot = CreatorB::getRandomBotPieces(BotN, playerGameInfo[0].indexPiece);
	std::vector<int> avatarsBot = CreatorB::getRandomBotAvatar(BotN);



	PlayerInformation plantillaInfoMBot;
	PlayerGameOff plantillaGMBot;
	sf::FloatRect globalBounds;
	for (int i = 0; i < BotN; i++)
	{

		plantillaInfoMBot.playerName = NamesBots[i];
		plantillaInfoMBot.PiecUserme = true;
		plantillaInfoMBot.indexPiece = PiecesBot[i];

		playerGameInfo.push_back(plantillaInfoMBot);
		plantillaGMBot.CashSprite.setTexture(TextureMoney1);
		plantillaGMBot.Home.setTexture(TextureBuilding);

		plantillaGMBot.textureAvatarPLayer.loadFromFile("assets/image/Avatars/avatar" + std::to_string(avatarsBot[i]) + ".png");
		plantillaGMBot.NamePlayer.setCharacterSize(17);
		plantillaGMBot.NamePlayer.setFont(fontUserProfile);
		plantillaGMBot.NamePlayer.setFillColor(sf::Color::White);
		plantillaGMBot.NamePlayer.setOutlineThickness(2);
		plantillaGMBot.NamePlayer.setOutlineColor(sf::Color(135, 135, 135));
		plantillaGMBot.NamePlayer.setString(plantillaInfoMBot.playerName);

		globalBounds = plantillaGMBot.NamePlayer.getGlobalBounds();
		plantillaGMBot.NamePlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
		plantillaGMBot.MarcoPlayer.setTexture(TextureFrame);

		globalBounds = plantillaGMBot.MarcoPlayer.getGlobalBounds();
		plantillaGMBot.MarcoPlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

		plantillaGMBot.MarcoPlayer.setPosition(52.5f, 62.5f);

		plantillaGMBot.PieceSelect.setTexture(pieceShape[plantillaInfoMBot.indexPiece]);
		plantillaGMBot.boxPlayer.setTexture(textureBoxPerfilOff);
		plantillaGMBot.boxPlayer.setOrigin(125, 40);
		plantillaGMBot.boxPlayer.setScale(0.9f, 0.9f);
		playerGameOff.push_back(plantillaGMBot);
		ActiveUsers.push_back(i + 1);

	}

}
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
	firstTurn = false;
	size_t currentTurn = IndexTurn1;
	IndexTurn1 = (currentTurn + 1) % ActiveUsers.size();



	if (playerGameInfo[IndexTurn1].GameFinal) {

		if (!playerGameInfo[IndexTurn1].inversionActiva) {
			playerGameInfo[IndexTurn1].GameTerm = true;

			juegoTerminadoo = true;
			for (size_t i = 0; i < playerGameInfo.size(); i++)
			{
				if (!playerGameInfo[i].GameTerm) {

					juegoTerminadoo = false;
				}
			}
	

			if (!juegoTerminadoo) {
				nextTurn();
			}

			if (juegoTerminadoo) {

				return;
			}
		}

		if (playerGameInfo[IndexTurn1].inversionActiva &&
			playerGameInfo[IndexTurn1].turnosInversion > 0) {

			playerGameInfo[IndexTurn1].turnosInversion -= 1;

		}
		else if (playerGameInfo[IndexTurn1].inversionActiva &&
			playerGameInfo[IndexTurn1].turnosInversion == 0) {
			playerGameInfo[IndexTurn1].inversionActiva = false;
			playerGameInfo[IndexTurn1].money += 200;
		
			playerGameOff[IndexTurn1].Money.setString(std::to_string(playerGameInfo[IndexTurn1].money));
		}

	}
	else {

		if (playerGameInfo[IndexTurn1].inversionActiva &&
			playerGameInfo[IndexTurn1].turnosInversion > 0) {

			playerGameInfo[IndexTurn1].turnosInversion -= 1;

		}
		else if (playerGameInfo[IndexTurn1].inversionActiva &&
			playerGameInfo[IndexTurn1].turnosInversion == 0) {
			playerGameInfo[IndexTurn1].inversionActiva = false;
			playerGameInfo[IndexTurn1].money += 200;
			playerGameOff[IndexTurn1].Money.setString(std::to_string(playerGameInfo[IndexTurn1].money));

		}

		if (playerGameInfo[IndexTurn1].controlSalario == 2) {
			playerGameInfo[IndexTurn1].money += playerGameInfo[IndexTurn1].salario;
			playerGameOff[IndexTurn1].Money.setString(std::to_string(playerGameInfo[IndexTurn1].money));
			playerGameInfo[IndexTurn1].controlSalario = 0;
		}
		else if (playerGameInfo[IndexTurn1].controlSalario < 2) {
			playerGameInfo[IndexTurn1].controlSalario += 1;
		}
		
	}

	if (IndexTurn1 == 0) {

		if (playerGameInfo[ActiveUsers[0]].final) {

			nextTurn();
			return;
		}
		BotTurn = false;
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

		BotTurn = true;
		turn_diceB = true;
		secondTurn = true;
		activeEvent = false;
		turn_roulette = true;
		turn_house = true;
		turn_Tax = true;
		turn_Move = true;
		bot.resetT();
	}
}

void GameManager::impuesto() {
	playerGameInfo[IndexTurn1].controlSalario += 1;
	playerGameInfo[IndexTurn1].money -= playerGameInfo[IndexTurn1].impuesto;
	playerGameOff[IndexTurn1].Money.setString(std::to_string(playerGameInfo[IndexTurn1].money));
}

void GameManager::processTurn(int playerId) {
	//std::cout << "Procesando el turno para el jugador con ID: " << playerId << std::endl;
	//  if (playerId < players.size()) {
  //        players[playerId]->playTurn();  
	 // }
}

void GameManager::addPlayer(bool isBot) {
	if (isBot) {
		// players.push_back(std::make_shared<Bot>(players.size()));
		std::cout << "Bot añadido al juego." << std::endl;
	}
	else {
		std::cout << "Jugador añadido al juego." << std::endl;
	}
}

bool GameManager::isGameOver() {
	return gameOver;
}
