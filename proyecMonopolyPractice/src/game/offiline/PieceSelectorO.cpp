#include "PieceSelectorO.hpp"
#include "../../core/ResourceGlobal.hpp"
#include "ResourceGameO.hpp"
#include "GameOfflineO.hpp"
#include "../../ui/ButtonG.hpp"
#include "../../ui/Scrollbar.hpp"
#include <thread>
#include "../../ui/ResourceGeneral.hpp"

PieceSelectOff::PieceSelectOff(sf::RenderWindow* windowRef, int UsersN, int Map)
	: window(windowRef), selectedPiece(-1),Nmap(Map) {
	loadResourceGame();
}
PieceSelectOff::~PieceSelectOff() {
	piecesOff.clear();
	shadow.clear();
	pieceShape.clear();
	window = nullptr;
	newSelection = nullptr;
}
void PieceSelectOff::Resource() {
	std::cout << "\nwo";
	
	int piecesCount = 19;  //Cantidad de piezas
	piecesOff.resize(piecesCount);
	shadow.resize(piecesCount);
	pieceShape.resize(piecesCount);



	turn_dice = false;
	firstTurn = false;
	turn_roulette =false;
	turn_house = false;
	turn_Tax = false;
	rolldicePlayer = false;
	std::cout << "\nwo";
	if (!Textufondopiece.loadFromFile("assets/image/Game/FondoGameScroll.png")) return;
	fondopiece.setTexture(Textufondopiece);

	if (!CheckOn.loadFromFile("assets/image/Game/check1on.png")) return;
	if (!CheckOff.loadFromFile("assets/image/Game/check1off.png")) return;

	std::cout << "\nwo";
	for (int i = 0; i < piecesCount; i++) {
		if (!pieceShape[i].loadFromFile("assets/image/Game/pieces/piece" + std::to_string(i) + ".png"))
			return;

		float radio = pieceShape[i].getSize().x / 2.0f;
		piecesOff[i].setTexture(pieceShape[i]);
		shadow[i].setTexture(pieceShape[i]);
		globalBounds = piecesOff[i].getGlobalBounds();
		piecesOff[i].setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
		shadow[i].setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	}
	std::cout << "\nwo";

	for (int i = 0; i < piecesOff.size(); i++) {
		int row = i / 8;  // Determina la fila (0 para la primera, 1 para la segunda, etc.)
		int col = i % 8;  // Determina la columna (0 a 7)

		float x = 92.0f + col * 156.0f;  // 28 es la posición inicial en x, 156 es la separación entre columnas
		float y = 472.0f + row * 156.0f;  // 500 es la posición inicial en y, y 156 es la separación entre filas
		//std::cout << i << "  X :" << x << "y :" << y << std::endl;

		piecesOff[i].setPosition(x, y);

		shadow[i].setPosition(x, y);
		shadow[i].setScale(2.0f, 2.0f);
		piecesOff[i].setScale(2.0f, 2.0f);
		shadow[i].setColor(sf::Color(0, 5, 100, 40)); // Aplicar un color negro semi-transparente

	}

}
void PieceSelectOff::displayPieces() {
	for (size_t i = 0; i < piecesOff.size(); ++i) {
		window->draw(piecesOff[i]);  // Draw all pieces
		window->draw(shadow[i]);  // Draw all pieces

	}
}

