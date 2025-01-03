#include "MultiplayerGame.hpp"
#include <String>
#include "GameEnd.hpp"
#include "Stealplayer.hpp"

MultiplayerGame::MultiplayerGame(sf::RenderWindow& win) : window(&win), Dado(window), moverFichas(UsuariosActivos.size(), MovePieces(win)) {
	ruleta = new Ruleta(500.0f, 500.0f, 640.0f, 360.0f); // Inicialización del puntero

	loadResourceGame();
	resource();
}
void MultiplayerGame::resource() {

	if (!TextureMapa.loadFromFile("resource/texture/Game/mapa+S+++.png")) return;
	if (!SettingsOff.loadFromFile("resource/texture/Game/settingOff.png")) return;
	if (!SettingsOn.loadFromFile("resource/texture/Game/settingOn.png")) return;

	if (!GameMusicFondo.openFromFile("resource/sounds/gamemusic.wav")) return;
	Opcioncami = -1;
	//Cargar Texturas de Flechas
	if (!TextureArrowIzq.loadFromFile("resource/texture/Game/Izq.png")) return;
	if (!TextureArrowDer.loadFromFile("resource/texture/Game/Der.png")) return;
	if (!TextureArrowArriba.loadFromFile("resource/texture/Game/Arriba.png")) return;
	if (!TextureImpuesto.loadFromFile("resource/texture/Game/Impuesto.png")) return;


	//posicin y tamanio de flechas
	SpriteArrowIzq.setTexture(TextureArrowIzq);
	SpriteArrowIzq.setOrigin(350.0f, 350.0f);
	SpriteArrowIzq.setPosition(370, 400);

	SpriteArrowDer.setTexture(TextureArrowDer);
	SpriteArrowDer.setOrigin(350.0f, 350.0f);
	SpriteArrowDer.setPosition(900, 400);

	SpriteArrowArriba.setTexture(TextureArrowArriba);
	SpriteArrowArriba.setOrigin(350.0f, 350.0f);
	SpriteArrowArriba.setPosition(370, 400);



	Settings.setTexture(SettingsOff);
	Settings.setOrigin(25, 25);
	Settings.setPosition(150, 30);

	spriteMapa.setTexture(TextureMapa);
	spriteMapa.setOrigin(360, 360);
	spriteMapa.setPosition(640, 360);


	if (!DiceBuffer.loadFromFile("resource/sounds/Dicerolling.wav")) return;

	if (!girosBuffer.loadFromFile("resource/sounds/ruleta.wav")) return;
	nular = true;
	girosSound.setBuffer(girosBuffer);


	DiceSound.setBuffer(DiceBuffer);


	std::vector<sf::Vector2f> camino1 = { sf::Vector2f(375, 480) };

	casillas0.push_back(camino1);
	casillas1.push_back(camino1);
	casillas2.push_back(camino1);
	casillas3.push_back(camino1);

	view.setSize(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y));
	view.setCenter(playersGame[0].PieceSelect.getPosition()); // Centra la vista en la ficha

	Bienvenida.setCharacterSize(45);
	Bienvenida.setFont(fontUser);
	Bienvenida.setFillColor(sf::Color::White);
	Bienvenida.setOutlineThickness(2);
	Bienvenida.setOutlineColor(sf::Color(135, 135, 135));
	Bienvenida.setString("Comienza el juego!");
	Bienvenida.setPosition(640, 360);
	sf::FloatRect globalBounds = Bienvenida.getGlobalBounds();
	Bienvenida.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
	posicionActual = 0;


	Impuesto.setCharacterSize(45);
	Impuesto.setFont(fontUser);
	Impuesto.setFillColor(sf::Color::White);
	Impuesto.setOutlineThickness(2);
	Impuesto.setOutlineColor(sf::Color(135, 135, 135));

	Impuesto.setPosition(640, 360);
	globalBounds = Impuesto.getGlobalBounds();
	Impuesto.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
	posicionActual = 0;

	DescripDado.setCharacterSize(15);
	DescripDado.setFont(fontUser);
	DescripDado.setFillColor(sf::Color::White);
	DescripDado.setOutlineThickness(2);
	DescripDado.setOutlineColor(sf::Color(135, 135, 135));
	DescripDado.setString("Presiona la tecla 'ESPACIO'.");
	DescripDado.setPosition(640, 450);
	globalBounds = DescripDado.getGlobalBounds();
	DescripDado.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	Conteosuel.setCharacterSize(10);
	Conteosuel.setFont(fontUser);
	Conteosuel.setFillColor(sf::Color::White);
	Conteosuel.setOutlineThickness(2);
	Conteosuel.setOutlineColor(sf::Color(135, 135, 135));
	Conteosuel.setString(std::to_string(conteosuel));
	Conteosuel.setPosition(60, 10);


	animacionIniciada = false;

}
void MultiplayerGame::positionPefil() {
	if (UsuariosActivos.size() >= 1) { 

	std::cout << "\nperrrrrrrrrrroooooooooooooooooooooo";
	playersGame[UsuariosActivos[0]].NamePlayer.setPosition(188.65f, 62.5f);

	playersGame[UsuariosActivos[0]].boxPlayer.setPosition(188.65f, 62.5f);
	playersGame[UsuariosActivos[0]].boxPlayer.setScale(0.7f, 0.7f);

	playersGame[UsuariosActivos[0]].MarcoPlayer.setTexture(TextureMarco);
	globalBounds = playersGame[UsuariosActivos[0]].MarcoPlayer.getGlobalBounds();
	playersGame[UsuariosActivos[0]].MarcoPlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	playersGame[UsuariosActivos[0]].MarcoPlayer.setPosition(52.5f, 62.5f);

	playersGame[UsuariosActivos[0]].Money.setString(std::to_string(playerInfos[UsuariosActivos[0]].money));
	playersGame[UsuariosActivos[0]].Money.setCharacterSize(17);
	playersGame[UsuariosActivos[0]].Money.setFont(fontUser);
	playersGame[UsuariosActivos[0]].Money.setFillColor(sf::Color::White);
	playersGame[UsuariosActivos[0]].Money.setOutlineThickness(2);
	playersGame[UsuariosActivos[0]].Money.setOutlineColor(sf::Color(135, 135, 135));
	playersGame[UsuariosActivos[0]].Money.setPosition(170.65f, 95.5f);

	playersGame[UsuariosActivos[0]].textureAvatarPLayer = *selectedAvatarCopy.getTexture();
	playersGame[UsuariosActivos[0]].AvatarPlayer.setTexture(&playersGame[UsuariosActivos[0]].textureAvatarPLayer);
	playersGame[UsuariosActivos[0]].AvatarPlayer.setRadius(static_cast<float>(playersGame[UsuariosActivos[0]].textureAvatarPLayer.getSize().x / 2));
	playersGame[UsuariosActivos[0]].AvatarPlayer.setOrigin(64, 64);
	playersGame[UsuariosActivos[0]].AvatarPlayer.setPosition(52.5f, 62.5f);
	playersGame[UsuariosActivos[0]].AvatarPlayer.setScale(0.7f, 0.7f);

	playersGame[UsuariosActivos[0]].PieceSelect.setScale(1, 1);
	globalBounds = playersGame[UsuariosActivos[0]].PieceSelect.getGlobalBounds();
	playersGame[UsuariosActivos[0]].PieceSelect.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	moverFichas[UsuariosActivos[0]].Inicializar(&playersGame[UsuariosActivos[0]].PieceSelect, &casillas0);


	playersGame[UsuariosActivos[0]].CashSprite.setOrigin(20, 16);
	playersGame[UsuariosActivos[0]].CashSprite.setPosition(245, 105);
	playersGame[0].PieceSelect.setPosition(330, 439);
} else {
		return;
	}


	//Perfil 2
	if (UsuariosActivos.size() >= 2) {




		globalBounds = playersGame[UsuariosActivos[1]].NamePlayer.getGlobalBounds();
		playersGame[UsuariosActivos[1]].NamePlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
		playersGame[UsuariosActivos[1]].NamePlayer.setPosition(1188.65f, 52.5f);

		playersGame[UsuariosActivos[1]].boxPlayer.setPosition(1188.65f, 52.5f);
		playersGame[UsuariosActivos[1]].boxPlayer.setScale(0.7f, 0.7f);

		playersGame[UsuariosActivos[1]].MarcoPlayer.setTexture(TextureMarco);
		globalBounds = playersGame[UsuariosActivos[1]].MarcoPlayer.getGlobalBounds();
		playersGame[UsuariosActivos[1]].MarcoPlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

		playersGame[UsuariosActivos[1]].MarcoPlayer.setPosition(1052.5f, 52.5f);

		playersGame[UsuariosActivos[1]].AvatarPlayer.setTexture(&playersGame[UsuariosActivos[1]].textureAvatarPLayer);
		playersGame[UsuariosActivos[1]].AvatarPlayer.setRadius(static_cast<float>(playersGame[UsuariosActivos[1]].textureAvatarPLayer.getSize().x / 2));
		playersGame[UsuariosActivos[1]].AvatarPlayer.setOrigin(64, 64);
		playersGame[UsuariosActivos[1]].AvatarPlayer.setPosition(1052.5f, 52.5f);
		playersGame[UsuariosActivos[1]].AvatarPlayer.setScale(0.7f, 0.7f);


		playersGame[UsuariosActivos[1]].Money.setString(std::to_string(playerInfos[UsuariosActivos[1]].money));
		playersGame[UsuariosActivos[1]].Money.setCharacterSize(17);
		playersGame[UsuariosActivos[1]].Money.setFont(fontUser);
		playersGame[UsuariosActivos[1]].Money.setFillColor(sf::Color::White);
		playersGame[UsuariosActivos[1]].Money.setOutlineThickness(2);
		playersGame[UsuariosActivos[1]].Money.setOutlineColor(sf::Color(135, 135, 135));
		playersGame[UsuariosActivos[1]].Money.setPosition(1170.65f, 85.5f);

		playersGame[UsuariosActivos[1]].PieceSelect.setScale(1, 1);
		globalBounds = playersGame[UsuariosActivos[1]].PieceSelect.getGlobalBounds();
		playersGame[UsuariosActivos[1]].PieceSelect.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
		moverFichas[UsuariosActivos[1]].Inicializar(&playersGame[UsuariosActivos[1]].PieceSelect, &casillas2);

		
		playersGame[UsuariosActivos[1]].CashSprite.setOrigin(25, 20);
		playersGame[UsuariosActivos[1]].CashSprite.setPosition(370, 400);

		playersGame[1].PieceSelect.setPosition(354, 427);
	}
	else {
		return;
	}

	//perfil 3
		if (UsuariosActivos.size() >= 3) {

			playersGame[UsuariosActivos[2]].NamePlayer.setPosition(188.65f, 552.5f);

			playersGame[UsuariosActivos[2]].boxPlayer.setPosition(188.65f, 552.5f);
			playersGame[UsuariosActivos[2]].boxPlayer.setScale(0.7f, 0.7f);

			playersGame[UsuariosActivos[2]].MarcoPlayer.setTexture(TextureMarco);
			globalBounds = playersGame[UsuariosActivos[2]].MarcoPlayer.getGlobalBounds();
			playersGame[UsuariosActivos[2]].MarcoPlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

			playersGame[UsuariosActivos[2]].MarcoPlayer.setPosition(52.5f, 552.5f);

			playersGame[UsuariosActivos[2]].AvatarPlayer.setTexture(&playersGame[UsuariosActivos[2]].textureAvatarPLayer);
			playersGame[UsuariosActivos[2]].AvatarPlayer.setRadius(static_cast<float>(playersGame[UsuariosActivos[2]].textureAvatarPLayer.getSize().x / 2));
			playersGame[UsuariosActivos[2]].AvatarPlayer.setOrigin(64, 64);
			playersGame[UsuariosActivos[2]].AvatarPlayer.setPosition(52.5f, 552.5f);
			playersGame[UsuariosActivos[2]].AvatarPlayer.setScale(0.7f, 0.7f);

			playersGame[UsuariosActivos[2]].Money.setString(std::to_string(playerInfos[UsuariosActivos[2]].money));
			playersGame[UsuariosActivos[2]].Money.setCharacterSize(17);
			playersGame[UsuariosActivos[2]].Money.setFont(fontUser);
			playersGame[UsuariosActivos[2]].Money.setFillColor(sf::Color::White);
			playersGame[UsuariosActivos[2]].Money.setOutlineThickness(2);
			playersGame[UsuariosActivos[2]].Money.setOutlineColor(sf::Color(135, 135, 135));
			playersGame[UsuariosActivos[2]].Money.setPosition(170.65f, 585.5f);

			playersGame[UsuariosActivos[2]].PieceSelect.setScale(1, 1);
			globalBounds = playersGame[UsuariosActivos[2]].PieceSelect.getGlobalBounds();
			playersGame[UsuariosActivos[2]].PieceSelect.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

			moverFichas[UsuariosActivos[2]].Inicializar(&playersGame[UsuariosActivos[2]].PieceSelect, &casillas1);


			playersGame[UsuariosActivos[2]].CashSprite.setOrigin(25, 20);
			playersGame[UsuariosActivos[2]].CashSprite.setPosition(370, 400);

			playersGame[2].PieceSelect.setPosition(399, 427);
		}else{
			return;
		}
	//perfil 4

		if (UsuariosActivos.size() >= 4) {
			playersGame[UsuariosActivos[3]].NamePlayer.setPosition(1188.65f, 552.5f)
				;
			playersGame[UsuariosActivos[3]].boxPlayer.setPosition(1188.65f, 552.5f);
			playersGame[UsuariosActivos[3]].boxPlayer.setScale(0.7f, 0.7f);

			playersGame[UsuariosActivos[3]].MarcoPlayer.setTexture(TextureMarco);
			globalBounds = playersGame[UsuariosActivos[3]].MarcoPlayer.getGlobalBounds();
			playersGame[UsuariosActivos[3]].MarcoPlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

			playersGame[UsuariosActivos[3]].MarcoPlayer.setPosition(1052.5f, 552.5f);

			playersGame[UsuariosActivos[3]].Money.setString(std::to_string(playerInfos[UsuariosActivos[3]].money));
			playersGame[UsuariosActivos[3]].Money.setCharacterSize(17);
			playersGame[UsuariosActivos[3]].Money.setFont(fontUser);
			playersGame[UsuariosActivos[3]].Money.setFillColor(sf::Color::White);
			playersGame[UsuariosActivos[3]].Money.setOutlineThickness(2);
			playersGame[UsuariosActivos[3]].Money.setOutlineColor(sf::Color(135, 135, 135));
			playersGame[UsuariosActivos[3]].Money.setPosition(1170.65f, 585.5f);

			playersGame[UsuariosActivos[3]].AvatarPlayer.setTexture(&playersGame[UsuariosActivos[3]].textureAvatarPLayer);
			playersGame[UsuariosActivos[3]].AvatarPlayer.setRadius(static_cast<float>(playersGame[UsuariosActivos[3]].textureAvatarPLayer.getSize().x / 2));
			playersGame[UsuariosActivos[3]].AvatarPlayer.setOrigin(64, 64);

			playersGame[UsuariosActivos[3]].AvatarPlayer.setPosition(1052.5f, 552.5f);
			playersGame[UsuariosActivos[3]].AvatarPlayer.setScale(0.7f, 0.7f);

			playersGame[UsuariosActivos[3]].PieceSelect.setScale(1, 1);
			globalBounds = playersGame[UsuariosActivos[3]].PieceSelect.getGlobalBounds();
			playersGame[UsuariosActivos[3]].PieceSelect.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
			moverFichas[UsuariosActivos[3]].Inicializar(&playersGame[UsuariosActivos[3]].PieceSelect, &casillas3);


			playersGame[UsuariosActivos[3]].CashSprite.setOrigin(25, 20);
			playersGame[UsuariosActivos[3]].CashSprite.setPosition(370, 400);

			playersGame[3].PieceSelect.setPosition(428, 440);
		}
}
void MultiplayerGame::update() {

	positionPefil();

	sf::Clock clock;

	resultadoDado = 0;
	mousePosition = sf::Mouse::getPosition(*window);
	mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

	SelectingMusicFondo.stop();
	GameMusicFondo.setLoop(true);
	GameMusicFondo.play();
	Nulo NUlO;
	NUlO.setWindow(*window);
	NUlO.Resource(&client);       

	float duracionMovimiento = 0.5f;

	
	std::vector<HouseBuy> house(UsuariosActivos.size());

	for (int i = 0; i < UsuariosActivos.size(); i++) {

		house[i].setWindow(*window, i);
		house[i].resource(&client);

	}

	Stealplayer robarjugador(window, UsuariosActivos, playersGame);
	robarjugador.resource();

	Dado.start(1280, 720);
	int DadoResul = 0;
	//GameEnd gameend(window);
   // gameend.update();

	animacionRuleta = false;
	InicioPartida();
	//std::cout << "\n4NOoooooooooooooooooooooooooooooooooooooooooooooooooooo";
	while (window->isOpen()) {
		//ruleta_draw = true;
		//impuesto_draw = true;
		Event();
		Dado.loopP(&client);
		// dado mecanica 
		resultadoDado = Dado.logica();
		if (resultadoDado != 0) {
			DadoResul = resultadoDado;
			TempoAnimacion.restart();
		}
		// mecanica ruleta
		if (animacionRuleta == true && !animacionIniciada) {
			TempoAnimacion.restart();
			animacionRuleta = false;
			animacionIniciada = true;
		}
		// mecanica ruleta
		if (client.giroActivo == true && animacionRuleta == true && ruleta_draw && TempoAnimacion.getElapsedTime().asSeconds() >= 4.0f) {
			client.giroActivo = false;
			ruleta_draw = false;
			eventoActivo = false;
			animacionIniciada = false;
			animacionRuleta = false;
		}

		// mecanica Impuesto
		if (animacionImpuesto == true && !animacionIniciada) {
			TempoAnimacion.restart();
			animacionImpuesto = false;
			animacionIniciada = true;
			//std::cout << "animacionImpuesto entro: " << std::boolalpha << animacionImpuesto << "\n";
		}

		if (animacionImpuesto == false && animacionIniciada && impuesto_draw && TempoAnimacion.getElapsedTime().asSeconds() >= 4.0f) {

			impuesto_draw = false;
			eventoActivo = false;
			animacionIniciada = false;
			animacionImpuesto = false;
		}

		currentCursor = &normalCursor;

		window->setMouseCursor(*currentCursor);
		Conteosuel.setString(std::to_string(conteosuel));


		if (DadoResul != 0 && TempoAnimacion.getElapsedTime().asSeconds() >= 1.0f) {
			turn_dado = false;
			std::cout << "\n FUuyti: "<< IndexTurn;
			moverFichas[IndexTurn].iniciarMovimiento(DadoResul, duracionMovimiento);
			std::cout << "\n FUi";
			DadoResul = 0;
		}

		sf::Clock clock;
		float tiempoRuletaVisible = 3.0f;
		bool ruletaVisible = false;

		float deltaTime = reloj.restart().asSeconds();


		if (!ruleta_draw) {

			switch (ruleta->event)
			{
			case 1:

				casa_draw = true;

				eventoActivo = true;
				break;


			case 2:


				impuesto_draw = true;
				turn_impuesto = false;
				eventoActivo = true;
				animacionImpuesto = true;
				break;

			case 3:
				robarjugador.update();
			default:
				break;
			}
			ruleta->event = 0;

		}


		if (client.turnopermitido != 0 &&nular== false) {
			renderTexture.clear();
			renderTexture.draw(spriteFondoGame);
			renderTexture.draw(spriteMapa);


			for (int i = 0; i < UsuariosActivos.size(); i++)
			{
				renderTexture.draw(playersGame[UsuariosActivos[i]].NamePlayer);
				renderTexture.draw(playersGame[UsuariosActivos[i]].boxPlayer);
				renderTexture.draw(playersGame[UsuariosActivos[i]].AvatarPlayer);
				renderTexture.draw(playersGame[UsuariosActivos[i]].MarcoPlayer);
				renderTexture.draw(playersGame[UsuariosActivos[i]].Money);
				renderTexture.draw(playersGame[UsuariosActivos[i]].PieceSelect);
				renderTexture.draw(playersGame[UsuariosActivos[i]].CashSprite);


			}


			renderTexture.draw(Settings);

			renderTexture.display();
			NUlO.Update();
			nular = true;
		}
		else if (moverFichas[IndexTurn].enMovimiento == true) {
				std::cout << "\nIndex de quien lo mueviendo " << IndexTurn;
				moverFichas[IndexTurn].actualizarMovimiento(deltaTime);
				DrawPieceMoviendo();
				window->display();
		}
			else if (ruleta_draw == true) {

				if (!ruletaVisible) {

					DrawGameRuleta();
					ruletaVisible = true;
					clock.restart();

				}
				else {

					if (clock.getElapsedTime().asSeconds() > tiempoRuletaVisible) {
						ruletaVisible = false;

					}
					else {
						DrawGameRuleta();
					}

				}
				window->display();

			}
			else if (casa_draw) {
				renderTexture.clear();
				renderTexture.draw(spriteFondoGame);
				renderTexture.draw(spriteMapa);


				for (int i = 0; i < UsuariosActivos.size(); i++)
				{
					renderTexture.draw(playersGame[UsuariosActivos[i]].NamePlayer);
					renderTexture.draw(playersGame[UsuariosActivos[i]].boxPlayer);
					renderTexture.draw(playersGame[UsuariosActivos[i]].AvatarPlayer);
					renderTexture.draw(playersGame[UsuariosActivos[i]].MarcoPlayer);
					renderTexture.draw(playersGame[UsuariosActivos[i]].Money);
					renderTexture.draw(playersGame[UsuariosActivos[i]].PieceSelect);
					renderTexture.draw(playersGame[UsuariosActivos[i]].CashSprite);


				}


				renderTexture.draw(Settings);

				renderTexture.display();
				house[IndexTurn].update(playersGame[IndexTurn].PieceSelect.getPosition());
				eventoActivo = false;
				casa_draw = false;

			}
			else  if (impuesto_draw) {

				DrawGameImpuesto();
				window->display();
			}
			else
			{
				DrawGame();
				window->display();
			}





	}

}
void MultiplayerGame::Event() {
	sf::Event event;

	do {
		if (window->pollEvent(event)) {
			Dado.loop(event, &client);

			sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
			sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {

				renderTexture.clear();
				renderTexture.draw(spriteFondoGame);
				renderTexture.draw(spriteMapa);
				for (int i = 0; i < UsuariosActivos.size(); i++) {
					renderTexture.draw(playersGame[UsuariosActivos[i]].NamePlayer);
					renderTexture.draw(playersGame[UsuariosActivos[i]].boxPlayer);
					renderTexture.draw(playersGame[UsuariosActivos[i]].MarcoPlayer);
					renderTexture.draw(playersGame[UsuariosActivos[i]].AvatarPlayer);
				}
				renderTexture.draw(spriteX);
				renderTexture.draw(overlay);

				Menup.MenuSalir();
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				if (Settings.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					Menup.MenuOpcion();
				}



				if (ruleta_draw && turn && turnoGiro) {
					ruleta->trurntrue();
					turnoGiro = false;
				}
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {

				if (ruleta_draw && turn && turnoGiro) {

					client.startSpin();
					ruleta->trurntrue();
					turnoGiro = false;
				}
			}
		}

	} while (window->pollEvent(event));
}
void MultiplayerGame::DrawPieceMoviendo() {

	sf::Vector2f fichaPos = playersGame[IndexTurn].PieceSelect.getPosition();
	float viewX = fichaPos.x;
	float viewY = fichaPos.y;

	if (viewY > 540) viewY = 540;
	if (viewX < 320) viewX = 320;

	if (viewY < 180) viewY = 180;


	view.setCenter(viewX, viewY);

	view.setSize(1280 * 0.5, 720 * 0.5);
	window->setView(view);
	window->clear();

	window->draw(spriteFondoGame);
	window->draw(spriteMapa);
	for (int i = 0; i < UsuariosActivos.size(); i++) {
		window->draw(playersGame[i].PieceSelect);
	}
	window->setView(window->getDefaultView());



}
void MultiplayerGame::DrawGameRuleta() {

	float deltaTime = clock.restart().asSeconds();

	window->clear();

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

	window->draw(renderedSprite);
	ruleta->draw(*window, deltaTime, client.giroActivo);
	if (!client.giroActivo) {
		float deltaTime = clockMensaje.restart().asSeconds();

		// Modificar el escalado
		if (increasing) {
			currentScale += (maxScale - minScale) / (duration / 2) * deltaTime; // Incrementa el escalado
			if (currentScale >= maxScale) {
				currentScale = maxScale;
				increasing = false; // Comienza a reducir el escalado
			}
		}
		else {
			currentScale -= (maxScale - minScale) / (duration / 2) * deltaTime; // Reduce el escalado
			if (currentScale <= minScale) {
				currentScale = minScale;
				increasing = true; // Comienza a aumentar el escalado
			}
		}
		DescripDado.setPosition(640, 550);
		// Aplicar el escalado a DescripDado
		DescripDado.setScale(currentScale, currentScale);

		window->draw(DescripDado);
	}
}

void MultiplayerGame::DrawGameImpuesto() {


	int valor = 100;
	int valortotal;

	valortotal = valor - 50;

	Impuesto.setFont(fontUser);
	Impuesto.setString(std::to_string(valortotal));
	Impuesto.setCharacterSize(24);
	Impuesto.setFillColor(sf::Color::Red);

	Impuesto.setPosition(695, 435);
	globalBounds = Impuesto.getGlobalBounds();
	Impuesto.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	window->clear();

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
	SpriteImpuesto.setTexture(TextureImpuesto);

	SpriteImpuesto.setPosition(640, 360);
	sf::FloatRect globalBounds = SpriteImpuesto.getGlobalBounds();
	SpriteImpuesto.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	renderTexture.draw(overlay);
	renderTexture.display();
	renderedSprite.setTexture(renderTexture.getTexture());

	window->draw(renderedSprite);
	window->draw(SpriteImpuesto);
	window->draw(Impuesto);

}
void MultiplayerGame::InicioPartida() {
	sf::Clock clocks;  // Inicia el temporizador
	sf::Clock deltaClock;
	Bienvenida.setScale(0.5, 0.5);

	float currentScaleX = 0.5f;
	float currentScaleY = 0.5f;
	float targetScaleX = 1.0f;
	float targetScaleY = 1.0f;
	float duration = 1.0f; // Duración en segundos
	float elapsedTime = 0.0f;

	// El bucle solo se ejecutará durante 5 segundos
	while (window->isOpen() && clocks.getElapsedTime().asSeconds() <= 2.5f) {







		float deltaTime = deltaClock.restart().asSeconds();
		elapsedTime += deltaTime;

		// Calcula el nuevo escalado basado en el tiempo
		if (elapsedTime < duration) {
			float progress = elapsedTime / duration;
			currentScaleX = 0.5f + progress * (targetScaleX - 0.5f);
			currentScaleY = 0.5f + progress * (targetScaleY - 0.5f);
			Bienvenida.setScale(currentScaleX, currentScaleY);
		}
		else {
			// Asegúrate de que el escalado final sea exactamente el objetivo
			Bienvenida.setScale(targetScaleX, targetScaleY);
		}

		window->setView(window->getDefaultView());
		window->clear();  // Limpia la ventana para dibujar la siguiente pantalla

		// Dibuja los elementos de fondo y mapa
		window->draw(spriteFondoGame);
		window->draw(spriteMapa);

		// Actualiza el dado y calcula el tiempo transcurrido
		Dado.update();

		// Dibuja los jugadores en la pantalla
		for (int i = 0; i < UsuariosActivos.size(); i++) {
			window->draw(playersGame[UsuariosActivos[i]].NamePlayer);
			window->draw(playersGame[UsuariosActivos[i]].boxPlayer);
			window->draw(playersGame[UsuariosActivos[i]].AvatarPlayer);
			window->draw(playersGame[UsuariosActivos[i]].MarcoPlayer);
			window->draw(playersGame[UsuariosActivos[i]].Money);
			window->draw(playersGame[UsuariosActivos[i]].PieceSelect);
			window->draw(playersGame[UsuariosActivos[i]].CashSprite);
		}



		// Dibuja los settings (configuración) al final
		window->draw(Settings);
		window->draw(overlay);
		window->draw(Bienvenida);
		// Muestra todo lo que se ha dibujado en la ventana
		window->display();
	}
}
void MultiplayerGame::DrawGame() {

	if (turn) {
		if (!eventoActivo) {

			if (turn_ruleta && giroRule && !turn_dado && !turn_Moviendo) {

				for (int i = 0; i < casillasRuleta.size(); i++)
				{
					if (playersGame[IndexTurn].PieceSelect.getPosition() == casillasRuleta[i])
					{
						client.EventoRuleta();
						ruleta_draw = true;
						turn_ruleta = false;
						eventoActivo = true;
						turnoGiro = true;
						ruleta->enviarestado();
						ruleta->trurntrue();
					}
				}
				giroRule = false;
				turn_ruleta = false;

			}

			if (turn_casa && !turn_dado && !turn_Moviendo) {

				for (int i = 0; i < caminocasa.size(); i++)
				{
					if (playersGame[IndexTurn].PieceSelect.getPosition() == caminocasa[i])
					{
						client.EventoCasa();
						casa_draw = true;
						eventoActivo = true;
					}
				}
				turn_casa = false;
			}
		}

		if (turn_impuesto && !turn_dado && !turn_Moviendo) {
			for (int i = 0; i < caminoimpuesto.size(); i++)
			{
				if (playersGame[IndexTurn].PieceSelect.getPosition() == caminoimpuesto[i])
				{
					client.EventoImpuesto();
					impuesto_draw = true;
					turn_impuesto = false;
					eventoActivo = true;
					animacionImpuesto = true;
				}
			}
			turn_impuesto = false;
		}
	}

	if (userRuleta) {
		ruleta_draw = true;
		turn_ruleta = false;
		eventoActivo = true;

		{
			std::unique_lock<std::mutex> lock(client.ruletaMutex);
			client.ruletaCondVar.wait(lock, [] { return client.ruletaMessageReceived; });

			client.ruletaMessageReceived = false;
		}

		ruleta->trurntrue();
		giroRule = false;
		turn_ruleta = false;
		userRuleta = false;
	}
	if (userCasa) {
		casa_draw = true;
		eventoActivo = true;
		userCasa = false;
		turn_casa = false;
	}
	if (userImpuesto) {

		impuesto_draw = true;
		turn_impuesto = false;
		eventoActivo = true;
		animacionImpuesto = true;
		userImpuesto = false;

	}



	if (turn && !turn_impuesto && !turn_casa && !turn_ruleta && !turn_dado && !turn_Moviendo && !eventoActivo && !impuesto_draw && !casa_draw && !ruleta_draw) {

		client.endTurn();
		turn = false;
		//std::cout << "\nTurno antes de enviar  de " << IndexTurn << "finalizo";
	}

	window->setView(window->getDefaultView());

	window->clear();

	window->draw(spriteFondoGame);
	window->draw(spriteMapa);

	Dado.update();
	float deltaTime = clock.restart().asSeconds();

	for (int i = 0; i < UsuariosActivos.size(); i++)
	{
		window->draw(playersGame[UsuariosActivos[i]].NamePlayer);
		window->draw(playersGame[UsuariosActivos[i]].boxPlayer);
		window->draw(playersGame[UsuariosActivos[i]].AvatarPlayer);
		window->draw(playersGame[UsuariosActivos[i]].MarcoPlayer);
		window->draw(playersGame[UsuariosActivos[i]].Money);
		window->draw(playersGame[UsuariosActivos[i]].PieceSelect);
		window->draw(playersGame[UsuariosActivos[i]].CashSprite);


	}
	if (turn_dado) {
		float deltaTime = clockMensaje.restart().asSeconds();

		// Modificar el escalado
		if (increasing) {
			currentScale += (maxScale - minScale) / (duration / 2) * deltaTime; // Incrementa el escalado
			if (currentScale >= maxScale) {
				currentScale = maxScale;
				increasing = false; // Comienza a reducir el escalado
			}
		}
		else {
			currentScale -= (maxScale - minScale) / (duration / 2) * deltaTime; // Reduce el escalado
			if (currentScale <= minScale) {
				currentScale = minScale;
				increasing = true; // Comienza a aumentar el escalado
			}
		}
		DescripDado.setPosition(640, 450);
		// Aplicar el escalado a DescripDado
		DescripDado.setScale(currentScale, currentScale);

		window->draw(DescripDado);
	}



	window->draw(Settings);
	window->draw(Conteosuel);
}