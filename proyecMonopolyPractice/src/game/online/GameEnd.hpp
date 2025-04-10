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
    sf::RenderWindow* window;                 
    sf::Text fingame12;
    sf::Text funciona;
    std::vector<sf::Text> posicionesGanadores;
    std::vector<int>posiGndrs;
    Client* client;

    sf::Texture TBotonMenu;
    sf::Texture TBotonPieces;
    sf::Sprite SBotonMenu;
    sf::Sprite SBotonPieces;


public:
    GameEnd(sf::RenderWindow* window, Client* clienT);        
    ~GameEnd();                               
    void resource();
    void update();

};

#endif
