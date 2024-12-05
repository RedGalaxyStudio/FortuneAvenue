#ifndef HOUSEBUY_HPP
#define HOUSEBUY_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "ResourceGame.hpp"
#include <vector>
#include "ResourceGlobal.hpp"
#include "Client.hpp"
#include "ButtonG.hpp"
class HouseBuy {

private:
sf::RenderWindow * window;
sf::Texture TextureBotonComprar;
sf::Sprite SpriteBotonComprar;


sf::Texture TextureXcOFF;
sf::Texture TextureXcOn;
sf::Sprite Xc;


std::vector<sf::Texture> TextureCasa;
std::vector<sf::Sprite> SpriteCasa;

sf::Clock tempoCarta;
sf::Sprite renderedSprite;
sf::Texture ReversoCart;
struct houseInfo {

    std::string nombre;
    int salario;
    int costo;
    int impuesto;
};


public:
    HouseBuy();   // Constructor que inicializa con el precio y fondos del jugador
    int IndexCAsa;
    std::vector<houseInfo> houses;
    void setWindow(sf::RenderWindow& win,int indice);
    void resource(Client* client);
    void update(sf::Vector2f posicionactuInicial);
    int index;
   

};
#endif // HOUSEBUY_HPP
