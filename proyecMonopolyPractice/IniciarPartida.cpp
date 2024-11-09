#include "IniciarPartida.hpp"
#include "ObjetosGlobal.hpp"
#include "ButtonG.hpp"
#include "TextBox.hpp"
#include "MensageBox.hpp"

IniciarPartida::IniciarPartida(sf::RenderWindow& win) : window(&win), pieceselector(window) {
	loadResourceGame();
	resource();
}

void IniciarPartida::resource() {
	TextureCrearPartidaOff.loadFromFile("resource/texture/Game/CrearPartidaOff.png");
	TextureCrearPartidaOn.loadFromFile("resource/texture/Game/CrearPartidaOn.png");
	TextureUnirse.loadFromFile("resource/texture/Game/unirse1encendido.png");

	TextureUnirsePartidaOff.loadFromFile("resource/texture/Game/UnirsePartidaOff.png");
	TextureUnirsePartidaOn.loadFromFile("resource/texture/Game/UnirsePartidaOn.png");

	SpriteCrearPartida.setTexture(TextureCrearPartidaOff);
	SpriteUnirse.setTexture(TextureUnirse);
	SpriteCrearPartida.setOrigin(150, 59);
	SpriteUnirse.setOrigin(100, 100);
	SpriteCrearPartida.setPosition(640, 300);
	SpriteUnirse.setPosition(640, 500);

	SpriteUnirsePartida.setTexture(TextureUnirsePartidaOff);
	SpriteUnirsePartida.setOrigin(150, 59);
	SpriteUnirsePartida.setPosition(640, 500);


	enunciado.setCharacterSize(40);
	enunciado.setFont(fontUser);
	enunciado.setFillColor(sf::Color::White);
	enunciado.setOutlineThickness(2);
	enunciado.setOutlineColor(sf::Color(135, 135, 135));
	enunciado.setString("Iniciar Partida");
	enunciado.setPosition(640, 100);
	sf::FloatRect globalBounds = enunciado.getGlobalBounds();
	enunciado.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
	NumPlayers = 1;
}



void IniciarPartida::update() {
	Valida = false;
	MensageBox message("   Error al conectar  \n    con el servidor", fontUser, 12);

	ButtonG botonCrearPartida(SpriteCrearPartida, TextureCrearPartidaOff, TextureCrearPartidaOn);
	ButtonG botonUnirsePartida(SpriteUnirsePartida, TextureUnirsePartidaOff, TextureUnirsePartidaOn);
	playerInfos[0].username = input1;
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
				renderTexture.draw(SpriteCrearPartida);
				renderTexture.draw(SpriteUnirsePartida);
				renderTexture.draw(enunciado);



				renderTexture.draw(spriteX);
				renderTexture.draw(overlay);
				Menup.MenuSalir();
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				if (SpriteUnirsePartida.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					updatejoinRoom();
					Valida = false;
					std::cout << "haaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

				}

				if (SpriteCrearPartida.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();

					client.initialize();
					client.connectToServer("208.68.36.50", 1234);
					Code = client.createRoom(playerInfos[0].username);
					std::cout << Code;

					pieceselector.Resource();
					pieceselector.updateSelection();

					//    message.showMessage();  // Muestra el mensaje al iniciar el programa


				}

				if (spriteX.getGlobalBounds().contains(mousePosFloat) && Valida == true) {
					playClickSound();
					valida2 = true;
					std::cout << "haaaaaaaaaaaaaaaaaaaa2aaaaaaaaa";
				}


			}
		}

		Valida = true;

		currentCursor = &normalCursor;
		botonCrearPartida.update(mousePosFloat, currentCursor, linkCursor, normalCursor);
		botonUnirsePartida.update(mousePosFloat, currentCursor, linkCursor, normalCursor);
		botonX->update(mousePosFloat, currentCursor, linkCursor, normalCursor);

		window->setMouseCursor(*currentCursor);

		// Actualiza el estado del MessageBox
		message.update();



		// Dibuja el MessageBox si está visible


		window->clear();
		window->draw(spriteFondoGame);
		window->draw(SpriteUnirsePartida);
		window->draw(enunciado);
		window->draw(spriteX);
		window->draw(SpriteCrearPartida);
		message.draw(*window);
		window->display();
	}
}

void IniciarPartida::updatejoinRoom() {
	std::string code;
	bool Valida1 = false;
	TextBox textBoxRoom(496, 80, "Ingresa el codigo: ");
	textBoxRoom.setPosition();
	MensageBox message("   Error al conectar  \n    con el servidor", fontUser, 12);
	MensageBox messageInvalido("   Por favor, introduce un código válido de 5 caracteres.", fontUser, 12);

	while (window->isOpen() && !Valida1) {
		sf::Event event1;
		mousePosition = sf::Mouse::getPosition(*window);
		mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

		while (window->pollEvent(event1)) {
			if (event1.type == sf::Event::Closed ||
				(event1.type == sf::Event::KeyPressed && event1.key.code == sf::Keyboard::Escape)) {

				renderTexture.clear();
				renderTexture.draw(spriteFondoGame);
				renderTexture.draw(SpriteUnirse);
				textBoxRoom.Prinf();  // Dibujar el cuadro de texto en la ventana


				renderTexture.draw(spriteX);
				renderTexture.draw(overlay);
				Menup.MenuSalir();



			}

			if (event1.type == sf::Event::MouseButtonPressed && event1.mouseButton.button == sf::Mouse::Left) {
				if (SpriteUnirse.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();

					// Desconectar solo si ya está conectado
					if (client.isConnected) {
						client.disconnect();
					}

					// Inicializar solo si no se ha creado el cliente
					if (!client.client) {
						client.initialize();
					}

					code = textBoxRoom.Actu();

					client.connectToServer("208.68.36.50", 1234);

					client.joinRoom(code, playerInfos[0].username);
					Code = code;

					pieceselector.Resource();
					pieceselector.updateSelection();


				}


				if (spriteX.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					Valida1 = true;
				}
			}

			textBoxRoom.handleInput(event1, 5);
		}

		currentCursor = &normalCursor;
		botonX->update(mousePosFloat, currentCursor, linkCursor, normalCursor);
		message.update();
		messageInvalido.update();

		window->setMouseCursor(*currentCursor);

		window->clear();
		window->draw(spriteFondoGame);
		window->draw(spriteX);

		window->draw(SpriteUnirse);
		textBoxRoom.draw(*window);
		message.draw(*window);
		messageInvalido.draw(*window);
		window->display();
	}

}
