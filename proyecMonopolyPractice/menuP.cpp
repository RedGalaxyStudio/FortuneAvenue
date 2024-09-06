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
        std::cerr << "Error al cargar la imagen del Boton Jugar Off" << std::endl;
        return;
    }
    if (!TexturaBotonJugarOn.loadFromFile("resource/texture/BotonJugarOn.png")) {
        std::cerr << "Error al cargar la imagen del Boton Jugar On" << std::endl;
        return;
    }
    if (!TexturaBotonOpcionesOff.loadFromFile("resource/texture/BotonOpcionesOff.png")) {
        std::cerr << "Error al cargar la imagen del Boton Opciones Off" << std::endl;
        return;
    }
    if (!TexturaBotonOpcionesOn.loadFromFile("resource/texture/BotonOpcionesOn.png")) {
        std::cerr << "Error al cargar la imagen del Boton Opciones On" << std::endl;
        return;
    }
    if (!TexturaBotonSalirOff.loadFromFile("resource/texture/BotonSalirOff.png")) {
        std::cerr << "Error al cargar la imagen del Boton Salir Off" << std::endl;
        return;
    }
    if (!TexturaBotonSalirOn.loadFromFile("resource/texture/BotonSalirOn.png")) {
        std::cerr << "Error al cargar la imagen del Boton Salir On" << std::endl;
        return;
    } // Faltaba esta llave

    // Configuración del sprite del logotipo
    spriteLogoFortuneAvenue.setTexture(textureLogoFortuneAvenue);
    spriteLogoFortuneAvenue.setOrigin(500, 2);
    spriteLogoFortuneAvenue.setPosition(640, 360);

    SpriteBotonJugar.setTexture(TexturaBotonJugarOff);
    SpriteBotonJugar.setOrigin(500, 2);
    SpriteBotonJugar.setPosition(640, 360);

    SpriteBotonOpciones.setTexture(TexturaBotonOpcionesOff);
    SpriteBotonOpciones.setOrigin(500, 2);
    SpriteBotonOpciones.setPosition(640, 360);

    SpriteBotonSalir.setTexture(TexturaBotonSalirOff);
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
        sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

        // Verificar si el ratón está sobre el botón Jugar
        if (SpriteBotonJugar.getGlobalBounds().contains(mousePosFloat)) {
            SpriteBotonJugar.setTexture(TexturaBotonJugarOn);
        }
        else {
            SpriteBotonJugar.setTexture(TexturaBotonJugarOff);
        }

        // Verificar si el ratón está sobre el botón Opciones
        if (SpriteBotonOpciones.getGlobalBounds().contains(mousePosFloat)) {
            SpriteBotonOpciones.setTexture(TexturaBotonOpcionesOn);
        }
        else {
            SpriteBotonOpciones.setTexture(TexturaBotonOpcionesOff);
        }

        // Verificar si el ratón está sobre el botón Salir
        if (SpriteBotonSalir.getGlobalBounds().contains(mousePosFloat)) {
            SpriteBotonSalir.setTexture(TexturaBotonSalirOn);
        }
        else {
            SpriteBotonSalir.setTexture(TexturaBotonSalirOff);
        }

        window.clear();
        window.draw(SpriteBotonJugar);
        window.draw(SpriteBotonOpciones);
        window.draw(SpriteBotonSalir);
        window.display();
    }
}

// Método para dibujar (implementa según sea necesario)
void menuP::Draw() {
    // Implementa el dibujo adicional si es necesario
}
