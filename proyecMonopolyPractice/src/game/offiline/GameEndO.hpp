#ifndef GAMEENDO_HPP
#define GAMEENDO_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "ResourceGameO.hpp"
#include "../../core/ResourceGlobal.hpp"
#include <vector>
#include <algorithm>
#include <iostream>


class GameEndO {
private:
    sf::RenderWindow* window;          
    sf::Text fingame12;
    sf::Text funciona;
    std::vector<sf::Text> posicionesGanadores;
    std::vector<int>posiGndrs;

    sf::Vector2i previousMousePosition;
    sf::Vector2i currentMousePosition;

public:
    GameEndO(sf::RenderWindow* window);       
    ~GameEndO();                              
    void resource();
    void update();

};

#endif 
