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
     cargarNombre();
     input = "";
if (!font.loadFromFile("resource/fonts/ARCADEPI.ttf")) {
        std::cerr << "Error loading font\n";
    }
     // Variables de texto en SFML
     
     textoPregunta.setFont(font);
     textoPregunta.setCharacterSize(24);
     textoPregunta.setString("Ingresa tu nombre: ");
     textoPregunta.setPosition(525, 300);
     textoGuardado.setFont(font);
     textoGuardado.setCharacterSize(24);
     textoGuardado.setString("");
     textoGuardado.setPosition(525, 250);

     if (!nombre.empty()) {
         textoGuardado.setString("Bienvenido de nuevo, " + nombre);
     }

    if (!textureBox.loadFromFile("resource/texture/Button/rectanguloEncendido.png")) return;
    box.setTexture(textureBox);
    
    
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

    if (event.type == sf::Event::TextEntered && nombre.empty()) {
        if (event.text.unicode < 128) {
            if (event.text.unicode == '\b' && !input.empty()) {  // Retroceso
                input.pop_back();
            }
            else if (event.text.unicode != '\b') {
                input += static_cast<char>(event.text.unicode);
            }
            text.setString(input);
        }
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && nombre.empty()) {
        if (!input.empty()) {
            nombre = input;
            guardarNombre();
            textoGuardado.setString("Nombre guardado: " + nombre);
        }
    }
}

// Dibujo del cuadro de texto
void TextBox::draw(sf::RenderWindow& window) {
    window.draw(box);
    window.draw(text);
    window.draw(textoPregunta);
    window.draw(textoGuardado);
}

void TextBox::guardarNombre() {
    std::ofstream archivo("nombre.txt");
    if (archivo.is_open()) {
        archivo << nombre;
        archivo.close();
    }
    else {
        std::cerr << "No se pudo abrir el archivo para escribir.\n";
    }
}

// Función para cargar el nombre desde un archivo
void TextBox::cargarNombre() {
    std::ifstream archivo("nombre.txt");
    if (archivo.is_open()) {
        std::getline(archivo, nombre);
        archivo.close();
    }
}