void bots() {






}
void PieceSelectOff::updateSelection() {

	sf::Clock clock;
	float baseXPos = 92.0f;
	float baseYPos = 472.0f;

	PlayerInformation playerInfoNew;
	PlayerGameOff playerGameNew;
	playerInfoNew.playerName = namePlayer;
	playerInfoNew.PiecUserme = true;
	playerGameInfo.push_back(playerInfoNew);
	playerGameNew.CashSprite.setTexture(TextureMoney1);
	playerGameNew.Home.setTexture(TextureBuilding);
	playerGameNew.NamePlayer.setCharacterSize(17);
	playerGameNew.NamePlayer.setFont(fontUserProfile);
	playerGameNew.NamePlayer.setFillColor(sf::Color::White);
	playerGameNew.NamePlayer.setOutlineThickness(2);
	playerGameNew.NamePlayer.setOutlineColor(sf::Color(135, 135, 135));
	playerGameNew.NamePlayer.setString(playerGameInfo[0].playerName);

	globalBounds = playerGameNew.NamePlayer.getGlobalBounds();


	playerGameNew.NamePlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
	playerGameNew.boxPlayer.setTexture(textureBoxPerfilOff);
	playerGameNew.boxPlayer.setOrigin(125, 40);
	playerGameNew.boxPlayer.setScale(0.9f, 0.9f);
	playerGameNew.Check.setTexture(CheckOff);
	playerGameNew.Check.setOrigin(50.0f, 46.5f);
	playerGameOff.push_back(playerGameNew);
	ActiveUsers.push_back(0);
	float deltaScroll = 0.0f;
	float scrollStep = 10.0f; // Para el desplazamiento con las teclas
	const float avatarWidth = 128.0f;
	const float avatarHeight = 128.0f;
	const float avatarSeparation = 28.0f;
	const float visibleAreaHeight = 248.0f;
	const float maxScrollOffset = 632.0f;

	float widthSeparation = avatarWidth + avatarSeparation;
	float heightSeparation = avatarHeight + avatarSeparation;

	
	mousePosition = sf::Mouse::getPosition(*window);
	mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

	const float totalContentHeight = 880.0f;
	const float scrollbarHeight = 340.0f;

	float proportion = visibleAreaHeight / totalContentHeight;
	float thumbHeight = scrollbarHeight * proportion;

	const float minThumbHeight = 14.0f;
	thumbHeight = std::max(thumbHeight, minThumbHeight);

	std::cout << "\nwo1111";
	Scrollbar scrollbarPiece(340, thumbHeight, 14);

	scrollbarPiece.setPosition(1260, 340);

	float avatarYOffset = 0.0f;
	 startX = 275;  // Posición inicial calculada en X
	 startY = 100;  // Posición calculada en Y (centrado verticalmente)

	bool cierre = false;

	MenuMusicFondo.stop();
	sf::sleep(sf::seconds(0.5)); // Silencio breve
	SelectingMusicFondo.setLoop(true);
	SelectingMusicFondo.play();
	// Configurar perfiles
	float perfilWidth = 200.0f; // Ancho estimado de cada perfil
	float separacion = 20.0f;   // Espaciado entre perfiles
	ButtonG botonCheck1(CheckOff, CheckOn);
	bool Agregado = false;
	std::cout << "\naqui";
	while (window->isOpen()&& !cierre) {

		sf::Event event;
		while (window->pollEvent(event)) {

			mousePosFloat = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
				renderTexture.draw(spriteBackgroundG);
				for (int i = 0; i < ActiveUsers.size(); i++) {
				
					renderTexture.draw(playerGameOff[ActiveUsers[i]].NamePlayer);
					renderTexture.draw(playerGameOff[ActiveUsers[i]].boxPlayer);
					renderTexture.draw(playerGameOff[ActiveUsers[i]].PieceSelect);
					renderTexture.draw(playerGameOff[ActiveUsers[i]].Check);
				}
				
				renderTexture.draw(spriteX);
				renderTexture.draw(overlay);
				Menup.MenuSalir(nullptr);
			}

			scrollbarPiece.handleEvent(event, *window);
			avatarYOffset = scrollbarPiece.getScrollOffset();

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
				std::vector<sf::FloatRect> avatarBounds(piecesOff.size());
				for (int i = 0; i < piecesOff.size(); ++i) {
					int column = i % 8;
					int row = i / 8;

					float xPos = baseXPos + column * widthSeparation;

					float yPos = (baseYPos + row * heightSeparation) - avatarYOffset;

					avatarBounds[i] = sf::FloatRect(xPos, yPos, piecesOff[i].getGlobalBounds().width, piecesOff[i].getGlobalBounds().height);

					piecesOff[i].setPosition(xPos, yPos);
					shadow[i].setPosition(xPos, yPos);
				}
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				static sf::Sprite* previousSelection = nullptr;  // Almacena la pieza previamente seleccionada


				for (int i = 0; i < piecesOff.size(); ++i) {
					// Verificar si el mouse está sobre la pieza
					if (piecesOff[i].getGlobalBounds().contains(mousePosFloat)) {
						if (previousSelection != &piecesOff[i]) {  // Evitar resaltado si es la misma pieza
							if (previousSelection != nullptr) {
								previousSelection->setColor(sf::Color::White);  // Quitar el efecto de la anterior
							}
							// Asigna la textura y ajusta la escala y el origen
							newSelection = &piecesOff[i];
							playerGameOff[0].PieceSelect.setTexture(pieceShape[i], true);  // Reajustar rectángulo de la textura
							playerGameOff[0].PieceSelect.setScale(piecesOff[i].getScale());  // Ajustar la escala
							playerGameOff[0].PieceSelect.setOrigin(piecesOff[i].getOrigin());  // Ajustar el origen
							playerGameOff[0].PieceSelect.setColor(sf::Color::White);  // Asegurar color correcto
							playerGameOff[0].PieceSelect.setPosition(startX + 0 * (250 + 10), startY + 100);
							piecesOff[i].setColor(sf::Color(248, 134, 255));  // Resaltar la nueva pieza
							playerGameInfo[0].indexPiece = i;
							piecesOff[i].setColor(sf::Color(248, 134, 255));
							playClickSound();
							previousSelection = &piecesOff[i];  // Actualizar la selección anterior
						}
						break;
					}

				}
				if (playerGameOff[ActiveUsers[0]].Check.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					const sf::Texture* texturePtr = playerGameOff[ActiveUsers[0]].PieceSelect.getTexture();

					if (texturePtr != nullptr&& ActiveUsers.size()>0) {
						sf::Texture textureSelec = *texturePtr;  // Desreferenciar el puntero

						playerGameInfo[ActiveUsers[0]].isSelectingPiece = true;
						//client.networkMessage.playerReady();
						
					}

					GameOffline gameOff(*window, Nmap);
					gameOff.update();

				}
				if (spriteX.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					cierre = true;
				

						playerGameOff.clear();
						playerGameInfo.clear();
						ActiveUsers.clear();

				}

			}

		}


		


		for (int i = 0; i < ActiveUsers.size(); i++) {

			if (!playerGameInfo[ActiveUsers[i]].isSelectingPiece ){// || UsuariosActivos.size()<2) {
				SelectorPieces = false;				
			}

		}


		currentCursor = &normalCursor;
		if(Agregado){
		botonCheck1.update(mousePosFloat, currentCursor, linkCursor, normalCursor);
		}
		botonX->update(mousePosFloat, currentCursor, linkCursor, normalCursor);

		window->setMouseCursor(*currentCursor);
		//std::cout << "\nCplayerIndex:" << CplayerIndex << " client.playerIndex:"<< client.playerIndex;
		/*if (CplayerIndex != client.playerIndex && CplayerIndex != -1) {


			std::cout << "\nentro";
			updatePlayerPieceSelection(playerInfos[CplayerIndex].indexPiece);
			CplayerIndex = -1;
			client.cvExisting.notify_all();

			std::cout << "\nSalio";
		}*/
	
		for (int i = 0; i < ActiveUsers.size(); i++)
		{
			if (playerGameInfo[ActiveUsers[i]].isSelectingPiece) {
				playerGameOff[ActiveUsers[i]].Check.setTexture(CheckOn);
			}
		}

	
		window->clear();
		window->draw(spriteBackgroundG);
		
		displayPieces();
		window->draw(fondopiece);


	
		float totalPerfiles = 1;
		if (4 > 0) {
			// Calcular ancho total ocupado por perfiles y separaciones
			float totalWidth = (totalPerfiles * perfilWidth) + ((totalPerfiles - 1) * separacion);

			// Calcular inicio X para centrar los perfiles horizontalmente
			float startX = (1280.0f - totalWidth) / 2.0f + (perfilWidth / 2.0f); // Desplaza para centrar el origen

			float startY = 100.0f; // Centrado verticalmente

			for (int i = 0; i < totalPerfiles; i++) {
				float xPos = startX + i * (perfilWidth + separacion); // Calcula la posición en X para cada perfil
				float yPos = startY;
				// Posicionar elementos
				playerGameOff[ActiveUsers[i]].NamePlayer.setPosition(xPos, startY );
				playerGameOff[ActiveUsers[i]].boxPlayer.setPosition(xPos, startY );
				playerGameOff[ActiveUsers[i]].PieceSelect.setPosition(xPos, startY + 100);
				playerGameOff[ActiveUsers[i]].Check.setPosition(xPos, yPos + 200);
				window->draw(playerGameOff[ActiveUsers[i]].NamePlayer);
				window->draw(playerGameOff[ActiveUsers[i]].boxPlayer);
				window->draw(playerGameOff[ActiveUsers[i]].PieceSelect);
				window->draw(playerGameOff[ActiveUsers[i]].Check);
			}


		}
		

		window->draw(CODE);
		window->draw(spriteX);

		scrollbarPiece.draw(*window);
		window->display();


	}

}

void PieceSelectOff::updatePlayerPieceSelection(int newPieceIndex) {
/*
	piecesOff[previousSelectionIndex[CplayerIndex]].setColor(sf::Color::White); // Color original
	piecesOff[newPieceIndex].setColor(sf::Color(248, 134, 255)); // Resaltar la nueva pieza
	std::cout << "\nplayersGame" << playerGameOff.size();
	// Actualizar el sprite del jugador con la nueva textura de la pieza seleccionada
	playerGameOff[CplayerIndex].PieceSelect.setTexture(piecesTextures[newPieceIndex], true);
	playerGameOff[CplayerIndex].PieceSelect.setScale(pieces[newPieceIndex].getScale());
	playerGameOff[CplayerIndex].PieceSelect.setOrigin(pieces[newPieceIndex].getOrigin());
	playerGameOff[CplayerIndex].PieceSelect.setColor(sf::Color::White); // Asegurar el color correcto
	playerGameOff[CplayerIndex].PieceSelect.setPosition(startX + CplayerIndex * (250 + 10), startY + 100);
	previousSelectionIndex[CplayerIndex] = newPieceIndex;
*/
}