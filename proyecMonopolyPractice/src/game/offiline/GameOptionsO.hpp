#ifndef GAMEOPTIONS_HPP
#define GAMEOPTIONS_HPP
#include "ResourceGameO.hpp"
#include "../../core/ResourceGlobal.hpp"
#include <SFML/Graphics.hpp>
#include "PieceSelectorO.hpp"

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

    sf::Texture TextureMapaS;
    sf::Texture TextureMapaSM;
    sf::Sprite SpriteMapaS;

    int CantNum=4;
    sf::Text cantUser;

    int selectedMap = -1;

    sf::Texture TextureMapa22;
    sf::Texture TextureMapa22M;
    sf::Sprite SpriteMapa22;

    sf::Texture TextureMapa;
    sf::Texture TextureMapa2;
    sf::Texture TextureMapa3;

    sf::Vector2f Maximo;
    sf::Vector2f Minimo;


    sf::Texture TextureMapa1;
    sf::Texture TextureMapa1M;
    sf::Sprite SpriteMapa1;


    sf::Texture TextureCrear;
    sf::Sprite SpriteCrear;

    sf::Texture TextureRectangle;
    sf::Sprite SpriteRectangle;

    sf::RectangleShape borde1;
    sf::RectangleShape borde2;
    sf::RectangleShape borde3;

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

