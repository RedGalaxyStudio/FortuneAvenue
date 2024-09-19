#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "TextBox.hpp"
#include <SFML/Audio.hpp>
#include <string>
#include "ResourceGlobal.hpp"
#include "menuP.hpp"

// Constructor e inicialización
Game::Game(sf::RenderWindow& windowRef)
    : window(windowRef){
    Resource();
    loadAvatars();
}
Game::~Game() {
}

// Carga de recursos (texturas y sprites)
void Game::Resource() {

    //if (!textureLogoJuego.loadFromFile("resource/texture/logojuego14.png")) return;
    SpriteFondoMenu.setTexture(TextureFondoMenu);

}

// Actualización de la animación (desvanecimiento del logotipo y fondo animado)
void Game::Update() {
    TextBox textBox(400, 50);  // Crear un cuadro de texto
    textBox.setPosition();  // Posicionar el cuadro de texto

    while (window.isOpen()) {
        
               mousePosition = sf::Mouse::getPosition(window);
               mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {

                Menup.MenuSalir();
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
               
                if (spriteX.getGlobalBounds().contains(mousePosFloat)) {
                    playClickSound();
                    Menup.MenuPrincipal();

                }
            }
            // Manejar la entrada de texto
            textBox.handleInput(event);
        }
        
        botonX->update(mousePosFloat, currentCursor, linkCursor, normalCursor);


        window.clear();

       
        window.draw(SpriteFondoMenu);
        textBox.draw(window);  // Dibujar el cuadro de texto en la ventana
        
        for (auto& avatar : avatars) {
            window.draw(avatar);
        }

        window.draw(spriteX);
        window.display();
    }
}
