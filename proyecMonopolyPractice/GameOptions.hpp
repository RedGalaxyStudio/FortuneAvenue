#ifndef GAMEOPTIONS_HPP
#define GAMEOPTIONS_HPP
#include "ResourceGame.hpp"
#include "ResourceGlobal.hpp"
#include <SFML/Graphics.hpp>
#include "PieceSelector.hpp"

class GameOptions {
public:

    GameOptions(sf::RenderWindow& win);
    void resource();

    void update();

private:
    sf::RenderWindow* window;
    sf::Texture texturaFondo;
    sf::Sprite spriteFondo;
    bool isWebViewOpen;
    bool sesionValida;
    bool Valida;
    sf::Texture TextureflecDerecha;
    sf::Texture TextureflecIzquier;
    sf::Texture TextureAceptar;
    sf::Clock LimTimeBotton;
    sf::Text enunciado;
    sf::Sprite SpriteflecDerecha;
    sf::Sprite SpriteflecIzquier;
    sf::Sprite SpriteAceptar;

    sf::Vector2i mousePosition;
    sf::Vector2f mousePosFloat;
    PieceSelector pieceselector;

    sf::Text TOpcion, TPlayers, TMapas;
};

#endif 

