#include "GameMode.hpp"
#include <String>
GameMode::GameMode(sf::RenderWindow& win) : window(&win), Dado(window), ruleta(500.0f, 500.0f, 640.0f, 360.0f), validar(false), moverFichas(4, MovePieces(win)), ruledraw(false){
	loadResourceGame();
	resource();
}

void GameMode::resource() {
	if (!TextureMapa.loadFromFile("resource/texture/Game/mapa+S+++.png")) return;
	if (!SettingsOff.loadFromFile("resource/texture/Game/settingOff.png")) return;
	if (!SettingsOn.loadFromFile("resource/texture/Game/settingOn.png")) return;

	//Cargar Texturas de Flechas
	if (!TextureArrowIzq.loadFromFile("resource/texture/Game/Izq.png")) return;
	if (!TextureArrowDer.loadFromFile("resource/texture/Game/Der.png")) return;
	if (!TextureArrowArriba.loadFromFile("resource/texture/Game/Arriba.png")) return;

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

	DiceSound.setBuffer(DiceBuffer);

	// Vector para cada grupo de casillas (caminos)
	std::vector<sf::Vector2f> camino1 = { sf::Vector2f(375, 480) };

	std::vector<sf::Vector2f> caminoruleta1 = { sf::Vector2f(0, 0) };

	


	// Agregar los caminos al vector principal
	for (int i = 0; i < 4; i++) {

		globalBounds = playersGame[i].NamePlayer.getGlobalBounds();
		playersGame[i].NamePlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
		playersGame[i].MarcoPlayer.setOrigin(45.5f, 45.5f);
	}
	casillas.push_back(camino1);
	casillasRuleta.push_back(caminoruleta1);



	view.setSize(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y));
	view.setCenter(playersGame[0].PieceSelect.getPosition()); // Centrar la vista en la ficha


	posicionActual = 0;
}

