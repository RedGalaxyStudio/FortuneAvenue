#include "PieceSelectorO.hpp"
#include "../../core/ResourceGlobal.hpp"
#include "ResourceGameO.hpp"
#include "../../core/ObjetosGlobal.hpp"
#include "../../ui/ButtonG.hpp"
#include "../../ui/Scrollbar.hpp"
#include <thread>


PieceSelectOff::PieceSelectOff(sf::RenderWindow* windowRef)
	: window(windowRef), selectedPiece(-1) {
	loadResourceGame();
}
PieceSelectOff::~PieceSelectOff() {
	pieces.clear();
	shadow.clear();
	piecesTextures.clear();
	window = nullptr;
	newSelection = nullptr;
}
void PieceSelectOff::Resource() {
	std::cout << "\nwo";
	
	int piecesCount = 19;  //Cantidad de piezas
	pieces.resize(piecesCount);
	shadow.resize(piecesCount);
	piecesTextures.resize(piecesCount);

	turn_dado = false;
	turn = false;
	turn_ruleta=false;
	turn_casa= false;
	turn_impuesto= false;
	rolldiceJugador = false;
	std::cout << "\nwo";
	if (!Textufondopiece.loadFromFile("assets/image/Game/FondoGameScroll.png")) return;
	fondopiece.setTexture(Textufondopiece);


	std::cout << "\nwo";
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
	std::cout << "\nwo";

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
void PieceSelectOff::displayPieces() {
	for (size_t i = 0; i < pieces.size(); ++i) {
		window->draw(pieces[i]);  // Draw all pieces
		window->draw(shadow[i]);  // Draw all pieces

	}
}
void PieceSelectOff::updateSelection() {

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
	 startX = 275;  // Posici�n inicial calculada en X
	 startY = 100;  // Posici�n calculada en Y (centrado verticalmente)

	bool cierre = false;

	MenuMusicFondo.stop();
	sf::sleep(sf::seconds(0.5)); // Silencio breve
	SelectingMusicFondo.setLoop(true);
	SelectingMusicFondo.play();
	// Configurar perfiles
	float perfilWidth = 200.0f; // Ancho estimado de cada perfil
	float separacion = 20.0f;   // Espaciado entre perfiles
	ButtonG botonCheck1(CheckTexturesOff, CheckTexturesOn);
	bool Agregado = false;
	while (window->isOpen()&& !cierre) {

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
					renderTexture.draw(playersGame[UsuariosActivos[i]].Check);
				}
				
				renderTexture.draw(spriteX);
				renderTexture.draw(overlay);
				Menup.MenuSalir();
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
							//client.networkMessage.playerChangedPiece(i);
							// Resaltar la nueva pieza
							
							pieces[i].setColor(sf::Color(248, 134, 255));
							playClickSound();
							previousSelection = &pieces[i];  // Actualizar la selecci�n anterior
						}
						break;
					}

				}
				if (playersGame[UsuariosActivos[0]].Check.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					const sf::Texture* texturePtr = playersGame[UsuariosActivos[0]].PieceSelect.getTexture();

					if (texturePtr != nullptr&&UsuariosActivos.size()>0) {
						sf::Texture textureSelec = *texturePtr;  // Desreferenciar el puntero

						//playerInfos[UsuariosActivos[0]].isSelectingPiece = true;
						//client.networkMessage.playerReady();
						
					}
				}
				if (spriteX.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					cierre = true;
				

						playersGame.clear();
						playerInfos.clear();
						UsuariosActivos.clear();
						std::cout<<"\n numero : "<<playersGame.size();
				
					//client.disconnect();

				}

			}

		}
		/*if (client.agregardor) {
			botonCheck1.spriteAsig(playersGame[UsuariosActivos[0]].Check);
			client.agregardor = false;
			Agregado = true;

		}


		if(client.disconnecte==true){
			client.disActiv = true;
			{
				std::unique_lock<std::mutex> lock(client.mtex);
				client.cvDis.wait(lock, [] { return client.eventOccurred; }); // Espera a que `eventOccurred` sea true.
			}
			client.disconnecte = false;
			client.disActiv = false;
			client.eventOccurred = false;
		}
		int totalPerfiles = static_cast<int>(UsuariosActivos.size());
	
		if(!cierre){

			SelectingPiece = true;

		}

		for (int i = 0; i < UsuariosActivos.size(); i++) {


			if (!playerInfos[UsuariosActivos[i]].isSelectingPiece ){// || UsuariosActivos.size()<2) {
				SelectingPiece = false;

				
			}
		}*/

		if (SelectingPiece) {

			
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
	
		for (int i = 0; i < UsuariosActivos.size(); i++)
		{
			if (playerInfos[UsuariosActivos[i]].isSelectingPiece) {
				playersGame[UsuariosActivos[i]].Check.setTexture(CheckTexturesOn);
			}
		}

	
		window->clear();
		window->draw(spriteFondoGame);
		
		displayPieces();
		window->draw(fondopiece);


	
		float totalPerfiles = 0;
		if (4 > 0) {
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
void PieceSelectOff::updatePlayerPieceSelection(int newPieceIndex) {

	pieces[previousSelectionIndex[CplayerIndex]].setColor(sf::Color::White); // Color original
	pieces[newPieceIndex].setColor(sf::Color(248, 134, 255)); // Resaltar la nueva pieza
	std::cout << "\nplayersGame" << playersGame.size();
	// Actualizar el sprite del jugador con la nueva textura de la pieza seleccionada
	playersGame[CplayerIndex].PieceSelect.setTexture(piecesTextures[newPieceIndex], true);
	playersGame[CplayerIndex].PieceSelect.setScale(pieces[newPieceIndex].getScale());
	playersGame[CplayerIndex].PieceSelect.setOrigin(pieces[newPieceIndex].getOrigin());
	playersGame[CplayerIndex].PieceSelect.setColor(sf::Color::White); // Asegurar el color correcto
	playersGame[CplayerIndex].PieceSelect.setPosition(startX + CplayerIndex * (250 + 10), startY + 100);
	previousSelectionIndex[CplayerIndex] = newPieceIndex;

}