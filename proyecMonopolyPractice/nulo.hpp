/*#ifndef NULO_HPP
#define NULO_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "ResourceGame.hpp"
#include <vector>
#include "ResourceGlobal.hpp"
#include "Client.hpp"

class Nulo {

private:
    sf::RenderWindow* window;
    sf::Texture TextureBotonNulo;  // Botón para la carta de "nulo"
    sf::Sprite SpriteBotonNulo;
    
    std::vector<sf::Texture> TextureNulo;  // Texturas para la carta de "nulo"
    std::vector<sf::Sprite> SpriteNulo;    // Sprites para la carta de "nulo"

    sf::Clock tempoCarta;
    sf::Sprite renderedSprite;

public:
    Nulo(); // Constructor por defecto
    int IndexCAsa;

    void setWindow(sf::RenderWindow& win);
    void Resource(Client* client);       // Cargar recursos para la carta de "nulo"
    void Update(sf::Vector2f posicionactuInicial); // Actualizar la animación de "nulo"
};

#endif // NULO_HPP*/
