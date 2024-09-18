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
    void setPosition(float x, float y);
    void handleInput(sf::Event event);
    void draw(sf::RenderWindow& window);
    void guardarNombre();
    void cargarNombre();
private:
    sf::Texture textureBox;
    sf::Sprite box;
    sf::Text textoPregunta;
    sf::Text textoGuardado;
    sf::Text text;
    sf::Font font;
    std::string input;
};

#endif // TEXTBOX_HPP
