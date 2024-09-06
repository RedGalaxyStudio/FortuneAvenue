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

    // Configuración del sprite del logotipo
    spriteLogoStudio.setTexture(textureLogoStudio);
    spriteLogoStudio.setOrigin(500, 238.5f);
    spriteLogoStudio.setPosition(640, 360);

    if (!textureLogoJuego.loadFromFile("resource/texture/logojuego.png")) {
        std::cerr << "Error al cargar la imagen del logotipo juego" << std::endl;
        return;
    }

    // Configuración del sprite del logotipo del juego
    spriteLogoJuego.setTexture(textureLogoJuego);
    spriteLogoJuego.setOrigin(275, 275);
    spriteLogoJuego.setPosition(640, 360);
}

// Actualización de la animación (desvanecimiento del logotipo)
void Cinematic::Update() {
    float alpha = 0.0f;
    bool fadingIn = true;
    float tiempoAcumulado = 0.0f;  // Para controlar la generación de caracteres
    float intervaloGeneracion = 0.1f;  // Generar un carácter nuevo cada 0.1 segundos

    while (window.isOpen() || clock.getElapsedTime().asSeconds() <= 5) {
        sf::Time deltaTime = fadeClock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Actualiza el color del sprite con la nueva opacidad
        spriteLogoStudio.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));

        window.clear();  // Limpia la pantalla

        if (clock.getElapsedTime().asSeconds() <= 6) {
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
            window.draw(spriteLogoStudio);  // Dibuja el logotipo si han pasado menos de 6 segundos
        }
        else if (clock.getElapsedTime().asSeconds() <= 80) {
            // Aplicar efectos de animación al logo del juego
            float tiempo = clock.getElapsedTime().asSeconds() - 6.0f;  // Tiempo desde que comenzó esta sección

            // Efecto de lluvia de caracteres
            static std::vector<sf::Text> caracteresLluvia;
            static sf::Font fuente;
            static bool fuenteCargada = false;

            if (!fuenteCargada) {
                if (!fuente.loadFromFile("ruta/a/tu/fuente.ttf")) {
                    std::cerr << "Error al cargar la fuente" << std::endl;
                }
                fuenteCargada = true;
            }

            // Acumular el tiempo transcurrido
            tiempoAcumulado += deltaTime.asSeconds();

            // Generar nuevos caracteres si ha pasado suficiente tiempo
            if (caracteresLluvia.size() < 100 && tiempoAcumulado >= intervaloGeneracion) {
                sf::Text nuevoCaracter;
                nuevoCaracter.setFont(fuente);
                nuevoCaracter.setCharacterSize(20);
                nuevoCaracter.setFillColor(sf::Color(255, 255, 255, 128));
                nuevoCaracter.setString(static_cast<char>(rand() % 26 + 65));  // Letras mayúsculas aleatorias
                nuevoCaracter.setPosition(static_cast<float>(rand() % window.getSize().x), 0.0f);
                caracteresLluvia.push_back(nuevoCaracter);

                // Reiniciar el tiempo acumulado
                tiempoAcumulado = 0.0f;
            }

            // Actualizar y dibujar caracteres
            for (auto it = caracteresLluvia.begin(); it != caracteresLluvia.end();) {
                it->move(0.0f, 100.0f * deltaTime.asSeconds());  // Velocidad de caída
                if (it->getPosition().y > window.getSize().y) {
                    it = caracteresLluvia.erase(it);
                }
                else {
                    window.draw(*it);
                    ++it;
                }
            }

            // Efecto de rotación
           // spriteLogoJuego.setRotation(tiempo * 30.0f);  // Gira 30 grados por segundo

            // Efecto de escala pulsante
            float escala = 1.0f + 0.1f * std::sin(tiempo * 3.0f);
            spriteLogoJuego.setScale(escala, escala);

            // Efecto de desvanecimiento
            int alpha = static_cast<int>(255.0f * (1.0f - (tiempo / 6.0f)));  // Se desvanece durante 6 segundos
            spriteLogoJuego.setColor(sf::Color(255, 255, 255, alpha));

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
