#ifndef NULOO_HPP
#define NULOO_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "ResourceGameO.hpp"
#include <vector>
#include "../../core/ResourceGlobal.hpp"

class NuloO {

private:
    sf::RenderWindow* window;
    sf::Texture TextureBotonNulo;
    sf::Sprite SpriteBotonNulo;
    
    std::vector<sf::Texture> TextureNulo;  
    std::vector<sf::Sprite> SpriteNulo;    

    sf::Clock tempoCarta;
    sf::Sprite renderedSprite;

public:
    NuloO(); 
    int IndexCAsa;

    void setWindow(sf::RenderWindow& win);
    void Resource();       
    void Update();
};

#endif // NULO_HPP
