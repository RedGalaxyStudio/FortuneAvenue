#include "IniciarPartida.hpp"


IniciarPartida::IniciarPartida(sf::RenderWindow& win) : window(&win){
    loadResourceGame();
    resource();
}

void IniciarPartida::resource() {
    if (!TextureCrearPartida.loadFromFile("resource/texture/Game/CrearPartida.jpg")) return;
    if (!TextureUnirsePartida.loadFromFile("resource/texture/Game/UnirsePartida.jpg"))return;

    SpriteCrearPartida.setTexture(TextureCrearPartida);
    SpriteCrearPartida.setOrigin(103.5f, 40);
    SpriteCrearPartida.setPosition(383, 560);

    SpriteUnirsePartida.setTexture(TextureUnirsePartida);
    SpriteUnirsePartida.setOrigin(103.5f, 40);
    SpriteUnirsePartida.setPosition(383, 560);
}

// Implementación del método update
void IniciarPartida::update() {

    while (window->isOpen()) {
        sf::Event evento;
        while (window->pollEvent(evento)) {
            if (evento.type == sf::Event::Closed)
                window->close();
        }

        window->clear();
        window->draw(spriteFondoGame); // Dibuja el fondo
        window->draw(SpriteUnirsePartida); // Dibuja el fondo
        window->draw(SpriteCrearPartida); // Dibuja el fondo
        window->display();
    }
 
}





