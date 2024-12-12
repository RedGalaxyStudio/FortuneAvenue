#include "GameEnd.hpp"
#include <iostream>

// Constructor
GameEnd::GameEnd(sf::RenderWindow* window) : window(window) {

}

// Destructor
GameEnd::~GameEnd() {}


void GameEnd::resource() {
	fingame12.setCharacterSize(40);
	fingame12.setFont(fontUser);
	fingame12.setFillColor(sf::Color::White);
	fingame12.setOutlineThickness(2);
	fingame12.setOutlineColor(sf::Color(135, 135, 135));
	fingame12.setString("Fin de la partida");
	//fingame12.setPosition(640,100);
	//s//f::FloatRect globalBounds = fingame12.getGlobalBounds();
	//fingame12.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
	fingame12.setPosition(640, 100);

}
void GameEnd::update() {
	while (window->isOpen()) {

		
		sf::Event event;

		while (window->pollEvent(event)){
			
				
				sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
				sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

				if (event.type == sf::Event::Closed ||
					(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {

					renderTexture.clear();
					renderTexture.draw(spriteFondoGame);
					for (int i = 0; i < 4; i++) {
						renderTexture.draw(playersGame[i].NamePlayer);
						renderTexture.draw(playersGame[i].boxPlayer);
						renderTexture.draw(playersGame[i].MarcoPlayer);
						renderTexture.draw(playersGame[i].AvatarPlayer);
					}
					renderTexture.draw(spriteX);
					renderTexture.draw(overlay);

					Menup.MenuSalir();
				}

				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
					//if (Settings.getGlobalBounds().contains(mousePosFloat)) {
						playClickSound();
					//	Menup.MenuOpcion();
				//	}
					
				}
			

		}   // Asegura que el bucle se repita mientras haya eventos pendientes
		
		window->setMouseCursor(*currentCursor);

		
		window->clear();

		window->draw(spriteFondoGame);

		
		
		float perfilWidth = 200.0f; // Ancho estimado para cada perfil
		float separacion = 20.0f;   // Espaciado entre perfiles
		int totalPerfiles = 4;      // Número total de perfiles

		// Ancho total ocupado por los perfiles y separaciones
		float totalWidth = (totalPerfiles * perfilWidth) + ((totalPerfiles - 1) * separacion);

		// Calcular el punto inicial en X para centrar los perfiles horizontalmente
		float startX = ((1280.0f - totalWidth) / 2.0f) +100 ;

		// Posición Y fija para centrar verticalmente
		float startY = (720.0f - (180.0f + 70.0f + 50.0f)) / 2.0f; // Ajusta según las alturas estimadas

		for (int i = 0; i < totalPerfiles; i++) {
			float xPos = startX + i * (perfilWidth + separacion); // Calcula la posición en X para cada perfil
			float yPos = startY;                                 // Calcula la posición en Y para centrar

			// Ajustar las posiciones de los elementos del perfil
			playersGame[i].NamePlayer.setPosition(xPos, yPos + 70);
			playersGame[i].boxPlayer.setPosition(xPos, yPos + 70);
			playersGame[i].AvatarPlayer.setPosition(xPos, yPos);
			playersGame[i].MarcoPlayer.setPosition(xPos, yPos);

			// Asegúrate de que PieceSelect tenga textura y escala configurada
			if (playersGame[i].PieceSelect.getTexture() != nullptr) {
				// Configurar escala primero
				playersGame[i].PieceSelect.setScale(2.0f, 2.0f);

				// Calcular origen tras escala
				sf::FloatRect pieceSelectBounds = playersGame[i].PieceSelect.getGlobalBounds();
				playersGame[i].PieceSelect.setOrigin(pieceSelectBounds.width / 2.0f, pieceSelectBounds.height / 2.0f);
				std::cout << "\npiece: " << pieceSelectBounds.width / 2.0f<< "," << pieceSelectBounds.height / 2.0f;
				// Posicionar el objeto centrado
				playersGame[i].PieceSelect.setPosition(xPos + (pieceSelectBounds.width / 2.0f), yPos + 240);
			}
			else {
			
				playersGame[i].PieceSelect.setPosition(0, 0);
			}

			// Centrar Money
			sf::FloatRect moneyBounds = playersGame[i].Money.getGlobalBounds();
			playersGame[i].Money.setOrigin(moneyBounds.width / 2.0f, moneyBounds.height / 2.0f);
			playersGame[i].Money.setPosition(xPos, yPos + 140);

			// Dibujar los elementos en la ventana
			window->draw(playersGame[i].NamePlayer);
			window->draw(playersGame[i].boxPlayer);
			window->draw(playersGame[i].AvatarPlayer);
			window->draw(playersGame[i].MarcoPlayer);
			window->draw(playersGame[i].Money);
			window->draw(playersGame[i].PieceSelect);	
		}
		
			
		

		window->display();
		
	}
}


