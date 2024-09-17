#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class TextBox {
public:
    TextBox();  // Constructor por defecto

    TextBox(float width, float height);  // Constructor con parámetros
    void setPosition(float x, float y);
    void handleInput(sf::Event event);
    void draw(sf::RenderWindow& window);

private:
    sf::Texture textureBox;
    sf::Sprite box;

    sf::Text text;
    sf::Font font;
    std::string input;
};

#endif // TEXTBOX_HPP
