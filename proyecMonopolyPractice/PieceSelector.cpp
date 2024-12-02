#include "PieceSelector.hpp"
#include "ResourceGlobal.hpp"
#include "ResourceGame.hpp"
#include "ObjetosGlobal.hpp"
#include "ButtonG.hpp"
#include "GameMode.hpp"
#include "Scrollbar.hpp"

// Constructor
PieceSelector::PieceSelector(sf::RenderWindow* windowRef)
	: window(windowRef), selectedPiece(-1) {
	loadResourceGame();
}

void PieceSelector::Resource() {

	playerInfos[0].username = input1;
	int piecesCount = 19;  //Cantidad de piezas
	pieces.resize(piecesCount);
	shadow.resize(piecesCount);
	piecesTextures.resize(piecesCount);
	Check.resize(4);
	CheckTexturesOn.resize(4);
	CheckTexturesOff.resize(4);
	turn_dado = false;
	turn = false;
	turn_ruleta=false;
	turn_casa= false;
	turn_impuesto= false;
	rolldiceJugador = false;

	if (!Textufondopiece.loadFromFile("resource/texture/Game/FondoGameScroll.png")) return;
	fondopiece.setTexture(Textufondopiece);

	for (int i = 0; i < 4; i++) {
		if (!CheckTexturesOn[i].loadFromFile("resource/texture/Game/check1on.png")) return;
		if (!CheckTexturesOff[i].loadFromFile("resource/texture/Game/check1off.png")) return;

		
		Check[i].setTexture(CheckTexturesOff[i]);
		Check[i].setOrigin(50.0f, 46.5f);

	}

	for (int i = 0; i < piecesCount; i++) {
		if (!piecesTextures[i].loadFromFile("resource/texture/Game/pieces/piece" + std::to_string(i) + ".png"))
			return;

		float radio = piecesTextures[i].getSize().x / 2.0f;
		pieces[i].setTexture(piecesTextures[i]);
		shadow[i].setTexture(piecesTextures[i]);
		globalBounds = pieces[i].getGlobalBounds();
		pieces[i].setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
		shadow[i].setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	}

	for (int i = 0; i < pieces.size(); i++) {
		int row = i / 8;  // Determina la fila (0 para la primera, 1 para la segunda, etc.)
		int col = i % 8;  // Determina la columna (0 a 7)

		float x = 92.0f + col * 156.0f;  // 28 es la posici�n inicial en x, 156 es la separaci�n entre columnas
		float y = 472.0f + row * 156.0f;  // 500 es la posici�n inicial en y, y 156 es la separaci�n entre filas
		//std::cout << i << "  X :" << x << "y :" << y << std::endl;

		pieces[i].setPosition(x, y);

		shadow[i].setPosition(x, y);
		shadow[i].setScale(2.0f, 2.0f);
		pieces[i].setScale(2.0f, 2.0f);
		shadow[i].setColor(sf::Color(0, 5, 100, 40)); // Aplicar un color negro semi-transparente

	}

}



// Display pieces for selection
void PieceSelector::displayPieces() {
	for (size_t i = 0; i < pieces.size(); ++i) {
		window->draw(pieces[i]);  // Draw all pieces
		window->draw(shadow[i]);  // Draw all pieces

	}
}


