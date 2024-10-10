#include "GameMode.hpp"
#include "ResourceGlobal.hpp"
#include "ObjetosGlobal.hpp"
#include "PieceSelector.hpp"
#include "Cube.hpp"
#include "ResourceGame.hpp"

GameMode::GameMode(sf::RenderWindow* windowRef): window(windowRef) {
    loadResourceGame();
	resource();
}



void GameMode::resource() {
	if (!TextureMapa.loadFromFile("resource/texture/Game/mapa+S++.png")) return;
	spriteMapa.setTexture(TextureMapa);
	spriteMapa.setOrigin(360, 360);
	spriteMapa.setPosition(640, 360);

    if (!piecesTextures.loadFromFile("resource/texture/Game/pieces/piece1.png"))
        return;

    pieces.setTexture(piecesTextures);
    pieces.setOrigin(18, 18);
    // Vector para cada grupo de casillas (caminos)
    std::vector<sf::Vector2f> camino1 = { sf::Vector2f(375, 480) };
    std::vector<sf::Vector2f> camino2 = { sf::Vector2f(325,523), sf::Vector2f(325,576), sf::Vector2f(323,629), sf::Vector2f(351,676), sf::Vector2f(394,678), sf::Vector2f(425,655) };
    std::vector<sf::Vector2f> camino3 = { sf::Vector2f(100, 200), sf::Vector2f(200, 200), sf::Vector2f(300, 200) };
    std::vector<sf::Vector2f> camino4 = { sf::Vector2f(100, 300), sf::Vector2f(200, 300), sf::Vector2f(300, 300) };

    // Agregar los caminos al vector principal
    for (int i = 1; i < 4; i++) {
        StringNamePlayers[i] = "bot" + std::to_string(i);
        NamePlayers[i].setString(StringNamePlayers[i]);
        globalBounds = NamePlayers[i].getGlobalBounds();
        NamePlayers[i].setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
        MarcoPlayers[i].setOrigin(65, 65);



    }
    casillas.push_back(camino1);
    casillas.push_back(camino2);
    casillas.push_back(camino3);
    casillas.push_back(camino4);

    posicionActual = 0; // Posición actual del sprite en las casillas


    selectedAvatarCopy.setPosition(52.5f,52.5f);
    selectedAvatarCopy.setScale(0.7f, 0.7f);  
    recua.setPosition(52.5f, 52.5f);
    recua.setScale(0.7f, 0.7f);
  
    Sesion.setCharacterSize(17);
    sf::FloatRect globalBounds = Sesion.getGlobalBounds();
    // Ajustar la posición centrando el texto
    Sesion.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
    Sesion.setPosition(188.65f, 52.5f - 3);
    box.setPosition(188.65f,52.5f);
    box.setScale(0.7f, 0.7f);
}

// Implementación del método update
void GameMode::update() {
    PieceSelector pieceselector(window);
   // pieceselector.Resource();
  //  pieceselector.updateSelection();

    sf::Clock clock;
    resultadoDado = 0;
    mousePosition = sf::Mouse::getPosition(*window);
    mousePosFloat = static_cast<sf::Vector2f>(mousePosition);
    
    //perfil 1
    NamePlayers[0].setPosition(188.65f, 52.5f);
    boxPlayers[0].setPosition(188.65f, 52.5f);
    boxPlayers[0].setScale(0.7f, 0.7f);
    MarcoPlayers[0].setPosition(52.5f, 52.5f);
    MarcoPlayers[0].setScale(0.7f, 0.7f);

    //perfil 2
    NamePlayers[1].setPosition(1188.65f, 52.5f);
    boxPlayers[1].setPosition(1188.65f, 52.5f);
    boxPlayers[1].setScale(0.7f, 0.7f);
    MarcoPlayers[1].setPosition(52.5f, 652.5f);
    MarcoPlayers[1].setScale(0.7f, 0.7f);
    //perfil 3
    NamePlayers[2].setPosition(188.65f, 652.5f);
    boxPlayers[2].setPosition(188.65f, 652.5f);
    boxPlayers[2].setScale(0.7f, 0.7f);
    MarcoPlayers[2].setPosition(1052.5f, 52.5f);
    MarcoPlayers[2].setScale(0.7f, 0.7f);
    //perfil 4
    NamePlayers[3].setPosition(1188.65f, 652.5f);
    boxPlayers[3].setPosition(1188.65f, 652.5f);
    boxPlayers[3].setScale(0.7f, 0.7f);
    MarcoPlayers[3].setPosition(1052.5f, 652.5f);
    MarcoPlayers[3].setScale(0.7f, 0.7f);

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                renderTexture.draw(spriteFondoGame);
                renderTexture.draw(spriteMapa);
                renderTexture.draw(box);
                renderTexture.draw(Sesion);
                renderTexture.draw(selectedAvatarCopy);
                renderTexture.draw(recua);
                renderTexture.draw(spriteX);
                renderTexture.draw(overlay);
                Menup.MenuSalir();
            }
            

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // Verificar el click en "si" y cerrar la vetana
                if (spriteMapa.getGlobalBounds().contains(mousePosFloat)) {
                    playClickSound();
                    resultadoDado = 1;
                    //cube.roll();  // Lanzar el dado
                        //saveSelectedAvatar();
                   // Menup.MenuPrincipal();
                }
            }
          
        }
        currentCursor = &normalCursor;

        window->setMouseCursor(*currentCursor);

        //cube.update(clock.getElapsedTime().asSeconds());


        moverSprite(pieces, resultadoDado);
        resultadoDado = 0;

        window->clear();
        window->draw(spriteFondoGame);
        window->draw(spriteMapa);
        for (int i = 0; i < 4; i++)
        {
            window->draw(NamePlayers[i]);
            window->draw(boxPlayers[i]);
            window->draw(MarcoPlayers[i]);
        }
        window->draw(Sesion);
        window->draw(selectedAvatarCopy);
        window->draw(recua);
       // cube.draw(*window);
        window->draw(pieces);
       // pieceselector.displayPieces();
   //     window->draw(spriteX);
        window->display();
    }
}

void GameMode::moverSprite(sf::Sprite& sprite, int resultadoDado) {
    posicionActual += resultadoDado;

    // Mientras se supere el tamaño del vector actual, cambiar al siguiente vector
    while (posicionActual >= casillas[vectorActual].size()) {
        posicionActual -= casillas[vectorActual].size();  // Ajustar la posición
        vectorActual++;  // Ir al siguiente vector

        // Verificar si llegamos al final de los vectores
        if (vectorActual >= casillas.size()) {
            vectorActual = 0;  // Reiniciar al primer vector si se superan todos
        }
    }

    // Mueve el sprite a la posición de la casilla correspondiente en el vector actual
    sprite.setPosition(casillas[vectorActual][posicionActual]);
}
