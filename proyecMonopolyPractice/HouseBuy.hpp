#ifndef HOUSEBUY_HPP
#define HOUSEBUY_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "ResourceGame.hpp"
#include <vector>
#include "ResourceGlobal.hpp"


class HouseBuy {

   



private:


public:
    HouseBuy();   // Constructor que inicializa con el precio y fondos del jugador

    

    void resource();
    void update();
};

sf::Texture TextureBotonComprar;
sf::Sprite SpriteBotonComprar;

std::vector<sf::Texture> TextureCasa;
std::vector<sf::Sprite> SpriteCasa;





#endif // HOUSEBUY_HPP
