#include "GameOptionsO.hpp"
#include "../../core/ObjetosGlobal.hpp"
#include "../../ui/ButtonG.hpp"
#include "../../ui/TextBox.hpp"
#include "../../ui/MensageBox.hpp"
#include "PieceSelectorO.hpp"
#include "../../ui/ResourceGeneral.hpp"

GameOptions::GameOptions(sf::RenderWindow& win) : window(&win) {
	loadResourceGame();
	resource();
}

void GameOptions::resource() {

	TPlayers.setCharacterSize(26);
	TPlayers.setFont(fontUser);
	TPlayers.setFillColor(sf::Color::White);
	TPlayers.setOutlineThickness(2);
	TPlayers.setOutlineColor(sf::Color(135, 135, 135));
	TPlayers.setString("Cantidad de jugadores");
	TPlayers.setPosition(640, 136);
	sf::FloatRect globalBounds = TPlayers.getGlobalBounds();
	TPlayers.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
	if (!TextureflecDerecha.loadFromFile("assets/image/Button/flechaOpcder.png")) return;
	if (!TextureflecIzquier.loadFromFile("assets/image/Button/flechaOpcizq.png")) return;
	if (!TextureMapaS.loadFromFile("assets/image/Game/mapaSop.png"))return;
	if (!TextureMapaSM.loadFromFile("assets/image/Game/mapaSopM.png")) return;
	if (!TextureMapa.loadFromFile("assets/image/Game/mapa+S+++.png")) return;
	if (!TextureMapa2.loadFromFile("assets/image/Game/mapa1L.png"))return;
	if (!TextureMapa3.loadFromFile("assets/image/Game/mapa22l.png")) return;
	SpriteMapaS.setTexture(TextureMapaS);
	globalBounds = SpriteMapaS.getGlobalBounds();
	SpriteMapaS.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	SpriteMapaS.setPosition(640, 460);
	SpriteflecDerecha.setTexture(TextureflecDerecha);
	SpriteflecIzquier.setTexture(TextureflecIzquier);

	if (!TextureMapa22.loadFromFile("assets/image/Game/mapa22m.png")) return;
	if (!TextureMapa22M.loadFromFile("assets/image/Game/mapa22mM.png")) return;


	if (!TextureMapa22.loadFromFile("assets/image/Game/mapa22m.png")) return;
	if (!TextureMapa22M.loadFromFile("assets/image/Game/mapa22mM.png")) return;

	SpriteMapa22.setTexture(TextureMapa22);
	globalBounds = SpriteMapa22.getGlobalBounds();
	SpriteMapa22.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	SpriteMapa22.setPosition(360, 460);
	borde1.setFillColor(sf::Color::Transparent);
	borde1.setOutlineColor(sf::Color::White);
	borde1.setOutlineThickness(6);
	borde2.setFillColor(sf::Color::Transparent);
	borde2.setOutlineColor(sf::Color::White);
	borde2.setOutlineThickness(6);
	borde3.setFillColor(sf::Color::Transparent);
	borde3.setOutlineColor(sf::Color::White);
	borde3.setOutlineThickness(6);

	Maximo = sf::Vector2f(280.f, 280.f);
	Minimo = sf::Vector2f(240.f, 240.f);
	borde1.setSize(Minimo);
	borde2.setSize(Minimo);
	borde3.setSize(Minimo);


	globalBounds = borde1.getGlobalBounds();
	borde1.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	globalBounds = borde2.getGlobalBounds();
	borde2.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	globalBounds = borde3.getGlobalBounds();
	borde3.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	if (!TextureMapa1.loadFromFile("assets/image/Game/mapa1.png")) return;
	if (!TextureMapa1M.loadFromFile("assets/image/Game/mapa1M.png")) return
		SpriteMapa1.setTexture(TextureMapa1);
	globalBounds = SpriteMapa22.getGlobalBounds();
	SpriteMapa1.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	SpriteMapa1.setPosition(920, 460);
	borde3.setPosition(920, 465);
	borde2.setPosition(640, 465);
	borde1.setPosition(360, 465);
	SpriteflecIzquier.setPosition(540, 210);
	SpriteflecDerecha.setPosition(740, 210);
	globalBounds = SpriteflecIzquier.getGlobalBounds();
	SpriteflecIzquier.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
	globalBounds = SpriteflecDerecha.getGlobalBounds();
	SpriteflecDerecha.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	if (!TextureCrear.loadFromFile("assets/image/Button/crearchiquito.png")) return;
	SpriteCrear.setTexture(TextureCrear);
	SpriteCrear.setOrigin(640, 545);
	SpriteCrear.setPosition(1170, 1153);

	if (!TextureRectangle.loadFromFile("assets/image/Button/rectanguloEncendido.png")) return;

	SpriteCrear.setPosition(1170, 1153);

	if (!TextureRectangle.loadFromFile("assets/image/Button/rectanguloEncendido.png")) return;

	SpriteRectangle.setTexture(TextureRectangle);
	SpriteRectangle.setOrigin(640, 545);
	SpriteRectangle.setPosition(1153, 568);

	TMapas.setCharacterSize(30);
	TMapas.setFont(fontUser);
	TMapas.setFillColor(sf::Color::White);
	TMapas.setOutlineThickness(2);
	TMapas.setOutlineColor(sf::Color(135, 135, 135));
	TMapas.setString("Mapas");
	TMapas.setPosition(643, 280);
	globalBounds = TMapas.getGlobalBounds();
	TMapas.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	cantUser.setCharacterSize(50);
	cantUser.setFont(fontUser);
	cantUser.setFillColor(sf::Color::White);
	cantUser.setOutlineThickness(2);
	cantUser.setOutlineColor(sf::Color(135, 135, 135));
	cantUser.setString(std::to_string(CantNum));
	cantUser.setPosition(640, 200);
	globalBounds = cantUser.getGlobalBounds();
	cantUser.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	namePlayer = input1;
	TOpcion.setCharacterSize(30);
	TOpcion.setFont(fontUser);
	TOpcion.setFillColor(sf::Color::White);
	TOpcion.setOutlineThickness(2);
	TOpcion.setOutlineColor(sf::Color(135, 135, 135));
	TOpcion.setString("Opciones");
	TOpcion.setPosition(640, 60);
	globalBounds = TOpcion.getGlobalBounds();
	TOpcion.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);


}
void GameOptions::update() {
	Valida = false;
	bool valida2 = false;

	ButtonG MapaS(SpriteMapaS, TextureMapaS, TextureMapaSM, borde2, Minimo, Maximo);
	ButtonG Mapa22(SpriteMapa22, TextureMapa22, TextureMapa22M, borde1, Minimo, Maximo);
	ButtonG Mapa11(SpriteMapa1, TextureMapa1, TextureMapa1M, borde3, Minimo, Maximo);
	bool Mapa1{ false }, Mapa2{ false }, Mapa3{ false };
	int Map=-1;
	while (window->isOpen() && !valida2) {
		sf::Event event;
		mousePosition = sf::Mouse::getPosition(*window);
		mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

		while (window->pollEvent(event)) {

			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
				renderTexture.clear();
				renderTexture.draw(spriteBackgroundG);
				renderTexture.draw(TOpcion);
				renderTexture.draw(spriteX);
				renderTexture.draw(overlay);
				Menup.MenuSalir(nullptr);
			}


			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				if (SpriteflecIzquier.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					if (CantNum > 2) {
						CantNum --;
						cantUser.setString(std::to_string(CantNum));
					}
				}
				if (SpriteflecDerecha.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					if (CantNum < 4) {
						CantNum ++;
						cantUser.setString(std::to_string(CantNum));
					}
				}

				if (spriteX.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					valida2 = true;
				}

				if (SpriteMapaS.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					SpriteMapaS.setTexture(TextureMapaSM);
					std::cout << "hola entre";

					Mapa1 = true;
					Mapa2 = false;
					Mapa3 = false;
					Map = 1;

				}
				else if (SpriteMapa22.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					SpriteMapa22.setTexture(TextureMapa22M);
					Mapa1 = false;
					Mapa2 = true;
					Mapa3 = false;
					Map = 2;
				}
				else if (SpriteMapa1.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					SpriteMapa1.setTexture(TextureMapa1M);
					Mapa1 = false;
					Mapa2 = false;
					Mapa3 = true;
					Map = 3;
				}

				if (SpriteCrear.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					PieceSelectOff pieceselectoff(window, CantNum,Map);
					pieceselectoff.Resource();
					pieceselectoff.updateSelection();

					pieceselectoff.~PieceSelectOff();
				}

			}
		}

		currentCursor = &normalCursor;
		botonX->update(mousePosFloat, currentCursor, linkCursor, normalCursor);
		MapaS.Update(mousePosFloat, currentCursor, linkCursor, normalCursor, Mapa1);
		Mapa22.Update(mousePosFloat, currentCursor, linkCursor, normalCursor, Mapa2);
		Mapa11.Update(mousePosFloat, currentCursor, linkCursor, normalCursor, Mapa3);

		window->setMouseCursor(*currentCursor);

		window->clear();
		window->draw(spriteBackgroundG);
		window->draw(TOpcion);
		window->draw(spriteX);
		window->draw(SpriteflecDerecha);
		window->draw(SpriteflecIzquier);
		window->draw(cantUser);
		window->draw(TPlayers);
		window->draw(TMapas);
		window->draw(SpriteMapaS);
		window->draw(SpriteMapa22);
		window->draw(SpriteMapa1);
		window->draw(borde1);
		window->draw(borde2);
		window->draw(borde3);
		window->draw(SpriteCrear);
		window->draw(SpriteRectangle);
		window->display();



	}
}
