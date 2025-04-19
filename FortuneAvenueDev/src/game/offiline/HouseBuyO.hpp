#ifndef HOUSEBUYO_HPP
#define HOUSEBUYO_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "ResourceGameO.hpp"
#include <vector>
#include "../../core/ResourceGlobal.hpp"
#include "../../ui/ButtonG.hpp"
#include "../../ui/cell.h"
#include "../../ui/fileio.h"


class HouseBuyO {

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

float perfilWidth;
float separacion;
int totalPerfiles;

bool CartaActiva;
int indexMouseOver;
int cartaActivaIndex;

public:
    bool seleccionlista;
    HouseBuyO(); 
    int IndexCAsa;
    std::vector<houseInfo> houses;
    void setWindow(sf::RenderWindow& win,int indice);
    void resource();
    void update(sf::Vector2f posicionactuInicial);
    void ViewHouseBuysO();
    void ViewHouseBsaO();
    void evenViewHouseCVO(sf::Event event);
    int indexX;
    
};
#endif 
