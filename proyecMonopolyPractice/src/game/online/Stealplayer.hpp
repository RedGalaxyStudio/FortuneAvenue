#ifndef STEALPLAYER_HPP
#define STEALPLAYER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "ResourceGame.hpp"
#include "../../core/ResourceGlobal.hpp"

class Stealplayer {
private:
    sf::RenderWindow* window;                 // Ventana principal para dibujar
    sf::Text SlectingPlayer;
    std::vector<int> UsuariosEleccion;
    std::vector<sf::RectangleShape> isMouseOver;
    std::vector<sf::Vector2f> PosIsMouseOver;
    sf::Texture texturebottonRobar;
    sf::Sprite SpritebottonRobar;
    std::vector<PlayerGame> PlayersSteal;
    
    
public:
    Stealplayer(sf::RenderWindow* window, std::vector<int> UsuariosElec, std::vector<PlayerGame> PSteal);        // Constructor que toma la ventana principal
    ~Stealplayer();                               // Destructor
    void resource();
    void update();

};

#endif 
