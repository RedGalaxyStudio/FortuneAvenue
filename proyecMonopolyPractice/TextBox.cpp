#include "TextBox.hpp"

// Constructor con parámetros

TextBox::TextBox() {}// Constructor por defecto


TextBox::TextBox(float width, float height,std::string solicitud) {
    
    input = "";

    // Variables de texto en SFML
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
        std::cout << "La variable está vacía.\n";
    
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
void TextBox::setPosition() {
    box.setPosition(x + 145, y + 60);
    text.setPosition(x + 145, y + 56); // Desplaza el texto un poco dentro del cuadro
    textoPregunta.setPosition(x, y - 25);
}

// Manejo de la entrada de texto
std::string TextBox::handleInput(sf::Event event, const size_t maxLength) {
    //const size_t maxLength = 11; // Limite de caracteres

    // Manejo de entrada de texto
    if (event.type == sf::Event::TextEntered && nombre.empty()) {
        if (event.text.unicode < 128) { // Solo caracteres ASCII
            // Retroceso
            if (event.text.unicode == '\b' && !input.empty()) {
                input.pop_back();
            }
            // Agregar nuevo carácter solo si no excede el límite
            else if (event.text.unicode != '\b' && input.size() < maxLength) {
                input += static_cast<char>(event.text.unicode);
            }

            text.setString(input);
            std::cout << "Input Text: " << input << std::endl;

            sf::FloatRect globalBounds = text.getGlobalBounds();
            // Ajustar la posición centrando el texto
            text.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

        }
    }
    return input;
}

std::string TextBox::Actu() {

    return input;

}

// Dibujo del cuadro de texto
void TextBox::draw(sf::RenderWindow& window) {
    window.draw(box);
    window.draw(text);
    window.draw(textoPregunta);
    //window.draw(textoGuardado);
}

void TextBox::Prinf() {
    renderTexture.draw(box);
    renderTexture.draw(text);
    renderTexture.draw(textoPregunta);
}

