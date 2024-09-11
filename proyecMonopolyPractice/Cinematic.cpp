#include "Cinematic.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>  // Necesario para std::cerr

// Constructor: inicializa la variable y la ventana
Cinematic::Cinematic(sf::RenderWindow& windowRef)
    : window(windowRef), alpha(0.0f), fadeIn(true) {
    // Inicializaciones adicionales si es necesario
}

// Carga de recursos (texturas y sprites)
void Cinematic::Resource() {
    if (!textureLogoStudio.loadFromFile("resource/texture/imagelogopresa.png")) {
        std::cerr << "Error al cargar la imagen del logotipo presa" << std::endl;
        return;
    }

    if (!TextureFondoLogo.loadFromFile("resource/texture/spritesheetFondo.png")) {
        std::cerr << "Error al cargar la imagen del logotipo fondo" << std::endl;
        return;
    }

    window.setMouseCursorVisible(false);

    SpriteFondoLogo.setTexture(TextureFondoLogo);
    spriteLogoStudio.setTexture(textureLogoStudio);
    spriteLogoStudio.setOrigin(500, 238.5f);
    spriteLogoStudio.setPosition(640, 360);

    if (!textureLogoJuego.loadFromFile("resource/texture/logojuego1.png")) {
        std::cerr << "Error al cargar la imagen del logotipo del juego" << std::endl;
        return;
    }

    spriteLogoJuego.setTexture(textureLogoJuego);
    spriteLogoJuego.setOrigin(275, 275);
    spriteLogoJuego.setPosition(640, 360);

    // Cargar la fuente para la lluvia de caracteres
    if (!fuente.loadFromFile("resource/texture/ave.ttf")) {
        std::cerr << "Error al cargar la fuente" << std::endl;
        return;
    }
}

// Actualización de la animación (desvanecimiento del logotipo)
void Cinematic::Update() {
    float tiempoAcumulado = 0.0f;  // Para controlar la generación de caracteres
    float intervaloGeneracion = 0.1f;  // Generar un carácter nuevo cada 0.1 segundos

    while (window.isOpen() && clock.getElapsedTime().asSeconds() <= 12) {
        sf::Time deltaTime = fadeClock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        }

        window.clear();

        if (clock.getElapsedTime().asSeconds() <= 6) {
            // Actualiza la opacidad oscilante
            if (fadeIn) {
                alpha += 200.0f * deltaTime.asSeconds();
                if (alpha >= 255.0f) {
                    alpha = 255.0f;
                    fadeIn = false;  // Comienza a decrementar
                }
            }
            else {
                alpha -= 200.0f * deltaTime.asSeconds();
                if (alpha <= 0.0f) {
                    alpha = 0.0f;
                    fadeIn = true;  // Comienza a incrementar
                }
            }

            spriteLogoStudio.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
            window.draw(spriteLogoStudio);
        }
        else if (clock.getElapsedTime().asSeconds() <= 12) {
            // Actualización del spritesheet
            if (controlframe.getElapsedTime().asSeconds() >= frameTime) {
                currentFrame = (currentFrame + 1) % totalFrames;
                int xFrame = (currentFrame % columns) * frameWidth;
                int yFrame = (currentFrame / columns) * frameHeight;
                SpriteFondoLogo.setTextureRect(sf::IntRect(xFrame, yFrame, frameWidth, frameHeight));

                controlframe.restart();
            }
            window.draw(SpriteFondoLogo);
            window.draw(spriteLogoJuego);
        }
        else {
            break;  // Sale del ciclo después de 12 segundos
        }

        window.display();  // Actualiza la ventana
    }
}

// Método para dibujar (implementa según sea necesario)
void Cinematic::Draw() {
    // Implementa el dibujo adicional si es necesario
}
