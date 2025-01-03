#include "Chat.hpp"
#include "ObjetosGlobal.hpp"
#include "ButtonG.hpp"
#include "TextBox.hpp"
#include "MensageBox.hpp"

Chat::Chat(sf::RenderWindow& win) : window(&win), pieceselector(window) {
	loadResourceGame();
	resource();
}

void Chat::resource() {
	TextureCrearPartidaOff.loadFromFile("resource/texture/Game/CrearPartidaOff.png");
	TextureCrearPartidaOn.loadFromFile("resource/texture/Game/CrearPartidaOn.png");
	TextureUnirse.loadFromFile("resource/texture/Game/unirse1encendido.png");
	TextureBotonEviar.loadFromFile("envio2.png");

	TextureUnirsePartidaOff.loadFromFile("resource/texture/Game/UnirsePartidaOff.png");
	TextureUnirsePartidaOn.loadFromFile("resource/texture/Game/UnirsePartidaOn.png");
	if (!TextureCash.loadFromFile("resource/texture/Game/cash.png")) return;
	
	SpriteCrearPartida.setTexture(TextureCrearPartidaOff);
	SpriteUnirse.setTexture(TextureUnirse);
	SpriteCrearPartida.setOrigin(150, 59);
	SpriteUnirse.setOrigin(100, 100);
	SpriteCrearPartida.setPosition(640, 300);
	SpriteUnirse.setPosition(640, 500);

	SpriteUnirsePartida.setTexture(TextureUnirsePartidaOff);
	SpriteUnirsePartida.setOrigin(150, 59);
	SpriteUnirsePartida.setPosition(640, 500);

	SpriteBotonEnviar.setTexture(TextureBotonEviar);
	SpriteBotonEnviar.setOrigin(20, 20);
	SpriteBotonEnviar.setPosition(1245, 675);

	spriteX.setPosition(1240, 35);

	nameUser = input1;
	std::cout << "\nnameUser: " + nameUser;
	enunciado.setCharacterSize(20);
	enunciado.setFont(fontUser);
	enunciado.setFillColor(sf::Color::White);
	enunciado.setOutlineThickness(2);
	enunciado.setOutlineColor(sf::Color(135, 135, 135));
	enunciado.setString("CHAT");
	enunciado.setPosition(1090, 35);
	sf::FloatRect globalBounds = enunciado.getGlobalBounds();
	enunciado.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);


	indicacion.setCharacterSize(20);
	indicacion.setFont(fontUser);
	indicacion.setFillColor(sf::Color::White);
	indicacion.setOutlineThickness(2);
	indicacion.setOutlineColor(sf::Color(135, 135, 135));
	indicacion.setString("Ingrese texto.");
	indicacion.setPosition(940, 668);
	 globalBounds = indicacion.getGlobalBounds();
	indicacion.setOrigin(0, globalBounds.height / 2.0f);

	Fondo.setOrigin(0,0);
	Fondo.setSize( sf::Vector2f  (380, 720));
	Fondo.setPosition(900, 0);
	Fondo.setFillColor(sf::Color(60,60,60));
	Fondo.setOutlineThickness(-10);
	Fondo.setOutlineColor(sf::Color(50,50,50));

	FondoChat.setOrigin(0, 0);
	FondoChat.setSize(sf::Vector2f(100, 40));
	FondoChat.setPosition(1040, 20);
	FondoChat.setFillColor(sf::Color(50, 50, 50));

	Caja.setOrigin(0, 0);
	Caja.setSize(sf::Vector2f(260, 40));
	Caja.setPosition(940, 650);
	Caja.setFillColor(sf::Color (50, 50, 50));
	
	Derecha.setOrigin(20, 20);
	Derecha.setRadius(20);
	Derecha.setFillColor(sf::Color (50,50,50));
	Derecha.setPosition(1200, 670);

	Izquierda.setOrigin(20, 20);
	Izquierda.setRadius(20);
	Izquierda.setFillColor(sf::Color (50, 50, 50));
	Izquierda.setPosition(940, 670);

}



void Chat::update() {
	Valida = false;
	MensageBox message("   Error al conectar  \n    con el servidor", fontUser, 12);

	ButtonG botonCrearPartida(SpriteCrearPartida, TextureCrearPartidaOff, TextureCrearPartidaOn);
	ButtonG botonUnirsePartida(SpriteUnirsePartida, TextureUnirsePartidaOff, TextureUnirsePartidaOn);



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
				renderTexture.draw(indicacion);



				renderTexture.draw(spriteX);
				renderTexture.draw(overlay);
				Menup.MenuSalir();
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				if (SpriteUnirsePartida.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
			
					Valida = false;
					//					////////////////////////////////////////std::cout << "haaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

				}

				if (SpriteCrearPartida.getGlobalBounds().contains(mousePosFloat)) {
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
		botonCrearPartida.update(mousePosFloat, currentCursor, linkCursor, normalCursor);
		botonUnirsePartida.update(mousePosFloat, currentCursor, linkCursor, normalCursor);
		botonX->update(mousePosFloat, currentCursor, linkCursor, normalCursor);

		window->setMouseCursor(*currentCursor);


		message.update();


		renderTexture.clear();

		renderTexture.draw(spriteFondoGame);
		renderTexture.draw(spriteMapa);
		for (int i = 0; i < UsuariosActivos.size(); i++)
		{
			renderTexture.draw(playersGame[UsuariosActivos[i]].NamePlayer);
			renderTexture.draw(playersGame[UsuariosActivos[i]].boxPlayer);
			renderTexture.draw(playersGame[UsuariosActivos[i]].AvatarPlayer);
			renderTexture.draw(playersGame[UsuariosActivos[i]].MarcoPlayer);
		}
		renderTexture.draw(overlay);

		renderTexture.display();

		renderedSprite.setTexture(renderTexture.getTexture());


		window->clear();
		window->draw(renderedSprite);
		window->draw(Fondo);
		window->draw(Caja);
		window->draw(FondoChat);
		window->draw(SpriteBotonEnviar);
		window->draw(Derecha);
		window->draw(Izquierda);
		window->draw(SpriteUnirsePartida);
		window->draw(enunciado);
		window->draw(indicacion);
		window->draw(spriteX);
		window->draw(SpriteCrearPartida);
		window->display();


	}
}