// Update the selection based on user input
void PieceSelector::updateSelection() {

	sf::Clock clock;
	float baseXPos = 92.0f;
	float baseYPos = 472.0f;



	float deltaScroll = 0.0f;
	float scrollStep = 10.0f; // Para el desplazamiento con las teclas
	const float avatarWidth = 128.0f;
	const float avatarHeight = 128.0f;
	const float avatarSeparation = 28.0f;
	const float visibleAreaHeight = 248.0f;
	const float maxScrollOffset = 632.0f;

	float widthSeparation = avatarWidth + avatarSeparation;
	float heightSeparation = avatarHeight + avatarSeparation;

	GameMode gamemode(*window);
	
	mousePosition = sf::Mouse::getPosition(*window);
	mousePosFloat = static_cast<sf::Vector2f>(mousePosition);



	const float totalContentHeight = 880.0f;
	const float scrollbarHeight = 340.0f;


	float proportion = visibleAreaHeight / totalContentHeight;
	float thumbHeight = scrollbarHeight * proportion;


	const float minThumbHeight = 14.0f;
	thumbHeight = std::max(thumbHeight, minThumbHeight);


	Scrollbar scrollbarPiece(340, thumbHeight, 14);

	scrollbarPiece.setPosition(1260, 340);

	float avatarYOffset = 0.0f;
	 startX = 275;  // Posici�n inicial calculada en X
	 startY = 100;  // Posici�n calculada en Y (centrado verticalmente)
	playersGame[0].NamePlayer.setString(playerInfos[0].username);
	globalBounds = playersGame[0].NamePlayer.getGlobalBounds();
	playersGame[0].NamePlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	CODE.setFont(fontUser);
	CODE.setCharacterSize(20);
	CODE.setString("CODIGO: " + Code);
	CODE.setFillColor(sf::Color::White);
	CODE.setOutlineThickness(2);
	CODE.setOutlineColor(sf::Color(135, 135, 135));
	bool cierre = false;
	// Ahora calcula los l�mites y centra
	globalBounds = CODE.getGlobalBounds();
	CODE.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	// Finalmente, establece la posici�n
	CODE.setPosition(640, 30);
	ButtonG botonCheck1(Check[0], CheckTexturesOff[0], CheckTexturesOn[0]);
	client.sendImage(TextureAvatarPath);

	for (int i = 0; i < 4; ++i) {
		// Asignar nombre al jugador actual
		playersGame[i].NamePlayer.setString(playerInfos[i].username);
		globalBounds = playersGame[i].NamePlayer.getGlobalBounds();
		playersGame[i].NamePlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
		playersGame[i].Activo = false;
		// Posicionar el jugador y los elementos relacionados
		playersGame[i].boxPlayer.setPosition(startX + i * (250 + 10), startY);
		playersGame[i].NamePlayer.setPosition(startX + i * (250 + 10), startY);
		playersGame[i].PieceSelect.setPosition(startX + i * (250 + 10), startY + 100);

	}
	MenuMusicFondo.stop();
	sf::sleep(sf::seconds(0.5)); // Silencio breve
	SelectingMusicFondo.setLoop(true);
	SelectingMusicFondo.play();
	playersGame[0].Activo = false;
	// Configurar perfiles
	float perfilWidth = 200.0f; // Ancho estimado de cada perfil
	float separacion = 20.0f;   // Espaciado entre perfiles
	
	while (window->isOpen()&& !cierre) {

		
		for (int i = 0; i < NumPlayers; ++i) {
			// Asignar nombre al jugador actual
			playersGame[i].NamePlayer.setString(playerInfos[i].username);
			globalBounds = playersGame[i].NamePlayer.getGlobalBounds();
			playersGame[i].NamePlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
		}




		sf::Event event;
		while (window->pollEvent(event)) {

			mousePosFloat = window->mapPixelToCoords(sf::Mouse::getPosition(*window));


			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
				renderTexture.draw(spriteFondoGame);
				for (int i = 0; i < UsuariosActivos.size(); i++) {
				
					renderTexture.draw(playersGame[UsuariosActivos[i]].NamePlayer);
					renderTexture.draw(playersGame[UsuariosActivos[i]].boxPlayer);
					renderTexture.draw(playersGame[UsuariosActivos[i]].PieceSelect);
					renderTexture.draw(Check[UsuariosActivos[i]]);
				}
				
				renderTexture.draw(spriteX);
				renderTexture.draw(overlay);
				Menup.MenuSalir();
			}


			scrollbarPiece.handleEvent(event, *window);
			avatarYOffset = scrollbarPiece.getScrollOffset();
			// scrollbar.evento(event);
			if (event.type == sf::Event::MouseWheelScrolled) {

				scrollbarPiece.update(event.mouseWheelScroll.delta);
				avatarYOffset = scrollbarPiece.getScrollOffset();

			}

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Down) {
					deltaScroll = 1.0f; // Desplazamiento hacia abajo
					scrollbarPiece.update(deltaScroll);
					avatarYOffset = scrollbarPiece.getScrollOffset();
				}
				else if (event.key.code == sf::Keyboard::Up) {
					deltaScroll = -1.0f; // Desplazamiento hacia arriba
					scrollbarPiece.update(deltaScroll);
					avatarYOffset = scrollbarPiece.getScrollOffset();
				}
			}


			if (avatarYOffset > maxScrollOffset) {
				avatarYOffset = maxScrollOffset;
			}
			else if (avatarYOffset < 0) {
				avatarYOffset = 0;
			}

			if (avatarYOffset != 0) {
				std::vector<sf::FloatRect> avatarBounds(pieces.size());
				for (int i = 0; i < pieces.size(); ++i) {
					int column = i % 8;
					int row = i / 8;

					float xPos = baseXPos + column * widthSeparation;

					float yPos = (baseYPos + row * heightSeparation) - avatarYOffset;

					avatarBounds[i] = sf::FloatRect(xPos, yPos, pieces[i].getGlobalBounds().width, pieces[i].getGlobalBounds().height);

					pieces[i].setPosition(xPos, yPos);
					shadow[i].setPosition(xPos, yPos);
				}
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				static sf::Sprite* previousSelection = nullptr;  // Almacena la pieza previamente seleccionada
				for (int i = 0; i < pieces.size(); ++i) {
					// Verificar si el mouse est� sobre la pieza
					if (pieces[i].getGlobalBounds().contains(mousePosFloat)) {
						if (previousSelection != &pieces[i]) {  // Evitar resaltado si es la misma pieza
							if (previousSelection != nullptr) {
								previousSelection->setColor(sf::Color::White);  // Quitar el efecto de la anterior
							}
							// Asigna la textura y ajusta la escala y el origen
							newSelection = &pieces[i];
							// Asigna la textura a PiecesSelect[0]
							playersGame[0].PieceSelect.setTexture(piecesTextures[i], true);  // Reajustar rect�ngulo de la textura
							playersGame[0].PieceSelect.setScale(pieces[i].getScale());  // Ajustar la escala
							playersGame[0].PieceSelect.setOrigin(pieces[i].getOrigin());  // Ajustar el origen
							playersGame[0].PieceSelect.setColor(sf::Color::White);  // Asegurar color correcto
							playersGame[0].PieceSelect.setPosition(startX + 0 * (250 + 10), startY + 100);
							pieces[i].setColor(sf::Color(248, 134, 255));  // Resaltar la nueva pieza
							playerInfos[0].indexPiece = i;
							client.playerChangedPiece();
							// Resaltar la nueva pieza
							
							pieces[i].setColor(sf::Color(248, 134, 255));
							playClickSound();
							previousSelection = &pieces[i];  // Actualizar la selecci�n anterior
						}
						break;
					}

				}
				if (Check[0].getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					const sf::Texture* texturePtr = playersGame[0].PieceSelect.getTexture();

					if (texturePtr != nullptr&&UsuariosActivos.size()>0) {
						sf::Texture textureSelec = *texturePtr;  // Desreferenciar el puntero

						playerInfos[0].isSelectingPiece = true;
						client.ReadyPlayer();
						
					}
				}
				if (spriteX.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					cierre = true;
					client.disconnect();

				}

			}

		}




		for (int i = 0; i < 4; i++) {

			if (!playerInfos[i].username.empty()&& !playersGame[i].Activo) {
				std::cout << "\nusuarios " << i;
				UsuariosActivos.push_back(i);
				playersGame[i].Activo = true;
				std::cout << "\n1";
			}

		}
		int totalPerfiles = UsuariosActivos.size(); // Usar el n�mero real de perfiles

	
		SelectingPiece = true;

		for (int i = 0; i < UsuariosActivos.size(); i++) {


			if (!playerInfos[UsuariosActivos[i]].isSelectingPiece) {
				SelectingPiece = false;

				
			}
		}

		if (SelectingPiece) {
			gamemode.update();
		}

		currentCursor = &normalCursor;
		botonCheck1.update(mousePosFloat, currentCursor, linkCursor, normalCursor);
		botonX->update(mousePosFloat, currentCursor, linkCursor, normalCursor);

		window->setMouseCursor(*currentCursor);

		if (CplayerIndex > 0 && CplayerIndex <= 3) {
			updatePlayerPieceSelection(playerInfos[CplayerIndex].indexPiece);
			CplayerIndex = -1;
			client.cvExisting.notify_all();
		}

		for (int i = 0; i < 4; i++)
		{
			if (playerInfos[i].isSelectingPiece) {
				Check[i].setTexture(CheckTexturesOn[i]);
			}
		}

		if (playerInfos[0].isSelectingPiece && playerInfos[1].isSelectingPiece && playerInfos[2].isSelectingPiece && playerInfos[3].isSelectingPiece) {

		}
		window->clear();
		window->draw(spriteFondoGame);
		
		displayPieces();
		window->draw(fondopiece);


	

		if (totalPerfiles > 0) {
			// Calcular ancho total ocupado por perfiles y separaciones
			float totalWidth = (totalPerfiles * perfilWidth) + ((totalPerfiles - 1) * separacion);

			// Calcular inicio X para centrar los perfiles horizontalmente
			float startX = (1280.0f - totalWidth) / 2.0f + (perfilWidth / 2.0f); // Desplaza para centrar el origen

			float startY = 100.0f; // Centrado verticalmente

			for (int i = 0; i < totalPerfiles; i++) {
				float xPos = startX + i * (perfilWidth + separacion); // Calcula la posici�n en X para cada perfil
				float yPos = startY;
				// Posicionar elementos
				playersGame[UsuariosActivos[i]].NamePlayer.setPosition(xPos, startY );
				playersGame[UsuariosActivos[i]].boxPlayer.setPosition(xPos, startY );
				playersGame[UsuariosActivos[i]].PieceSelect.setPosition(xPos, startY + 100);
				Check[UsuariosActivos[i]].setPosition(xPos, yPos + 200);
				window->draw(playersGame[UsuariosActivos[i]].NamePlayer);
				window->draw(playersGame[UsuariosActivos[i]].boxPlayer);
				window->draw(playersGame[UsuariosActivos[i]].PieceSelect);
				window->draw(Check[UsuariosActivos[i]]);
			}
		}
		

		window->draw(CODE);
		window->draw(spriteX);

		scrollbarPiece.draw(*window);
		window->display();


	}

}

