#ifndef GAMEEND_HPP
#define GAMEEND_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "ResourceGame.hpp"
#include "../../core/ResourceGlobal.hpp"
#include <vector>
#include <algorithm>
#include <iostream>
#include "../../network/Client.hpp"


class GameEnd {
private:
    sf::RenderWindow* window;                 // Ventana principal para dibujar
    sf::Text fingame12;
    sf::Text funciona;
    std::vector<sf::Text> posicionesGanadores;
    std::vector<int>posiGndrs;
    Client* client;
public:
    GameEnd(sf::RenderWindow* window, Client* clienT);        // Constructor que toma la ventana principal
    ~GameEnd();                               // Destructor
    void resource();
    void update();

};

#endif // GAMEEND_HPP
