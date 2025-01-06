#ifndef CHAT_HPP
#define CHAT_HPP
#include "ResourceGame.hpp"
#include "ResourceGlobal.hpp"
#include <SFML/Graphics.hpp>
#include "PieceSelector.hpp"

class Chat {
public:

    Chat(sf::RenderWindow& win);
    void resource();

    void update();

private:

    sf::RectangleShape FondoChat;
    sf::RectangleShape Fondo;
    sf::RectangleShape Caja;
    sf::CircleShape Derecha;
    sf::CircleShape Izquierda;

    sf::RenderWindow* window;
   
    bool isWebViewOpen;
    bool sesionValida;
    bool Valida;
        
    sf::Texture TextureBotonEviar;
    sf::Texture texturaFondo;
    sf::Texture TextureCrearPartidaOff;
    sf::Texture TextureCrearPartidaOn;
    sf::Texture TextureUnirsePartidaOff;
    sf::Texture TextureUnirsePartidaOn;
    sf::Texture TextureUnirse;

    sf::Clock LimTimeBotton;

    sf::Text indicacion;
    sf::Text mensaje;
    sf::Text enunciado;

    sf::Sprite spriteFondo;
    sf::Sprite renderedSprite;
    sf::Sprite SpriteBotonEnviar;
    sf::Sprite SpriteCrearPartida;
    sf::Sprite SpriteUnirsePartida;
    sf::Sprite SpriteUnirse;

    sf::Vector2i mousePosition;
    sf::Vector2f mousePosFloat;
    PieceSelector pieceselector;
};

#endif 

