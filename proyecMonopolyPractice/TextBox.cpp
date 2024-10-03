#include "TextBox.hpp"

// Constructor con par�metros

TextBox::TextBox() {}// Constructor por defecto


TextBox::TextBox(float width, float height) {
    cargarNombre();
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
        std::cout << "La variable est� vac�a.\n";
    
    textoPregunta.setFont(fontUser);
    textoPregunta.setCharacterSize(24);
    textoPregunta.setString("Ingresa tu nombre: ");
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

// Posici�n del cuadro de texto
void TextBox::setPosition() {
    box.setPosition(x + 20, y + 20);
    text.setPosition(x + 30, y + 45); // Desplaza el texto un poco dentro del cuadro
    textoPregunta.setPosition(x, y-25);
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
        }
    }
}

// Dibujo del cuadro de texto
void TextBox::draw(sf::RenderWindow& window) {
    window.draw(box);
    window.draw(text);
    window.draw(textoPregunta);
    //window.draw(textoGuardado);
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

// Funci�n para cargar el nombre desde un archivo
void TextBox::cargarNombre() {
    std::ifstream archivo("nombre.txt");
    if (archivo.is_open()) {
        std::getline(archivo, nombre);
        archivo.close();
    }
}
