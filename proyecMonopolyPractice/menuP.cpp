#include "menuP.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

// Constructor: inicializa la variable y la ventana
menuP::menuP(sf::RenderWindow& windowRef) : window(windowRef) {
    // Inicializaciones adicionales si es necesario
}

// Carga de recursos (texturas y sprites)
void menuP::Resource() {
    if (!textureLogoFortuneAvenue.loadFromFile("resource/texture/logojuego.png")) {
        std::cerr << "Error al cargar la imagen del logotipo presa" << std::endl;
        return;
    }
    if (!TexturaBotonJugarOff.loadFromFile("resource/texture/BotonJugarOff.png")) {
        std::cerr << "Error al cargar la imagen del Boton Jugar" << std::endl;
        return;
    }
    if (!texturaBotonJugarOn.loadFromFile("resource/texture/BotonJugarOn.png")) {
        std::cerr << "Error al cargar la imagen del Boton Jugar On" << std::endl;
        return;
    }
    if (!TexturaBotonOpciones.loadFromFile("resource/texture/BotonOpcionesOff.png")) {
        std::cerr << "Error al cargar la imagen del Boton Opciones" << std::endl;
        return;
    }
    if (!TexturaBotonSalir.loadFromFile("resource/texture/BotonSalirOff.png")) {
        std::cerr << "Error al cargar la imagen del Boton Salir" << std::endl;
        return;
    }
    

    // Configuración del sprite del logotipo
    spriteLogoFortuneAvenue.setTexture(textureLogoFortuneAvenue);
    spriteLogoFortuneAvenue.setOrigin(500, 2);
    spriteLogoFortuneAvenue.setPosition(640, 360);

    SpriteBotonJugar.setTexture(TexturaBotonJugar);
    SpriteBotonJugar.setOrigin(500, 2);
    SpriteBotonJugar.setPosition(640, 360);

    SpriteBotonOpcion.setTexture(TexturaBotonOpciones);
    SpriteBotonOpcion.setOrigin(500, 2);
    SpriteBotonOpcion.setPosition(640, 360);

    SpriteBotonSalir.setTexture(TexturaBotonSalir);
    SpriteBotonSalir.setOrigin(500, 2);
    SpriteBotonSalir.setPosition(640, 360);
}

// Actualización de la animación (desvanecimiento del logotipo)
void menuP::Update() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Obtener la posición del ratón
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::FloatRect buttonJugar = SpriteBotonJugar.getGlobalBounds();

        // Detectar si el ratón está sobre el botón
        if (buttonJugar.contains(static_cast<sf::Vector2f>(mousePosition))) {
            SpriteBotonJugar.setTexture(texturaBotonJugarOn);
        }
        else {
            SpriteBotonJugar.setTexture(TexturaBotonJugar);
        }

        window.clear();
        window.draw(SpriteBotonJugar);
        window.display();
    }
}

// Método para dibujar (implementa según sea necesario)
void menuP::Draw() {
    // Implementa el dibujo adicional si es necesario
}
