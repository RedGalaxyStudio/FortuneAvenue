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
	if (!TextureMapa.loadFromFile("resource/texture/Game/mapa+S+.png")) return;
	spriteMapa.setTexture(TextureMapa);
	spriteMapa.setOrigin(360, 360);
	spriteMapa.setPosition(640, 360);

    if (!piecesTextures.loadFromFile("resource/texture/Game/pieces/piece1.png"))
        return;

    pieces.setTexture(piecesTextures);
    pieces.setOrigin(18, 18);
    // Vector para cada grupo de casillas (caminos)
    std::vector<sf::Vector2f> camino1 = { sf::Vector2f(375, 480) };
    std::vector<sf::Vector2f> camino2 = { sf::Vector2f(376.f,848.f), sf::Vector2f(325,523), sf::Vector2f(325,576), sf::Vector2f(323,629), sf::Vector2f(351,676), sf::Vector2f(394,678), sf::Vector2f(425,655) };
    std::vector<sf::Vector2f> camino3 = { sf::Vector2f(100, 200), sf::Vector2f(200, 200), sf::Vector2f(300, 200) };
    std::vector<sf::Vector2f> camino4 = { sf::Vector2f(100, 300), sf::Vector2f(200, 300), sf::Vector2f(300, 300) };

    // Agregar los caminos al vector principal
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
        window->draw(box);
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
