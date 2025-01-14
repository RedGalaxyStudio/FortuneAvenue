#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP
#include "../core/ResourceGlobal.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>

class TextBox {
public:
    TextBox();  // Constructor por defecto

    TextBox(float width, float height,std::string solicitud);  
    void setPosition(int XX, int YY);
    std::string handleInput(sf::Event event, const size_t maxLength);
    void draw(sf::RenderWindow& window);
    void Prinf();
    std::string Actu();
    std::string input;
private:
    
    float x, y;
    sf::Text textoPregunta;
    sf::Text textoGuardado;
    sf::Text text;
};

#endif // TEXTBOX_HPP
