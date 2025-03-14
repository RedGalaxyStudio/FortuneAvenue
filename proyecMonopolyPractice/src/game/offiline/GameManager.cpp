#include "GameManager.hpp"
#include <iostream>
#include "ResourceGameO.hpp"
GameManager::GameManager() : currentTurn(0), gameOver(false) {


}





void GameManager::GenerarBot(int BotN) {

	std::vector<std::string> NamesBots = CreatorB::getRandomBotNames(BotN);

	std::vector<int> PiecesBot = CreatorB::getRandomBotPieces(BotN);
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
