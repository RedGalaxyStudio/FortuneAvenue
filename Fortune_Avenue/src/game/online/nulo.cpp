#include "nulo.hpp"
#include <sstream>
#include "../../libs/nlohmann/json.hpp"
#include <filesystem>
#include <cstring>
#include <fstream>
#include "../../ui/cell.h"
#include "../../ui/fileio.h"
#include "../../core/ObjetosGlobal.hpp"
#include "../../ui/ResourceGeneral.hpp"
using json = nlohmann::json;
#include "OnlineVars.hpp"

Nulo::Nulo() : window(nullptr), client(nullptr), IndexCAsa(-1) {}

void Nulo::setWindow(sf::RenderWindow& win, Client& clienT) {
    window = &win;
    client = &clienT;
}

void Nulo::Resource() {
    
    if (!TextureBotonNulo.loadFromFile("assets/image/Button/nulo.png")) {
        std::cerr << "Error al cargar el botón de confirmación.\n";
    }
    SpriteBotonNulo.setTexture(TextureBotonNulo);
    SpriteBotonNulo.setPosition(0, 0);


    }


void Nulo::Update() {
  

    renderedSprite.setTexture(renderTexture.getTexture());
  
  
    sf::Clock clocks;  // Inicia el temporizador

    while (window->isOpen() && clocks.getElapsedTime().asSeconds() <= 2.5f) {
    
        sf::Event event;
        while (window->pollEvent(event)) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
            sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                renderTexture.clear();
                renderTexture.draw(spriteBackgroundG);
                for (int i = 0; i < UsuariosActivos.size(); i++) {
                    renderTexture.draw(playersGame[i].NamePlayer);
                    renderTexture.draw(playersGame[i].boxPlayer);
                    renderTexture.draw(playersGame[i].MarcoPlayer);
                    renderTexture.draw(playersGame[i].AvatarPlayer);
                }
                renderTexture.draw(spriteX);
                renderTexture.draw(overlay);
                Menup.MenuSalir(client);
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
    turnopermitido++;
    client->networkMessage.endTurn();
    nular = true;
  

}
