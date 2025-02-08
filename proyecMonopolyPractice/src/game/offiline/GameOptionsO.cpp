#include "GameOptionsO.hpp"
#include "../../core/ObjetosGlobal.hpp"
#include "../../ui/ButtonG.hpp"
#include "../../ui/TextBox.hpp"
#include "../../ui/MensageBox.hpp"
#include "PieceSelectorO.hpp"


GameOptions::GameOptions(sf::RenderWindow& win) : window(&win), pieceselector(window) {
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
	TPlayers.setPosition(640, 190);
	sf::FloatRect globalBounds = TPlayers.getGlobalBounds();
	TPlayers.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
	if (!TextureflecDerecha.loadFromFile("assets/image/Button/flechaOpcder.png")) return;
	if (!TextureflecIzquier.loadFromFile("assets/image/Button/flechaOpcizq.png")) return;
	if (!TextureMapaS.loadFromFile("assets/image/Game/mapaSop.png")) return;
	if (!TextureMapaSM.loadFromFile("assets/image/Game/mapaSopM.png")) return;
	if (!TextureMapa.loadFromFile("assets/image/Game/mapa+S+++.png")) return;
	if (!TextureMapa2.loadFromFile("assets/image/Game/mapa1L.png")) return;
	if (!TextureMapa3.loadFromFile("assets/image/Game/mapa22l.png")) return;
	SpriteMapaS.setTexture(TextureMapaS);
	globalBounds = SpriteMapaS.getGlobalBounds();
	SpriteMapaS.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	SpriteMapaS.setPosition(640, 550);
	SpriteflecDerecha.setTexture(TextureflecDerecha);
	SpriteflecIzquier.setTexture(TextureflecIzquier);
	
	if (!TextureMapa22.loadFromFile("assets/image/Game/mapa22m.png")) return;
	if (!TextureMapa22M.loadFromFile("assets/image/Game/mapa22mM.png")) return;
	SpriteMapa22.setTexture(TextureMapa22);
	globalBounds = SpriteMapa22.getGlobalBounds();
	SpriteMapa22.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	SpriteMapa22.setPosition(360, 550);
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
	Minimo=sf::Vector2f(240.f, 240.f);
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
	if (!TextureMapa1M.loadFromFile("assets/image/Game/mapa1M.png")) return;
	SpriteMapa1.setTexture(TextureMapa1);
	globalBounds = SpriteMapa22.getGlobalBounds();
	SpriteMapa1.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	SpriteMapa1.setPosition(920, 550);
	borde3.setPosition(920, 550);
	borde2.setPosition(640, 550);
	borde1.setPosition(360, 550);
	SpriteflecIzquier.setPosition(540, 280);
	SpriteflecDerecha.setPosition(740, 280);
	globalBounds = SpriteflecIzquier.getGlobalBounds();
	SpriteflecIzquier.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
	globalBounds = SpriteflecDerecha.getGlobalBounds();
	SpriteflecDerecha.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);





	if (!TextureCrear.loadFromFile("assets/image/Button/crearchiquito.png")) return;
	SpriteCrear.setTexture(TextureCrear);
	SpriteCrear.setOrigin(640, 545);
    SpriteCrear.setPosition(920, 550);
	

	TMapas.setCharacterSize(30);
	TMapas.setFont(fontUser);
	TMapas.setFillColor(sf::Color::White);
	TMapas.setOutlineThickness(2);
	TMapas.setOutlineColor(sf::Color(135, 135, 135));
	TMapas.setString("Mapas");
	TMapas.setPosition(640, 380);
	globalBounds = TMapas.getGlobalBounds();
	TMapas.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	cantUser.setCharacterSize(50);
	cantUser.setFont(fontUser);
	cantUser.setFillColor(sf::Color::White);
	cantUser.setOutlineThickness(2);
	cantUser.setOutlineColor(sf::Color(135, 135, 135));
	cantUser.setString(std::to_string(CantNum));
	cantUser.setPosition(640, 280);
	globalBounds = cantUser.getGlobalBounds();
	cantUser.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	nameUser = input1;
	TOpcion.setCharacterSize(30);
	TOpcion.setFont(fontUser);
	TOpcion.setFillColor(sf::Color::White);
	TOpcion.setOutlineThickness(2);
	TOpcion.setOutlineColor(sf::Color(135, 135, 135));
	TOpcion.setString("Opciones");
	TOpcion.setPosition(640, 100);
	 globalBounds = TOpcion.getGlobalBounds();
	TOpcion.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
	
}



void GameOptions::update() {
	Valida = false;

	bool valida2 = false;


	ButtonG MapaS(SpriteMapaS,TextureMapaS,TextureMapaSM,borde2,Minimo,Maximo);
	ButtonG Mapa22(SpriteMapa22, TextureMapa22, TextureMapa22M, borde1, Minimo, Maximo);
	ButtonG Mapa1(SpriteMapa1, TextureMapa1, TextureMapa1M, borde3, Minimo, Maximo);
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

					if (CantNum > 2) {
						CantNum -= 1;
						cantUser.setString(std::to_string(CantNum));
					}

				}

				if (SpriteflecDerecha.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					if (CantNum < 4) {
						CantNum += 1;
						cantUser.setString(std::to_string(CantNum));
					}
				}

				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
					if (SpriteMapaS.getGlobalBounds().contains(mousePosFloat)) {
						playClickSound();
						selectedMap = 0;
					}
					else if (SpriteMapa22.getGlobalBounds().contains(mousePosFloat)) {
						playClickSound();
						selectedMap = 1;
					}
					else if (SpriteMapa1.getGlobalBounds().contains(mousePosFloat)) {
						playClickSound();
						selectedMap = 2;
					}
				}


					if (selectedMap == 0) {

						spriteMapa.setTexture(TextureMapa);
						spriteMapa.setOrigin(360, 360);
						spriteMapa.setPosition(640, 360);


						window->draw(spriteMapa);
					}

					if (selectedMap == 1) {

						spriteMapa.setTexture(TextureMapa2);
						spriteMapa.setOrigin(360, 360);
						spriteMapa.setPosition(640, 360);

						window->draw(spriteMapa);
					}

					if (selectedMap == 2) {

						spriteMapa.setTexture(TextureMapa3);
						spriteMapa.setOrigin(360, 360);
						spriteMapa.setPosition(640, 360);

						window->draw(spriteMapa);

					} 
				
			
			

					if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {




						if (spriteX.getGlobalBounds().contains(mousePosFloat) && Valida == true) {
							playClickSound();
							valida2 = true;

					}
				}
			
		}

			if (SpriteCrear.getGlobalBounds().contains(mousePosFloat) && Valida == true) {
				playClickSound();
				PieceSelectOff pieceselectoff(window);
				pieceselectoff.Resource();
				pieceselectoff.updateSelection();

				pieceselectoff.~PieceSelectOff();



			}


		}


		Valida = true;

		currentCursor = &normalCursor;
		botonX->update(mousePosFloat, currentCursor, linkCursor, normalCursor);
		MapaS.Update(mousePosFloat, currentCursor, linkCursor, normalCursor);
		Mapa22.Update(mousePosFloat, currentCursor, linkCursor, normalCursor);
		Mapa1.Update(mousePosFloat, currentCursor, linkCursor, normalCursor);

		window->setMouseCursor(*currentCursor);

		window->clear();
		window->draw(spriteFondoGame);
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


		window->display();
	}
}
