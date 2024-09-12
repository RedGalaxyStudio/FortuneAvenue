#include "menuP.hpp"
//#include <iostream>
#include <SFML/Graphics.hpp>

// Constructor: inicializa la variable y la ventana
menuP::menuP(sf::RenderWindow& windowRef) : window(windowRef),
lastHoveredButton(nullptr) {
    // Inicializaciones adicionales si es necesario
}

// Carga de recursos (texturas y sprites)
void menuP::Resource() {
    if (!textureLogoFortuneAvenue.loadFromFile("resource/texture/logojuego14.png")) {
        //std::cerr << "Error al cargar la imagen del logotipo presa" << std::endl;
        return;
    }
    if (!TextureBotonJugarOff.loadFromFile("resource/texture/BotonJugarOff.png")) {
        //std::cerr << "Error al cargar la imagen del Boton Jugar Off" << std::endl;
        return;
    }
    if (!TextureBotonJugarOn.loadFromFile("resource/texture/BotonJugarOn.png")) {
        //std::cerr << "Error al cargar la imagen del Boton Jugar On" << std::endl;
        return;
    }
    if (!TextureBotonOpcionesOff.loadFromFile("resource/texture/BotonOpcionesOff.png")) {
        //std::cerr << "Error al cargar la imagen del Boton Opciones Off" << std::endl;
        return;
    }
    if (!TextureBotonOpcionesOn.loadFromFile("resource/texture/BotonOpcionesOn.png")) {
        //std::cerr << "Error al cargar la imagen del Boton Opciones On" << std::endl;
        return;
    }
    if (!TextureBotonSalirOff.loadFromFile("resource/texture/BotonSalirOff.png")) {
       // std::cerr << "Error al cargar la imagen del Boton Salir Off" << std::endl;
        return;
    }
    if (!TextureBotonSalirOn.loadFromFile("resource/texture/BotonSalirOn.png")) {
       // std::cerr << "Error al cargar la imagen del Boton Salir On" << std::endl;
        return;
    }

    if (!TextureFondoMenu.loadFromFile("resource/texture/fondomenu.png")) {
        //std::cerr << "Error al cargar la imagen del Boton Salir On" << std::endl;
        return;
    }

    if (!HoverBuffer.loadFromFile("resource/sounds/deciB.wav")) {
       // std::cerr << "Error al cargar el sonido B" << std::endl;
        return;
    }
    if (!ClickBuffer.loadFromFile("resource/sounds/deciA.wav")) {
       // std::cerr << "Error al cargar el sonido A" << std::endl;
        return;
    }
    if (!MusicBuffer.loadFromFile("resource/sounds/MenuB.wav")) {
        return;
    }

    HoverSound.setBuffer(HoverBuffer);
    ClickSound.setBuffer(ClickBuffer);
    MusicSound.setBuffer(MusicBuffer);

    // Configuración del sprite del logotipo
    spriteLogoFortuneAvenue.setTexture(textureLogoFortuneAvenue);
    spriteLogoFortuneAvenue.setOrigin(256.5, 209.4);
    spriteLogoFortuneAvenue.setPosition(640, 260);

    SpriteBotonJugar.setTexture(TextureBotonJugarOff);
    SpriteBotonJugar.setOrigin(103.5, 40);
    SpriteBotonJugar.setPosition(383, 560);

    SpriteBotonOpciones.setTexture(TextureBotonOpcionesOff);
    SpriteBotonOpciones.setOrigin(103.5, 40);
    SpriteBotonOpciones.setPosition(640, 560);

    SpriteBotonSalir.setTexture(TextureBotonSalirOff);
    SpriteBotonSalir.setOrigin(103.5, 40);
    SpriteBotonSalir.setPosition(895, 560);
    SpriteFondoMenu.setTexture(TextureFondoMenu);
}

// Actualización de la animación (desvanecimiento del logotipo)
void menuP::Update() {
    MusicSound.setLoop(true);
    MusicSound.play();

    window.setMouseCursorVisible(true);
    while (window.isOpen()) {

        evento();

        // Actualizar estado de los botones según la posición del mouse
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

        // Verificar si el ratón está sobre el botón Jugar
        if (SpriteBotonJugar.getGlobalBounds().contains(mousePosFloat)) {
            SpriteBotonJugar.setTexture(TextureBotonJugarOn);
            handleHover(&SpriteBotonJugar);
        }
        else {
            SpriteBotonJugar.setTexture(TextureBotonJugarOff);
            resetLastHoveredButton(&SpriteBotonJugar);
        }

        // Verificar si el ratón está sobre el botón Opciones
        if (SpriteBotonOpciones.getGlobalBounds().contains(mousePosFloat)) {
            SpriteBotonOpciones.setTexture(TextureBotonOpcionesOn);
            handleHover(&SpriteBotonOpciones);
        }
        else {
            SpriteBotonOpciones.setTexture(TextureBotonOpcionesOff);
            resetLastHoveredButton(&SpriteBotonOpciones);
        }

        // Verificar si el ratón está sobre el botón Salir
        if (SpriteBotonSalir.getGlobalBounds().contains(mousePosFloat)) {
            SpriteBotonSalir.setTexture(TextureBotonSalirOn);
            handleHover(&SpriteBotonSalir);
        }
        else {
            SpriteBotonSalir.setTexture(TextureBotonSalirOff);
            resetLastHoveredButton(&SpriteBotonSalir);
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
                playClickSound();
               // std::cout << "Jugar presionado" << std::endl;
                // Aquí puedes cambiar la escena o empezar el juego
            }

            // Verificar si el clic fue en el botón Opciones
            if (SpriteBotonOpciones.getGlobalBounds().contains(mousePosFloat)) {
                playClickSound();
                windowOpcion();
                //std::cout << "Opciones presionado" << std::endl;
                // Aquí puedes abrir el menú de opciones
            }

            // Verificar si el clic fue en el botón Salir
            if (SpriteBotonSalir.getGlobalBounds().contains(mousePosFloat)) {
                playClickSound();
                //std::cout << "Salir presionado" << std::endl;
                window.close(); // Salir del juego
            }
        }
    }
}

void menuP::handleHover(sf::Sprite* currentButton) {
    if (lastHoveredButton != currentButton) {
        playHoverSound();
        lastHoveredButton = currentButton;
    }
}

void menuP::resetLastHoveredButton(sf::Sprite* currentButton) {
    if (lastHoveredButton == currentButton) {
        lastHoveredButton = nullptr;
    }
}

void menuP::playHoverSound() {
    if (HoverSound.getStatus() != sf::Sound::Playing) {
        HoverSound.play();
    }
}

void menuP::playClickSound() {
    ClickSound.play();
}

// Método para dibujar (implementa según sea necesario)
void menuP::Draw() {
    // Implementa el dibujo adicional si es necesario
}

void menuP::windowOpcion() {
    
    
    
    SpriteBotonOpciones.setTexture(TextureBotonOpcionesOn);
    SpriteBotonOpciones.setPosition(640, 100);

    window.setMouseCursorVisible(true);
    while (window.isOpen()) {

        evento();

    
  
        // Dibujar elementos en la ventana
        window.clear();
        window.draw(SpriteFondoMenu);
        window.draw(SpriteBotonOpciones);
        window.display();
    }

}