void PieceSelector::updatePlayerPieceSelection(int newPieceIndex) {
	// Suponiendo que `pieces` es un vector de sprites que contiene todas las piezas del juego
	// y `playersGame` es un arreglo de estructuras que almacena la informaci�n de los jugadores.
	pieces[previousSelectionIndex[CplayerIndex]].setColor(sf::Color::White); // Color original
	// Primero, quita el resaltado de la pieza previamente seleccionada del jugador

	// Ahora resaltar la nueva pieza seleccionada
	pieces[newPieceIndex].setColor(sf::Color(248, 134, 255)); // Resaltar la nueva pieza

	// Actualizar el sprite del jugador con la nueva textura de la pieza seleccionada
	playersGame[CplayerIndex].PieceSelect.setTexture(piecesTextures[newPieceIndex], true);
	playersGame[CplayerIndex].PieceSelect.setScale(pieces[newPieceIndex].getScale());
	playersGame[CplayerIndex].PieceSelect.setOrigin(pieces[newPieceIndex].getOrigin());
	playersGame[CplayerIndex].PieceSelect.setColor(sf::Color::White); // Asegurar el color correcto
	playersGame[CplayerIndex].PieceSelect.setPosition(startX + CplayerIndex * (250 + 10), startY + 100);
	// Guardar el �ndice de la pieza seleccionada
	//playerInfos[CplayerIndex].indexPiece = newPieceIndex;
	previousSelectionIndex[CplayerIndex] = newPieceIndex;
	// Aseg�rate de que el nuevo sprite est� correctamente posicionado si es necesario
	// playersGame[playerIndex].PieceSelect.setPosition(...);
}