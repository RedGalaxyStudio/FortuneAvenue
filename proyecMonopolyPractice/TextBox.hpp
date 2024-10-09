#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP
#include "ResourceGlobal.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>

class TextBox {
public:
    TextBox();  // Constructor por defecto

    TextBox(float width, float height);  // Constructor con parámetros
    void setPosition();
    void handleInput(sf::Event event);
    void draw(sf::RenderWindow& window);

private:

    float x, y;
    sf::Text textoPregunta;
    sf::Text textoGuardado;
    sf::Text text;
};

#endif // TEXTBOX_HPP
