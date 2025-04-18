#include "menuP.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../settings/SettingsManager.hpp"
#include "../core/ResourceGlobal.hpp"
#include "../ui/ButtonG.hpp"
#include "../game/online/ResourceGame.hpp"
#include "../ui/ResourceGeneral.hpp"
#include "GameModeSelector.hpp"
#include "IniciaUser.hpp"
#include "../ui/Sound.hpp"
menuP::menuP() : window(nullptr), SesionValida(true) {}
menuP::~menuP() {
	if (musicSlider) {
		delete musicSlider;
		musicSlider = nullptr;
	}
	if (effectSlider) {
		delete effectSlider;
		effectSlider = nullptr;
	}


	textureLogoFortuneAvenue = sf::Texture();
	Textureflechainstder = sf::Texture();
	Textureflechainstizq = sf::Texture();
	textureInstruccionesOn = sf::Texture();
	textureInstruccionesOff = sf::Texture();
	textureAcercaDeOn = sf::Texture();
	textureAcercaDeOff = sf::Texture();
	TextureEditButton = sf::Texture();
	TextureBotonJugarOff = sf::Texture();
	TextureBotonJugarOn = sf::Texture();
	TextureBotonOpcionesOff = sf::Texture();
	TextureBotonOpcionesOn = sf::Texture();
	TextureBotonSiOff = sf::Texture();
	TextureBotonSiOn = sf::Texture();
	TextureBotonNoOff = sf::Texture();
	TextureBotonNoOn = sf::Texture();
	TextureBotonSalirOff = sf::Texture();
	TextureBotonSalirOn = sf::Texture();
	TextureConfirmarSalir = sf::Texture();
	TextureConfirmarSalirSala = sf::Texture();
	TextureConfirmarSalirPartida = sf::Texture();

}
void menuP::setWindow(sf::RenderWindow& win) {
	window = &win;
}
void menuP::Resource() {

	if (!TextureFondoMenu.loadFromFile("assets/image/Fondos/fondomenu.png")) return;
	if (!textureXOn.loadFromFile("assets/image/Button/XOn.png")) return;
	if (!textureXOff.loadFromFile("assets/image/Button/XOff.png")) return;
	if (!TextureBotonSiOn.loadFromFile("assets/image/Button/BotonSiOn.png")) return;
	if (!TextureBotonSiOff.loadFromFile("assets/image/Button/BotonSiOff.png")) return;
	if (!TextureBotonNoOn.loadFromFile("assets/image/Button/BotonNoOn.png")) return;
	if (!TextureBotonNoOff.loadFromFile("assets/image/Button/BotonNoOff.png")) return;
	spriteX.setTexture(textureXOff);
	SpriteBotonNo.setTexture(TextureBotonNoOff);
	SpriteBotonSi.setTexture(TextureBotonSiOff);
	// Ahora que las texturas están cargadas, se puede crear el botón
	botonX = new ButtonG(spriteX, textureXOff, textureXOn);
	if (!fontUser.loadFromFile("assets/fonts/ARCADEPI.ttf")) {
		std::cerr << "Error loading font\n";
	}
	if (!textureBox.loadFromFile("assets/image/Button/rectanguloEncendido.png")) return;
	box.setTexture(textureBox);
	box.setOrigin(125, 40);

	if (!TextureConfirmarSalir.loadFromFile("assets/image/Button/boton2.png")) return;
	if (!TextureConfirmarSalirSala.loadFromFile("assets/image/Button/ExitSala.png")) return;
	if (!TextureConfirmarSalirPartida.loadFromFile("assets/image/Button/boton2.png")) return;
	if (!textureLogoFortuneAvenue.loadFromFile("assets/image/Logos/logojuego14.png")) return;
	if (!TextureBotonJugarOff.loadFromFile("assets/image/Button/BotonJugarOff.png")) return;
	if (!TextureBotonJugarOn.loadFromFile("assets/image/Button/BotonJugarOn.png")) return;
	if (!TextureBotonOpcionesOff.loadFromFile("assets/image/Button/BotonOpcionesOff.png")) return;
	if (!TextureBotonOpcionesOn.loadFromFile("assets/image/Button/BotonOpcionesOn.png")) return;
	if (!TextureBotonSalirOff.loadFromFile("assets/image/Button/BotonSalirOff.png")) return;
	if (!TextureBotonSalirOn.loadFromFile("assets/image/Button/BotonSalirOn.png")) return;
	if (!textureAcercaDeOn.loadFromFile("assets/image/Button/AcercaDeOn.png")) return;
	if (!textureAcercaDeOff.loadFromFile("assets/image/Button/AcercaDeOff.png")) return;

	if (!TextureBotonNoOff.loadFromFile("assets/image/Button/BotonNoOff.png"))return;
	if (!TextureBotonNoOn.loadFromFile("assets/image/Button/BotonNoOn.png"))return;
	if (!TextureBotonSiOff.loadFromFile("assets/image/Button/BotonSiOff.png"))return;
	if (!TextureBotonSiOn.loadFromFile("assets/image/Button/BotonSiOn.png"))return;

	if (!TextureEditButton.loadFromFile("assets/image/Nueva carpeta/edit22.png"))return;

	if (!Textureflechainstder.loadFromFile("assets/image/Button/flechapagder.png")) return;
	if (!Textureflechainstizq.loadFromFile("assets/image/Button/flechapagizq.png")) return;
	if (!textureInstruccionesOn.loadFromFile("assets/image/Button/instruccionesencendido.png")) return;
	if (!textureInstruccionesOff.loadFromFile("assets/image/Button/instruccionesapagado.png")) return;
	if (!MenuMusicFondo.openFromFile("assets/sounds/MenuB.wav")) return;
	if (!Blur.loadFromFile("assets/Shaders/blur.frag", sf::Shader::Fragment)) return;
	if (!renderTexture.create(window->getSize().x, window->getSize().y)) return;
	if (!SelectingMusicFondo.openFromFile("assets/sounds/SelectingPieces.wav")) return;

	flechainstder.setTexture(Textureflechainstder);
	flechainstder.setPosition(1180, 600);
	flechainstder.setOrigin(50, 45);

	flechainstizq.setTexture(Textureflechainstizq);
	flechainstizq.setPosition(100, 600);
	flechainstizq.setOrigin(50, 45);


	spriteInstrucciones.setTexture(textureInstruccionesOff);
	spriteInstrucciones.setPosition(200, 520);
	spriteInstrucciones.setOrigin(103.5f, 36.5f);

	Blur.setUniform("resolution", sf::Glsl::Vec2(
		static_cast<float>(window->getSize().x),
		static_cast<float>(window->getSize().y)
	));

	if (!HoverBuffer.loadFromFile("assets/sounds/HoverBoton.wav")) return;
	if (!ClickBuffer.loadFromFile("assets/sounds/ClickBoton.wav")) return;

	HoverSound.setBuffer(HoverBuffer);
	ClickSound.setBuffer(ClickBuffer);

	std::vector<sf::Sound*> effectPointers = { &HoverSound, &ClickSound,&girosSound,&DiceSound };
	std::vector<sf::Music*> MusicPointers = { &MenuMusicFondo,&GameMusicFondo,&SelectingMusicFondo };

	overlay.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
	overlay.setFillColor(sf::Color(0, 0, 0, 150));

	Sesion.setFont(fontUser);
	Sesion.setFillColor(sf::Color::White);
	Sesion.setOutlineThickness(2);
	Sesion.setOutlineColor(sf::Color(135, 135, 135));

	spriteLogoFortuneAvenue.setTexture(textureLogoFortuneAvenue);
	spriteLogoFortuneAvenue.setOrigin(256.5f, 209.4f);
	spriteLogoFortuneAvenue.setPosition(640, 260);

	SpriteBotonJugar.setTexture(TextureBotonJugarOff);
	SpriteBotonJugar.setOrigin(103.5f, 40);
	SpriteBotonJugar.setPosition(383, 560);

	SpriteBotonOpciones.setTexture(TextureBotonOpcionesOff);
	SpriteBotonOpciones.setOrigin(103.5f, 40);
	SpriteBotonOpciones.setPosition(640, 560);

	spriteEditButton.setTexture(TextureEditButton);
	spriteEditButton.setOrigin(256.5f, 209.4f);
	spriteEditButton.setPosition(384, 315);

	SpriteBotonSalir.setTexture(TextureBotonSalirOff);
	SpriteBotonSalir.setOrigin(103.5f, 40);
	SpriteBotonSalir.setPosition(895, 560);

	spriteX.setTexture(textureXOff);
	spriteX.setOrigin(20, 20);
	spriteX.setPosition(1200.5f, 50);

	spriteAcercaDe.setTexture(textureAcercaDeOff);
	spriteAcercaDe.setOrigin(64.5f, 25);
	spriteAcercaDe.setPosition(1200.5f, 680);
	SpriteFondoMenu.setTexture(TextureFondoMenu);

	musicSlider = new SettingsManager(200, 300, 200, 10, MusicPointers, *window);

	effectSlider = new SettingsManager(200, 400, 200, 10, effectPointers, *window);
	
	sf::Image cursorNormal;
	if (!cursorNormal.loadFromFile("assets/image/Cursor/normal-select-0.png")) return;

	sf::Image cursorLink;
	if (!cursorLink.loadFromFile("assets/image/Cursor/link-select-0.png")) return;

	sf::Image cursorText;
	if (!cursorText.loadFromFile("assets/image/Cursor/text-select-0.png")) return;

	sf::Image cursorMove;
	if (!cursorMove.loadFromFile("assets/image/Cursor/move-0.png")) return;

	// Tamaño de cada cursor (por ejemplo 32x32)
	sf::Vector2u cursorSize(32, 32);

	// Crear cursores
	if (!normalCursor.loadFromPixels(cursorNormal.getPixelsPtr(), cursorSize, sf::Vector2u(0, 0))) return;

	if (!linkCursor.loadFromPixels(cursorLink.getPixelsPtr(), cursorSize, sf::Vector2u(0, 0))) return;

	if (!textCursor.loadFromPixels(cursorText.getPixelsPtr(), cursorSize, sf::Vector2u(0, 0))) return;

	if (!moveCursor.loadFromPixels(cursorMove.getPixelsPtr(), cursorSize, sf::Vector2u(0, 0))) return;

	window->setMouseCursor(normalCursor);

}
void menuP::MenuPrincipal() {
	window->setMouseCursorVisible(true);
	MenuMusicFondo.setLoop(true);
	MenuMusicFondo.play();

	Inicializar();

	selectedAvatarCopy.setPosition(84, 74);
	selectedAvatarCopy.setScale(1, 1);
	sf::CircleShape hola;




	recua.setPosition(84, 74);
	recua.setScale(1, 1);
	Sesion.setCharacterSize(24);
	Sesion.setPosition(273, 74 - 4);
	box.setPosition(273, 74);
	box.setScale(1, 1);

	// Crear botones
	ButtonG botonJugar(SpriteBotonJugar, TextureBotonJugarOff, TextureBotonJugarOn);
	ButtonG botonOpciones(SpriteBotonOpciones, TextureBotonOpcionesOff, TextureBotonOpcionesOn);
	ButtonG botonSalir(SpriteBotonSalir, TextureBotonSalirOff, TextureBotonSalirOn);
	ButtonG botonAcercaDe(spriteAcercaDe, textureAcercaDeOff, textureAcercaDeOn);
	window->setMouseCursorVisible(true);

	SpriteBotonOpciones.setPosition(640, 560);
	ValidarUser();

	while (window->isOpen()) {



		eventoMenuP();


		sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
		sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);
		window->setMouseCursorVisible(true);


		currentCursor = &normalCursor;
		botonJugar.update(mousePosFloat, currentCursor, linkCursor, normalCursor);
		botonOpciones.update(mousePosFloat, currentCursor, linkCursor, normalCursor);
		botonSalir.update(mousePosFloat, currentCursor, linkCursor, normalCursor);
		botonAcercaDe.update(mousePosFloat, currentCursor, linkCursor, normalCursor);
		window->setMouseCursor(*currentCursor);



		window->clear();
		window->draw(SpriteFondoMenu);
		window->draw(spriteLogoFortuneAvenue);
		window->draw(box);
		window->draw(Sesion);
		window->draw(selectedAvatarCopy);
		window->draw(recua);
		window->draw(SpriteBotonJugar);
		window->draw(SpriteBotonOpciones);
		window->draw(SpriteBotonSalir);
		window->draw(spriteAcercaDe);
		window->draw(spriteEditButton);
		window->display();
	}
}
void menuP::ValidarUser() {

	if (SesionValida) {

		Sesion.setString(input1);
		sf::FloatRect globalBounds = Sesion.getGlobalBounds();

		// Ajustar la posición centrando el texto
		Sesion.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
	}

}
void menuP::eventoMenuP() {

	sf::Event event;

	while (window->pollEvent(event)) {

		renderTexture.clear(sf::Color::Transparent);
		renderTexture.draw(SpriteFondoMenu);
		renderTexture.draw(spriteLogoFortuneAvenue);
		renderTexture.draw(box);
		renderTexture.draw(Sesion);
		renderTexture.draw(selectedAvatarCopy);
		renderTexture.draw(recua);
		renderTexture.draw(SpriteBotonJugar);
		renderTexture.draw(SpriteBotonOpciones);
		renderTexture.draw(SpriteBotonSalir);
		renderTexture.draw(spriteAcercaDe);
		renderTexture.draw(spriteEditButton);
		renderTexture.draw(overlay);
		renderTexture.display();
		if (event.type == sf::Event::Closed ||
			(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {

			MenuSalir(nullptr);
		}


		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);

			sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);


			if (SpriteBotonJugar.getGlobalBounds().contains(mousePosFloat)) {
				playClickSound();
				MenuJugar();

				selectedAvatarCopy.setPosition(84, 74);
				selectedAvatarCopy.setScale(1, 1);
				recua.setPosition(84, 74);
				recua.setScale(1, 1);
				Sesion.setCharacterSize(24);
				Sesion.setPosition(273, 74 - 4);
				box.setPosition(273, 74);
				box.setScale(1, 1);

			}


			if (SpriteBotonOpciones.getGlobalBounds().contains(mousePosFloat)) {
				playClickSound();
				MenuOpcion(true);
				SpriteBotonOpciones.setPosition(640, 560);

			}


			if (SpriteBotonSalir.getGlobalBounds().contains(mousePosFloat)) {
				playClickSound();
				MenuSalir(nullptr);

			}
			if (spriteAcercaDe.getGlobalBounds().contains(mousePosFloat)) {
				playClickSound();
				MenuAcercaDe();

			}

			if (spriteEditButton.getGlobalBounds().contains(mousePosFloat)) {

				playClickSound();
				editPerfil();
				ValidarUser();


			}

		}
	}
}
void menuP::MenuJugar() {


	GameModeSelector GMSelector(*window);
	GMSelector.update();

	box.setPosition(273, 74);

};
void menuP::Inicializar() {
	IniciaUser iniciaUser(*window);



	iniciaUser.Resource();


	iniciaUser.Update();

	iniciaUser.~IniciaUser();

}
void menuP::editPerfil() {
	IniciaUser iniciaUserEdit(*window, Sesion.getString());

	iniciaUserEdit.Resource();


	iniciaUserEdit.UpdateEdit();


	iniciaUserEdit.~IniciaUser();

	selectedAvatarCopy.setPosition(84, 74);
	selectedAvatarCopy.setScale(1, 1);
	recua.setPosition(84, 74);
	recua.setScale(1, 1);
	Sesion.setCharacterSize(24);
	Sesion.setPosition(273, 74 - 4);
	box.setPosition(273, 74);
	box.setScale(1, 1);

}
void menuP::MenuOpcion(bool fon) {

	SpriteBotonOpciones.setTexture(TextureBotonOpcionesOn);
	SpriteBotonOpciones.setPosition(640, 100);

	SpriteBotonSi.setTexture(TextureBotonSiOn);
	SpriteBotonSi.setPosition(800, 350);


	SpriteBotonNo.setTexture(TextureBotonNoOff);
	SpriteBotonNo.setPosition(1000, 350);


	if (!Fuente.loadFromFile("assets/fonts/ARCADEPI.ttf")) {
		return;
	}


	sf::Text TextpantallaCompleta;


	TextpantallaCompleta.setString("Pantalla Completa");
	TextpantallaCompleta.setFont(Fuente);
	TextpantallaCompleta.setCharacterSize(30);
	TextpantallaCompleta.setFillColor(sf::Color::White);
	TextpantallaCompleta.setPosition(795, 270);

	bool cierre = false;
	window->setMouseCursorVisible(true);




	ButtonG BotonSi(SpriteBotonSi, TextureBotonSiOff, TextureBotonSiOn);
	ButtonG BotonNo(SpriteBotonNo, TextureBotonNoOff, TextureBotonNoOn);
	ButtonG BotonInstrucciones(spriteInstrucciones, textureInstruccionesOff, textureInstruccionesOn);

	while (window->isOpen()) {
		currentCursor = &normalCursor;
		mousePosition = sf::Mouse::getPosition(*window);
		mousePosFloat = static_cast<sf::Vector2f>(mousePosition);
		botonX->update(mousePosFloat, currentCursor, linkCursor, normalCursor);


		sf::Event event;

		while (window->pollEvent(event)) {

			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
				renderTexture.clear();
				renderTexture.draw(SpriteFondoMenu);
				renderTexture.draw(SpriteBotonOpciones);
				renderTexture.draw(spriteX);
				musicSlider->Printf();
				effectSlider->Printf();
				renderTexture.display();
				MenuSalir(nullptr);
			}



			musicSlider->handleEvent(event, *window);
			effectSlider->handleEvent(event, *window);


			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
				sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

				if (SpriteBotonSi.getGlobalBounds().contains(mousePosFloat)) {
					window->create(sf::VideoMode(1280, 720), "Juego en Pantalla Completa", sf::Style::Fullscreen);
					playClickSound();

					SpriteBotonNo.setTexture(TextureBotonNoOff);
					SpriteBotonNo.setPosition(1000, 350);

					SpriteBotonSi.setTexture(TextureBotonSiOn);
					SpriteBotonSi.setPosition(800, 350);

					spriteX.setTexture(textureXOff);
					spriteX.setOrigin(20, 20);
					spriteX.setPosition(1200.5f, 50);

				}

				if (SpriteBotonNo.getGlobalBounds().contains(mousePosFloat)) {
					window->create(sf::VideoMode(1280, 720), "Juego en Pantalla Completa");

					playClickSound();

					SpriteBotonNo.setTexture(TextureBotonNoOn);
					SpriteBotonNo.setPosition(1000, 350);

					SpriteBotonSi.setTexture(TextureBotonSiOff);
					SpriteBotonSi.setPosition(800, 350);
				}

				if (spriteX.getGlobalBounds().contains(mousePosFloat)) {
					musicSlider->saveSettings();
					effectSlider->saveSettings();
					playClickSound();

					return;

				}
				if (spriteInstrucciones.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					instruccionesGame();

				}
			}
		}
		BotonInstrucciones.update(mousePosFloat, currentCursor, linkCursor, normalCursor);
		window->setMouseCursor(*currentCursor);

		// Dibujo de elementos en la ventana
		window->clear();
		if (fon) {
			window->draw(SpriteFondoMenu);
		}
		else {
			window->draw(spriteBackgroundG);
		}
		window->draw(spriteX);
		window->draw(SpriteBotonOpciones);
		window->draw(spriteInstrucciones);
		musicSlider->draw(*window);
		effectSlider->draw(*window);
		window->setMouseCursor(*currentCursor);
		window->draw(SpriteBotonSi);
		window->draw(SpriteBotonNo);

		window->draw(TextpantallaCompleta);

		window->display();

	}

}
void menuP::MenuSalir(Client* client) {
	
	sf::RectangleShape overlay(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
	overlay.setFillColor(sf::Color(0, 0, 0, 10));

	SpriteConfirmarSalir.setTexture(TextureConfirmarSalir);
	SpriteConfirmarSalir.setPosition(660, 370);
	SpriteConfirmarSalir.setOrigin(340, 240);

	SpriteBotonSi.setPosition(480, 380);


	SpriteBotonNo.setPosition(680, 380);

	ButtonG BotonSi(SpriteBotonSi, TextureBotonSiOff, TextureBotonSiOn);
	ButtonG BotonNo(SpriteBotonNo, TextureBotonNoOff, TextureBotonNoOn);
	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
				if (client != nullptr && client->clientData->running && client->peer != nullptr) {
					client->disconnect();
				}
				window->setActive(false);
				SpriteConfirmarSalir.setTexture(sf::Texture());
				renderTexture.create(1, 1);  // Reset renderTexture

				window->close();
				break;  
			}
			
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
				sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

				if (SpriteBotonSi.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();

					if (client != nullptr && client->clientData->running && client->peer != nullptr) {
						client->disconnect();
					}
					window->setActive(false);
					window->close();
					break;
				}


				if (SpriteBotonNo.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					return;
				}
			}


		}

		currentCursor = &normalCursor;
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
		sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);
		BotonSi.update(mousePosFloat, currentCursor, linkCursor, normalCursor);
		BotonNo.update(mousePosFloat, currentCursor, linkCursor, normalCursor);

		window->setMouseCursor(*currentCursor);

		renderedSprite.setTexture(renderTexture.getTexture());
		window->clear();
		window->draw(renderedSprite, &Blur);

		window->draw(SpriteConfirmarSalir);
		window->draw(SpriteBotonSi);
		window->draw(SpriteBotonNo);

		window->display();


	}
}
void menuP::instruccionesGame() {

	int pag = 0;
	sf::RectangleShape overlay(sf::Vector2f(
		static_cast<float>(window->getSize().x - 50),
		static_cast<float>(window->getSize().y - 50)
	));



	overlay.setPosition(25.0f, 25.0f);

	overlay.setFillColor(sf::Color(0, 0, 0, 100));

	sf::Font Fuente;
	if (!Fuente.loadFromFile("assets/fonts/ARCADEPI.ttf")) {
		return;
	}

	sf::Text TextInstruccion1;
	sf::Text TextInstruccion2;
	sf::Text TextInstruccion3;
	TextInstruccion1.setFont(Fuente);
	TextInstruccion2.setFont(Fuente);
	TextInstruccion3.setFont(Fuente);

	TextInstruccion1.setString("Instrucciones de Fortuna Avenue\n\nObjetivo del juego :\nEl objetivo de Fortuna Avenue es ser el jugador con mas dinero al final de la partida, despues de \ncompletar 2 vueltas alrededor del tablero.Los jugadores deben administrar sus recursos, hacer \ninversiones y aprovechar tanto la suerte como la estrategia para ganar.\n\nComponentes del juego :\n    - Tablero : Un tablero con 4 tipos de casillas :\n    - Casillas :\n    -  Casillas de Casas.\n    - Casillas de Impuestos.\n    - Casillas de Ruleta.\n    - Casillas Vacias.    \n    - Dados : Un dado de 6 caras que dicta la cantidad de casillas que se movera el jugador.    \n    - Dinero : Cada jugador comienza con 300 billetes y recibe 60 billetes cada 2 turnos como sueldo \nbase y de ahi en adelante, al sueldo base se le ira sumando el sueldo de las casas que adquiera.\n\nPreparacion del juego :\n    1. Cada jugador selecciona una ficha que al iniciar el juego, se colocara automaticamente en la \ncasilla de ''Start''.\n    2. Los jugadores reciben 200 billetes como su primer sueldo.\n    3. El orden de turnos se elegira a partir de quienes ingresen primero a la sala, es decir, el \n    primer turno sera del creador de la sala y a partir de ahi, se elegira por orden de entrada, \n    que se mantendra durante toda la partida.\n    4. En el juego, se dan 3 vueltas por el tablero.Despues de la tercera vuelta de todos los \n    jugadores, el jugador con mas dinero gana.");
	TextInstruccion2.setString(
		"Como jugar:\n\n"
		"1. Turnos:\n"
		"    Los jugadores se turnan para tirar el dado. En cada turno, un jugador debe:\n"
		"    - Lanzar el dado para determinar cuantas casillas avanzara su ficha.\n"
		"    - Mover su ficha el numero de casillas indicado por el dado.\n"
		"    - Realizar una accion segun la casilla en la que caiga.\n\n"
		"2. Tipos de Casillas:\n"
		"    Existen 3 tipos principales de casillas con acciones especificas:\n"
		"    - Casillas de Impuestos:\n"
		"        - El jugador paga una cantidad de dinero.\n"
		"        - El monto base es 50 billetes, pero aumenta segun las casas del jugador.\n"
		"    - Casillas de Casas:\n"
		"        - El jugador puede comprar una casa entre 400 y 750 billetes.\n"
		"        - Las casas incrementan el sueldo en un rango de 60 a 113 billetes.\n"
		"        - Tambien aumentan los impuestos entre 50 y 94 billetes, segun la casa.\n"
		"    - Casillas de Ruleta:\n"
		"        - Al caer aqui, el jugador gira la ruleta, que tiene 7 posibles resultados:\n"
		"          1. Paga impuestos: Debe pagar dinero al banco.\n"
		"          2. Gana 150 billetes.\n"
		"          3. Pierde el siguiente turno.\n"
		"          4. Todos los demas jugadores le pagan 30 billetes.\n"
		"          5. Compra de casa: Puede adquirir una casa.\n"
		"          6. Inversión segura: Invierte 100 billetes y recibe 200 en dos turnos.\n"
		"          7. Robo a un jugador: Roba 100 billetes a un jugador al azar.\n\n"
		"       - Casillas Vacias:\n"
		"           - No ocurre ningun evento especial."
	);
	TextInstruccion3.setString(
		"Final del juego:\n\n"
		"El juego finaliza cuando todos los jugadores hayan dado 2 vueltas alrededor del tablero. Al finalizar, \n"
		"se cuentan los billetes de cada jugador, y el jugador con la mayor cantidad de billetes es el ganador.\n\n"
		"Ejemplo de turno:\n"
		"1. Jugador 1 lanza el dado y obtiene un 4. Elige el camino de la izquierda, mueve su ficha 4 casillas \ny cae en una casilla de casa.\n"
		"    - El jugador decide comprar una casa por 400 billetes. Su sueldo aumenta en 60 billetes por \n    encima del sueldo base \n"
		"      (es decir, 60$ + 60$ = 120$ -> nuevo sueldo). Sin embargo, sus impuestos tambien suben 70 \n    billetes por encima del impuesto base \n"
		"      (es decir, 50$ + 50$ = 100$ -> nuevo impuesto).\n"
		"2. Jugador 2 lanza el dado y obtiene un 2. Mueve su ficha 2 casillas a la derecha y cae en una\n casilla de impuestos. \n"
		"    - El jugador paga 50 billetes (si no ha comprado casas aún).\n"
		"3. El turno pasa al siguiente jugador.\n\n"
		"Consejos:\n"
		"- Administra bien tu dinero: Comprar casas aumenta tu sueldo, pero tambien tus impuestos. Tomate \ntu tiempo para decidir \n"
		"  si invertir es lo mejor en cada momento.\n"
		"- Observa a tus oponentes: Las decisiones de otros jugadores pueden afectar tu estrategia. Presta \natencion a sus movimientos \n"
		"  y gestiona tu dinero para contrarrestar sus ventajas.\n"
		"- Aprovecha las ruletas: Las casillas de ruleta son impredecibles, pero algunas pueden darte grandes \n      beneficios. \n"
		"         Aprovecha las oportunidades cuando las encuentres.\n\n"
		"           ¡Diviertete jugando a Fortuna Avenue!"
	);


	TextInstruccion1.setCharacterSize(static_cast <unsigned int>(17.5f));
	TextInstruccion2.setCharacterSize(static_cast <unsigned int>(17.5f));
	TextInstruccion3.setCharacterSize(static_cast <unsigned int>(17.5f));
	TextInstruccion1.setFillColor(sf::Color::White);
	TextInstruccion2.setFillColor(sf::Color::White);
	TextInstruccion3.setFillColor(sf::Color::White);
	TextInstruccion1.setPosition(50, 100);
	TextInstruccion2.setPosition(50, 100);
	TextInstruccion3.setPosition(50, 100);

	bool cierre = false;
	window->setMouseCursorVisible(true);

	while (window->isOpen() && !cierre) {
		currentCursor = &normalCursor;
		mousePosition = sf::Mouse::getPosition(*window);
		mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

		sf::Event event;

		while (window->pollEvent(event)) {

			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
				renderTexture.clear();
				renderTexture.draw(SpriteFondoMenu);
				renderTexture.draw(SpriteBotonOpciones);
				renderTexture.draw(spriteX);
				musicSlider->Printf();
				effectSlider->Printf();
				renderTexture.display();
				MenuSalir(nullptr);
			}


			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
				sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

				if (spriteX.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					cierre = true;

				}

				if (flechainstizq.getGlobalBounds().contains(mousePosFloat)) {

					if (pag > 0) {
						playClickSound();
						pag--;
					}
				}
				if (flechainstder.getGlobalBounds().contains(mousePosFloat)) {

					if (pag < 2) {
						playClickSound();
						pag++;
					}
				}
			}
		}

		botonX->update(mousePosFloat, currentCursor, linkCursor, normalCursor);

		renderedSprite.setTexture(renderTexture.getTexture());
		window->setMouseCursor(*currentCursor);
		window->clear();


		window->draw(renderedSprite, &Blur);
		window->draw(spriteX);

		window->draw(overlay);


		if (pag == 0) {
			window->draw(TextInstruccion1);
			window->draw(flechainstder);
		}
		else if (pag == 1) {
			window->draw(TextInstruccion2);
			window->draw(flechainstizq);
			window->draw(flechainstder);
		}
		else if (pag == 2) {

			window->draw(TextInstruccion3);
			window->draw(flechainstizq);
		}




		window->display();
	}



}
void menuP::MenuAcercaDe() {


	sf::RectangleShape overlay(sf::Vector2f(
		static_cast<float>(window->getSize().x - 50),
		static_cast<float>(window->getSize().y - 50)
	));



	overlay.setPosition(25.0f, 25.0f);

	overlay.setFillColor(sf::Color(0, 0, 0, 100));

	sf::Font Fuente;
	if (!Fuente.loadFromFile("assets/fonts/ARCADEPI.ttf")) {
		return;
	}

	sf::Text TextAcercaDe;
	TextAcercaDe.setFont(Fuente);

	TextAcercaDe.setString(
		"Fortune Avenue\n"
		"version 2.0.0\n\n"
		"Fortune Avenue esta basado en los clasicos juegos de mesa donde el objetivo principal es obtener \nla mayor cantidad de dinero al finalizar la partida, tomando decisiones sobre la compra de viviendas \ny el pago de impuestos, todo mientras el azar juega un papel importante al final de cada partida.\n\n"
		"Este proyecto fue desarrollado por Red Galaxy Studio, un equipo de 4 estudiantes apasionados por el \ndesarrollo de videojuegos. Nuestra mision es crear experiencias unicas e interactivas que entretengan \ny desafien a los jugadores.\n\n"
		"Desarrolladores:\n\n"
		"Daniel Fernandez\n"
		"Lider del Proyecto | Programador | Especialista en Redes\n\n"
		"Jose Garcia\n"
		"Especialista en Testing y Calidad | Disenador de Mecanicas | Encargado de Documentacion\n\n"
		"Susana Rendon\n"
		"Artista Grafico | Disenadora de Interfaz de Usuario (UI/UX) | Encargada de Implementacion de Sonidos\n\n"
		"Marcos Rondon\n"
		"Encargado de Marketing | Disenador de Mecanicas | Responsable de Economia del Juego\n\n"
		"Nota: Aunque cada miembro asumio roles especificos, el proyecto fue un esfuerzo colaborativo en el \nque todos contribuyeron activamente en diversas areas del desarrollo.\n\n"
		"Ubicacion: Proyecto academico, Universidad de los Andes.\n"
		"Tecnologias utilizadas: SFML, ENet, C++.\n"
		"Contacto: redgalaxy.studio24@gmail.com"
	);

	TextAcercaDe.setCharacterSize(static_cast <unsigned int>(17.5f));
	TextAcercaDe.setFillColor(sf::Color::White);
	TextAcercaDe.setPosition(50, 100);
	
	window->setMouseCursorVisible(true);

	while (window->isOpen()) {
		currentCursor = &normalCursor;
		mousePosition = sf::Mouse::getPosition(*window);
		mousePosFloat = static_cast<sf::Vector2f>(mousePosition);



		sf::Event event;

		while (window->pollEvent(event)) {

			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
				renderTexture.clear();

				renderTexture.draw(renderedSprite, &Blur);
				renderTexture.draw(spriteX);

				renderTexture.draw(overlay);


				renderTexture.draw(TextAcercaDe);
				renderTexture.draw(spriteX);
				renderTexture.display();
				MenuSalir(nullptr);
			}



			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
				sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

				if (spriteX.getGlobalBounds().contains(mousePosFloat)) {

					playClickSound();

					return;

				}

			}
		}
		botonX->update(mousePosFloat, currentCursor, linkCursor, normalCursor);

		renderedSprite.setTexture(renderTexture.getTexture());

		window->clear();


		window->draw(renderedSprite, &Blur);
		window->draw(spriteX);

		window->draw(overlay);


		window->draw(TextAcercaDe);

		window->setMouseCursor(*currentCursor);
		window->display();
	}
}