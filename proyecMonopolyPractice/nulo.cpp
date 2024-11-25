#include "nulo.hpp"
#include <sstream>
#include "nlohmann/json.hpp"
#include "card.h"
#include <filesystem>
#include <cstring>
#include <fstream>
#include "cell.h"
#include "fileio.h"

using json = nlohmann::json;

Nulo::Nulo() : window(nullptr), IndexCAsa(-1) {}

void Nulo::setWindow(sf::RenderWindow& win) {
    window = &win;
}

void Nulo::Resource(Client* client) {
    
    if (!TextureBotonNulo.loadFromFile("iconos ruleta/nulo.png")) {
        std::cerr << "Error al cargar el botón de confirmación.\n";
    }
    SpriteBotonNulo.setTexture(TextureBotonNulo);
    SpriteBotonNulo.setPosition(640, 545);
    SpriteBotonNulo.setOrigin(101, 40);

    }


void Nulo::Update(sf::Vector2f posicionactuInicial) {
  
bool cierre= false;

    renderedSprite.setTexture(renderTexture.getTexture());

    while (window->isOpen() && !cierre) {
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
                    cierre = true;
                }
            }
        }

        window->setMouseCursor(*currentCursor);
        window->clear();
        window->draw(renderedSprite);

            window->draw(SpriteBotonNulo);
        

        window->display();
    }

}
