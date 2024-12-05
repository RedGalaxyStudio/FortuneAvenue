#ifndef STEALPLAYER_HPP
#define STEALPLAYER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "ResourceGame.hpp"
#include "ResourceGlobal.hpp"

class Stealplayer {
private:
    sf::RenderWindow* window;                 // Ventana principal para dibujar
    sf::Text SlectingPlayer;
    std::vector<int> UsuariosEleccion;
    sf::Texture texturebottonRobar;
    sf::Sprite SpritebottonRobar;

public:
    Stealplayer(sf::RenderWindow* window, std::vector<int> UsuariosElec);        // Constructor que toma la ventana principal
    ~Stealplayer();                               // Destructor
    void resource();
    void update();

};

#endif 
