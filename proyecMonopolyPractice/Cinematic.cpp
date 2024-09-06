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
        std::cerr << "Error al cargar la imagen del logotipo presa" << std::endl;
        return;
    }

    spriteLogoStudio.setTexture(textureLogoStudio);
    spriteLogoStudio.setOrigin(500, 238.5f);
    spriteLogoStudio.setPosition(640, 360);

    if (!textureLogoJuego.loadFromFile("resource/texture/logojuego.png")) {
        std::cerr << "Error al cargar la imagen del logotipo juego" << std::endl;
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
    float alpha = 0.0f;
    float tiempoAcumulado = 0.0f;  // Para controlar la generación de caracteres
    float intervaloGeneracion = 0.1f;  // Generar un carácter nuevo cada 0.1 segundos

    while (window.isOpen() && clock.getElapsedTime().asSeconds() <= 12) {
        sf::Time deltaTime = fadeClock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();  // Limpia la pantalla

        if (clock.getElapsedTime().asSeconds() <= 6) {
            alpha += 255.0f * deltaTime.asSeconds();  // Incrementa la opacidad
            alpha = std::min(alpha, 255.0f);
            spriteLogoStudio.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
            window.draw(spriteLogoStudio);
        }
        else if (clock.getElapsedTime().asSeconds() <= 12) {
            float tiempo = clock.getElapsedTime().asSeconds() - 6.0f;

            static std::vector<sf::Text> caracteresLluvia;

            tiempoAcumulado += deltaTime.asSeconds();

            if (caracteresLluvia.size() < 100 && tiempoAcumulado >= intervaloGeneracion) {
                sf::Text nuevoCaracter;
                nuevoCaracter.setFont(fuente);
                nuevoCaracter.setCharacterSize(20);
                nuevoCaracter.setFillColor(sf::Color(255, 255, 255, 128));
                nuevoCaracter.setString(static_cast<char>(rand() % 26 + 65));
                nuevoCaracter.setPosition(static_cast<float>(rand() % window.getSize().x), 0.0f);
                caracteresLluvia.push_back(nuevoCaracter);

                tiempoAcumulado = 0.0f;
            }

            for (auto it = caracteresLluvia.begin(); it != caracteresLluvia.end();) {
                it->move(0.0f, 100.0f * deltaTime.asSeconds());
                if (it->getPosition().y > window.getSize().y) {
                    it = caracteresLluvia.erase(it);
                }
                else {
                    window.draw(*it);
                    ++it;
                }
            }

            float escala = 1.0f + 0.1f * std::sin(tiempo * 3.0f);
            spriteLogoJuego.setScale(escala, escala);

            int logoAlpha = static_cast<int>(255.0f * (1.0f - (tiempo / 6.0f)));
            spriteLogoJuego.setColor(sf::Color(255, 255, 255, logoAlpha));

            window.draw(spriteLogoJuego);
        }
        else {
            break;
        }

        window.display();  // Actualiza la ventana
    }
}

// Método para dibujar (implementa según sea necesario)
void Cinematic::Draw() {
    // Implementa el dibujo adicional si es necesario
}


