#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "TextBox.hpp"
#include <SFML/Audio.hpp>
#include <string>
#include "ResourceGlobal.hpp"

// Constructor e inicialización
Game::Game(sf::RenderWindow& windowRef)
    : window(windowRef){
    Resource();
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
    textBox.setPosition(200, 275);  // Posicionar el cuadro de texto


    while (window.isOpen()) {
        

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }

            // Manejar la entrada de texto
            textBox.handleInput(event);
        }

        window.clear();
        window.draw(SpriteFondoMenu);
        textBox.draw(window);  // Dibujar el cuadro de texto en la ventana
        window.display();
    }
}
