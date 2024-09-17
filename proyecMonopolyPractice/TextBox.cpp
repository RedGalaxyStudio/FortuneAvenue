#include "TextBox.hpp"

// Constructor con parámetros
TextBox::TextBox() {
    if (!textureBox.loadFromFile("resource/texture/Button/rectanguloEncendido.png")) return;
    box.setTexture(textureBox);

    if (!font.loadFromFile("resource/fonts/ARCADEPI.ttf")) {
        std::cerr << "Error loading font\n";
    }
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setString("");
}

TextBox::TextBox(float width, float height) {
    if (!textureBox.loadFromFile("resource/texture/Button/rectanguloEncendido.png")) return;
    box.setTexture(textureBox);

    if (!font.loadFromFile("resource/fonts/ARCADEPI.ttf")) {
        std::cerr << "Error loading font\n";
    }
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setOutlineThickness(2);
    text.setOutlineColor(sf::Color::Black);
}

// Posición del cuadro de texto
void TextBox::setPosition(float x, float y) {
    box.setPosition(x, y);
    text.setPosition(x + 25, y + 28); // Desplaza el texto un poco dentro del cuadro
}

// Manejo de la entrada de texto
void TextBox::handleInput(sf::Event event) {
    const size_t maxLength = 24; // Limite de caracteres

    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == '\b') { // Manejar retroceso
            if (!input.empty()) {
                input.pop_back();
            }
        }
        else if (event.text.unicode < 128) { // Añadir caracteres si son ASCII
            if (input.size() < maxLength) { // Verificar si se ha alcanzado el límite
                input += static_cast<char>(event.text.unicode);
            }
        }
        text.setString(input);
    }
}

// Dibujo del cuadro de texto
void TextBox::draw(sf::RenderWindow& window) {
    window.draw(box);
    window.draw(text);
}
