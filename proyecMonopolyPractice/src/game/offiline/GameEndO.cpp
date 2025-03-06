#include "GameEndO.hpp"
#include <iostream>
#include "../../core/ObjetosGlobal.hpp"
#include "../../ui/ResourceGeneral.hpp"

GameEndO::GameEndO(sf::RenderWindow* window) : window(window) {

}

GameEndO::~GameEndO() {}


void assignPositions(const std::vector<PlayerInformation>& players, std::vector<int>& positions) {
	std::vector<size_t> indices(players.size());
	for (size_t i = 0; i < players.size(); ++i) {
		indices[i] = i;
	}

	std::sort(indices.begin(), indices.end(), [&players](size_t a, size_t b) {
		return players[a].money > players[b].money;
		});

	int currentRank = 1;
	int playersInSameRank = 0; 
	positions.resize(players.size(), 0);

	for (size_t i = 0; i < indices.size(); ++i) {
		if (i > 0 && players[indices[i]].money == players[indices[i - 1]].money) {
			positions[indices[i]] = currentRank;
			playersInSameRank++;
		}
		else {
			currentRank += playersInSameRank;
			positions[indices[i]] = currentRank;
			playersInSameRank = 1;
		}
	}
}


void GameEndO::resource() {
	fingame12.setCharacterSize(40);
	fingame12.setFont(fontUser);
	fingame12.setFillColor(sf::Color::White);
	fingame12.setOutlineThickness(2);
	fingame12.setOutlineColor(sf::Color(135, 135, 135));

	fingame12.setString("Fin de la Partida");
	fingame12.setPosition(440, 70);

	fingame12.setString("Fin de la partida");
	fingame12.setPosition(640,70);
	sf::FloatRect globalBounds = fingame12.getGlobalBounds();
	fingame12.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);


	posicionesGanadores.resize(ActiveUsers.size());

	assignPositions(playerGameInfo, posiGndrs);

	for (int i = 0; i < posicionesGanadores.size(); i++) {

		posicionesGanadores[i].setCharacterSize(40);
		posicionesGanadores[i].setFont(fontUser);
		posicionesGanadores[i].setFillColor(sf::Color::White);
		posicionesGanadores[i].setOutlineThickness(2);
		posicionesGanadores[i].setOutlineColor(sf::Color(135, 135, 135));
		posicionesGanadores[i].setString(std::to_string(posiGndrs[i])+"�");
		sf::FloatRect globalBounds = posicionesGanadores[i].getGlobalBounds();
		posicionesGanadores[i].setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	}
}

