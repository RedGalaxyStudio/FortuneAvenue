// IniciarPartida.hpp
#ifndef INICIARPARTIDA_HPP
#define INICIARPARTIDA_HPP
#include "ResourceGame.hpp"
#include "ResourceGlobal.hpp"
#include <SFML/Graphics.hpp>
#include "PieceSelector.hpp"

class IniciarPartida {
public:
    // Constructor
    IniciarPartida(sf::RenderWindow& win);
    void updatejoinRoom();
    void resource();

    void update();

private:
    sf::RenderWindow* window; // Puntero a la ventana de SFML
    sf::Texture texturaFondo; // Textura de fondo
    sf::Sprite spriteFondo; // Sprite para mostrar el fondo
    bool isWebViewOpen; // Variable para manejar si la vista web está abierta
    bool sesionValida; // Variable para verificar la sesión
    bool Valida;
    sf::Texture TextureCrearPartidaOff;
    sf::Texture TextureCrearPartidaOn;
    sf::Texture TextureUnirsePartidaOff;
    sf::Texture TextureUnirsePartidaOn;
    sf::Texture TextureUnirse;

    sf::Text enunciado;
    sf::Sprite SpriteCrearPartida;
    sf::Sprite SpriteUnirsePartida;
    sf::Sprite SpriteUnirse;

    sf::Vector2i mousePosition;
    sf::Vector2f mousePosFloat;
    PieceSelector pieceselector;
};

#endif // INICIARPARTIDA_HPP

