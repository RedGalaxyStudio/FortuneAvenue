#ifndef HOUSEBUY_HPP
#define HOUSEBUY_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "ResourceGame.hpp"
#include <vector>
#include "../../core/ResourceGlobal.hpp"
#include "../../network/Client.hpp"
#include "../../ui/ButtonG.hpp"
#include "../../ui/cell.h"
#include "../../ui/fileio.h"


class HouseBuy {

private:
sf::RenderWindow * window;
sf::Texture TextureBotonComprar;
sf::Sprite SpriteBotonComprar;


sf::Texture TextureXcOFF;
sf::Texture TextureXcOn;
sf::Sprite Xc;

struct CasasCompradas{

     sf::Sprite CsCmpdrsSprite;
     sf::Vector2f mostrarCasa;
     sf::Vector2f ocultaCasa;

};

std::vector<CasasCompradas> VCcompradas;
std::vector<int> CsCmpdrsindex;

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
Client* client;
float perfilWidth;
float separacion ;
int totalPerfiles ;

bool CartaActiva;
int indexMouseOver ;
int cartaActivaIndex;
public:
    bool seleccionlista ;
    HouseBuy();   
    int IndexCAsa;
    std::vector<houseInfo> houses;
    void setWindow(sf::RenderWindow& win, int indice, Client& clienT);
    void resource();
    void evenViewHouseCV(const sf::Event& event);
    void update(sf::Vector2f posicionactuInicial);
    void ViewHouseBuys();
    void ViewHouseBs();
    int csIndex;
   

};
#endif
