#include "menuP.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

// Constructor: inicializa la variable y la ventana
menuP::menuP(sf::RenderWindow& windowRef) : window(windowRef) {
    // Inicializaciones adicionales si es necesario
}

// Carga de recursos (texturas y sprites)
void menuP::Resource() {
    if (!textureLogoFortuneAvenue.loadFromFile("resource/texture/logojuego1.png")) {
        std::cerr << "Error al cargar la imagen del logotipo presa" << std::endl;
        return;
    }
    if (!TextureBotonJugarOff.loadFromFile("resource/texture/BotonJugarOff.png")) {
        std::cerr << "Error al cargar la imagen del Boton Jugar Off" << std::endl;
        return;
    }
    if (!TextureBotonJugarOn.loadFromFile("resource/texture/BotonJugarOn.png")) {
        std::cerr << "Error al cargar la imagen del Boton Jugar On" << std::endl;
        return;
    }
    if (!TextureBotonOpcionesOff.loadFromFile("resource/texture/BotonOpcionesOff.png")) {
        std::cerr << "Error al cargar la imagen del Boton Opciones Off" << std::endl;
        return;
    }
    if (!TextureBotonOpcionesOn.loadFromFile("resource/texture/BotonOpcionesOn.png")) {
        std::cerr << "Error al cargar la imagen del Boton Opciones On" << std::endl;
        return;
    }
    if (!TextureBotonSalirOff.loadFromFile("resource/texture/BotonSalirOff.png")) {
        std::cerr << "Error al cargar la imagen del Boton Salir Off" << std::endl;
        return;
    }
    if (!TextureBotonSalirOn.loadFromFile("resource/texture/BotonSalirOn.png")) {
        std::cerr << "Error al cargar la imagen del Boton Salir On" << std::endl;
        return;
    }

    if (!TextureFondoMenu.loadFromFile("resource/texture/fondomenu.png")) {
        std::cerr << "Error al cargar la imagen del Boton Salir On" << std::endl;
        return;
    }

    // Configuración del sprite del logotipo
    spriteLogoFortuneAvenue.setTexture(textureLogoFortuneAvenue);
    spriteLogoFortuneAvenue.setOrigin(300, 300);
    spriteLogoFortuneAvenue.setPosition(640, 275);

    SpriteBotonJugar.setTexture(TextureBotonJugarOff);
    SpriteBotonJugar.setOrigin(103.5, 40);
    SpriteBotonJugar.setPosition(400, 560);

    SpriteBotonOpciones.setTexture(TextureBotonOpcionesOff);
    SpriteBotonOpciones.setOrigin(103.5, 40);
    SpriteBotonOpciones.setPosition(640, 560);

    SpriteBotonSalir.setTexture(TextureBotonSalirOff);
    SpriteBotonSalir.setOrigin(103.5, 40);
    SpriteBotonSalir.setPosition(860, 560);
    SpriteFondoMenu.setTexture(TextureFondoMenu);
}

// Actualización de la animación (desvanecimiento del logotipo)
void menuP::Update() {
    window.setMouseCursorVisible(true);
    while (window.isOpen()) {
        
        evento();

        // Actualizar estado de los botones según la posición del mouse
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

        // Verificar si el ratón está sobre el botón Jugar
        if (SpriteBotonJugar.getGlobalBounds().contains(mousePosFloat)) {
            SpriteBotonJugar.setTexture(TextureBotonJugarOn);
        }
        else {
            SpriteBotonJugar.setTexture(TextureBotonJugarOff);
        }

        // Verificar si el ratón está sobre el botón Opciones
        if (SpriteBotonOpciones.getGlobalBounds().contains(mousePosFloat)) {
            SpriteBotonOpciones.setTexture(TextureBotonOpcionesOn);
        }
        else {
            SpriteBotonOpciones.setTexture(TextureBotonOpcionesOff);
        }

        // Verificar si el ratón está sobre el botón Salir
        if (SpriteBotonSalir.getGlobalBounds().contains(mousePosFloat)) {
            SpriteBotonSalir.setTexture(TextureBotonSalirOn);
        }
        else {
            SpriteBotonSalir.setTexture(TextureBotonSalirOff);
        }

        // Dibujar elementos en la ventana
        window.clear();
        window.draw(SpriteFondoMenu);
        window.draw(spriteLogoFortuneAvenue);
        window.draw(SpriteBotonJugar);
        window.draw(SpriteBotonOpciones);
        window.draw(SpriteBotonSalir);
        window.display();
    }
}

void menuP::evento() {

    sf::Event event;

    while (window.pollEvent(event)) {
        // Cerrar la ventana con Escape o al cerrar
        if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            window.close();
        }

        // Manejar clic del mouse
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

            // Verificar si el clic fue en el botón Jugar
            if (SpriteBotonJugar.getGlobalBounds().contains(mousePosFloat)) {
                std::cout << "Jugar presionado" << std::endl;
                // Aquí puedes cambiar la escena o empezar el juego
            }

            // Verificar si el clic fue en el botón Opciones
            if (SpriteBotonOpciones.getGlobalBounds().contains(mousePosFloat)) {
                std::cout << "Opciones presionado" << std::endl;
                // Aquí puedes abrir el menú de opciones
            }

            // Verificar si el clic fue en el botón Salir
            if (SpriteBotonSalir.getGlobalBounds().contains(mousePosFloat)) {
                std::cout << "Salir presionado" << std::endl;
                window.close(); // Salir del juego
            }
        }
    }

}

// Método para dibujar (implementa según sea necesario)
void menuP::Draw() {
    // Implementa el dibujo adicional si es necesario
}
