#include "GameManager.hpp"
#include <iostream>
#include "ResourceGameO.hpp"
#include <random>
GameManager::GameManager() : currentTurn(0), gameOver(false) {}

void GameManager::CasasAleatorias() {
	int numJugadores = static_cast<int>(ActiveUsers.size());
	int numCasas = 17;
	std::vector<std::vector<int>> casasR;
	casasR.resize(numJugadores);
	std::vector<int> casas;
	for (int i = 0; i < numCasas; ++i) {
		casas.push_back(i);
	}
	for (int i = 0; i < numJugadores; i++) {
		casasR[i].resize(numCasas);
	}
	std::random_device rd;
	std::mt19937 g(rd());

	// Asignar las casas a los jugadores
	for (int i = 0; i < numJugadores; ++i) {
		std::shuffle(casas.begin(), casas.end(), g);

		for (int j = 0; j < numCasas; ++j) {

			casasR[i][j] = casas[j];
		}
	}

	for (int i = 0; i < numJugadores; ++i) {
		playerGameInfo[i].casasPorJugador = casasR[i];
	}

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

		plantillaGMBot.PieceSelect.setTexture(pieceShape[plantillaInfoMBot.indexPiece], true);
		sf::IntRect rect = plantillaGMBot.PieceSelect.getTextureRect();
		plantillaGMBot.boxPlayer.setTexture(textureBoxPerfilOff);
		plantillaGMBot.boxPlayer.setOrigin(125, 40);
		plantillaGMBot.boxPlayer.setScale(0.9f, 0.9f);
		playerGameOff.push_back(plantillaGMBot);
		ActiveUsers.push_back(i + 1);

	}

}
void GameManager::startGame() {
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

	playerGameOff[IndexTurn1].boxPlayer.setTexture(textureBoxPerfilOn);
	firstTurn = false;
	size_t currentTurn = IndexTurn1;
	IndexTurn1 = (currentTurn + 1) % static_cast<int>(ActiveUsers.size());



	if (playerGameInfo[IndexTurn1].final) {

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

	if (playerGameInfo[IndexTurn1].turnopermitido != 0) {
		if(IndexTurn1==0){
		zero = false;
		return;
		}
		else {
			playerGameInfo.at(IndexTurn1).turnopermitido = 0;
			nextTurn();
			return;

		}
	}
	
	if (IndexTurn1 == 0) {

		if (playerGameInfo[ActiveUsers[0]].final) {
			nextTurn();
			return;
		}
		playerGameOff[IndexTurn1].boxPlayer.setTexture(textureBoxPerfilOff);
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
	else if (IndexTurn1 != 0) {
		playerGameOff[IndexTurn1].boxPlayer.setTexture(textureBoxPerfilOff);
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
	playerGameInfo[IndexTurn1].money -= playerGameInfo[IndexTurn1].impuesto;
	playerGameOff[IndexTurn1].Money.setString(std::to_string(playerGameInfo[IndexTurn1].money));
}

