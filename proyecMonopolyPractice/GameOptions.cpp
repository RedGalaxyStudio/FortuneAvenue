#include "GameOptions.hpp"
#include "ObjetosGlobal.hpp"
#include "ButtonG.hpp"
#include "TextBox.hpp"
#include "MensageBox.hpp"

GameOptions::GameOptions(sf::RenderWindow& win) : window(&win), pieceselector(window) {
	loadResourceGame();
	resource();
}

void GameOptions::resource() {
	if (!TextureflecDerecha.loadFromFile("resource/texture/Button/flechaOpcder.png")) return;
	if (!TextureflecIzquier.loadFromFile("resource/texture/Button/flechaOpcizq.png")) return;

	
	SpriteflecDerecha.setTexture(TextureflecDerecha);
	SpriteflecIzquier.setTexture(TextureflecIzquier);

	SpriteflecIzquier.setPosition(500, 300);
	SpriteflecDerecha.setPosition(760, 300);


	TPlayers.setCharacterSize(26);
	TPlayers.setFont(fontUser);
	TPlayers.setFillColor(sf::Color::White);
	TPlayers.setOutlineThickness(2);
	TPlayers.setOutlineColor(sf::Color(135, 135, 135));
	TPlayers.setString("Cantidad de jugadores");
	TPlayers.setPosition(640, 250);
	sf::FloatRect globalBounds = TPlayers.getGlobalBounds();
	TPlayers.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	TMapas.setCharacterSize(20);
	TMapas.setFont(fontUser);
	TMapas.setFillColor(sf::Color::White);
	TMapas.setOutlineThickness(2);
	TMapas.setOutlineColor(sf::Color(135, 135, 135));
	TMapas.setString("Mapas");
	TMapas.setPosition(640, 400);
	globalBounds = TMapas.getGlobalBounds();
	TMapas.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);



	nameUser = input1;
	std::cout << "\nnameUser: " + nameUser;
	TOpcion.setCharacterSize(30);
	TOpcion.setFont(fontUser);
	TOpcion.setFillColor(sf::Color::White);
	TOpcion.setOutlineThickness(2);
	TOpcion.setOutlineColor(sf::Color(135, 135, 135));
	TOpcion.setString("Opciones");
	TOpcion.setPosition(640, 100);
	 globalBounds = TOpcion.getGlobalBounds();
	TOpcion.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
	//NumPlayers = 1;
}



void GameOptions::update() {
	Valida = false;
	MensageBox message("   Error al conectar  \n    con el servidor", fontUser, 12);

	bool valida2 = false;
	while (window->isOpen() && !valida2) {
		sf::Event event;
		mousePosition = sf::Mouse::getPosition(*window);
		mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
				renderTexture.clear();
				renderTexture.draw(spriteFondoGame);
				renderTexture.draw(TOpcion);



				renderTexture.draw(spriteX);
				renderTexture.draw(overlay);
				Menup.MenuSalir();
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				if (SpriteflecIzquier.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
			
					Valida = false;

				}

				if (SpriteflecDerecha.getGlobalBounds().contains(mousePosFloat)) {
					if (LimTimeBotton.getElapsedTime().asSeconds() >= 1.0f) { // Verifica si ha pasado al menos 1 segundo
						// Reinicia el reloj
						LimTimeBotton.restart();
						playClickSound();

						client.initialize();
						if (true == client.connectToServer("208.68.36.50", 1234)) {
							Code = client.createRoom(nameUser, TextureAvatarPath);

							pieceselector.Resource();
							pieceselector.updateSelection();
						}
						else
						{
							message.showMessage();
						}

					}

				}

				if (spriteX.getGlobalBounds().contains(mousePosFloat) && Valida == true) {
					playClickSound();
					valida2 = true;

				}


			}
		}

		Valida = true;

		currentCursor = &normalCursor;
		botonX->update(mousePosFloat, currentCursor, linkCursor, normalCursor);

		window->setMouseCursor(*currentCursor);


		message.update();






		window->clear();
		window->draw(spriteFondoGame);
		window->draw(TOpcion);
		window->draw(spriteX);
		window->draw(SpriteflecDerecha);
		window->draw(SpriteflecIzquier);
		window->draw(TPlayers);
		window->draw(TMapas);
		
		message.draw(*window);
		window->display();
	}
}