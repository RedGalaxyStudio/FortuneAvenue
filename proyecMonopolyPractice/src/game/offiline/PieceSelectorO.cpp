#include "PieceSelectorO.hpp"
#include "../../core/ResourceGlobal.hpp"
#include "ResourceGameO.hpp"
#include "GameOfflineO.hpp"
#include "../../ui/ButtonG.hpp"
#include "../../ui/Scrollbar.hpp"
#include <thread>
#include "../../ui/ResourceGeneral.hpp"

PieceSelectOff::PieceSelectOff(sf::RenderWindow* windowRef, int UsersN, int Map)
	: window(windowRef), selectedPiece(-1), nUserBot(UsersN), Nmap(Map) {
	loadResourceGameO();
}
PieceSelectOff::~PieceSelectOff() {
	piecesOff.clear();
	shadow.clear();
	pieceShape.clear();
	window = nullptr;
	newSelection = nullptr;
}
void PieceSelectOff::Resource() {

	int piecesCount = 19; 
	piecesOff.resize(piecesCount);
	shadow.resize(piecesCount);
	pieceShape.resize(piecesCount);
	if (!TextureFrame.loadFromFile("assets/image/Avatars/MarcoTexture.png")) return;
	if (!TextureMoney1.loadFromFile("assets/image/Game/cash.png")) return;
	if (!TextureBuilding.loadFromFile("assets/image/Game/casa.png")) return;

	turn_dice = false;
	firstTurn = false;
	turn_roulette =false;
	turn_house = false;
	turn_Tax = false;
	rolldicePlayer = false;
	if (!Textufondopiece.loadFromFile("assets/image/Game/FondoGameScroll.png")) return;
	fondopiece.setTexture(Textufondopiece);

	if (!CheckOn.loadFromFile("assets/image/Game/check1on.png")) return;
	if (!CheckOff.loadFromFile("assets/image/Game/check1off.png")) return;

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
	

	for (int i = 0; i < piecesOff.size(); i++) {
		int row = i / 8; 
		int col = i % 8;  

		float x = 92.0f + col * 156.0f; 
		float y = 472.0f + row * 156.0f; 
	

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
	playerGameNew.MarcoPlayer.setTexture(TextureFrame);
	globalBounds = playerGameNew.MarcoPlayer.getGlobalBounds();
	playerGameNew.MarcoPlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	playerGameNew.MarcoPlayer.setPosition(52.5f, 62.5f);

	playerGameNew.boxPlayer.setTexture(textureBoxPerfilOff);
	playerGameNew.boxPlayer.setOrigin(125, 40);
	playerGameNew.boxPlayer.setScale(0.9f, 0.9f);
	playerGameNew.Check.setTexture(CheckOff);
	playerGameNew.Check.setOrigin(50.0f, 46.5f);
	playerGameOff.push_back(playerGameNew);
	ActiveUsers.push_back(0);
	float deltaScroll = 0.0f;
	float scrollStep = 10.0f;
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

	Scrollbar scrollbarPiece(340, thumbHeight, 14);

	scrollbarPiece.setPosition(1260, 340);

	float avatarYOffset = 0.0f;
	 startX = 275; 
	 startY = 100;  

	bool cierre = false;

	MenuMusicFondo.stop();
	sf::sleep(sf::seconds(0.5)); 
	SelectingMusicFondo.setLoop(true);
	SelectingMusicFondo.play();
	// Configurar perfiles
	float perfilWidth = 200.0f; 
	float separacion = 20.0f;  
	ButtonG botonCheck1(CheckOff, CheckOn);
	bool Agregado = false;
	
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
				static sf::Sprite* previousSelection = nullptr; 


				for (int i = 0; i < piecesOff.size(); ++i) {
					// Verificar si el mouse está sobre la pieza
					if (piecesOff[i].getGlobalBounds().contains(mousePosFloat)) {
						if (previousSelection != &piecesOff[i]) { 
							if (previousSelection != nullptr) {
								previousSelection->setColor(sf::Color::White); 
							}
							
							newSelection = &piecesOff[i];
							playerGameOff[0].PieceSelect.setTexture(pieceShape[i], true); 
							playerGameOff[0].PieceSelect.setScale(piecesOff[i].getScale()); 
							playerGameOff[0].PieceSelect.setOrigin(piecesOff[i].getOrigin()); 
							playerGameOff[0].PieceSelect.setColor(sf::Color::White); 
							playerGameOff[0].PieceSelect.setPosition(startX + 0 * (250 + 10), startY + 100);
							piecesOff[i].setColor(sf::Color(248, 134, 255));  // Resaltar la nueva pieza
							playerGameInfo[0].indexPiece = i;
							piecesOff[i].setColor(sf::Color(248, 134, 255));
							playClickSound();
							previousSelection = &piecesOff[i]; 
						}
						break;
					}

				}
				if (playerGameOff[ActiveUsers[0]].Check.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					const sf::Texture* texturePtr = playerGameOff[ActiveUsers[0]].PieceSelect.getTexture();
					std::cout << "\n\nPROBANDO" << std::endl;
					if (texturePtr != nullptr&& ActiveUsers.size()>0) {
						sf::Texture textureSelec = *texturePtr; 

						playerGameInfo[ActiveUsers[0]].isSelectingPiece = true;
						//client.networkMessage.playerReady();
						std::cout << "\n\nPROBANDO2" << std::endl;
					}
					GM.GenerarBot(nUserBot);
					GameOffline gameOff(*window, Nmap);
					std::cout << "\nuy";
					gameOff.update();
					std::cout << "\n\nPROBANDO3" << std::endl;
				}
				if (spriteX.getGlobalBounds().contains(mousePosFloat)) {
					std::cout << "\n\nPROBANDO4" << std::endl;
					playClickSound();
					//cierre = true;
				

						//playerGameOff.clear();
						//playerGameInfo.clear();
						//ActiveUsers.clear();
					return;
				}

			}

		}

		for (int i = 0; i < ActiveUsers.size(); i++) {
			std::cout << "\n\nPROBANDO5" << std::endl;
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
		std::cout << "\n\nPROBANDO6" << std::endl;
	
		for (int i = 0; i < ActiveUsers.size(); i++)
		{
			std::cout << "\n\nPROBANDO7" << std::endl;
			if (playerGameInfo[ActiveUsers[i]].isSelectingPiece) {
				std::cout << "\n\nPROBANDO8" << std::endl;
				playerGameOff[ActiveUsers[i]].Check.setTexture(CheckOn);
			}
		}

		window->clear();
		window->draw(spriteBackgroundG);
		
		displayPieces();
		window->draw(fondopiece);

		float totalPerfiles = 1;
		if (4 > 0) {
			std::cout << "\n\nPROBANDO9" << std::endl;
			
			float totalWidth = (totalPerfiles * perfilWidth) + ((totalPerfiles - 1) * separacion);
			float startX = (1280.0f - totalWidth) / 2.0f + (perfilWidth / 2.0f);

			float startY = 100.0f; 

			for (int i = 0; i < totalPerfiles; i++) {
				float xPos = startX + i * (perfilWidth + separacion); // Calcula la posición en X para cada perfil
				float yPos = startY;
				
				playerGameOff[ActiveUsers[i]].NamePlayer.setPosition(xPos, startY );
				playerGameOff[ActiveUsers[i]].boxPlayer.setPosition(xPos, startY );
				playerGameOff[ActiveUsers[i]].PieceSelect.setPosition(xPos, startY + 100);
				playerGameOff[ActiveUsers[i]].Check.setPosition(xPos, yPos + 200);
				window->draw(playerGameOff[ActiveUsers[i]].NamePlayer);
				window->draw(playerGameOff[ActiveUsers[i]].boxPlayer);
				window->draw(playerGameOff[ActiveUsers[i]].PieceSelect);
				window->draw(playerGameOff[ActiveUsers[i]].Check);
				std::cout << "\n\nPROBANDO10" << std::endl;
			}


		}

		window->draw(CODE);
		window->draw(spriteX);

		scrollbarPiece.draw(*window);
		window->display();
		std::cout << "\n\nPROBANDO11" << std::endl;
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