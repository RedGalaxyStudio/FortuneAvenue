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
    sf::Texture TextureBotonNulo; 
    sf::Sprite SpriteBotonNulo;
    
    std::vector<sf::Texture> TextureNulo;  
    std::vector<sf::Sprite> SpriteNulo;  

    sf::Clock tempoCarta;
    sf::Sprite renderedSprite;
    Client* client;

public:
    Nulo();
    int IndexCAsa;

    void setWindow(sf::RenderWindow& win, Client& clienT);
    void Resource();    
    void Update();
};

#endif
