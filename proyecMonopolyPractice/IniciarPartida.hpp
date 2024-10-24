// IniciarPartida.hpp
#ifndef INICIARPARTIDA_HPP
#define INICIARPARTIDA_HPP
#include "ResourceGame.hpp"
#include <SFML/Graphics.hpp>

class IniciarPartida {
public:
    // Constructor
    IniciarPartida(sf::RenderWindow& win);

    void resource();

    void update();

private:
    sf::RenderWindow* window; // Puntero a la ventana de SFML
    sf::Texture texturaFondo; // Textura de fondo
    sf::Sprite spriteFondo; // Sprite para mostrar el fondo
    bool isWebViewOpen; // Variable para manejar si la vista web está abierta
    bool sesionValida; // Variable para verificar la sesión
    sf::Texture TextureCrearPartida;
sf::Texture TextureUnirsePartida;
sf::Sprite SpriteCrearPartida;
sf::Sprite SpriteUnirsePartida;
};

#endif // INICIARPARTIDA_HPP

