#include "PieceSelector.hpp"
#include "ResourceGlobal.hpp"
#include "ResourceGame.hpp"
#include "ObjetosGlobal.hpp"
#include "ButtonG.hpp"
#include "GameMode.hpp"

// Constructor
PieceSelector::PieceSelector(sf::RenderWindow* windowRef)
    : window(windowRef), selectedPiece(-1) {
    loadResourceGame();
}

void PieceSelector::Resource() {
    
    playerInfos[0].username = input1;
    int piecesCount = 16;  //Cantidad de piezas
    pieces.resize(piecesCount);
    shadow.resize(piecesCount);  
    piecesTextures.resize(piecesCount);
    Check.resize(4);
    CheckTexturesOn.resize(4);
    CheckTexturesOff.resize(4);
   
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

        float x = 92.0f + col * 156.0f;  // 28 es la posición inicial en x, 156 es la separación entre columnas
        float y = 472.0f + row * 156.0f;  // 500 es la posición inicial en y, y 156 es la separación entre filas
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
    
    GameMode gamemode(*window);

    mousePosition = sf::Mouse::getPosition(*window);
    mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

    float startX = 275;  // Posición inicial calculada en X
    float startY = 100;  // Posición calculada en Y (centrado verticalmente)
    playersGame[0].NamePlayer.setString(playerInfos[0].username);
    globalBounds = playersGame[0].NamePlayer.getGlobalBounds();
    playersGame[0].NamePlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);



    CODE.setFont(fontUser);
    CODE.setCharacterSize(20);
    CODE.setString("CODIGO: " + Code);
    CODE.setFillColor(sf::Color::White);
    CODE.setOutlineThickness(2);
    CODE.setOutlineColor(sf::Color(135, 135, 135));
    
    // Ahora calcula los límites y centra
    globalBounds = CODE.getGlobalBounds();
    CODE.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

    // Finalmente, establece la posición
    CODE.setPosition(640, 30);
    ButtonG botonCheck1(Check[0],CheckTexturesOff[0], CheckTexturesOn[0]);
    
    while (window->isOpen()) {
       
                NumPlayers++;
     
    

        switch (NumPlayers)
        {
        case 1:
            playersGame[1].NamePlayer.setString(playerInfos[1].username);
            globalBounds = playersGame[1].NamePlayer.getGlobalBounds();
            playersGame[1].NamePlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
            for (int i = 0; i < 2; ++i) {
                playersGame[i].boxPlayer.setPosition(startX + i * (250 + 10), startY);
                playersGame[i].NamePlayer.setPosition(startX + i * (250 + 10), startY);
            }
            break;

        case 2:
            playersGame[2].NamePlayer.setString(playerInfos[2].username);
            globalBounds = playersGame[2].NamePlayer.getGlobalBounds();
            playersGame[2].NamePlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
            for (int i = 0; i < 3; ++i) {
                playersGame[i].boxPlayer.setPosition(startX + i * (250 + 10), startY);
                playersGame[i].NamePlayer.setPosition(startX + i * (250 + 10), startY);
            }
            break;

        case 3:
            playersGame[3].NamePlayer.setString(playerInfos[3].username);
            globalBounds = playersGame[3].NamePlayer.getGlobalBounds();
            playersGame[3].NamePlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
            for (int i = 0; i < 4; ++i) {
                playersGame[i].boxPlayer.setPosition(startX + i * (250 + 10), startY);
                playersGame[i].NamePlayer.setPosition(startX + i * (250 + 10), startY);
                
                
                playersGame[i].PieceSelect.setPosition(startX + i * (250 + 10), startY+100);
                    
                
                Check[i].setPosition(startX + i * (250 + 10), startY + 200 );
            }
           
            break;

        }
        


        sf::Event event;
        while (window->pollEvent(event)) {

            mousePosFloat = window->mapPixelToCoords(sf::Mouse::getPosition(*window));


            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                renderTexture.draw(spriteFondoGame);
                for (int i = 0; i < 4; i++)
                {
                    renderTexture.draw(playersGame[i].NamePlayer);
                    renderTexture.draw(playersGame[i].boxPlayer);
                }
                renderTexture.draw(spriteX);
                renderTexture.draw(overlay);
                Menup.MenuSalir();
            }


            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                static sf::Sprite* previousSelection = nullptr;  // Almacena la pieza previamente seleccionada
                for (int i = 0; i < pieces.size(); ++i) {
                    // Verificar si el mouse está sobre la pieza
                    if (pieces[i].getGlobalBounds().contains(mousePosFloat)) {
                        if (previousSelection != &pieces[i]) {  // Evitar resaltado si es la misma pieza
                            if (previousSelection != nullptr) {
                                previousSelection->setColor(sf::Color::White);  // Quitar el efecto de la anterior
                            }
                            // Asigna la textura y ajusta la escala y el origen
                            newSelection = &pieces[i];
                            // Asigna la textura a PiecesSelect[0]
                            playersGame[0].PieceSelect.setTexture(piecesTextures[i], true);  // Reajustar rectángulo de la textura
                            playersGame[0].PieceSelect.setScale(pieces[i].getScale());  // Ajustar la escala
                            playersGame[0].PieceSelect.setOrigin(pieces[i].getOrigin());  // Ajustar el origen
                            playersGame[0].PieceSelect.setColor(sf::Color::White);  // Asegurar color correcto
                            pieces[i].setColor(sf::Color(248, 134, 255));  // Resaltar la nueva pieza
                            playerInfos[0].indexPiece = i;
                            client.playerChangedPiece();
                            // Resaltar la nueva pieza
                            pieces[i].setColor(sf::Color(248, 134, 255));
                            playClickSound();
                            previousSelection = &pieces[i];  // Actualizar la selección anterior
                        }
                        break;
                    }
                 
                }
                if (Check[0].getGlobalBounds().contains(mousePosFloat)) {
                    playClickSound();
                    const sf::Texture* texturePtr = playersGame[0].PieceSelect.getTexture();

                    if (texturePtr != nullptr) {
                        sf::Texture textureSelec = *texturePtr;  // Desreferenciar el puntero

                        playerInfos[0].isSelectingPiece = true;
                        client.ReadyPlayer();
                        gamemode.update();
                    }
                }
               
            }

        }
        
        if (SelectingPiece) {
        
            gamemode.update();

        }
        



        
        currentCursor = &normalCursor;
        botonCheck1.update(mousePosFloat, currentCursor, linkCursor, normalCursor);
        window->setMouseCursor(*currentCursor);

        if (CplayerIndex>0&& CplayerIndex<=3){ 
            updatePlayerPieceSelection(playerInfos[CplayerIndex].indexPiece);
                CplayerIndex = -1;
        }
        
           for (int i = 0; i < 4; i++)
           {
               if (playerInfos[i].isSelectingPiece) {
                   Check[i].setTexture(CheckTexturesOn[i]);
               }
           }
           
           if (playerInfos[0].isSelectingPiece && playerInfos[1].isSelectingPiece&& playerInfos[2].isSelectingPiece&& playerInfos[3].isSelectingPiece){

           }
        window->clear();
        window->draw(spriteFondoGame);
        for (int i = 0; i < 4; i++)
        {
            window->draw(playersGame[i].NamePlayer);
            window->draw(playersGame[i].boxPlayer);
            window->draw(playersGame[i].AvatarPlayer);
            window->draw(playersGame[i].PieceSelect);
            window->draw(Check[i]);
        }
        


        displayPieces();

        window->draw(CODE);
        window->display();

        
    }

}

