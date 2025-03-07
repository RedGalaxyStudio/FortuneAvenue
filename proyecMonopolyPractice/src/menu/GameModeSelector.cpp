#include "GameModeSelector.hpp"
#include "../game/offiline/GameOptionsO.hpp"
#include "IniciarPartida.hpp"
#include "../core/ObjetosGlobal.hpp"
#include "../ui/ButtonG.hpp"
#include "../ui/TextBox.hpp"
#include "../ui/MensageBox.hpp"
#include "../ui/ResourceGeneral.hpp"

GameModeSelector::GameModeSelector(sf::RenderWindow& win) : window(&win) {
	resource();
}

void GameModeSelector::resource() {


	if (!TextureBackgroundG.loadFromFile("assets/image/Game/FondoGame2.jpg")) return;
	spriteBackgroundG.setTexture(TextureBackgroundG);
	TextureOfflineOff.loadFromFile("assets/image/MenuSelector/offline400.png");
	TextureOfflineOn.loadFromFile("assets/image/MenuSelector/offline400X.png");

	TextureOnlineOff.loadFromFile("assets/image/MenuSelector/online500.png");
	TextureOnlineOn.loadFromFile("assets/image/MenuSelector/online500X.png");

	SpriteOffline.setTexture(TextureOfflineOff);
	SpriteOffline.setOrigin(194.f, 233.5f);
	SpriteOffline.setPosition(840, 360);
	

	SpriteOnline.setTexture(TextureOnlineOff);
	SpriteOnline.setOrigin(193.5f, 233.f);
	SpriteOnline.setPosition(440, 360);

	enunciado.setCharacterSize(40);
	enunciado.setFont(fontUser);
	enunciado.setFillColor(sf::Color::White);
	enunciado.setOutlineThickness(2);
	enunciado.setOutlineColor(sf::Color(135, 135, 135));
	enunciado.setString("Modo de Juego");
	enunciado.setPosition(640, 100);
	sf::FloatRect globalBounds = enunciado.getGlobalBounds();
	enunciado.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

}



void GameModeSelector::update() {
	Valida = false;
	MensageBox message("   Error al conectar  \n    con el servidor", fontUser, 12);

	ButtonG botonOffline(SpriteOffline, TextureOfflineOff, TextureOfflineOn);
	ButtonG botonOnline(SpriteOnline, TextureOnlineOff, TextureOnlineOn);



	bool valida2 = false;
	while (window->isOpen() && !valida2) {
		sf::Event event;
		mousePosition = sf::Mouse::getPosition(*window);
		mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
				renderTexture.clear();
				renderTexture.draw(spriteBackgroundG);
				renderTexture.draw(SpriteOffline);
				renderTexture.draw(SpriteOnline);
				renderTexture.draw(enunciado);



				renderTexture.draw(spriteX);
				renderTexture.draw(overlay);
				Menup.MenuSalir(nullptr);
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				if (SpriteOnline.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
				



					IniciarPartida inicial(*window);
					inicial.update();

					box.setPosition(273, 74);

					Valida = false;
					
				}

				if (SpriteOffline.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					std::cout << "\n1";
					GameOptions partida(*window);
					std::cout << "\n1";
					partida.update();
					std::cout << "\n1";

					box.setPosition(273, 74);

				}

				if (spriteX.getGlobalBounds().contains(mousePosFloat) && Valida == true) {
					playClickSound();
					valida2 = true;

				}


			}
		}

		Valida = true;

		currentCursor = &normalCursor;
		botonOffline.update(mousePosFloat, currentCursor, linkCursor, normalCursor);
		botonOnline.update(mousePosFloat, currentCursor, linkCursor, normalCursor);
		botonX->update(mousePosFloat, currentCursor, linkCursor, normalCursor);

		window->setMouseCursor(*currentCursor);


		message.update();


		window->clear();
		window->draw(spriteBackgroundG);
		window->draw(SpriteOnline);
		window->draw(enunciado);
		window->draw(spriteX);
		window->draw(SpriteOffline);
		message.draw(*window);
		window->display();
	}
}

void GameModeSelector::updatejoinRoom() {
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
				renderTexture.draw(spriteBackgroundG);
			
				textBoxRoom.Prinf();


				renderTexture.draw(spriteX);
				renderTexture.draw(overlay);
				Menup.MenuSalir(nullptr);



			}

			if (event1.type == sf::Event::MouseButtonPressed && event1.mouseButton.button == sf::Mouse::Left) {
	
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
		window->draw(spriteBackgroundG);
		window->draw(spriteX);
;
		textBoxRoom.draw(*window);
		message.draw(*window);
		messageInvalido.draw(*window);
		window->display();
	}

}
