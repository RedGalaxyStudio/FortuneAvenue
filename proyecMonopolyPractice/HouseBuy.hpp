#ifndef HOUSEBUY_HPP
#define HOUSEBUY_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "ResourceGame.hpp"
#include <vector>
#include "ResourceGlobal.hpp"


class HouseBuy {

private:
sf::RenderWindow * window;
sf::Texture TextureBotonComprar;
sf::Sprite SpriteBotonComprar;

std::vector<sf::Texture> TextureCasa;
std::vector<sf::Sprite> SpriteCasa;

sf::Clock tempoCarta;
sf::Sprite renderedSprite;
struct houseInfo {

    std::string nombre;
    int salario;
    int costo;
    int impuesto;
};
public:
    HouseBuy();   // Constructor que inicializa con el precio y fondos del jugador

    
    void setWindow(sf::RenderWindow& win);
    void resource();
    void update(sf::Vector2f posicionactuInicial);



};
#endif // HOUSEBUY_HPP
