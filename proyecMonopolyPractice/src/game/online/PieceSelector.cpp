#include "PieceSelector.hpp"
#include "../../core/ResourceGlobal.hpp"
#include "ResourceGame.hpp"
#include "../../ui/ResourceGeneral.hpp"
#include "../../core/ObjetosGlobal.hpp"
#include "../../ui/ButtonG.hpp"
#include "MultiplayerGame.hpp"
#include "../../ui/Scrollbar.hpp"
#include <thread>
#include <atomic>
#include "Chat.hpp"
#include "OnlineVars.hpp"
#include "loading.hpp"
#include "string"

PieceSelector::PieceSelector(sf::RenderWindow* windowRef, Client* clientRef)
	: window(windowRef),client(clientRef), selectedPiece(-1) {
	loadResourceGame();
}

PieceSelector::~PieceSelector() {
	pieces.clear();
	shadow.clear();

	piecesTextures.clear();

	window = nullptr;

	newSelection = nullptr;
}
void PieceSelector::Resource() {
	//printMemoryUsage();
	
	int piecesCount = 19; 
	pieces.resize(piecesCount);
	shadow.resize(piecesCount);
	piecesTextures.resize(piecesCount);

	turn_dado = false;
	turn = false;
	turn_ruleta=false;
	turn_casa= false;
	turn_impuesto= false;
	rolldiceJugador = false;
	if (!Textufondopiece.loadFromFile("assets/image/Game/FondoGameScroll.png")) return;
	if (!Preguntasalir.loadFromFile("assets/image/Button/ExitSala.png")) return;
	fondopiece.setTexture(Textufondopiece);

	//printMemoryUsage();

	for (int i = 0; i < piecesCount; i++) {
		if (!piecesTextures[i].loadFromFile("assets/image/Game/pieces/piece" + std::to_string(i) + ".png"))
			return;

		float radio = piecesTextures[i].getSize().x / 2.0f;
		pieces[i].setTexture(piecesTextures[i]);
		shadow[i].setTexture(piecesTextures[i]);
		globalBounds = pieces[i].getGlobalBounds();
		pieces[i].setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
		shadow[i].setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	}

	//printMemoryUsage();
	for (int i = 0; i < pieces.size(); i++) {
		int row = i / 8;  
		int col = i % 8;  

		float x = 92.0f + col * 156.0f; 
		float y = 472.0f + row * 156.0f;  

		pieces[i].setPosition(x, y);

		shadow[i].setPosition(x, y);
		shadow[i].setScale(2.0f, 2.0f);
		pieces[i].setScale(2.0f, 2.0f);
		shadow[i].setColor(sf::Color(0, 5, 100, 40));

	}

}
void PieceSelector::displayPieces() {
	for (size_t i = 0; i < pieces.size(); ++i) {
		window->draw(pieces[i]);  
		window->draw(shadow[i]); 

	}
}
void PieceSelector::updateSelection() {
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	Chat chat(window,client);
	sf::Clock clock;
	float baseXPos = 92.0f;
	float baseYPos = 472.0f;
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
	CODE.setFont(fontUser);
	CODE.setCharacterSize(20);
	CODE.setString("CODIGO: " + Code);
	CODE.setFillColor(sf::Color::White);
	CODE.setOutlineThickness(2);
	CODE.setOutlineColor(sf::Color(135, 135, 135));
	bool cierre = false;

	globalBounds = CODE.getGlobalBounds();
	CODE.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	CODE.setPosition(640, 30);
	MenuMusicFondo.stop();
	sf::sleep(sf::seconds(0.5)); 
	SelectingMusicFondo.setLoop(true);
	SelectingMusicFondo.play();

	float perfilWidth = 200.0f; 
	float separacion = 20.0f;  
	ButtonG botonCheck1(CheckTexturesOff, CheckTexturesOn);
	bool Agregado = false;
	while (window->isOpen()&& !cierre) {


		sf::Event event;
		while (window->pollEvent(event)) {

			mousePosFloat = window->mapPixelToCoords(sf::Mouse::getPosition(*window));


			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
				renderTexture.draw(spriteBackgroundG);
				for (int i = 0; i < UsuariosActivos.size(); i++) {
				
					renderTexture.draw(playersGame[UsuariosActivos[i]].NamePlayer);
					renderTexture.draw(playersGame[UsuariosActivos[i]].boxPlayer);
					renderTexture.draw(playersGame[UsuariosActivos[i]].PieceSelect);
					renderTexture.draw(playersGame[UsuariosActivos[i]].Check);
				}
				
				renderTexture.draw(spriteX);
				renderTexture.draw(overlay);
				Menup.MenuSalir(client);
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
					deltaScroll = 1.0f;
					scrollbarPiece.update(deltaScroll);
					avatarYOffset = scrollbarPiece.getScrollOffset();
				}
				else if (event.key.code == sf::Keyboard::Up) {
					deltaScroll = -1.0f; 
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
				static sf::Sprite* previousSelection = nullptr; 


				for (int i = 0; i < pieces.size(); ++i) {

					if (pieces[i].getGlobalBounds().contains(mousePosFloat) ) {


						bool validP = true;
						for (int j = 0; j < UsuariosActivos.size(); j++)
						{
							if (playerInfos[j].indexPiece == i)
							{
								validP = false;
								break; 
							}
						}

						if ((previousSelection != &pieces[i])&& validP) {
							if (previousSelection != nullptr) {
								previousSelection->setColor(sf::Color::White);
							}
							newSelection = &pieces[i];

							playersGame[playerIndex].PieceSelect.setTexture(piecesTextures[i], true); 
							playersGame[playerIndex].PieceSelect.setScale(pieces[i].getScale()); 
							playersGame[playerIndex].PieceSelect.setOrigin(pieces[i].getOrigin());  
							playersGame[playerIndex].PieceSelect.setColor(sf::Color::White); 
							playersGame[playerIndex].PieceSelect.setPosition(startX + 0 * (250 + 10), startY + 100);
							pieces[i].setColor(sf::Color(248, 134, 255)); 
							playerInfos[playerIndex].indexPiece = i;
							client->networkMessage.playerChangedPiece(i);
				
							
							pieces[i].setColor(sf::Color(248, 134, 255));
							playClickSound();
							previousSelection = &pieces[i];
						}
						break;
					}

				}
				if (playersGame[UsuariosActivos[0]].Check.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					const sf::Texture* texturePtr = playersGame[UsuariosActivos[0]].PieceSelect.getTexture();

					if (texturePtr != nullptr&&UsuariosActivos.size()>0) {
						sf::Texture textureSelec = *texturePtr;  // Desreferenciar el puntero

						playerInfos[UsuariosActivos[0]].isSelectingPiece = true;
						client->networkMessage.playerReady();
						
					}
				}
				if (spriteX.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					renderTexture.clear();
					renderTexture.draw(spriteBackgroundG);
					for (int i = 0; i < UsuariosActivos.size(); i++) {

						renderTexture.draw(playersGame[UsuariosActivos[i]].NamePlayer);
						renderTexture.draw(playersGame[UsuariosActivos[i]].boxPlayer);
						renderTexture.draw(playersGame[UsuariosActivos[i]].PieceSelect);
						renderTexture.draw(playersGame[UsuariosActivos[i]].Check);
					}

					renderTexture.draw(spriteX);
					renderTexture.draw(overlay);
					renderTexture.display();
					cierre = salirX(Preguntasalir,window,client);
				
					if(cierre){
						playersGame.clear();
						playerInfos.clear();
						UsuariosActivos.clear();
				
					client->disconnect();}

				}

			}

		}
		if (client->clientData->agregardor) {
			botonCheck1.spriteAsig(playersGame[UsuariosActivos[0]].Check);
			client->clientData->agregardor = false;
			Agregado = true;

		}


		if(client->clientData->disconnecte==true){
			client->clientData->disActiv = true;
			{
				std::unique_lock<std::mutex> lock(client->clientData->mtex);
				client->clientData->cvDis.wait(lock, [this] { return client->clientData->eventOccurred; });
			}
			client->clientData->disconnecte = false;
			client->clientData->disActiv = false;
			client->clientData->eventOccurred = false;
		}
		int totalPerfiles = static_cast<int>(UsuariosActivos.size());
	
		if(!cierre){

			SelectingPiece = true;

		}

		for (int i = 0; i < UsuariosActivos.size(); i++) {


			if (!playerInfos[UsuariosActivos[i]].isSelectingPiece ){
				SelectingPiece = false;
				
				
			}
		}

		if (SelectingPiece) {

			LoadingScreen loading(*window);
			window->setActive(false);

			loading.LoadResources();


			MultiplayerGame mpGame(*window,chat,client);
			client->networkMessage.cargarImagen(TextureAvatarPath);
			mpGame.update(loading);
			if(ReturnMenu){
				
				client->~Client();
				resetGameResources();
				return;
			}
			else {
				SelectingPiece = false;
				for (int i = 0; i < UsuariosActivos.size(); i++) {
					playerInfos[i].reset();
					playersGame[i].reset();


				}



			}
		}

		currentCursor = &normalCursor;
		if(Agregado){
		botonCheck1.update(mousePosFloat, currentCursor, linkCursor, normalCursor);
		}
		botonX->update(mousePosFloat, currentCursor, linkCursor, normalCursor);

		window->setMouseCursor(*currentCursor);
		//std::cout << "\nCplayerIndex:" << CplayerIndex << " playerIndex:"<< playerIndex;
		if (CplayerIndex != playerIndex && CplayerIndex != -1) {


			updatePlayerPieceSelection(playerInfos[CplayerIndex].indexPiece);
			CplayerIndex = -1;
			client->clientData->cvExisting.notify_all();

		}
	
		for (int i = 0; i < UsuariosActivos.size(); i++)
		{
			if (playerInfos[UsuariosActivos[i]].isSelectingPiece) {
				playersGame[UsuariosActivos[i]].Check.setTexture(CheckTexturesOn);
			}
		}

	
		window->clear();
		window->draw(spriteBackgroundG);
		
		displayPieces();
		window->draw(fondopiece);


	

		if (totalPerfiles > 0) {
			float totalWidth = (totalPerfiles * perfilWidth) + ((totalPerfiles - 1) * separacion);

			float startX = (1280.0f - totalWidth) / 2.0f + (perfilWidth / 2.0f); 
			float startY = 100.0f; 

			for (int i = 0; i < totalPerfiles; i++) {
				float xPos = startX + i * (perfilWidth + separacion); 
				float yPos = startY;
			
				playersGame[UsuariosActivos[i]].NamePlayer.setPosition(xPos, startY );
				playersGame[UsuariosActivos[i]].boxPlayer.setPosition(xPos, startY );
				playersGame[UsuariosActivos[i]].PieceSelect.setPosition(xPos, startY + 100);
				playersGame[UsuariosActivos[i]].Check.setPosition(xPos, yPos + 200);
				window->draw(playersGame[UsuariosActivos[i]].NamePlayer);
				window->draw(playersGame[UsuariosActivos[i]].boxPlayer);
				window->draw(playersGame[UsuariosActivos[i]].PieceSelect);
				window->draw(playersGame[UsuariosActivos[i]].Check);
			}


		}
		

		window->draw(CODE);
		window->draw(spriteX);

		scrollbarPiece.draw(*window);
		window->display();


	}

}
void PieceSelector::updatePlayerPieceSelection(int newPieceIndex) {

	pieces[previousSelectionIndex[CplayerIndex]].setColor(sf::Color::White); 
	pieces[newPieceIndex].setColor(sf::Color(248, 134, 255));

	playersGame[CplayerIndex].PieceSelect.setTexture(piecesTextures[newPieceIndex], true);
	playersGame[CplayerIndex].PieceSelect.setScale(pieces[newPieceIndex].getScale());
	playersGame[CplayerIndex].PieceSelect.setOrigin(pieces[newPieceIndex].getOrigin());
	playersGame[CplayerIndex].PieceSelect.setColor(sf::Color::White);
	playersGame[CplayerIndex].PieceSelect.setPosition(startX + CplayerIndex * (250 + 10), startY + 100);
	previousSelectionIndex[CplayerIndex] = newPieceIndex;

}

std::atomic<bool> chatActivo(true); 

void chat() {
	std::string mensaje;
	while (chatActivo) {
		std::getline(std::cin, mensaje);
		if (mensaje == "/salir") {
			chatActivo = false;
			break;
		}
	}
}