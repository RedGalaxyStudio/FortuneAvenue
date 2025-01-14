#ifndef INICIARPARTIDA_HPP
#define INICIARPARTIDA_HPP
#include "../game/online/ResourceGame.hpp"
#include "../core/ResourceGlobal.hpp"
#include <SFML/Graphics.hpp>
#include "../game/online/PieceSelector.hpp"

class IniciarPartida {
public:
    
    IniciarPartida(sf::RenderWindow& win);
    void updatejoinRoom();
    void resource();

    void update();

private:
    sf::RenderWindow* window; 
    sf::Texture texturaFondo; 
    sf::Sprite spriteFondo; 
    bool isWebViewOpen; 
    bool sesionValida; 
    bool Valida;
    sf::Texture TextureCrearPartidaOff;
    sf::Texture TextureCrearPartidaOn;
    sf::Texture TextureUnirsePartidaOff;
    sf::Texture TextureUnirsePartidaOn;
    sf::Texture TextureUnirse;
    sf::Clock LimTimeBotton;
    sf::Text enunciado;
    sf::Sprite SpriteCrearPartida;
    sf::Sprite SpriteUnirsePartida;
    sf::Sprite SpriteUnirse;

    sf::Vector2i mousePosition;
    sf::Vector2f mousePosFloat;

};

#endif 