void PieceSelector::updatePlayerPieceSelection(int newPieceIndex) {
    // Suponiendo que `pieces` es un vector de sprites que contiene todas las piezas del juego
    // y `playersGame` es un arreglo de estructuras que almacena la información de los jugadores.

    // Primero, quita el resaltado de la pieza previamente seleccionada del jugador
    if (playersGame[CplayerIndex].PieceSelect.getColor() != sf::Color::White) {
        // Asegúrate de que estamos quitando el efecto de la pieza seleccionada previamente
        playersGame[CplayerIndex].PieceSelect.setColor(sf::Color::White);
    }

    // Ahora resaltar la nueva pieza seleccionada
    pieces[newPieceIndex].setColor(sf::Color(248, 134, 255)); // Resaltar la nueva pieza

    // Actualizar el sprite del jugador con la nueva textura de la pieza seleccionada
    playersGame[CplayerIndex].PieceSelect.setTexture(piecesTextures[newPieceIndex], true);
    playersGame[CplayerIndex].PieceSelect.setScale(pieces[newPieceIndex].getScale());
    playersGame[CplayerIndex].PieceSelect.setOrigin(pieces[newPieceIndex].getOrigin());
    playersGame[CplayerIndex].PieceSelect.setColor(sf::Color::White); // Asegurar el color correcto

    // Guardar el índice de la pieza seleccionada
    //playerInfos[CplayerIndex].indexPiece = newPieceIndex;

    // Asegúrate de que el nuevo sprite esté correctamente posicionado si es necesario
    // playersGame[playerIndex].PieceSelect.setPosition(...);
}
