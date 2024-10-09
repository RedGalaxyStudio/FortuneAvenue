#include "PieceSelector.hpp"
#include "ResourceGlobal.hpp"
#include "ResourceGame.hpp"
#include "ObjetosGlobal.hpp"

// Constructor
PieceSelector::PieceSelector(sf::RenderWindow* windowRef)
    : window(windowRef), selectedPiece(0) {
    loadResourceGame();
}

void PieceSelector::Resource() {

    StringNamePlayers[0] = input;
    int piecesCount = 9;  // Si tienes 17 pieces
    pieces.resize(piecesCount);
    shadow.resize(piecesCount);  // List of pieces to select
    piecesTextures.resize(piecesCount);

    for (int i = 0; i < piecesCount; i++) {
        if (!piecesTextures[i].loadFromFile("resource/texture/Game/pieces/piece" + std::to_string(i) + ".png"))
            return;

        float radio = piecesTextures[i].getSize().x / 2.0f;
    //    pieces[i].setRadius(radio);
        pieces[i].setTexture(piecesTextures[i]);
        shadow[i].setTexture(piecesTextures[i]);
        pieces[i].setOrigin(18,18);
        shadow[i].setOrigin(18,18);
             

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
    NumPlayers = 0;
    sf::Clock clock;
    
    mousePosition = sf::Mouse::getPosition(*window);
    mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

    float startX = 275;  // Posici�n inicial calculada en X
    float startY = 100;  // Posici�n calculada en Y (centrado verticalmente)
    NamePlayers[0].setString(StringNamePlayers[0]);
    globalBounds = NamePlayers[0].getGlobalBounds();
    NamePlayers[0].setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
    for (int i = 1; i < 4; i++) {
        StringNamePlayers[i] = "bot" + std::to_string(i);
    }

    while (window->isOpen()) {
        NumPlayers += 1;
        switch (NumPlayers)
        {
        case 1:
            NamePlayers[1].setString(StringNamePlayers[1]);
            globalBounds = NamePlayers[1].getGlobalBounds();
            NamePlayers[1].setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
            for (int i = 0; i < 2; ++i) {
                boxPlayers[i].setPosition(startX + i * (250 + 10), startY);
                NamePlayers[i].setPosition(startX + i * (250 + 10), startY);
            }
            break;

        case 2:
            NamePlayers[2].setString(StringNamePlayers[2]);
            globalBounds = NamePlayers[2].getGlobalBounds();
            NamePlayers[2].setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
            for (int i = 0; i < 3; ++i) {
                boxPlayers[i].setPosition(startX + i * (250 + 10), startY);
                NamePlayers[i].setPosition(startX + i * (250 + 10), startY);
            }
            break;

        case 3:
            NamePlayers[3].setString(StringNamePlayers[3]);
            globalBounds = NamePlayers[3].getGlobalBounds();
            NamePlayers[3].setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
            for (int i = 0; i < 4; ++i) {
                boxPlayers[i].setPosition(startX + i * (250 + 10), startY);
                NamePlayers[i].setPosition(startX + i * (250 + 10), startY);
                if (i==0)
                {
                    PiecesSelect[0].setPosition(startX + i * (250 + 10), startY+100);
                }
                
            }
           
            break;

        }
        
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                renderTexture.draw(spriteFondoGame);
                renderTexture.draw(Sesion);
                renderTexture.draw(selectedAvatarCopy);
                renderTexture.draw(recua);
                renderTexture.draw(spriteX);
                renderTexture.draw(overlay);
                Menup.MenuSalir();
            }


            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                static sf::Sprite* previousSelection = nullptr;  // Almacena la pieza previamente seleccionada

                mousePosFloat = window->mapPixelToCoords(sf::Mouse::getPosition(*window));


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
                            PiecesSelect[0].setTexture(piecesTextures[i], true);  // Reajustar rect�ngulo de la textura
                            PiecesSelect[0].setScale(pieces[i].getScale());  // Ajustar la escala
                            PiecesSelect[0].setOrigin(pieces[i].getOrigin());  // Ajustar el origen
                            PiecesSelect[0].setColor(sf::Color::White);  // Asegurar color correcto
                            pieces[i].setColor(sf::Color(248, 134, 255));  // Resaltar la nueva pieza

                            // Resaltar la nueva pieza
                            pieces[i].setColor(sf::Color(248, 134, 255));
                            playClickSound();
                            previousSelection = &pieces[i];  // Actualizar la selecci�n anterior
                        }
                        break;
                    }
                }
               
            }

        }
        currentCursor = &normalCursor;

        window->setMouseCursor(*currentCursor);

   

        window->clear();
        window->draw(spriteFondoGame);
        for (int i = 0; i < 4; i++)
        {
            window->draw(NamePlayers[i]);
            window->draw(boxPlayers[i]);
        }
        
        
        

        displayPieces();
        window->draw(PiecesSelect[0]);
        window->display();
    }

}


// Get the selected piece
sf::Sprite& PieceSelector::getSelectedPiece() {
    return pieces[selectedPiece];
}
