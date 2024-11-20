#include "GameMode.hpp"
#include <String>
#include "GameEnd.hpp"


GameMode::GameMode(sf::RenderWindow& win) : window(&win), Dado(window), ruleta(500.0f, 500.0f, 640.0f, 360.0f), validar(false), moverFichas(4, MovePieces(win)), ruleta_draw(false) {
	loadResourceGame();
	resource();
}

void GameMode::resource() {
	if (!TextureMapa.loadFromFile("resource/texture/Game/mapa+S+++.png")) return;
	if (!SettingsOff.loadFromFile("resource/texture/Game/settingOff.png")) return;
	if (!SettingsOn.loadFromFile("resource/texture/Game/settingOn.png")) return;
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

	DiceSound.setBuffer(DiceBuffer);

	std::vector<sf::Vector2f> camino1 = { sf::Vector2f(375, 480) };

	for (int i = 0; i < 4; i++) {

		globalBounds = playersGame[i].NamePlayer.getGlobalBounds();
		playersGame[i].NamePlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
		playersGame[i].MarcoPlayer.setOrigin(45.5f, 45.5f);
	}
	casillas0.push_back(camino1);
	casillas1.push_back(camino1);
	casillas2.push_back(camino1);
	casillas3.push_back(camino1);
	
	view.setSize(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y));
	view.setCenter(playersGame[0].PieceSelect.getPosition()); // Centra la vista en la ficha


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
		
	}
	
	for (const auto& posicion : caminoimpuesto) {
		sf::CircleShape punto(5); // Radio de 5
		punto.setFillColor(sf::Color::Red); // Color rojo para los puntos
		punto.setOrigin(5, 5); // Centrar el origen del círculo
		punto.setPosition(posicion);
		puntos.push_back(punto);
	}

	moverFichas[0].Inicializar(&playersGame[0].PieceSelect, &casillas0, &casillasimpuesto0);
	moverFichas[1].Inicializar(&playersGame[1].PieceSelect, &casillas1, &casillasimpuesto1);
	moverFichas[2].Inicializar(&playersGame[2].PieceSelect, &casillas2, &casillasimpuesto2);
	moverFichas[3].Inicializar(&playersGame[3].PieceSelect, &casillas3, &casillasimpuesto3);


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


	playersGame[0].AvatarPlayer.setPosition(52.5f, 62.5f);
	playersGame[0].AvatarPlayer.setScale(0.7f, 0.7f);


	//perfil 2

	playersGame[1].NamePlayer.setPosition(188.65f, 552.5f);
	playersGame[1].boxPlayer.setPosition(188.65f, 552.5f);
	playersGame[1].boxPlayer.setScale(0.7f, 0.7f);
	playersGame[1].MarcoPlayer.setPosition(52.5f, 552.5f); 
	playersGame[1].AvatarPlayer.setPosition(52.5f, 552.5f);
	playersGame[1].AvatarPlayer.setScale(0.7f, 0.7f);
	playersGame[1].Money.setPosition(170.65f, 585.5f);

	//perfil 3
	globalBounds = playersGame[2].NamePlayer.getGlobalBounds();
	playersGame[2].NamePlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	playersGame[2].NamePlayer.setPosition(1188.65f, 52.5f);
	playersGame[2].boxPlayer.setPosition(1188.65f, 52.5f);
	playersGame[2].boxPlayer.setScale(0.7f, 0.7f);
	playersGame[2].MarcoPlayer.setPosition(1052.5f, 52.5f);
	playersGame[2].AvatarPlayer.setPosition(1052.5f, 52.5f);
	playersGame[2].AvatarPlayer.setScale(0.7f, 0.7f);
	playersGame[2].Money.setPosition(1170.65f, 85.5f);

	//perfil 4
	playersGame[3].NamePlayer.setPosition(1188.65f, 552.5f);
	playersGame[3].boxPlayer.setPosition(1188.65f, 552.5f);
	playersGame[3].boxPlayer.setScale(0.7f, 0.7f);
	playersGame[3].MarcoPlayer.setPosition(1052.5f, 552.5f);
	playersGame[3].Money.setPosition(1170.65f, 585.5f);
	playersGame[3].AvatarPlayer.setPosition(1052.5f, 552.5f);
	playersGame[3].AvatarPlayer.setScale(0.7f, 0.7f);


	float duracionMovimiento = 0.5f;



	
	HouseBuy houseee;
	houseee.setWindow(*window);

	houseee.resource();
	Dado.start(1280, 720);
	int DadoResul = 0;
	//GameEnd gameend(window);
	//gameend.update();
	animacionRuleta = false;

	while (window->isOpen()) {

		Event();
		Dado.loopP( &client);
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
		if (validar == true && animacionRuleta == true&& ruleta_draw && TempoAnimacion.getElapsedTime().asSeconds() >= 4.0f) {
			std::cout << "\ntempo  " << TempoAnimacion.getElapsedTime().asSeconds();
			std::cout << "feo";
			validar = false;
			ruleta_draw = false;
			animacionIniciada = false;
			animacionRuleta = false;
			std::cout << "error Ruleta: \n";
		}

		// mecanica Impuesto
		if (animacionImpuesto == true && !animacionIniciada) {
			TempoAnimacion.restart();
			animacionImpuesto = false;
			animacionIniciada = true;
			std::cout << "animacionImpuesto entro: " << std::boolalpha << animacionImpuesto << "\n";
		}
		// mecanica Impuesto

		//std::cout << "animacionImpuesto: " << std::boolalpha << animacionImpuesto << "\n";
		//std::cout << "animacionIniciada: " << std::boolalpha << animacionIniciada << "\n";
		//std::cout << "Tiempo transcurrido: " << TempoAnimacion.getElapsedTime().asSeconds() << "\n";

		if (animacionImpuesto == false && animacionIniciada && impuesto_draw && TempoAnimacion.getElapsedTime().asSeconds() >= 4.0f) {
			//std::cout << "\ntempo  " << TempoAnimacion.getElapsedTime().asSeconds();
			//std::cout << "feo";
			
			impuesto_draw = false;
			animacionIniciada = false;
			animacionImpuesto = false;
		}

		/*/ mecanica Casa
		if (animacionCasa == true && !animacionIniciada) {
			TempoAnimacion.restart();
			animacionCasa = false;
			animacionIniciada = true;
			std::cout << "error Casa: \n";
		}
		// mecanica Casa
		if (animacionIniciada == true && animacionCasa == false && casa_draw &&TempoAnimacion.getElapsedTime().asSeconds() >= 4.0f) {
			//std::cout << "\ntempo  " << TempoAnimacion.getElapsedTime().asSeconds();
			//std::cout << "feo";
			//std::cout << "error Casa 2: \n";
			casa_draw = false;
			animacionIniciada = false;
			animacionCasa = false;
		}*/


		//cursor
		currentCursor = &normalCursor;

		window->setMouseCursor(*currentCursor);


		//dado mecanica movimiento

		if (DadoResul != 0 && TempoAnimacion.getElapsedTime().asSeconds() >= 1.0f) {
			turn_dado = false;
			std::cout << "\nIndex de quien lo mueve " << IndexTurn;
			moverFichas[IndexTurn].iniciarMovimiento(DadoResul, duracionMovimiento);
			DadoResul = 0;
		}

		sf::Clock clock;
		float tiempoRuletaVisible = 3.0f; 
		bool ruletaVisible = false;

	
		float deltaTime = reloj.restart().asSeconds();

//		DrawGameImpuesto();
		
		if (moverFichas[IndexTurn].enMovimiento == true) {
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

			
			for (int i = 0; i < 4; i++)
			{
				renderTexture.draw(playersGame[i].NamePlayer);
				renderTexture.draw(playersGame[i].boxPlayer);
				renderTexture.draw(playersGame[i].AvatarPlayer);
				renderTexture.draw(playersGame[i].MarcoPlayer);
				renderTexture.draw(playersGame[i].Money);
				renderTexture.draw(playersGame[i].PieceSelect);


			}
		

			renderTexture.draw(Settings);
			
			renderTexture.display();
			houseee.update(playersGame[0].PieceSelect.getPosition());
	
			casa_draw = false;
		
		}else  if (impuesto_draw) {

			DrawGameImpuesto();
			window->display();
		}else
		{
			DrawGame();
			window->display();
		}



	
		
	}
	
}

