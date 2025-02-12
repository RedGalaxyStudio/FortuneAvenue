#ifndef CHAT_HPP
#define CHAT_HPP
#include "ResourceGame.hpp"
#include "../../core/ResourceGlobal.hpp"
#include <SFML/Graphics.hpp>
#include "PieceSelector.hpp"

class Chat {
public:

    Chat(sf::RenderWindow& win);
    void resource();
    void insertarSaltoDeLinea();
    void update();
    void Event(sf::Event event);
    void draw();

private:

    const size_t maxLength = 60;


    sf::RectangleShape FondoChat;
    sf::RectangleShape Fondo;
    sf::RectangleShape Caja;
    sf::RectangleShape CajaD;
    sf::RectangleShape CajaI;
    sf::CircleShape ArriDerecha;
    sf::CircleShape ArriIzquierda;
    sf::CircleShape AbajDerecha;
    sf::CircleShape AbajIzquierda;

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

    sf::Font Fuentechat;
    sf::Font FuenteMensaje;

    sf::Clock LimTimeBotton;

    sf::Text indicacion;
    sf::Text mensaje;
    sf::Text enunciado;
    
    std::string input;

    sf::Sprite spriteFondo;
    sf::Sprite renderedSprite;
    sf::Sprite SpriteBotonEnviar;
    sf::Sprite SpriteCrearPartida;
    sf::Sprite SpriteUnirsePartida;
    sf::Sprite SpriteUnirse;

    int Aumento = 0;


    sf::Vector2i mousePosition;
    sf::Vector2f mousePosFloat;


    MensajeMSG PlantillaMensajeE;

};

#endif 