void GameEndO::update() {

	float perfilWidth = 200.0f; 
	float separacion = 20.0f;  
	int totalPerfiles = ActiveUsers.size();    

	if (totalPerfiles > 0) {
		float totalWidth = (totalPerfiles * perfilWidth) + ((totalPerfiles - 1) * separacion);

		float startX = (1280.0f - totalWidth) / 2.0f + (perfilWidth / 2.0f);

		float startY = 290.f;

		for (int i = 0; i < totalPerfiles; i++) {
			float xPos = startX + i * (perfilWidth + separacion);
			float yPos = startY;
			posicionesGanadores[i].setPosition(xPos, startY- 90);
			playerGameOff[i].NamePlayer.setPosition(xPos, startY + 70);
			playerGameOff[i].boxPlayer.setPosition(xPos, startY + 70);
			playerGameOff[i].AvatarPlayer.setPosition(xPos, startY);
			playerGameOff[i].MarcoPlayer.setPosition(xPos, startY);
			if (playerGameOff[i].PieceSelect.getTexture() != nullptr) {
				playerGameOff[i].PieceSelect.setScale(2.0f, 2.0f);
				sf::FloatRect pieceSelectBounds = playerGameOff[i].PieceSelect.getGlobalBounds();
				playerGameOff[i].PieceSelect.setOrigin(pieceSelectBounds.width / 2.0f, pieceSelectBounds.height / 2.0f);
				playerGameOff[i].PieceSelect.setPosition(xPos + (pieceSelectBounds.width / 2.0f), startY + 220);
			}

			sf::FloatRect moneyBounds = playerGameOff[i].Money.getGlobalBounds();
			playerGameOff[i].Money.setOrigin(moneyBounds.width / 2.0f, moneyBounds.height / 2.0f);
			playerGameOff[i].Money.setPosition(xPos, startY + 120);


		}
	}


	while (window->isOpen()) {


		sf::Event event;

		while (window->pollEvent(event)) {



			sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
			sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

					renderTexture.clear();
					renderTexture.draw(spriteBackgroundG);
					for (int i = 0; i < ActiveUsers.size(); i++) {
						renderTexture.draw(playerGameOff[i].NamePlayer);
						renderTexture.draw(playerGameOff[i].boxPlayer);
						renderTexture.draw(playerGameOff[i].MarcoPlayer);
						renderTexture.draw(playerGameOff[i].AvatarPlayer);
					}
					renderTexture.draw(spriteX);
					renderTexture.draw(overlay);


			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {

				renderTexture.clear();
				renderTexture.draw(spriteBackgroundG);
				for (int i = 0; i < 4; i++) {
					renderTexture.draw(playerGameOff[i].NamePlayer);
					renderTexture.draw(playerGameOff[i].boxPlayer);
					renderTexture.draw(playerGameOff[i].MarcoPlayer);
					renderTexture.draw(playerGameOff[i].AvatarPlayer);
				}
				renderTexture.draw(spriteX);
				renderTexture.draw(overlay);

				Menup.MenuSalir(nullptr);
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				playClickSound();
			}

				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
						playClickSound();
				}
			
		}  

		window->setMouseCursor(*currentCursor);


		window->clear();

		window->draw(spriteBackgroundG);


		window->draw(fingame12);

		float perfilWidth = 200.0f; 
		float separacion = 20.0f;  
		int totalPerfiles = ActiveUsers.size();    
		float totalWidth = (totalPerfiles * perfilWidth) + ((totalPerfiles - 1) * separacion);
		float startX = ((1280.0f - totalWidth) / 2.0f) + 100;
		float startY = (720.0f - (180.0f + 70.0f + 50.0f)) / 2.0f;


		if (totalPerfiles > 0) {
			
			float totalWidth = (totalPerfiles * perfilWidth) + ((totalPerfiles - 1) * separacion);
			float startX = (1280.0f - totalWidth) / 2.0f + (perfilWidth / 2.0f);
			float startY = 100.0f;


			for (int i = 0; i < totalPerfiles; i++) {
				float xPos = startX + i * (perfilWidth + separacion); // Calcula la posici�n en X para cada perfil
				float yPos = startY;

				playerGameOff[ActiveUsers[i]].NamePlayer.setPosition(xPos, startY+170);
				playerGameOff[ActiveUsers[i]].boxPlayer.setPosition(xPos, startY+170);
				//playerGameOff[ActiveUsers[i]].PieceSelect.setPosition(xPos+ 30, startY + 330);
				playerGameOff[ActiveUsers[i]].AvatarPlayer.setPosition(xPos, yPos+100);
				playerGameOff[ActiveUsers[i]].AvatarPlayer.setScale(1,1);
				playerGameOff[ActiveUsers[i]].MarcoPlayer.setPosition(xPos, yPos+100);

				if (playerGameOff[ActiveUsers[i]].PieceSelect.getTexture() != nullptr) {
					playerGameOff[ActiveUsers[i]].PieceSelect.setScale(2.0f, 2.0f);
					sf::FloatRect pieceSelectBounds = playerGameOff[ActiveUsers[i]].PieceSelect.getGlobalBounds();
					playerGameOff[ActiveUsers[i]].PieceSelect.setOrigin(pieceSelectBounds.width / 2.0f, pieceSelectBounds.height / 2.0f);
					playerGameOff[ActiveUsers[i]].PieceSelect.setPosition(xPos + (pieceSelectBounds.width / 2.0f), startY + 310);
				}

				sf::FloatRect moneyBounds = playerGameOff[i].Money.getGlobalBounds();
				playerGameOff[ActiveUsers[i]].Money.setOrigin(moneyBounds.width / 2.0f, moneyBounds.height / 2.0f);
				playerGameOff[ActiveUsers[i]].Money.setPosition(xPos, yPos + 210);

				if (playerGameOff[ActiveUsers[i]].PieceSelect.getTexture() != nullptr) {

					playerGameOff[ActiveUsers[i]].PieceSelect.setScale(2.0f, 2.0f);
					sf::FloatRect pieceSelectBounds = playerGameOff[ActiveUsers[i]].PieceSelect.getGlobalBounds();
					playerGameOff[ActiveUsers[i]].PieceSelect.setOrigin(pieceSelectBounds.width / 2.0f, pieceSelectBounds.height / 2.0f);
					std::cout << "\npiece: " << pieceSelectBounds.width / 2.0f << "," << pieceSelectBounds.height / 2.0f;
					
				}
				
				window->draw(playerGameOff[ActiveUsers[i]].NamePlayer);
				window->draw(playerGameOff[ActiveUsers[i]].boxPlayer);
				window->draw(playerGameOff[ActiveUsers[i]].AvatarPlayer);
				window->draw(playerGameOff[ActiveUsers[i]].MarcoPlayer);
				window->draw(playerGameOff[ActiveUsers[i]].Money);
				window->draw(playerGameOff[ActiveUsers[i]].PieceSelect);
			}
		}
		
		for(int i=0;i<ActiveUsers.size();i++){
		// Dibujar los elementos en la ventana
		window->draw(playerGameOff[i].NamePlayer);
		window->draw(playerGameOff[i].boxPlayer);
		window->draw(playerGameOff[i].AvatarPlayer);
		window->draw(playerGameOff[i].MarcoPlayer);
		window->draw(playerGameOff[i].Money);
		window->draw(playerGameOff[i].PieceSelect);
		window->draw(posicionesGanadores[i]);
		}
			
		window->draw(fingame12);


		window->display();

	}
}
		