void GameMode::Event() {
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
				for (int i = 0; i < 4; i++) {
					renderTexture.draw(playersGame[i].NamePlayer);
					renderTexture.draw(playersGame[i].boxPlayer);
					renderTexture.draw(playersGame[i].MarcoPlayer);
					renderTexture.draw(playersGame[i].AvatarPlayer);
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
				if (ruleta_draw) {
					validar = true;
				}
			}
		}

	} while (window->pollEvent(event));  
}

void GameMode::DrawPieceMoviendo(  ) {
	
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

	window->draw(playersGame[IndexTurn].PieceSelect);
	window->setView(window->getDefaultView());



}


void GameMode::DrawGameRuleta() {
	
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
void GameMode::DrawGameCasa() {



}


void GameMode::DrawGameImpuesto() {



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

	SpriteImpuesto.setTexture(TextureImpuesto);
    SpriteImpuesto.setOrigin(310.0f, 310.0f);
	SpriteImpuesto.setPosition(640, 360);


	renderTexture.draw(overlay);

	renderTexture.display();

	renderedSprite.setTexture(renderTexture.getTexture());

	window->draw(renderedSprite);
	window->draw(SpriteImpuesto);
	
}



void GameMode::DrawGame() {
	int CaminoActu = moverFichas[IndexTurn].getCaminoActual();
	//CaminoActu -= 1;
	int cas= moverFichas[0].getcasillaActual();


	//std::cout << "\n CaminoActu:"<< CaminoActu<<"casilla:" <<cas;
	
	

	if(turn_ruleta && giroRule){

	

	for (int i = 0; i < casillasRuleta.size(); i++)
	{
		if (playersGame[IndexTurn].PieceSelect.getPosition() == casillasRuleta[i])
		{
			ruleta_draw = true;
			turn_ruleta = false;
			ruleta.trurntrue();
		}
	}
	giroRule = false;
	turn_ruleta = false;
	
	}
	else if(turn_casa) {
		for (int i = 0; i < caminocasa.size(); i++)
		{
			if (playersGame[IndexTurn].PieceSelect.getPosition() == caminocasa[i])
			{
				casa_draw = true;
			}
		}
		
		turn_casa = false;
		
	}else if(turn_impuesto) {
		for (int i = 0; i < caminoimpuesto.size(); i++)
		{
			if (playersGame[IndexTurn].PieceSelect.getPosition() == caminoimpuesto[i])
			{
				impuesto_draw = true;
				turn_impuesto = false;
				animacionImpuesto = true;
			}
		}

		turn_impuesto = false;

	}if( turn && !turn_impuesto && !turn_casa &&!turn_ruleta && !turn_dado) {
		client.endTurn();
		turn = false;
		std::cout << "\nTurno antes de enviar  de " << IndexTurn << "finalizo";
	}
	

	// Imprimir los valores de las variables
	//std::cout << "Estado de turn: " << turn << std::endl;
	//std::cout << "Estado de turn_impuesto: " << turn_impuesto << std::endl;
	//std::cout << "Estado de turn_casa: " << turn_casa << std::endl;
	//std::cout << "Estado de turn_ruleta: " << turn_ruleta << std::endl;
	//std::cout << "Estado de turn_dado: " << turn_dado << std::endl;

	window->setView(window->getDefaultView());



	window->clear();

	window->draw(spriteFondoGame);
	window->draw(spriteMapa);

	Dado.update();
	float deltaTime = clock.restart().asSeconds();

	for (int i = 0; i < 4; i++)
	{
		window->draw(playersGame[i].NamePlayer);
		window->draw(playersGame[i].boxPlayer);
		window->draw(playersGame[i].AvatarPlayer);
		window->draw(playersGame[i].MarcoPlayer);
		window->draw(playersGame[i].Money);
		window->draw(playersGame[i].PieceSelect);


	}
	for (const auto& punto : puntos) {
		window->draw(punto);
	}

	window->draw(Settings);
}