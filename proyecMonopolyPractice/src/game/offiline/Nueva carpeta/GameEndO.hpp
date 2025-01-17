#ifndef GAMEENDO_HPP
#define GAMEENDO_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "ResourceGameO.hpp"
#include "../../core/ResourceGlobal.hpp"
#include <vector>
#include <algorithm>
#include <iostream>


class GameEnd {
private:
    sf::RenderWindow* window;                 // Ventana principal para dibujar
    sf::Text fingame12;
    sf::Text funciona;
    std::vector<sf::Text> posicionesGanadores;
    std::vector<int>posiGndrs;
public:
    GameEnd(sf::RenderWindow* window);        // Constructor que toma la ventana principal
    ~GameEnd();                               // Destructor
    void resource();
    void update();

};

#endif // GAMEEND_HPP