void GameMode::update() {

	playersGame[0].textureAvatarPLayer = *selectedAvatarCopy.getTexture();
	for (int i = 0; i < 4; i++)
	{
		playersGame[i].Money.setString(std::to_string(playerInfos[i].money));
		playersGame[i].Money.setCharacterSize(17);
		playersGame[i].Money.setFont(fontUser);
		playersGame[i].Money.setFillColor(sf::Color::White);
		playersGame[i].Money.setOutlineThickness(2);
		playersGame[i].Money.setOutlineColor(sf::Color(135, 135, 135));
		playersGame[i].PieceSelect.setScale(1, 1);
		globalBounds = playersGame[i].PieceSelect.getGlobalBounds();
		playersGame[i].PieceSelect.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

		playersGame[i].AvatarPlayer.setTexture(&playersGame[i].textureAvatarPLayer);
		playersGame[i].AvatarPlayer.setRadius(static_cast<float>(playersGame[i].textureAvatarPLayer.getSize().x / 2));
		playersGame[i].AvatarPlayer.setOrigin(64, 64);
		moverFichas[i].Inicializar(&playersGame[i].PieceSelect, &casillas, &casillasRuleta,&casillasimpuesto);
	}
	
	animacionIniciada = false;

	playersGame[0].PieceSelect.setPosition(330, 439);
	playersGame[1].PieceSelect.setPosition(354, 427);
	playersGame[2].PieceSelect.setPosition(399, 427);
	playersGame[3].PieceSelect.setPosition(428, 440);


	sf::Clock clock;
	resultadoDado = 0;
	mousePosition = sf::Mouse::getPosition(*window);
	mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

	playersGame[0].NamePlayer.setPosition(188.65f, 62.5f);
	playersGame[0].boxPlayer.setPosition(188.65f, 62.5f);
	playersGame[0].boxPlayer.setScale(0.7f, 0.7f);
	playersGame[0].MarcoPlayer.setPosition(52.5f, 62.5f);
	playersGame[0].Money.setPosition(170.65f, 95.5f);
	/// const sf::Texture* texture = 
	// if (texture != nullptr) {
	  //   playersGame[0].AvatarPlayer.setTexture(texture);

   //  }

	playersGame[0].AvatarPlayer.setPosition(52.5f, 62.5f);
	playersGame[0].AvatarPlayer.setScale(0.7f, 0.7f);


	//perfil 2

	playersGame[1].NamePlayer.setPosition(188.65f, 552.5f);
	playersGame[1].boxPlayer.setPosition(188.65f, 552.5f);
	playersGame[1].boxPlayer.setScale(0.7f, 0.7f);
	playersGame[1].MarcoPlayer.setPosition(1052.5f, 52.5f);
	playersGame[1].AvatarPlayer.setPosition(1052.5f, 552.5f);
	playersGame[1].AvatarPlayer.setScale(0.7f, 0.7f);
	playersGame[1].Money.setPosition(170.65f, 585.5f);

	//perfil 3
	playersGame[2].NamePlayer.setPosition(1188.65f, 52.5f);
	playersGame[2].boxPlayer.setPosition(1188.65f, 52.5f);
	playersGame[2].boxPlayer.setScale(0.7f, 0.7f);
	playersGame[2].MarcoPlayer.setPosition(52.5f, 552.5f);
	playersGame[2].AvatarPlayer.setPosition(52.5f, 552.5f);
	playersGame[2].Money.setPosition(1170.65f, 85.5f);

	//perfil 4
	playersGame[3].NamePlayer.setPosition(1188.65f, 552.5f);
	playersGame[3].boxPlayer.setPosition(1188.65f, 552.5f);
	playersGame[3].boxPlayer.setScale(0.7f, 0.7f);
	playersGame[3].MarcoPlayer.setPosition(1052.5f, 552.5f);
	playersGame[3].Money.setPosition(1170.65f, 585.5f);



	float duracionMovimiento = 0.5f;



	playersGame[3].AvatarPlayer.setPosition(1052.5f, 652.5f);
	playersGame[3].AvatarPlayer.setScale(0.7f, 0.7f);


	Dado.start(1280, 720);
	int DadoResul = 0;


	muerte = false;

	while (window->isOpen()) {

		Event();
		//std::cout << "\n la cagaste princi:";
		resultadoDado = Dado.logica();
		if (resultadoDado != 0) {
			DadoResul = resultadoDado;
			TempoAnimacion.restart();
		}

		if (muerte == true && !animacionIniciada) {
			TempoAnimacion.restart();
			muerte = false;
			animacionIniciada = true;    // Marcar que ya se ha iniciado la animación
		}

		if (validar == true && muerte == true && TempoAnimacion.getElapsedTime().asSeconds() >= 4.0f) {
			std::cout << "\ntempo  " << TempoAnimacion.getElapsedTime().asSeconds();
			std::cout << "feo";
			validar = false;
			ruledraw = false;
			animacionIniciada = false;
			muerte = false;
		}

		currentCursor = &normalCursor;

		window->setMouseCursor(*currentCursor);

		if (DadoResul != 0 && TempoAnimacion.getElapsedTime().asSeconds() >= 1.0f) {
			turn_dado = false;
			moverFichas[IndexTurn].iniciarMovimiento(DadoResul, duracionMovimiento);
			DadoResul = 0;
		}

		// Variables para controlar el temporizador
		sf::Clock clock;
		float tiempoRuletaVisible = 3.0f; // 3 segundos
		bool ruletaVisible = false;

		// En tu lógica de juego:
		float deltaTime = reloj.restart().asSeconds();
		//std::cout << "\n la cagaste medio:";


		if (moverFichas[IndexTurn].enMovimiento == true) {
			moverFichas[IndexTurn].actualizarMovimiento(deltaTime);
			DrawPieceMoviendo();
		}
		else if (ruledraw == true) {
			if (!ruletaVisible) {
				// Mostrar la ruleta y reiniciar el temporizador
				DrawGameRuleta();
				ruletaVisible = true;
				clock.restart(); // Reinicia el reloj
				std::cout << "false";
			}
			else {
				// Verifica si ha pasado el tiempo
				if (clock.getElapsedTime().asSeconds() > tiempoRuletaVisible) {
					ruletaVisible = false; // Oculta la ruleta
				}
				else {
					DrawGameRuleta(); // Mantén la ruleta visible
				}
				std::cout << "true";
			}
		}
		else {
			DrawGame();
		}

		window->display();
		//std::cout << "\n la cagaste display:";
	}
	
}

