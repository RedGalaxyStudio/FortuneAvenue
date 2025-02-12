#include "MultiplayerGame.hpp"
#include <String>
#include "GameEnd.hpp"
#include "Stealplayer.hpp"

MultiplayerGame::MultiplayerGame(sf::RenderWindow& win, Chat& chat) : window(&win), Dado(window),chats(&chat), moverFichas(UsuariosActivos.size(), MovePieces(win)), house(UsuariosActivos.size(), HouseBuy()), impuestoCasa(0) {
	ruleta = new Ruleta(500.0f, 500.0f, 640.0f, 360.0f); // Inicializaci�n del puntero

	loadResourceGame();
	resource();
}
void MultiplayerGame::resource() {


	if (!TextureChat.loadFromFile("assets/image/window_13905854.png")) return;
	if (!TextureMapa.loadFromFile("assets/image/Game/mapa+S+++.png")) return;
	if (!TextureMapa2.loadFromFile("assets/image/Game/mapa1L.png")) return;
	if (!TextureMapa3.loadFromFile("assets/image/Game/mapa22l.png")) return;
	if (!SettingsOff.loadFromFile("assets/image/Game/settingOff.png")) return;
	if (!SettingsOn.loadFromFile("assets/image/Game/settingOn.png")) return;

	if (!GameMusicFondo.openFromFile("assets/sounds/gamemusic.wav")) return;
	Opcioncami = -1;

	//Cargar Texturas de Flechas
	if (!TextureArrowIzq.loadFromFile("assets/image/Game/Izq.png")) return;
	if (!TextureArrowDer.loadFromFile("assets/image/Game/Der.png")) return;
	if (!TextureArrowAbajo.loadFromFile("assets/image/Game/Abajo.png")) return;
	if (!TextureArrowArriba.loadFromFile("assets/image/Game/Arriba.png")) return;
	if (!TextureImpuesto.loadFromFile("assets/image/Game/Impuesto.png")) return;

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

	SpriteArrowAbajo.setTexture(TextureArrowAbajo);
	SpriteArrowAbajo.setOrigin(350.0f, 350.0f);
	SpriteArrowAbajo.setPosition(370, 400);

	SpriteChat.setTexture(TextureChat);
	SpriteChat.setOrigin(20, 20);
	SpriteChat.setPosition(23, 100);

	Settings.setTexture(SettingsOff);
	Settings.setPosition(130, 6);

	spriteMapa.setTexture(TextureMapa);
	spriteMapa.setOrigin(360, 360);
	spriteMapa.setPosition(640, 360);

	/*if (MapaSelector == 1)
	{
		spriteMapa.setTexture(TextureMapa);
		spriteMapa.setOrigin(360, 360);
		spriteMapa.setPosition(640, 360);

	}
	else if (MapaSelector == 2)
	{
		spriteMapa.setTexture(TextureMapa2);
		spriteMapa.setOrigin(360, 360);
		spriteMapa.setPosition(640, 360);

	}
	else if (MapaSelector == 2)
	{
		spriteMapa.setTexture(TextureMapa3);
		spriteMapa.setOrigin(360, 360);
		spriteMapa.setPosition(640, 360);
	}*/
	
	TextureCasa.resize(17);
	for (int i = 0; i < 17; i++)
	{
		std::cout << "\ni";
		if (!TextureCasa[i].loadFromFile("assets/image/Game/Casas/Casa" + std::to_string(i) + ".png")) {
			std::cerr << "Error al cargar la textura de la casa " << i << "\n";
		}

	}


	if (!DiceBuffer.loadFromFile("assets/sounds/Dicerolling.wav")) return;

	if (!girosBuffer.loadFromFile("assets/sounds/ruleta.wav")) return;
	nular = true;
	girosSound.setBuffer(girosBuffer);


	DiceSound.setBuffer(DiceBuffer);


	std::vector<sf::Vector2f> camino1 = { sf::Vector2f(375, 480) };

	casillas.resize(UsuariosActivos.size());

	for (int i = 0; i < casillas.size(); i++)
	{
		casillas[i].push_back(camino1);

	}


	view.setSize(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y));
	view.setCenter(playersGame[0].PieceSelect.getPosition()); // Centra la vista en la ficha

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
	//Impuesto.setOutlineThickness(2);
	//Impuesto.setOutlineColor(sf::Color(135, 135, 135));

	Impuesto.setPosition(715, 434);


	ImpuestoCasa.setCharacterSize(18);
	ImpuestoCasa.setFont(fontUser);
	ImpuestoCasa.setFillColor(sf::Color::Red);
	//ImpuestoCasa.setOutlineThickness(-1);
	//ImpuestoCasa.setOutlineColor(sf::Color(135, 135, 135));

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
	Conteosuel.setString(std::to_string(conteosuel));
	Conteosuel.setPosition(60, 10);


	animacionIniciada = false;

}
void MultiplayerGame::positionPefil() {
	if (UsuariosActivos.size() >= 1) {

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
		playersGame[UsuariosActivos[0]].Money.setPosition(198.65f, 95.5f);

		playersGame[UsuariosActivos[0]].CashSprite.setPosition(240.65f, 95.5f);


		playersGame[UsuariosActivos[0]].CasasN.setCharacterSize(17);
		playersGame[UsuariosActivos[0]].CasasN.setFont(fontUserPerfil);
		playersGame[UsuariosActivos[0]].CasasN.setFillColor(sf::Color::White);
		playersGame[UsuariosActivos[0]].CasasN.setOutlineThickness(2);
		playersGame[UsuariosActivos[0]].CasasN.setOutlineColor(sf::Color(135, 135, 135));
		playersGame[UsuariosActivos[0]].CasasN.setString(std::to_string(playerInfos[UsuariosActivos[0]].numCasas));

		playersGame[UsuariosActivos[0]].CasasN.setPosition(138.65f, 95.5f);//-60
		playersGame[UsuariosActivos[0]].Home.setPosition(158.65f, 95.5f);//-40




		playersGame[UsuariosActivos[0]].textureAvatarPLayer = *selectedAvatarCopy.getTexture();
		playersGame[UsuariosActivos[0]].AvatarPlayer.setTexture(&playersGame[UsuariosActivos[0]].textureAvatarPLayer);
		playersGame[UsuariosActivos[0]].AvatarPlayer.setRadius(static_cast<float>(playersGame[UsuariosActivos[0]].textureAvatarPLayer.getSize().x / 2));
		playersGame[UsuariosActivos[0]].AvatarPlayer.setOrigin(64, 64);
		playersGame[UsuariosActivos[0]].AvatarPlayer.setPosition(52.5f, 62.5f);
		playersGame[UsuariosActivos[0]].AvatarPlayer.setScale(0.7f, 0.7f);

		playersGame[UsuariosActivos[0]].PieceSelect.setScale(1, 1);
		globalBounds = playersGame[UsuariosActivos[0]].PieceSelect.getGlobalBounds();
		playersGame[UsuariosActivos[0]].PieceSelect.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);


		playersGame[0].origen = sf::Vector2f(330, 439);
		playersGame[0].PieceSelect.setPosition(playersGame[0].origen);
	}
	else {
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
		playersGame[UsuariosActivos[1]].Money.setPosition(1198.65f, 95.5f);

		playersGame[UsuariosActivos[1]].CashSprite.setPosition(1240.65f, 95.5f);

		playersGame[UsuariosActivos[1]].CasasN.setCharacterSize(17);
		playersGame[UsuariosActivos[1]].CasasN.setFont(fontUserPerfil);
		playersGame[UsuariosActivos[1]].CasasN.setFillColor(sf::Color::White);
		playersGame[UsuariosActivos[1]].CasasN.setOutlineThickness(2);
		playersGame[UsuariosActivos[1]].CasasN.setOutlineColor(sf::Color(135, 135, 135));
		playersGame[UsuariosActivos[1]].CasasN.setString(std::to_string(playerInfos[UsuariosActivos[1]].numCasas));

		playersGame[UsuariosActivos[1]].CasasN.setPosition(1138.65f, 95.5f);//-60
		playersGame[UsuariosActivos[1]].Home.setPosition(1158.65f, 95.5f);//-40

		playersGame[UsuariosActivos[1]].PieceSelect.setScale(1, 1);
		globalBounds = playersGame[UsuariosActivos[1]].PieceSelect.getGlobalBounds();
		playersGame[UsuariosActivos[1]].PieceSelect.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

		playersGame[1].origen = sf::Vector2f(354, 427);
		playersGame[1].PieceSelect.setPosition(playersGame[1].origen);

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
		playersGame[UsuariosActivos[2]].Money.setPosition(198.65f, 595.5f);

		playersGame[UsuariosActivos[2]].CashSprite.setPosition(240.65f, 595.5f);

		playersGame[UsuariosActivos[2]].CasasN.setCharacterSize(17);
		playersGame[UsuariosActivos[2]].CasasN.setFont(fontUserPerfil);
		playersGame[UsuariosActivos[2]].CasasN.setFillColor(sf::Color::White);
		playersGame[UsuariosActivos[2]].CasasN.setOutlineThickness(2);
		playersGame[UsuariosActivos[2]].CasasN.setOutlineColor(sf::Color(135, 135, 135));
		playersGame[UsuariosActivos[2]].CasasN.setString(std::to_string(playerInfos[UsuariosActivos[2]].numCasas));

		playersGame[UsuariosActivos[0]].CasasN.setPosition(138.65f, 595.5f);//-60
		playersGame[UsuariosActivos[0]].Home.setPosition(158.65f, 595.5f);//-40

		playersGame[UsuariosActivos[2]].PieceSelect.setScale(1, 1);
		globalBounds = playersGame[UsuariosActivos[2]].PieceSelect.getGlobalBounds();
		playersGame[UsuariosActivos[2]].PieceSelect.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

		playersGame[2].origen = sf::Vector2f(399, 427);
		playersGame[2].PieceSelect.setPosition(playersGame[2].origen);

	}
	else {
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
		playersGame[UsuariosActivos[3]].Money.setPosition(1198.65f, 595.5f);

		playersGame[UsuariosActivos[3]].CashSprite.setPosition(1240.65f, 595.5f);

		playersGame[UsuariosActivos[3]].CasasN.setCharacterSize(17);
		playersGame[UsuariosActivos[3]].CasasN.setFont(fontUserPerfil);
		playersGame[UsuariosActivos[3]].CasasN.setFillColor(sf::Color::White);
		playersGame[UsuariosActivos[3]].CasasN.setOutlineThickness(2);
		playersGame[UsuariosActivos[3]].CasasN.setOutlineColor(sf::Color(135, 135, 135));
		playersGame[UsuariosActivos[3]].CasasN.setString(std::to_string(playerInfos[UsuariosActivos[3]].numCasas));

		playersGame[UsuariosActivos[1]].CasasN.setPosition(1138.65f, 595.5f);//-60
		playersGame[UsuariosActivos[1]].Home.setPosition(1158.65f, 595.5f);//-40

		playersGame[UsuariosActivos[3]].AvatarPlayer.setTexture(&playersGame[UsuariosActivos[3]].textureAvatarPLayer);
		playersGame[UsuariosActivos[3]].AvatarPlayer.setRadius(static_cast<float>(playersGame[UsuariosActivos[3]].textureAvatarPLayer.getSize().x / 2));
		playersGame[UsuariosActivos[3]].AvatarPlayer.setOrigin(64, 64);

		playersGame[UsuariosActivos[3]].AvatarPlayer.setPosition(1052.5f, 552.5f);
		playersGame[UsuariosActivos[3]].AvatarPlayer.setScale(0.7f, 0.7f);

		playersGame[UsuariosActivos[3]].PieceSelect.setScale(1, 1);
		globalBounds = playersGame[UsuariosActivos[3]].PieceSelect.getGlobalBounds();
		playersGame[UsuariosActivos[3]].PieceSelect.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);


		playersGame[3].origen = sf::Vector2f(428, 440);
		playersGame[3].PieceSelect.setPosition(playersGame[3].origen);

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

	for (int i = 0; i < UsuariosActivos.size(); i++) {

		house[i].setWindow(*window, i);
		house[i].resource(&client);

		moverFichas[i].Inicializar(&playersGame[i].PieceSelect, &casillas[i], &playerInfos[i].Vueltas, playersGame[i].origen, &playerInfos[i].final, playerInfos[i].PiecUserme);

	}
	std::cout << "hola";

	Stealplayer robarjugador(window, UsuariosActivos, playersGame);
	robarjugador.resource();

	Dado.start(610, 360);
	int DadoResul = 0;

	animacionRuleta = false;
	InicioPartida();

	while (window->isOpen() && !client.juegoTerminado) {

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
		chats->update();
		currentCursor = &normalCursor;

		window->setMouseCursor(*currentCursor);
		Conteosuel.setString(std::to_string(conteosuel));


		if (DadoResul != 0 && TempoAnimacion.getElapsedTime().asSeconds() >= 1.0f) {
			turn_dado = false;
			moverFichas[IndexTurn].iniciarMovimiento(DadoResul, duracionMovimiento);
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

				if (IndexTurn == client.playerIndex) {
					client.networkMessage.sendEventTax();
					impuesto_draw = true;
					turn_impuesto = false;
					eventoActivo = true;
					animacionImpuesto = true;
					{
						std::unique_lock<std::mutex> lock(client.impuestoMutex);
						client.impuestoCondVar.wait(lock, [] { return client.impuestoMessageReceived; });

						client.impuestoMessageReceived = false;
					}
					impuestoCasa = playerInfos[IndexTurn].impuesto - 50;

					Impuesto.setString(std::to_string(playerInfos[IndexTurn].impuesto));
					globalBounds = Impuesto.getGlobalBounds();
					Impuesto.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

					ImpuestoCasa.setString(std::to_string(impuestoCasa));
					globalBounds = ImpuestoCasa.getGlobalBounds();
					ImpuestoCasa.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

				}

				break;

			case 3:
				robarjugador.update();
			default:
				break;
			}
			ruleta->event = 0;

		}
	

		if (client.turnopermitido != 0 && nular == false) {
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
				renderTexture.draw(playersGame[UsuariosActivos[i]].CashSprite);
				renderTexture.draw(playersGame[UsuariosActivos[i]].CasasN);
				renderTexture.draw(playersGame[UsuariosActivos[i]].Home);
				renderTexture.draw(playersGame[UsuariosActivos[i]].PieceSelect);



			}

			renderTexture.draw(SpriteChat);
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

	if (window->isOpen() && client.juegoTerminado) {
		GameEnd gameend(window);
		gameend.resource();
		gameend.update();
	}
}
void MultiplayerGame::Event() {
	sf::Event event;
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
	sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

	while (window->pollEvent(event)) {
	
			Dado.loop(event, &client);
			chats->Event(event);

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
					Menup.MenuOpcion(false);
				}
				if (playersGame[UsuariosActivos[0]].Home.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					house[UsuariosActivos[0]].ViewHouseBuys();
				}



				if (ruleta_draw && turn && turnoGiro) {
					ruleta->trurntrue();
					turnoGiro = false;
				}

				if (SpriteChat.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					
					chatOn = true;
				}

			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {

				if (ruleta_draw && turn && turnoGiro) {

					client.networkMessage.startSpin();
					ruleta->trurntrue();
					turnoGiro = false;
				}
			}
		

	}
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

	if (chatOn)
	{

		chats->draw();
	}

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
		renderTexture.draw(playersGame[UsuariosActivos[i]].Money);
		renderTexture.draw(playersGame[UsuariosActivos[i]].CashSprite);
		renderTexture.draw(playersGame[UsuariosActivos[i]].CasasN);
		renderTexture.draw(playersGame[UsuariosActivos[i]].Home);
		renderTexture.draw(playersGame[UsuariosActivos[i]].PieceSelect);

	}

	renderTexture.draw(SpriteChat);
	renderTexture.draw(Settings);
	renderTexture.draw(overlay);

	renderTexture.display();

	renderedSprite.setTexture(renderTexture.getTexture());

	window->draw(renderedSprite);
	ruleta->draw(*window, deltaTime, client.giroActivo);
	if (!client.giroActivo && turn) {
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
	if (chatOn)
	{

		chats->draw();
	}
}
void MultiplayerGame::DrawGameImpuesto() {

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
		renderTexture.draw(playersGame[UsuariosActivos[i]].Money);
		renderTexture.draw(playersGame[UsuariosActivos[i]].CashSprite);
		renderTexture.draw(playersGame[UsuariosActivos[i]].CasasN);
		renderTexture.draw(playersGame[UsuariosActivos[i]].Home);
		renderTexture.draw(playersGame[UsuariosActivos[i]].PieceSelect);
	}
	
	renderTexture.draw(Settings);
	renderTexture.draw(overlay);
	renderTexture.display();
	renderedSprite.setTexture(renderTexture.getTexture());

	window->draw(renderedSprite);
	window->draw(SpriteImpuesto);
	window->draw(Impuesto);
	window->draw(ImpuestoCasa);
	if (!chatOn)
	{
		window->draw(SpriteChat);
	}
	else {

		chats->draw();
	}


}
void MultiplayerGame::InicioPartida() {
	sf::Clock clocks;  // Inicia el temporizador
	sf::Clock deltaClock;
	Bienvenida.setScale(0.5, 0.5);

	float currentScaleX = 0.5f;
	float currentScaleY = 0.5f;
	float targetScaleX = 1.0f;
	float targetScaleY = 1.0f;
	float duration = 1.0f; // Duraci�n en segundos
	float elapsedTime = 0.0f;

	// El bucle solo se ejecutar� durante 5 segundos
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
			// Aseg�rate de que el escalado final sea exactamente el objetivo
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
			window->draw(playersGame[UsuariosActivos[i]].CashSprite);
			window->draw(playersGame[UsuariosActivos[i]].CasasN);
			window->draw(playersGame[UsuariosActivos[i]].Home);
			window->draw(playersGame[UsuariosActivos[i]].PieceSelect);

		}



		// Dibuja los settings (configuraci�n) al final
		window->draw(SpriteChat);
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
						client.networkMessage.sendEventSpin();
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
						client.networkMessage.sendEventHouse();
						casa_draw = true;
						eventoActivo = true;
					}
				}
				turn_casa = false;
			}


			if (turn_impuesto && !turn_dado && !turn_Moviendo) {
				for (int i = 0; i < caminoimpuesto.size(); i++)
				{
					if (playersGame[IndexTurn].PieceSelect.getPosition() == caminoimpuesto[i])
					{
						client.networkMessage.sendEventTax();
						impuesto_draw = true;
						turn_impuesto = false;
						eventoActivo = true;
						animacionImpuesto = true;
						{
							std::unique_lock<std::mutex> lock(client.impuestoMutex);
							client.impuestoCondVar.wait(lock, [] { return client.impuestoMessageReceived; });

							client.impuestoMessageReceived = false;
						}
						impuestoCasa = playerInfos[IndexTurn].impuesto - 50;

						Impuesto.setString(std::to_string(playerInfos[IndexTurn].impuesto));
						globalBounds = Impuesto.getGlobalBounds();
						Impuesto.setOrigin(globalBounds.width, globalBounds.height / 2.0f);

						ImpuestoCasa.setString(std::to_string(impuestoCasa));
						globalBounds = ImpuestoCasa.getGlobalBounds();
						ImpuestoCasa.setOrigin(globalBounds.width, globalBounds.height / 2.0f);

					}
				}
				turn_impuesto = false;
			}

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
		impuestoCasa = playerInfos[IndexTurn].impuesto - 50;

		Impuesto.setString(std::to_string(playerInfos[IndexTurn].impuesto));
		globalBounds = Impuesto.getGlobalBounds();
		Impuesto.setOrigin(globalBounds.width, globalBounds.height / 2.0f);

		ImpuestoCasa.setString(std::to_string(impuestoCasa));
		globalBounds = ImpuestoCasa.getGlobalBounds();
		ImpuestoCasa.setOrigin(globalBounds.width, globalBounds.height / 2.0f);

	}


	std::cout << "turn: " << turn << "\n";
	std::cout << "turn_impuesto: " << turn_impuesto << "\n";
	std::cout << "turn_casa: " << turn_casa << "\n";
	std::cout << "turn_ruleta: " << turn_ruleta << "\n";
	std::cout << "turn_dado: " << turn_dado << "\n";
	std::cout << "turn_Moviendo: " << turn_Moviendo << "\n";
	std::cout << "eventoActivo: " << eventoActivo << "\n";
	std::cout << "impuesto_draw: " << impuesto_draw << "\n";
	std::cout << "casa_draw: " << casa_draw << "\n";
	std::cout << "ruleta_draw: " << ruleta_draw << "\n";

	if (turn && !turn_impuesto && !turn_casa && !turn_ruleta && !turn_dado && !turn_Moviendo && !eventoActivo && !impuesto_draw && !casa_draw && !ruleta_draw) {

		client.networkMessage.endTurn();
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
		window->draw(playersGame[UsuariosActivos[i]].CashSprite);
		window->draw(playersGame[UsuariosActivos[i]].CasasN);
		window->draw(playersGame[UsuariosActivos[i]].Home);
		window->draw(playersGame[UsuariosActivos[i]].PieceSelect);



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
	//window->draw(Conteosuel);
	if (!chatOn)
	{
		window->draw(SpriteChat);
	}
	else {

		chats->draw();
	}
	

}