#include "IniciarPartida.hpp"
#include "../core/ObjetosGlobal.hpp"
#include "../ui/ButtonG.hpp"
#include "../ui/TextBox.hpp"
#include "../game/online/Chat.hpp"
#include "../ui/MensageBox.hpp"

IniciarPartida::IniciarPartida(sf::RenderWindow& win) : window(&win), client(new Client()) {
	
	loadResourceGame();
	resource();
}

void IniciarPartida::resource() {
	printMemoryUsage();
	TextureCrearPartidaOff.loadFromFile("assets/image/Game/CrearPartidaOff.png");
	TextureCrearPartidaOn.loadFromFile("assets/image/Game/CrearPartidaOn.png");
	TextureUnirse.loadFromFile("assets/image/Game/unirse1encendido.png");
	if (!CheckTexturesOn.loadFromFile("assets/image/Game/check1on.png")) return;
	if (!CheckTexturesOff.loadFromFile("assets/image/Game/check1off.png")) return;

	TextureUnirsePartidaOff.loadFromFile("assets/image/Game/UnirsePartidaOff.png");
	TextureUnirsePartidaOn.loadFromFile("assets/image/Game/UnirsePartidaOn.png");
	if (!TextureCash.loadFromFile("assets/image/Game/cash.png")) return;
	if (!TextureHome.loadFromFile("assets/image/Game/casa.png")) return;
	SpriteCrearPartida.setTexture(TextureCrearPartidaOff);
	SpriteUnirse.setTexture(TextureUnirse);
	SpriteCrearPartida.setOrigin(150, 59);
	SpriteUnirse.setOrigin(100, 100);
	SpriteCrearPartida.setPosition(640, 300);
	SpriteUnirse.setPosition(640, 500);

	SpriteUnirsePartida.setTexture(TextureUnirsePartidaOff);
	SpriteUnirsePartida.setOrigin(150, 59);
	SpriteUnirsePartida.setPosition(640, 500);

	nameUser = input1;
	std::cout << "\nnameUser: "+ nameUser;
	enunciado.setCharacterSize(40);
	enunciado.setFont(fontUser);
	enunciado.setFillColor(sf::Color::White);
	enunciado.setOutlineThickness(2);
	enunciado.setOutlineColor(sf::Color(135, 135, 135));
	enunciado.setString("Iniciar Partida");
	enunciado.setPosition(640, 100);
	sf::FloatRect globalBounds = enunciado.getGlobalBounds();
	enunciado.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
	//NumPlayers = 1;
}

void IniciarPartida::update() {
	Valida = false;
	MensageBox message("   Error al conectar  \n    con el servidor", fontUser, 12);
	
	ButtonG botonCrearPartida(SpriteCrearPartida, TextureCrearPartidaOff, TextureCrearPartidaOn);
	ButtonG botonUnirsePartida(SpriteUnirsePartida, TextureUnirsePartidaOff, TextureUnirsePartidaOn);


	int xPos=180;
	int startY=120;

	Sesion.setPosition(xPos, startY + 110);
	box.setPosition(xPos, startY + 110);
	selectedAvatarCopy.setPosition(xPos, startY);
	recua.setPosition(xPos, startY);
	printMemoryUsage();
	
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
				Menup.MenuSalir(nullptr);
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				if (SpriteUnirsePartida.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					updatejoinRoom();
					Valida = false;

				}

				if (SpriteCrearPartida.getGlobalBounds().contains(mousePosFloat)) {
					std::cout << "\nque mierda";
					if (LimTimeBotton.getElapsedTime().asSeconds() >= 1.0f) { // Verifica si ha pasado al menos 1 segundo
						std::cout << "\nque mierda";
						// Rcia el reloj
						LimTimeBotton.restart();
						std::cout << "\nque mierda2";
						playClickSound();
						std::cout << "\nque mierda3";


						client->initialize();
						std::cout << "\nque mierda4";
						Chat CHat(window,client);
						std::cout << "\nque mierda5";
						if (true == client->connectToServer("208.68.36.50", 1234)) {
							Code = client->createRoom(nameUser, TextureAvatarPath);


							std::cout << "\nque mierda";
							PieceSelector pieceselector(window, client);
							pieceselector.Resource();
							pieceselector.updateSelection();

							pieceselector.~PieceSelector();
							
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



	


		window->clear();
		window->draw(spriteFondoGame);
		window->draw(box);
		window->draw(Sesion);
		window->draw(selectedAvatarCopy);
		window->draw(recua);
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
	TextBox textBoxRoom(640, 80, "Ingresa el codigo: ");
	textBoxRoom.setPosition(505, 80);
	MensageBox message("   Error al conectar  \n    con el servidor", fontUser, 12);
	MensageBox messageInvalido("Codigo invalido", fontUser, 12);

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
				textBoxRoom.Prinf(); 


				renderTexture.draw(spriteX);
				renderTexture.draw(overlay);
				Menup.MenuSalir(client);



			}

			if (event1.type == sf::Event::MouseButtonPressed && event1.mouseButton.button == sf::Mouse::Left) {
				if (SpriteUnirse.getGlobalBounds().contains(mousePosFloat)) {
					if (LimTimeBotton.getElapsedTime().asSeconds() >= 1.0f) { // Verifica si ha pasado al menos 1 segundo
						// Reinicia el reloj
						LimTimeBotton.restart();
						playClickSound();
						code = textBoxRoom.Actu();
						if (code.length() == 5) {
							// Tiene exactamente 5 caracteres
							client->initialize();

							if (true == client->connectToServer("208.68.36.50", 1234)) {

								client->joinRoom(code, nameUser, TextureAvatarPath);
								Code = code;
								PieceSelector pieceselector(window,client);
								pieceselector.Resource();
								pieceselector.updateSelection();

								pieceselector.~PieceSelector();

							}
							else {
								message.showMessage();
							}
						}
						else {
							messageInvalido.showMessage();
							// No tiene 5 caracteres
						}

					}
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
