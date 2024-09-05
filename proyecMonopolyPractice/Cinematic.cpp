#include "Cinematic.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>  // Necesario para std::cerr

// Constructor: inicializa la variable y la ventana
Cinematic::Cinematic(sf::RenderWindow& windowRef) : window(windowRef) {
    // Inicializaciones adicionales si es necesario
}

// Carga de recursos (texturas y sprites)
void Cinematic::Resource() {
    if (!textureLogoStudio.loadFromFile("resource/texture/imagelogopresa.png")) {
        std::cerr << "Error al cargar la imagen del logotipo" << std::endl;
        return;
    }

    // Configuración del sprite del logotipo
    spriteLogoStudio.setTexture(textureLogoStudio);
    spriteLogoStudio.setOrigin(500, 238.5f);
    spriteLogoStudio.setPosition(750, 500);
}

// Actualización de la animación (desvanecimiento del logotipo)
void Cinematic::Update() {
    float alpha = 0.0f;
    bool fadingIn = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Calcular el tiempo transcurrido y actualizar la opacidad
        sf::Time deltaTime = fadeClock.restart();

        if (fadingIn) {
            alpha += 255.0f * deltaTime.asSeconds();  // Incrementa la opacidad
            if (alpha >= 255.0f) {
                alpha = 255.0f;
                fadingIn = false;
            }
        }
        else {
            alpha -= 255.0f * deltaTime.asSeconds();  // Decrementa la opacidad
            if (alpha <= 0.0f) {
                alpha = 0.0f;
                fadingIn = true;
            }
        }

        // Actualiza el color del sprite con la nueva opacidad
        spriteLogoStudio.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));

        window.clear();  // Limpia la pantalla

        if (clock.getElapsedTime().asSeconds() <= 5) {
            window.draw(spriteLogoStudio);  // Dibuja el logotipo si han pasado menos de 5 segundos
        }

        window.display();  // Actualiza la ventana
    }
}

// Método para dibujar (implementa según sea necesario)
void Cinematic::Draw() {
    // Implementa el dibujo adicional si es necesario
}
