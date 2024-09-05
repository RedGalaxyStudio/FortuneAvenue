#include "Cinematic.hpp"
#include <iostream>

Cinematic::Cinematic(sf::RenderWindow& window)
    : window(window), cargaTerminada(false) {
}

Cinematic::~Cinematic() {
    if (hiloCarga.joinable()) {
        hiloCarga.join(); // Asegura que el hilo termine antes de destruir la clase
    }
}

void Cinematic::iniciarCarga() {
    // Cargar la textura del logo
    if (!texture.loadFromFile("resource/texture/imagelogopresa.png")) {
        std::cerr << "Error al cargar la textura del logo" << std::endl;
        return;
    }

    sprite.setTexture(texture);
    sprite.setOrigin(500, 238.5f); // Ajusta según el tamaño del sprite
    sprite.setPosition(750, 500);  // Posición del sprite

    // Iniciar el hilo para cargar recursos en segundo plano
    hiloCarga = std::thread(&Cinematic::cargarRecursos, this);
}

void Cinematic::cargarRecursos() {
    // Cargar recursos necesarios para el juego
    sf::Texture textura;
    if (textura.loadFromFile("resource/texture/image.png")) {
        texturas.push_back(textura);
    }

    if (!buffer.loadFromFile("resource/sonid/sonidouu.wav")) {
        std::cerr << "Error al cargar el archivo de sonido" << std::endl;
        return;
    }

    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    // Marcar como completada la carga
    cargaTerminada = true;
}

void Cinematic::dibujar() {
    float alpha = 0.0f;
    bool fadingIn = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time deltaTime = fadeClock.restart();

        if (fadingIn) {
            alpha += 255.0f * deltaTime.asSeconds(); // Incrementa la opacidad
            if (alpha >= 255.0f) {
                alpha = 255.0f;
                fadingIn = false;
            }
        }
        else {
            alpha -= 255.0f * deltaTime.asSeconds(); // Decrementa la opacidad
            if (alpha <= 0.0f) {
                alpha = 0.0f;
                fadingIn = true;
            }
        }

        sprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));

        window.clear();
        if (clock.getElapsedTime().asSeconds() <= 5) {
            window.draw(sprite);
        }

        window.display();

        if (cargaTerminada) {
            break; // Salir del loop de la pantalla de carga cuando los recursos estén listos
        }
    }
}

bool Cinematic::cargaCompleta() const {
    return cargaTerminada;
}
