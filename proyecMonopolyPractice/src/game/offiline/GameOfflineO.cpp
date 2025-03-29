#include "GameOfflineO.hpp"
#include <String>
#include "GameEndO.hpp"
#include "StealplayerO.hpp"
#include "../../ui/ResourceGeneral.hpp"


GameOffline::GameOffline(sf::RenderWindow& win, int NumMapa) : window(&win), NMapa(NumMapa), Dado(window), moverFichas(ActiveUsers.size(), MovePiecesO(win, NumMapa)), house(ActiveUsers.size(), HouseBuyO()), impuestoCasa(0) {
	ruleta = new RuletaO(500.0f, 500.0f, 640.0f, 360.0f); // Inicialización del puntero

	resource();
}
void GameOffline::resource() {

	if (NMapa == 1) {
		if (!TextureMapa.loadFromFile("assets/image/Game/mapa+S+++.png")) return;

		Dado.start(640, 360);
		int DadoResul = 0;
		MapSprite.setTexture(TextureMapa);
		MapSprite.setOrigin(360, 360);
		MapSprite.setPosition(640, 360);

		std::vector<sf::Vector2f> camino1 = { sf::Vector2f(375, 480) };

		casillas.resize(ActiveUsers.size());
		origenS = { sf::Vector2f(330, 439),sf::Vector2f(354, 427),sf::Vector2f(399, 427),sf::Vector2f(428, 440) };
		for (int i = 0; i < casillas.size(); i++)
		{
			casillas[i].push_back(camino1);

		}

	}
	else if (NMapa == 2) {

		if (!TextureMapa.loadFromFile("assets/image/Game/mapa22l.png")) return;
		Dado.start(630, 350);
		int DadoResul = 0;
		MapSprite.setTexture(TextureMapa);
		MapSprite.setOrigin(360, 360);
		MapSprite.setPosition(640, 360);


	}
	else if (NMapa == 3) {

		if (!TextureMapa.loadFromFile("assets/image/Game/mapa1l.png")) return;

		Dado.start(590 - 24, 232 + 100);
		int DadoResul = 0;
		MapSprite.setTexture(TextureMapa);
		MapSprite.setOrigin(470, 360);
		MapSprite.setPosition(640, 380);
		std::vector<sf::Vector2f> camino1 = {
			sf::Vector2f(906.000f, 207.000f),
			sf::Vector2f(853.500f, 212.500f),
			sf::Vector2f(857.500f, 273.500f),
			sf::Vector2f(858.500f, 332.500f)
		};

		origenS = {
	sf::Vector2f(958.500f, 207.500f),
	sf::Vector2f(1017.500f, 207.500f),
	sf::Vector2f(990.500f, 208.500f),
	sf::Vector2f(1041.500f, 209.500f)
		};

		casillas.resize(ActiveUsers.size());

		for (int i = 0; i < casillas.size(); i++)
		{
			casillas[i].push_back(camino1);

		}

	}
	if (!SettingsOff.loadFromFile("assets/image/Game/settingOff.png")) return;
	if (!SettingsOn.loadFromFile("assets/image/Game/settingOn.png")) return;

	if (!GameMusicFondo.openFromFile("assets/sounds/gamemusic.wav")) return;
	RoadOption = -1;

	if (!TextureArrowIzq.loadFromFile("assets/image/Game/Izq.png")) return;
	if (!TextureArrowDer.loadFromFile("assets/image/Game/Der.png")) return;
	if (!TextureArrowArriba.loadFromFile("assets/image/Game/Arriba.png")) return;
	if (!TextureImpuesto.loadFromFile("assets/image/Game/Impuesto.png")) return;

	LeftArrow.setTexture(TextureArrowIzq);
	LeftArrow.setOrigin(350.0f, 350.0f);
	LeftArrow.setPosition(370, 400);

	RightArrow.setTexture(TextureArrowDer);
	RightArrow.setOrigin(350.0f, 350.0f);
	RightArrow.setPosition(900, 400);

	SpriteUpArrow.setTexture(TextureArrowArriba);
	SpriteUpArrow.setOrigin(350.0f, 350.0f);
	SpriteUpArrow.setPosition(370, 400);

	Settings.setTexture(SettingsOff);
	Settings.setPosition(130, 6);


	TextureHouse.resize(17);
	for (int i = 0; i < 17; i++)
	{
		if (!TextureHouse[i].loadFromFile("assets/image/Game/Casas/Casa" + std::to_string(i) + ".png")) {
			std::cerr << "Error al cargar la textura de la casa " << i << "\n";
		}

	}

	if (!DiceSoundBuffer.loadFromFile("assets/sounds/Dicerolling.wav")) return;

	if (!turnBuffer.loadFromFile("assets/sounds/ruleta.wav")) return;
	zero = true;
	turnSound.setBuffer(turnBuffer);


	DicesSound.setBuffer(DiceSoundBuffer);




	vision.setSize(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y));
	vision.setCenter(playerGameOff[0].PieceSelect.getPosition());

	Bienvenida.setCharacterSize(45);
	Bienvenida.setFont(fontUser);
	Bienvenida.setFillColor(sf::Color::White);
	Bienvenida.setOutlineThickness(2);
	Bienvenida.setOutlineColor(sf::Color(135, 135, 135));
	Bienvenida.setString("Comienza el juego!");
	Bienvenida.setPosition(640, 360);
	globalBounds = Bienvenida.getGlobalBounds();
	Bienvenida.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
	posicionActual = 0;

	Impuesto.setCharacterSize(20);
	Impuesto.setFont(fontUser);
	Impuesto.setFillColor(sf::Color::Red);
	Impuesto.setPosition(715, 434);

	ImpuestoCasa.setCharacterSize(18);
	ImpuestoCasa.setFont(fontUser);
	ImpuestoCasa.setFillColor(sf::Color::Red);
	ImpuestoCasa.setPosition(715, 382);

	SpriteImpuesto.setTexture(TextureImpuesto);
	SpriteImpuesto.setPosition(640, 360);
	sf::FloatRect globalBounds = SpriteImpuesto.getGlobalBounds();
	SpriteImpuesto.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

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
	Conteosuel.setString(std::to_string(countsalary));
	Conteosuel.setPosition(60, 10);


	animacionIniciada = false;
	//	std::cout << "COSitta";

}
void GameOffline::positionPefil() {
	if (ActiveUsers.size() >= 1) {
		playerGameOff[ActiveUsers[0]].NamePlayer.setPosition(188.65f, 62.5f);

		playerGameOff[ActiveUsers[0]].boxPlayer.setPosition(188.65f, 62.5f);
		playerGameOff[ActiveUsers[0]].boxPlayer.setScale(0.7f, 0.7f);

		playerGameOff[ActiveUsers[0]].MarcoPlayer.setTexture(TextureFrame);
		globalBounds = playerGameOff[ActiveUsers[0]].MarcoPlayer.getGlobalBounds();
		playerGameOff[ActiveUsers[0]].MarcoPlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

		playerGameOff[ActiveUsers[0]].MarcoPlayer.setPosition(52.5f, 62.5f);

		playerGameOff[ActiveUsers[0]].Money.setString(std::to_string(playerGameInfo[ActiveUsers[0]].money));
		playerGameOff[ActiveUsers[0]].Money.setCharacterSize(17);
		playerGameOff[ActiveUsers[0]].Money.setFont(fontUser);
		playerGameOff[ActiveUsers[0]].Money.setFillColor(sf::Color::White);
		playerGameOff[ActiveUsers[0]].Money.setOutlineThickness(2);
		playerGameOff[ActiveUsers[0]].Money.setOutlineColor(sf::Color(135, 135, 135));
		playerGameOff[ActiveUsers[0]].Money.setPosition(198.65f, 95.5f);

		playerGameOff[ActiveUsers[0]].CashSprite.setPosition(240.65f, 95.5f);


		playerGameOff[ActiveUsers[0]].CasasN.setCharacterSize(17);
		playerGameOff[ActiveUsers[0]].CasasN.setFont(fontUserProfile);
		playerGameOff[ActiveUsers[0]].CasasN.setFillColor(sf::Color::White);
		playerGameOff[ActiveUsers[0]].CasasN.setOutlineThickness(2);
		playerGameOff[ActiveUsers[0]].CasasN.setOutlineColor(sf::Color(135, 135, 135));
		playerGameOff[ActiveUsers[0]].CasasN.setString(std::to_string(playerGameInfo[ActiveUsers[0]].numCasas));

		playerGameOff[ActiveUsers[0]].CasasN.setPosition(138.65f, 95.5f);
		playerGameOff[ActiveUsers[0]].Home.setPosition(158.65f, 95.5f);

		playerGameOff[ActiveUsers[0]].textureAvatarPLayer = *selectedAvatarCopy.getTexture();
		playerGameOff[ActiveUsers[0]].AvatarPlayer.setTexture(&playerGameOff[ActiveUsers[0]].textureAvatarPLayer);
		playerGameOff[ActiveUsers[0]].AvatarPlayer.setRadius(static_cast<float>(playerGameOff[ActiveUsers[0]].textureAvatarPLayer.getSize().x / 2));
		playerGameOff[ActiveUsers[0]].AvatarPlayer.setOrigin(64, 64);
		playerGameOff[ActiveUsers[0]].AvatarPlayer.setPosition(52.5f, 62.5f);
		playerGameOff[ActiveUsers[0]].AvatarPlayer.setScale(0.7f, 0.7f);

		playerGameOff[ActiveUsers[0]].PieceSelect.setScale(1, 1);
		globalBounds = playerGameOff[ActiveUsers[0]].PieceSelect.getGlobalBounds();
		playerGameOff[ActiveUsers[0]].PieceSelect.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);


		playerGameOff[0].origen = origenS[0];
		playerGameOff[0].PieceSelect.setPosition(playerGameOff[0].origen);
	}
	else {
		return;
	}

	//Perfil 2
	if (ActiveUsers.size() >= 2) {

		globalBounds = playerGameOff[ActiveUsers[1]].NamePlayer.getGlobalBounds();
		playerGameOff[ActiveUsers[1]].NamePlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
		playerGameOff[ActiveUsers[1]].NamePlayer.setPosition(1188.65f, 52.5f);

		playerGameOff[ActiveUsers[1]].boxPlayer.setPosition(1188.65f, 52.5f);
		playerGameOff[ActiveUsers[1]].boxPlayer.setScale(0.7f, 0.7f);

		playerGameOff[ActiveUsers[1]].MarcoPlayer.setTexture(TextureFrame);
		globalBounds = playerGameOff[ActiveUsers[1]].MarcoPlayer.getGlobalBounds();
		playerGameOff[ActiveUsers[1]].MarcoPlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

		playerGameOff[ActiveUsers[1]].MarcoPlayer.setPosition(1052.5f, 52.5f);

		playerGameOff[ActiveUsers[1]].AvatarPlayer.setTexture(&playerGameOff[ActiveUsers[1]].textureAvatarPLayer);
		playerGameOff[ActiveUsers[1]].AvatarPlayer.setRadius(static_cast<float>(playerGameOff[ActiveUsers[1]].textureAvatarPLayer.getSize().x / 2));
		playerGameOff[ActiveUsers[1]].AvatarPlayer.setOrigin(64, 64);
		playerGameOff[ActiveUsers[1]].AvatarPlayer.setPosition(1052.5f, 52.5f);
		playerGameOff[ActiveUsers[1]].AvatarPlayer.setScale(0.7f, 0.7f);


		playerGameOff[ActiveUsers[1]].Money.setString(std::to_string(playerGameInfo[ActiveUsers[1]].money));
		playerGameOff[ActiveUsers[1]].Money.setCharacterSize(17);
		playerGameOff[ActiveUsers[1]].Money.setFont(fontUser);
		playerGameOff[ActiveUsers[1]].Money.setFillColor(sf::Color::White);
		playerGameOff[ActiveUsers[1]].Money.setOutlineThickness(2);
		playerGameOff[ActiveUsers[1]].Money.setOutlineColor(sf::Color(135, 135, 135));
		playerGameOff[ActiveUsers[1]].Money.setPosition(1198.65f, 95.5f);

		playerGameOff[ActiveUsers[1]].CashSprite.setPosition(1240.65f, 95.5f);

		playerGameOff[ActiveUsers[1]].CasasN.setCharacterSize(17);
		playerGameOff[ActiveUsers[1]].CasasN.setFont(fontUser);
		playerGameOff[ActiveUsers[1]].CasasN.setFillColor(sf::Color::White);
		playerGameOff[ActiveUsers[1]].CasasN.setOutlineThickness(2);
		playerGameOff[ActiveUsers[1]].CasasN.setOutlineColor(sf::Color(135, 135, 135));
		playerGameOff[ActiveUsers[1]].CasasN.setString(std::to_string(playerGameInfo[ActiveUsers[1]].numCasas));

		playerGameOff[ActiveUsers[1]].CasasN.setPosition(1138.65f, 95.5f);//-60
		playerGameOff[ActiveUsers[1]].Home.setPosition(1158.65f, 95.5f);//-40



		playerGameOff[ActiveUsers[1]].PieceSelect.setScale(1, 1);
		globalBounds = playerGameOff[ActiveUsers[1]].PieceSelect.getGlobalBounds();
		playerGameOff[ActiveUsers[1]].PieceSelect.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

		playerGameOff[1].origen = origenS[1];
		playerGameOff[1].PieceSelect.setPosition(playerGameOff[1].origen);

	}
	else {
		return;
	}

	//perfil 3
	if (ActiveUsers.size() >= 3) {

		playerGameOff[ActiveUsers[2]].NamePlayer.setPosition(188.65f, 552.5f);

		playerGameOff[ActiveUsers[2]].boxPlayer.setPosition(188.65f, 552.5f);
		playerGameOff[ActiveUsers[2]].boxPlayer.setScale(0.7f, 0.7f);

		playerGameOff[ActiveUsers[2]].MarcoPlayer.setTexture(TextureFrame);
		globalBounds = playerGameOff[ActiveUsers[2]].MarcoPlayer.getGlobalBounds();
		playerGameOff[ActiveUsers[2]].MarcoPlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

		playerGameOff[ActiveUsers[2]].MarcoPlayer.setPosition(52.5f, 552.5f);

		playerGameOff[ActiveUsers[2]].AvatarPlayer.setTexture(&playerGameOff[ActiveUsers[2]].textureAvatarPLayer);
		playerGameOff[ActiveUsers[2]].AvatarPlayer.setRadius(static_cast<float>(playerGameOff[ActiveUsers[2]].textureAvatarPLayer.getSize().x / 2));
		playerGameOff[ActiveUsers[2]].AvatarPlayer.setOrigin(64, 64);
		playerGameOff[ActiveUsers[2]].AvatarPlayer.setPosition(52.5f, 552.5f);
		playerGameOff[ActiveUsers[2]].AvatarPlayer.setScale(0.7f, 0.7f);

		playerGameOff[ActiveUsers[2]].Money.setString(std::to_string(playerGameInfo[ActiveUsers[2]].money));
		playerGameOff[ActiveUsers[2]].Money.setCharacterSize(17);
		playerGameOff[ActiveUsers[2]].Money.setFont(fontUser);
		playerGameOff[ActiveUsers[2]].Money.setFillColor(sf::Color::White);
		playerGameOff[ActiveUsers[2]].Money.setOutlineThickness(2);
		playerGameOff[ActiveUsers[2]].Money.setOutlineColor(sf::Color(135, 135, 135));
		playerGameOff[ActiveUsers[2]].Money.setPosition(198.65f, 595.5f);

		playerGameOff[ActiveUsers[2]].CashSprite.setPosition(240.65f, 595.5f);

		playerGameOff[ActiveUsers[2]].CasasN.setCharacterSize(17);
		playerGameOff[ActiveUsers[2]].CasasN.setFont(fontUser);
		playerGameOff[ActiveUsers[2]].CasasN.setFillColor(sf::Color::White);
		playerGameOff[ActiveUsers[2]].CasasN.setOutlineThickness(2);
		playerGameOff[ActiveUsers[2]].CasasN.setOutlineColor(sf::Color(135, 135, 135));
		playerGameOff[ActiveUsers[2]].CasasN.setString(std::to_string(playerGameInfo[ActiveUsers[2]].numCasas));

		playerGameOff[ActiveUsers[2]].CasasN.setPosition(138.65f, 595.5f);//-60
		playerGameOff[ActiveUsers[2]].Home.setPosition(158.65f, 595.5f);//-40

		playerGameOff[ActiveUsers[2]].PieceSelect.setScale(1, 1);
		globalBounds = playerGameOff[ActiveUsers[2]].PieceSelect.getGlobalBounds();
		playerGameOff[ActiveUsers[2]].PieceSelect.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

		playerGameOff[2].origen = origenS[2];
		playerGameOff[2].PieceSelect.setPosition(playerGameOff[2].origen);

	}
	else {
		return;
	}

	if (ActiveUsers.size() >= 4) {
		playerGameOff[ActiveUsers[3]].NamePlayer.setPosition(1188.65f, 552.5f)
			;
		playerGameOff[ActiveUsers[3]].boxPlayer.setPosition(1188.65f, 552.5f);
		playerGameOff[ActiveUsers[3]].boxPlayer.setScale(0.7f, 0.7f);

		playerGameOff[ActiveUsers[3]].MarcoPlayer.setTexture(TextureFrame);
		globalBounds = playerGameOff[ActiveUsers[3]].MarcoPlayer.getGlobalBounds();
		playerGameOff[ActiveUsers[3]].MarcoPlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

		playerGameOff[ActiveUsers[3]].MarcoPlayer.setPosition(1052.5f, 552.5f);

		playerGameOff[ActiveUsers[3]].Money.setString(std::to_string(playerGameInfo[ActiveUsers[3]].money));
		playerGameOff[ActiveUsers[3]].Money.setCharacterSize(17);
		playerGameOff[ActiveUsers[3]].Money.setFont(fontUser);
		playerGameOff[ActiveUsers[3]].Money.setFillColor(sf::Color::White);
		playerGameOff[ActiveUsers[3]].Money.setOutlineThickness(2);
		playerGameOff[ActiveUsers[3]].Money.setOutlineColor(sf::Color(135, 135, 135));
		playerGameOff[ActiveUsers[3]].Money.setPosition(1198.65f, 595.5f);

		playerGameOff[ActiveUsers[3]].CashSprite.setPosition(1240.65f, 595.5f);

		playerGameOff[ActiveUsers[3]].CasasN.setCharacterSize(17);
		playerGameOff[ActiveUsers[3]].CasasN.setFont(fontUserProfile);
		playerGameOff[ActiveUsers[3]].CasasN.setFillColor(sf::Color::White);
		playerGameOff[ActiveUsers[3]].CasasN.setOutlineThickness(2);
		playerGameOff[ActiveUsers[3]].CasasN.setOutlineColor(sf::Color(135, 135, 135));
		playerGameOff[ActiveUsers[3]].CasasN.setString(std::to_string(playerGameInfo[ActiveUsers[3]].numCasas));

		playerGameOff[ActiveUsers[3]].CasasN.setPosition(1138.65f, 595.5f);//-60
		playerGameOff[ActiveUsers[3]].Home.setPosition(1158.65f, 595.5f);//-40

		playerGameOff[ActiveUsers[3]].AvatarPlayer.setTexture(&playerGameOff[ActiveUsers[3]].textureAvatarPLayer);
		playerGameOff[ActiveUsers[3]].AvatarPlayer.setRadius(static_cast<float>(playerGameOff[ActiveUsers[3]].textureAvatarPLayer.getSize().x / 2));
		playerGameOff[ActiveUsers[3]].AvatarPlayer.setOrigin(64, 64);

		playerGameOff[ActiveUsers[3]].AvatarPlayer.setPosition(1052.5f, 552.5f);
		playerGameOff[ActiveUsers[3]].AvatarPlayer.setScale(0.7f, 0.7f);

		playerGameOff[ActiveUsers[3]].PieceSelect.setScale(1, 1);
		globalBounds = playerGameOff[ActiveUsers[3]].PieceSelect.getGlobalBounds();
		playerGameOff[ActiveUsers[3]].PieceSelect.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);


		playerGameOff[3].origen = origenS[3];
		playerGameOff[3].PieceSelect.setPosition(playerGameOff[3].origen);

	}
}
void GameOffline::update() {

	positionPefil();

	sf::Clock clock;
	//std::cout << "COSitta";
	GM.CasasAleatorias();
	//std::cout << "COSitta";
	resultadoDado = 0;
	mousePosition = sf::Mouse::getPosition(*window);
	mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

	SelectingMusicFondo.stop();
	GameMusicFondo.setLoop(true);
	GameMusicFondo.play();
	NuloO NUlOO;
	NUlOO.setWindow(*window);
	NUlOO.Resource();

	float duracionMovimiento = 0.5f;

	for (int i = 0; i < ActiveUsers.size(); i++) {

		house[i].setWindow(*window, i);
		house[i].resource();

		moverFichas[i].Inicializar(&playerGameOff[i].PieceSelect, &casillas[i], &playerGameInfo[i].Vueltas, playerGameOff[i].origen, &playerGameInfo[i].final, playerGameInfo[i].PiecUserme);

	}
	std::cout << "\n\nl::" << playerGameOff[0].origen.x << ":" << playerGameOff[0].origen.y;

	StealplayerO robarjugador(window, ActiveUsers, playerGameOff);
	robarjugador.resource();


	//GameEnd gameend(window);
	//gameend.resource();
	//gameend.update();

	//Dado.start(640, 360);
	int DadoResul = 0;

	rouletteAnimation = false;
	InicioPartida();
	GM.startGame();

	playerGameInfo[IndexTurn1].controlSalario += 1;
	while (window->isOpen()) {


		if (secondTurn) {

			if (turn_diceB && GM.bot.roll()) {

				Dado.loopP();

			}
		}


		Event();





		// dado mecanica 
		resultadoDado = Dado.logica();
		if (resultadoDado != 0) {
			DadoResul = resultadoDado;
			TempoAnimacion.restart();
		}
		// ruleta mecanica
		if (rouletteAnimation == true && !animacionIniciada) {
			TempoAnimacion.restart();
			rouletteAnimation = false;
			animacionIniciada = true;
		}

		if (rouletteAnimation == true && draw_roulette && TempoAnimacion.getElapsedTime().asSeconds() >= 4.0f) {
			draw_roulette = false;
			activeEvent = false;
			animacionIniciada = false;
			rouletteAnimation = false;
		}

		// impuesto mecanica
		if (animacionImpuesto == true && !animacionIniciada) {
			TempoAnimacion.restart();
			animacionImpuesto = false;
			animacionIniciada = true;
		}

		if (animacionImpuesto == false && animacionIniciada && draw_tax && TempoAnimacion.getElapsedTime().asSeconds() >= 4.0f) {

			draw_tax = false;
			activeEvent = false;
			animacionIniciada = false;
			animacionImpuesto = false;
		}

		currentCursor = &normalCursor;

		window->setMouseCursor(*currentCursor);
		Conteosuel.setString(std::to_string(countsalary));


		if (DadoResul != 0 && TempoAnimacion.getElapsedTime().asSeconds() >= 1.0f) {
			turn_dice = false;
			moverFichas[IndexTurn1].iniciarMovimiento(DadoResul, duracionMovimiento);
			DadoResul = 0;
		}

		sf::Clock clock;
		float tiempoRuletaVisible = 3.0f;
		bool ruletaVisible = false;

		float deltaTime = watch.restart().asSeconds();


		if (!draw_roulette) {

			switch (ruleta->event)
			{
			case 1:
				draw_house = true;
				activeEvent = true;
				break;


			case 2:
				GM.impuesto();
				draw_tax = true;
				turn_Tax = false;
				activeEvent = true;
				animacionImpuesto = true;
				impuestoCasa = playerGameInfo[IndexTurn1].impuesto - 50;

				Impuesto.setString(std::to_string(playerGameInfo[IndexTurn1].impuesto));
				globalBounds = Impuesto.getGlobalBounds();
				Impuesto.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

				ImpuestoCasa.setString(std::to_string(impuestoCasa));
				globalBounds = ImpuestoCasa.getGlobalBounds();
				ImpuestoCasa.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);



				break;

			case 3:
				robarjugador.update();
			default:
				break;
			}
			ruleta->event = 0;

		}


		if (GM.turnopermitido != 0 && zero == false) {
			renderTexture.clear();
			renderTexture.draw(spriteBackgroundG);
			renderTexture.draw(MapSprite);


			for (int i = 0; i < ActiveUsers.size(); i++)
			{
				renderTexture.draw(playerGameOff[ActiveUsers[i]].NamePlayer);
				renderTexture.draw(playerGameOff[ActiveUsers[i]].boxPlayer);
				renderTexture.draw(playerGameOff[ActiveUsers[i]].AvatarPlayer);
				renderTexture.draw(playerGameOff[ActiveUsers[i]].MarcoPlayer);
				renderTexture.draw(playerGameOff[ActiveUsers[i]].Money);
				renderTexture.draw(playerGameOff[ActiveUsers[i]].PieceSelect);
				renderTexture.draw(playerGameOff[ActiveUsers[i]].CashSprite);

			}

			renderTexture.draw(Settings);
			renderTexture.display();
			NUlOO.Update();
			zero = true;
		}
		else if (moverFichas[IndexTurn1].enMovimiento == true) {
			moverFichas[IndexTurn1].actualizarMovimiento(deltaTime);
			DrawPieceMoviendo();
			window->display();
		}
		else if (draw_roulette == true) {

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
		else if (draw_house) {
			//	std::cout << "COSitto";
			renderTexture.clear();
			renderTexture.draw(spriteBackgroundG);
			renderTexture.draw(MapSprite);


			for (int i = 0; i < ActiveUsers.size(); i++)
			{
				renderTexture.draw(playerGameOff[ActiveUsers[i]].NamePlayer);
				renderTexture.draw(playerGameOff[ActiveUsers[i]].boxPlayer);
				renderTexture.draw(playerGameOff[ActiveUsers[i]].AvatarPlayer);
				renderTexture.draw(playerGameOff[ActiveUsers[i]].MarcoPlayer);
				renderTexture.draw(playerGameOff[ActiveUsers[i]].Money);
				renderTexture.draw(playerGameOff[ActiveUsers[i]].CashSprite);
				renderTexture.draw(playerGameOff[ActiveUsers[i]].CasasN);
				renderTexture.draw(playerGameOff[ActiveUsers[i]].Home);
				renderTexture.draw(playerGameOff[ActiveUsers[i]].PieceSelect);



			}

			renderTexture.draw(Settings);

			renderTexture.display();
			//std::cout << "COSitto";
			//std::cout << "house: " << house.size()<<":  IndexTurn1  :"<< IndexTurn1<<": playerGameOff[IndexTurn1].PieceSelect.getPosition() :"<< playerGameOff[IndexTurn1].PieceSelect.getPosition().x << ", "
				//<< playerGameOff[IndexTurn1].PieceSelect.getPosition().y << ")";
			house[IndexTurn1].update(playerGameOff[IndexTurn1].PieceSelect.getPosition());
			std::cout << "COSitto";
			activeEvent = false;
			draw_house = false;

		}
		else  if (draw_tax) {

			DrawGameImpuesto();
			window->display();
		}
		else
		{
			DrawGame();
			window->display();
		}

	}

	if (window->isOpen() && GM.juegoTerminadoo) {
		GameEndO gameend(window);
		gameend.resource();
		gameend.update();
	}
}
void GameOffline::Event() {
	sf::Event event;

	do {
		if (window->pollEvent(event)) {
			Dado.loop(event);

			sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
			sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {

				renderTexture.clear();
				renderTexture.draw(spriteBackgroundG);
				renderTexture.draw(MapSprite);
				for (int i = 0; i < ActiveUsers.size(); i++) {
					renderTexture.draw(playerGameOff[ActiveUsers[i]].NamePlayer);
					renderTexture.draw(playerGameOff[ActiveUsers[i]].boxPlayer);
					renderTexture.draw(playerGameOff[ActiveUsers[i]].MarcoPlayer);
					renderTexture.draw(playerGameOff[ActiveUsers[i]].AvatarPlayer);
				}
				renderTexture.draw(spriteX);
				renderTexture.draw(overlay);

				Menup.MenuSalir(nullptr);
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				if (Settings.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					Menup.MenuOpcion(false);
				}
				if (playerGameOff[ActiveUsers[0]].Home.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					house[ActiveUsers[0]].ViewHouseBuys();
				}



			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {

				if (draw_roulette && firstTurn && turnoGiro) {

					ruleta->trurntrue();
					GM.giroActivo = true;
					turnoGiro = false;
				}
			}
		}

	} while (window->pollEvent(event));
}
void GameOffline::DrawPieceMoviendo() {

	sf::Vector2f fichaPos = playerGameOff[IndexTurn1].PieceSelect.getPosition();
	float viewX = fichaPos.x;
	float viewY = fichaPos.y;

	if (viewY > 540) viewY = 540;
	if (viewX < 320) viewX = 320;
	if (viewY < 180) viewY = 180;

	vision.setCenter(viewX, viewY);
	vision.setSize(1280 * 0.5, 720 * 0.5);
	window->setView(vision);
	window->clear();

	window->draw(spriteBackgroundG);
	window->draw(MapSprite);
	for (int i = 0; i < ActiveUsers.size(); i++) {
		window->draw(playerGameOff[i].PieceSelect);
	}
	window->setView(window->getDefaultView());

}
void GameOffline::DrawGameRuleta() {
	float deltaTime = clock.restart().asSeconds();
	if (secondTurn) {

		if (draw_roulette && turnoGiro && GM.bot.roll()) {
			ruleta->trurntrue();
			turnoGiro = false;

			GM.giroActivo = true;


		}
	}
	window->clear();
	renderTexture.clear();

	renderTexture.draw(spriteBackgroundG);
	renderTexture.draw(MapSprite);
	for (int i = 0; i < ActiveUsers.size(); i++)
	{
		renderTexture.draw(playerGameOff[ActiveUsers[i]].NamePlayer);
		renderTexture.draw(playerGameOff[ActiveUsers[i]].boxPlayer);
		renderTexture.draw(playerGameOff[ActiveUsers[i]].AvatarPlayer);
		renderTexture.draw(playerGameOff[ActiveUsers[i]].MarcoPlayer);
		renderTexture.draw(playerGameOff[ActiveUsers[i]].Money);
		renderTexture.draw(playerGameOff[ActiveUsers[i]].CashSprite);
		renderTexture.draw(playerGameOff[ActiveUsers[i]].CasasN);
		renderTexture.draw(playerGameOff[ActiveUsers[i]].Home);
		renderTexture.draw(playerGameOff[ActiveUsers[i]].PieceSelect);

	}

	//renderTexture.draw(SpriteChat);
	renderTexture.draw(Settings);
	renderTexture.draw(overlay);

	renderTexture.display();

	renderedSprite.setTexture(renderTexture.getTexture());

	window->draw(renderedSprite);
	ruleta->draw(*window, deltaTime, GM.giroActivo);
	if (!GM.giroActivo && firstTurn) {
		float deltaTime = clockMensaje.restart().asSeconds();

		if (increasing) {
			currentScale += (maxScale - minScale) / (duration / 2) * deltaTime; // Incrementa el escalado
			if (currentScale >= maxScale) {
				currentScale = maxScale;
				increasing = false;
			}
		}
		else {
			currentScale -= (maxScale - minScale) / (duration / 2) * deltaTime; // Reduce el escalado
			if (currentScale <= minScale) {
				currentScale = minScale;
				increasing = true;
			}
		}
		DescripDado.setPosition(640, 550);
		DescripDado.setScale(currentScale, currentScale);

		window->draw(DescripDado);
	}
}
void GameOffline::DrawGameImpuesto() {

	window->clear();

	renderTexture.clear();

	renderTexture.draw(spriteBackgroundG);
	renderTexture.draw(MapSprite);

	for (int i = 0; i < ActiveUsers.size(); i++)
	{
		renderTexture.draw(playerGameOff[ActiveUsers[i]].NamePlayer);
		renderTexture.draw(playerGameOff[ActiveUsers[i]].boxPlayer);
		renderTexture.draw(playerGameOff[ActiveUsers[i]].AvatarPlayer);
		renderTexture.draw(playerGameOff[ActiveUsers[i]].MarcoPlayer);
		renderTexture.draw(playerGameOff[ActiveUsers[i]].Money);
		renderTexture.draw(playerGameOff[ActiveUsers[i]].CashSprite);
		renderTexture.draw(playerGameOff[ActiveUsers[i]].CasasN);
		renderTexture.draw(playerGameOff[ActiveUsers[i]].Home);
		renderTexture.draw(playerGameOff[ActiveUsers[i]].PieceSelect);
	}

	//renderTexture.draw(SpriteChat);
	renderTexture.draw(Settings);
	renderTexture.draw(overlay);
	renderTexture.display();
	renderedSprite.setTexture(renderTexture.getTexture());

	window->draw(renderedSprite);
	window->draw(SpriteImpuesto);
	window->draw(Impuesto);
	window->draw(ImpuestoCasa);

}
void GameOffline::InicioPartida() {
	sf::Clock clocks;
	sf::Clock deltaClock;
	Bienvenida.setScale(0.5, 0.5);

	float currentScaleX = 0.5f;
	float currentScaleY = 0.5f;
	float targetScaleX = 1.0f;
	float targetScaleY = 1.0f;
	float duration = 1.0f;
	float elapsedTime = 0.0f;

	while (window->isOpen() && clocks.getElapsedTime().asSeconds() <= 2.5f) {


		float deltaTime = deltaClock.restart().asSeconds();
		elapsedTime += deltaTime;

		if (elapsedTime < duration) {
			float progress = elapsedTime / duration;
			currentScaleX = 0.5f + progress * (targetScaleX - 0.5f);
			currentScaleY = 0.5f + progress * (targetScaleY - 0.5f);
			Bienvenida.setScale(currentScaleX, currentScaleY);
		}
		else {
			Bienvenida.setScale(targetScaleX, targetScaleY);
		}

		window->setView(window->getDefaultView());
		window->clear();
		window->draw(spriteBackgroundG);
		window->draw(MapSprite);

		Dado.update();

		for (int i = 0; i < ActiveUsers.size(); i++) {
			window->draw(playerGameOff[ActiveUsers[i]].NamePlayer);
			window->draw(playerGameOff[ActiveUsers[i]].boxPlayer);
			window->draw(playerGameOff[ActiveUsers[i]].AvatarPlayer);
			window->draw(playerGameOff[ActiveUsers[i]].MarcoPlayer);
			window->draw(playerGameOff[ActiveUsers[i]].Money);
			window->draw(playerGameOff[ActiveUsers[i]].CashSprite);
			window->draw(playerGameOff[ActiveUsers[i]].CasasN);
			window->draw(playerGameOff[ActiveUsers[i]].Home);
			window->draw(playerGameOff[ActiveUsers[i]].PieceSelect);

		}

		//window->draw(SpriteChat);
		window->draw(Settings);
		window->draw(overlay);
		window->draw(Bienvenida);
		window->display();
	}
}
void GameOffline::DrawGame() {

	if (firstTurn) {
		if (!activeEvent) {

			if (turn_roulette && turnRule && !turn_dice && !turn_Move) {

				for (int i = 0; i < casillasRuleta.size(); i++)
				{
					if (playerGameOff[IndexTurn1].PieceSelect.getPosition() == casillasRuleta[i])
					{
						//client.EventoRuleta();
						draw_roulette = true;
						turn_roulette = false;
						activeEvent = true;
						turnoGiro = true;
						ruleta->trurntrue();
					}
				}
				turnRule = false;
				turn_roulette = false;

			}

			if (turn_house && !turn_dice && !turn_Move) {

				for (int i = 0; i < caminocasa.size(); i++)
				{
					if (playerGameOff[IndexTurn1].PieceSelect.getPosition() == caminocasa[i])
					{
						//client.EventoCasa();
						draw_house = true;
						activeEvent = true;
					}
				}
				turn_house = false;
			}


			if (turn_Tax && !turn_dice && !turn_Move) {
				for (int i = 0; i < caminoimpuesto.size(); i++)
				{
					if (playerGameOff[IndexTurn1].PieceSelect.getPosition() == caminoimpuesto[i])
					{
						GM.impuesto();
						draw_tax = true;
						turn_Tax = false;
						activeEvent = true;
						animacionImpuesto = true;

						impuestoCasa = playerGameInfo[IndexTurn1].impuesto - 50;
						Impuesto.setString(std::to_string(playerGameInfo[IndexTurn1].impuesto));
						globalBounds = Impuesto.getGlobalBounds();
						Impuesto.setOrigin(globalBounds.width, globalBounds.height / 2.0f);
						ImpuestoCasa.setString(std::to_string(impuestoCasa));
						globalBounds = ImpuestoCasa.getGlobalBounds();
						ImpuestoCasa.setOrigin(globalBounds.width, globalBounds.height / 2.0f);

					}
				}
				turn_Tax = false;
			}

		}
	}
	if (secondTurn) {
		if (!activeEvent) {

			if (turn_roulette && turnRule && !turn_diceB && !turn_Move) {

				for (int i = 0; i < casillasRuleta.size(); i++)
				{
					if (playerGameOff[IndexTurn1].PieceSelect.getPosition() == casillasRuleta[i])
					{
						//client.EventoRuleta();
						draw_roulette = true;
						turn_roulette = false;
						activeEvent = true;
						turnoGiro = true;
						GM.bot.resetTCAMRuleta();
						ruleta->trurntrue();
					}
				}
				turnRule = false;
				turn_roulette = false;

			}

			if (turn_house && !turn_diceB && !turn_Move) {

				for (int i = 0; i < caminocasa.size(); i++)
				{
					if (playerGameOff[IndexTurn1].PieceSelect.getPosition() == caminocasa[i])
					{
						//client.EventoCasa();
						draw_house = true;
						activeEvent = true;
					}
				}
				turn_house = false;
			}


			if (turn_Tax && !turn_diceB && !turn_Move) {
				for (int i = 0; i < caminoimpuesto.size(); i++)
				{
					if (playerGameOff[IndexTurn1].PieceSelect.getPosition() == caminoimpuesto[i])
					{
						//client.EventoImpuesto();
						draw_tax = true;
						turn_Tax = false;
						activeEvent = true;
						animacionImpuesto = true;

						impuestoCasa = playerGameInfo[IndexTurn1].impuesto - 50;
						Impuesto.setString(std::to_string(playerGameInfo[IndexTurn1].impuesto));
						globalBounds = Impuesto.getGlobalBounds();
						Impuesto.setOrigin(globalBounds.width, globalBounds.height / 2.0f);
						ImpuestoCasa.setString(std::to_string(impuestoCasa));
						globalBounds = ImpuestoCasa.getGlobalBounds();
						ImpuestoCasa.setOrigin(globalBounds.width, globalBounds.height / 2.0f);

					}
				}
				turn_Tax = false;
			}

		}
	}

	//std::cout << "hola no11";

	if (BotTurn) {
		if (secondTurn && !turn_Tax && !turn_house && !turn_roulette && !turn_diceB && !turn_Move && !activeEvent && !draw_tax && !draw_house && !draw_roulette) {

			GM.nextTurn();

		}


	}
	else {
		if (firstTurn && !turn_Tax && !turn_house && !turn_roulette && !turn_dice && !turn_Move && !activeEvent && !draw_tax && !draw_house && !draw_roulette) {

			GM.nextTurn();

		}
	}

	//std::cout << "hola si11";
	//std::cout << "firstTurn: " << firstTurn
	//	<< ", turn_Tax: " << turn_Tax
	//	<< ", turn_house: " << turn_house
	//	<< ", turn_roulette: " << turn_roulette
	//	<< ", turn_dice: " << turn_dice
	//	<< ", turn_Move: " << turn_Move
	//	<< ", activeEvent: " << activeEvent
	//	<< ", draw_tax: " << draw_tax
	//	<< ", draw_house: " << draw_house
	//	<< ", draw_roulette: " << draw_roulette
	//	<< std::endl;

	/*/std::cout << "hola si11";
	std::cout << "firstTurn: " << firstTurn
		<< ", turn_Tax: " << turn_Tax
		<< ", turn_house: " << turn_house
		<< ", turn_roulette: " << turn_roulette
		<< ", turn_dice: " << turn_dice
		<< ", turn_Move: " << turn_Move
		<< ", activeEvent: " << activeEvent
		<< ", draw_tax: " << draw_tax
		<< ", draw_house: " << draw_house
		<< ", draw_roulette: " << draw_roulette
		<< std::endl;*/



	window->setView(window->getDefaultView());
	window->clear();
	window->draw(spriteBackgroundG);
	window->draw(MapSprite);

	Dado.update();
	float deltaTime = clock.restart().asSeconds();

	for (int i = 0; i < ActiveUsers.size(); i++)
	{
		window->draw(playerGameOff[ActiveUsers[i]].NamePlayer);
		window->draw(playerGameOff[ActiveUsers[i]].boxPlayer);
		window->draw(playerGameOff[ActiveUsers[i]].AvatarPlayer);
		window->draw(playerGameOff[ActiveUsers[i]].MarcoPlayer);
		window->draw(playerGameOff[ActiveUsers[i]].Money);
		window->draw(playerGameOff[ActiveUsers[i]].CashSprite);
		window->draw(playerGameOff[ActiveUsers[i]].CasasN);
		window->draw(playerGameOff[ActiveUsers[i]].Home);
		window->draw(playerGameOff[ActiveUsers[i]].PieceSelect);

	}

	if (turn_dice) {
		float deltaTime = clockMensaje.restart().asSeconds();

		if (increasing) {
			currentScale += (maxScale - minScale) / (duration / 2) * deltaTime; // Incrementa el escalado
			if (currentScale >= maxScale) {
				currentScale = maxScale;
				increasing = false;
			}
		}
		else {
			currentScale -= (maxScale - minScale) / (duration / 2) * deltaTime; // Reduce el escalado
			if (currentScale <= minScale) {
				currentScale = minScale;
				increasing = true;
			}
		}
		DescripDado.setPosition(640, 450);
		DescripDado.setScale(currentScale, currentScale);

		window->draw(DescripDado);
	}

	window->draw(Settings);
	//window->draw(countsalary);
	//window->draw(SpriteChat);
	//std::cout << "COSitta";
}