void  GameMode::Event() {

	sf::Event event;

	while (window->pollEvent(event)) {


		Dado.loop(event, &client);
	
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
		sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

		if (event.type == sf::Event::Closed ||
			(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {

			renderTexture.clear();
			renderTexture.draw(spriteFondoGame);
			renderTexture.draw(spriteMapa);
			for (int i = 0; i < 4; i++)
			{
				renderTexture.draw(playersGame[i].NamePlayer);
				renderTexture.draw(playersGame[i].boxPlayer);
				renderTexture.draw(playersGame[i].MarcoPlayer);
				renderTexture.draw(playersGame[i].AvatarPlayer);
			}
			renderTexture.draw(spriteX);
			renderTexture.draw(overlay);

			Menup.MenuSalir();
			//  running = false;
		}


		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

			if (Settings.getGlobalBounds().contains(mousePosFloat)) {
				playClickSound();

				Menup.MenuOpcion();

			}
			if(ruledraw){
			validar = true;}

		}

	}


}

void GameMode::DrawPieceMoviendo(  ) {
	//std::cout << "\n la cagaste Movi:";
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
	//for (const auto& s : rastro) {
	 //   window->draw(s);
	///}
	window->draw(playersGame[IndexTurn].PieceSelect);
	window->setView(window->getDefaultView());


	std::cout << "\n la cagaste movi2:";
}


void GameMode::DrawGameRuleta() {
	//std::cout << "\n la cagaste rule:";
	float deltaTime = clock.restart().asSeconds();

	window->clear();

	renderTexture.clear();

	renderTexture.draw(spriteFondoGame);
	renderTexture.draw(spriteMapa);
	for (int i = 0; i < 4; i++)
	{
		renderTexture.draw(playersGame[i].NamePlayer);
		renderTexture.draw(playersGame[i].boxPlayer);
		renderTexture.draw(playersGame[i].MarcoPlayer);
		renderTexture.draw(playersGame[i].AvatarPlayer);

	}
	renderTexture.draw(overlay);

	renderTexture.display();

	renderedSprite.setTexture(renderTexture.getTexture());

	window->draw(renderedSprite);
	ruleta.draw(*window, deltaTime, validar);
}

void GameMode::DrawGame() {
	int CaminoActu = moverFichas[IndexTurn].getCaminoActual();
	//CaminoActu -= 1;
	int cas= moverFichas[0].getcasillaActual();


	std::cout << "\n CaminoActu:"<< CaminoActu<<"casilla:" <<cas;


	if(turn_ruleta){

	if(casillasRuleta.size()> CaminoActu && CaminoActu >= 1){

	for (int i = 0; i < casillasRuleta[CaminoActu].size(); i++)
	{
		if (playersGame[IndexTurn].PieceSelect.getPosition() == casillasRuleta[CaminoActu][i])
		{
			ruledraw = true;
			turn_ruleta = false;
			ruleta.trurntrue();
		}
	}
	}
	}
	else if(turn_casa) {


	}else if(turn_impuesto) {


	}if( turn && !turn_impuesto && !turn_casa &&!turn_ruleta && !turn_dado) {
		client.endTurn();
		turn = false;
	}

	window->setView(window->getDefaultView());



	window->clear();

	window->draw(spriteFondoGame);
	window->draw(spriteMapa);

	Dado.update();
	float deltaTime = clock.restart().asSeconds();

	//ruleta.draw(*window, deltaTime, validar);
	for (int i = 0; i < 4; i++)
	{
		window->draw(playersGame[i].NamePlayer);
		window->draw(playersGame[i].boxPlayer);
		window->draw(playersGame[i].AvatarPlayer);
		window->draw(playersGame[i].MarcoPlayer);
		window->draw(playersGame[i].Money);
		window->draw(playersGame[i].PieceSelect);


	}

	window->draw(Settings);
}