#include "GameEndO.hpp"
#include <iostream>
#include "../../core/ObjetosGlobal.hpp"
#include "../../ui/ResourceGeneral.hpp"
// Constructor
GameEndO::GameEndO(sf::RenderWindow* window) : window(window) {

}

// Destructor
GameEndO::~GameEndO() {}


void assignPositions(const std::vector<PlayerInformation>& players, std::vector<int>& positions) {
	// Crear un vector de índices
	std::vector<size_t> indices(players.size());
	for (size_t i = 0; i < players.size(); ++i) {
		indices[i] = i;
	}

	// Ordenar los índices según el puntaje de los jugadores
	std::sort(indices.begin(), indices.end(), [&players](size_t a, size_t b) {
		return players[a].money > players[b].money;
		});

	// Asignar posiciones respetando los empates
	int currentRank = 1; // El puesto actual
	int playersInSameRank = 0; // Cuántos jugadores están en el mismo puesto
	positions.resize(players.size(), 0);

	for (size_t i = 0; i < indices.size(); ++i) {
		if (i > 0 && players[indices[i]].money == players[indices[i - 1]].money) {
			// Si el puntaje es igual al anterior, comparten el mismo puesto
			positions[indices[i]] = currentRank;
			playersInSameRank++;
		}
		else {
			// Si no hay empate, asignar el nuevo puesto
			currentRank += playersInSameRank;
			positions[indices[i]] = currentRank;
			playersInSameRank = 1; // Reiniciar el contador de empates
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
	//fingame12.setPosition(640,100);
	//s//f::FloatRect globalBounds = fingame12.getGlobalBounds();
	//fingame12.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
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
		posicionesGanadores[i].setString(std::to_string(posiGndrs[i])+"°");
		sf::FloatRect globalBounds = posicionesGanadores[i].getGlobalBounds();
		posicionesGanadores[i].setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);



	}
}

void GameEndO::update() {

	float perfilWidth = 200.0f; // Ancho estimado para cada perfil
	float separacion = 20.0f;   // Espaciado entre perfiles
	int totalPerfiles = ActiveUsers.size();      // Número total de perfiles

	if (totalPerfiles > 0) {
		// Calcular ancho total ocupado por perfiles y separaciones
		float totalWidth = (totalPerfiles * perfilWidth) + ((totalPerfiles - 1) * separacion);

		// Calcular inicio X para centrar los perfiles horizontalmente
		float startX = (1280.0f - totalWidth) / 2.0f + (perfilWidth / 2.0f); // Desplaza para centrar el origen

		float startY = 290.f; // Centrado verticalmente

		for (int i = 0; i < totalPerfiles; i++) {
			float xPos = startX + i * (perfilWidth + separacion); // Calcula la posición en X para cada perfil
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
				//if (Settings.getGlobalBounds().contains(mousePosFloat)) {
				playClickSound();
				//	Menup.MenuOpcion();
			//	}

			}



				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
					//if (Settings.getGlobalBounds().contains(mousePosFloat)) {
						playClickSound();
	
					
				}
			


		}   // Asegura que el bucle se repita mientras haya eventos pendientes

		window->setMouseCursor(*currentCursor);


		window->clear();

		window->draw(spriteBackgroundG);


		window->draw(fingame12);




		float perfilWidth = 200.0f; // Ancho estimado para cada perfil
		float separacion = 20.0f;   // Espaciado entre perfiles
		int totalPerfiles = ActiveUsers.size();      // Número total de perfiles

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

				// Centrar Money
				sf::FloatRect moneyBounds = playerGameOff[i].Money.getGlobalBounds();
				playerGameOff[ActiveUsers[i]].Money.setOrigin(moneyBounds.width / 2.0f, moneyBounds.height / 2.0f);
				playerGameOff[ActiveUsers[i]].Money.setPosition(xPos, yPos + 210);

				if (playerGameOff[ActiveUsers[i]].PieceSelect.getTexture() != nullptr) {
					// Configurar escala primero
					playerGameOff[ActiveUsers[i]].PieceSelect.setScale(2.0f, 2.0f);

					// Calcular origen tras escala
					sf::FloatRect pieceSelectBounds = playerGameOff[ActiveUsers[i]].PieceSelect.getGlobalBounds();
					playerGameOff[ActiveUsers[i]].PieceSelect.setOrigin(pieceSelectBounds.width / 2.0f, pieceSelectBounds.height / 2.0f);
					std::cout << "\npiece: " << pieceSelectBounds.width / 2.0f << "," << pieceSelectBounds.height / 2.0f;
					// Posicionar el objeto centrado
					
				}
				
				// Dibujar los elementos en la ventana
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
		




