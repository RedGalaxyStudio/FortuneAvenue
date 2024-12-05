#include "TextBox.hpp"

// Constructor con parámetros

TextBox::TextBox() {}// Constructor por defecto


TextBox::TextBox(float width, float height,std::string solicitud) {
    
    input = "";

    if (!nombre.empty()) {  
        
     textoGuardado.setFont(fontUser);
    textoGuardado.setCharacterSize(24);
    textoGuardado.setString("");
    textoGuardado.setPosition(525, 250);

    x = 50;
    y = 50;
    text.setString(nombre);
        std::cout << "La variable tiene contenido.\n";
    }
    else {
        std::cout << "La variable esta vacia.\n";
    
    textoPregunta.setFont(fontUser);
    textoPregunta.setCharacterSize(24);
    textoPregunta.setString(solicitud);
    textoPregunta.setOutlineColor(sf::Color(135, 135, 135));
    textoPregunta.setOutlineThickness(2);
    x = 525;
    y = 80;

    }
    text.setFont(fontUser);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setOutlineThickness(2);
    text.setOutlineColor(sf::Color(135, 135, 135));
}

// Posición del cuadro de texto
void TextBox::setPosition(int XX ,int YY) {
    box.setPosition(XX + 145, YY + 60);
    text.setPosition(XX + 145, YY + 56);
    textoPregunta.setPosition(XX, YY - 25);
}


std::string TextBox::handleInput(sf::Event event, const size_t maxLength) {
 

  
    if (event.type == sf::Event::TextEntered && nombre.empty()) {
        if (event.text.unicode < 128) {
            if (event.text.unicode == '\b' && !input.empty()) {
                input.pop_back();
            }
            
            else if (event.text.unicode != '\b' && input.size() < maxLength) {
                input += static_cast<char>(event.text.unicode);
            }

            text.setString(input);
            std::cout << "Input Text: " << input << std::endl;

            sf::FloatRect globalBounds = text.getGlobalBounds();
            
            text.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

        }
    }
    return input;
}

std::string TextBox::Actu() {

    return input;

}


void TextBox::draw(sf::RenderWindow& window) {
    window.draw(box);
    window.draw(text);
    window.draw(textoPregunta);
}

void TextBox::Prinf() {
    renderTexture.draw(box);
    renderTexture.draw(text);
    renderTexture.draw(textoPregunta);
}

