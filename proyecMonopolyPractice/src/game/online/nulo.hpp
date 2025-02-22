#ifndef NULO_HPP
#define NULO_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "ResourceGame.hpp"
#include <vector>
#include "../../core/ResourceGlobal.hpp"
#include "../../network/Client.hpp"

class Nulo {

private:
    sf::RenderWindow* window;
    sf::Texture TextureBotonNulo;  // Botón para la carta de "nulo"
    sf::Sprite SpriteBotonNulo;
    
    std::vector<sf::Texture> TextureNulo;  // Texturas para la carta de "nulo"
    std::vector<sf::Sprite> SpriteNulo;    // Sprites para la carta de "nulo"

    sf::Clock tempoCarta;
    sf::Sprite renderedSprite;
    Client* client;

public:
    Nulo(); // Constructor por defecto
    int IndexCAsa;

    void setWindow(sf::RenderWindow& win, Client& clienT);
    void Resource();       // Cargar recursos para la carta de "nulo"
    void Update(); // Actualizar la animación de "nulo"
};

#endif // NULO_HPP
