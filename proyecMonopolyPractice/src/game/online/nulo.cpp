#include "nulo.hpp"
#include <sstream>
#include "../../libs/nlohmann/json.hpp"
#include <filesystem>
#include <cstring>
#include <fstream>
#include "../../ui/cell.h"
#include "../../ui/fileio.h"

using json = nlohmann::json;

Nulo::Nulo() : window(nullptr), IndexCAsa(-1) {}

void Nulo::setWindow(sf::RenderWindow& win) {
    window = &win;
}

void Nulo::Resource(Client* client) {
    
    if (!TextureBotonNulo.loadFromFile("assets/image/Button/nulo.png")) {
        std::cerr << "Error al cargar el botón de confirmación.\n";
    }
    SpriteBotonNulo.setTexture(TextureBotonNulo);
    SpriteBotonNulo.setPosition(0, 0);


    }


void Nulo::Update() {
  

    renderedSprite.setTexture(renderTexture.getTexture());
  
  
    sf::Clock clocks;  // Inicia el temporizador

    // El bucle solo se ejecutará durante 5 segundos
    while (window->isOpen() && clocks.getElapsedTime().asSeconds() <= 2.5f) {
    
        sf::Event event;
        while (window->pollEvent(event)) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
            sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                renderTexture.clear();
                renderTexture.draw(spriteFondoGame);
                for (int i = 0; i < 4; i++) {
                    renderTexture.draw(playersGame[i].NamePlayer);
                    renderTexture.draw(playersGame[i].boxPlayer);
                    renderTexture.draw(playersGame[i].MarcoPlayer);
                    renderTexture.draw(playersGame[i].AvatarPlayer);
                }
                renderTexture.draw(spriteX);
                renderTexture.draw(overlay);
                Menup.MenuSalir();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (SpriteBotonNulo.getGlobalBounds().contains(mousePosFloat)) {
                    playClickSound();
               
                }
            }
        }

        window->setMouseCursor(*currentCursor);
        window->clear();
        window->draw(renderedSprite);

           window->draw(SpriteBotonNulo);
        

        window->display();
    }
    client.turnopermitido++;
    client.networkMessage.endTurn();
    nular = true;
  

}
