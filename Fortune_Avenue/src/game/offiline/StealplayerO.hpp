#ifndef STEALPLAYERO_HPP
#define STEALPLAYERO_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "ResourceGameO.hpp"
#include "../../core/ResourceGlobal.hpp"

class StealplayerO {
private:
    sf::RenderWindow* window;               
    sf::Text SlectingPlayer;
    std::vector<int> UsuariosEleccion;
    std::vector<int> UsuariosEleccionC;
    std::vector<sf::RectangleShape> isMouseOver;
    std::vector<sf::Vector2f> PosIsMouseOver;
    sf::Texture texturebottonRobar;
    sf::Sprite SpritebottonRobar;
    std::vector<PlayerGameOff> PlayersSteal;
    
    
public:
    StealplayerO(sf::RenderWindow* window, std::vector<int> UsuariosElec, std::vector<PlayerGameOff> PSteal);  
    ~StealplayerO();                            
    void resource();
    void update();
    void BotRobar();


};

#endif 
