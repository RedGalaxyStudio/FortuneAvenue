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
	fingame12.setString("Fin de la Partida");
	//fingame12.setPosition(640,100);
	//s//f::FloatRect globalBounds = fingame12.getGlobalBounds();
	//fingame12.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
	fingame12.setPosition(440, 70);

}

void GameEnd::update() {
	while (window->isOpen()) {


		sf::Event event;

		while (window->pollEvent(event)) {


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

		window->draw(fingame12);




		float perfilWidth = 200.0f; // Ancho estimado para cada perfil
		float separacion = 20.0f;   // Espaciado entre perfiles
		int totalPerfiles = UsuariosActivos.size();      // Número total de perfiles

		// Ancho total ocupado por los perfiles y separaciones
		float totalWidth = (totalPerfiles * perfilWidth) + ((totalPerfiles - 1) * separacion);

		// Calcular el punto inicial en X para centrar los perfiles horizontalmente
		float startX = ((1280.0f - totalWidth) / 2.0f) + 100;

		// Posición Y fija para centrar verticalmente
		float startY = (720.0f - (180.0f + 70.0f + 50.0f)) / 2.0f; // Ajusta según las alturas estimadas



		if (totalPerfiles > 0) {
			// Calcular ancho total ocupado por perfiles y separaciones
			float totalWidth = (totalPerfiles * perfilWidth) + ((totalPerfiles - 1) * separacion);

			// Calcular inicio X para centrar los perfiles horizontalmente
			float startX = (1280.0f - totalWidth) / 2.0f + (perfilWidth / 2.0f); // Desplaza para centrar el origen

			float startY = 100.0f; // Centrado verticalmente

			for (int i = 0; i < totalPerfiles; i++) {
				float xPos = startX + i * (perfilWidth + separacion); // Calcula la posición en X para cada perfil
				float yPos = startY;

				// Posicionar elementos
				playersGame[UsuariosActivos[i]].NamePlayer.setPosition(xPos, startY+170);
				playersGame[UsuariosActivos[i]].boxPlayer.setPosition(xPos, startY+170);
				//playersGame[UsuariosActivos[i]].PieceSelect.setPosition(xPos+ 30, startY + 330);
				playersGame[UsuariosActivos[i]].AvatarPlayer.setPosition(xPos, yPos+100);
				playersGame[UsuariosActivos[i]].AvatarPlayer.setScale(1,1);
				playersGame[UsuariosActivos[i]].MarcoPlayer.setPosition(xPos, yPos+100);

				if (playersGame[UsuariosActivos[i]].PieceSelect.getTexture() != nullptr) {
					playersGame[UsuariosActivos[i]].PieceSelect.setScale(2.0f, 2.0f);
					sf::FloatRect pieceSelectBounds = playersGame[UsuariosActivos[i]].PieceSelect.getGlobalBounds();
					playersGame[UsuariosActivos[i]].PieceSelect.setOrigin(pieceSelectBounds.width / 2.0f, pieceSelectBounds.height / 2.0f);
					playersGame[UsuariosActivos[i]].PieceSelect.setPosition(xPos + (pieceSelectBounds.width / 2.0f), startY + 310);
				}

				// Centrar Money
				sf::FloatRect moneyBounds = playersGame[i].Money.getGlobalBounds();
				playersGame[UsuariosActivos[i]].Money.setOrigin(moneyBounds.width / 2.0f, moneyBounds.height / 2.0f);
				playersGame[UsuariosActivos[i]].Money.setPosition(xPos, yPos + 210);

				if (playersGame[UsuariosActivos[i]].PieceSelect.getTexture() != nullptr) {
					// Configurar escala primero
					playersGame[UsuariosActivos[i]].PieceSelect.setScale(2.0f, 2.0f);

					// Calcular origen tras escala
					sf::FloatRect pieceSelectBounds = playersGame[UsuariosActivos[i]].PieceSelect.getGlobalBounds();
					playersGame[UsuariosActivos[i]].PieceSelect.setOrigin(pieceSelectBounds.width / 2.0f, pieceSelectBounds.height / 2.0f);
					std::cout << "\npiece: " << pieceSelectBounds.width / 2.0f << "," << pieceSelectBounds.height / 2.0f;
					// Posicionar el objeto centrado
					
				}
				
				// Dibujar los elementos en la ventana
				window->draw(playersGame[UsuariosActivos[i]].NamePlayer);
				window->draw(playersGame[UsuariosActivos[i]].boxPlayer);
				window->draw(playersGame[UsuariosActivos[i]].AvatarPlayer);
				window->draw(playersGame[UsuariosActivos[i]].MarcoPlayer);
				window->draw(playersGame[UsuariosActivos[i]].Money);
				window->draw(playersGame[UsuariosActivos[i]].PieceSelect);
			}
		}


		window->display();

	}
}
		




