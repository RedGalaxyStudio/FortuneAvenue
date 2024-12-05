#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>  // Para funciones trigonométricas

class Card {
public:
    sf::Vector3f position;
    sf::RectangleShape shape;  // Representa la carta

    float angleX = 0.0f;  // Ángulo de rotación sobre el eje X
    float angleY = 0.0f;  // Ángulo de rotación sobre el eje Y
    float angleZ = 0.0f;  // Ángulo de rotación sobre el eje Z

    // Constructor de la clase Card
    Card(float width, float height) {
        shape.setSize(sf::Vector2f(width, height));
        shape.setOrigin(width / 2, height / 2);  // Centro de la carta para rotación
    }

    // Establecer la posición de la carta en 2D
    void setPosition(float x, float y, float z) {
        position = sf::Vector3f(x, y, z);
        shape.setPosition(x, y);  // Posición en 2D (para SFML)
    }

    // Función para simular la rotación en 3D
    void rotate(float deltaX, float deltaY) {
        angleX += deltaX;
        angleY += deltaY;
        // Calculamos la rotación usando las matrices de rotación en 3D
    }

    // Proyección en 2D (simple) de las coordenadas 3D
    sf::Vector2f project() {
        // Matriz de rotación sobre el eje Z (plano X-Y)
        float cosZ = cos(angleZ);
        float sinZ = sin(angleZ);
        float cosX = cos(angleX);
        float sinX = sin(angleX);
        float cosY = cos(angleY);
        float sinY = sin(angleY);

        // Aplicamos la proyección 3D a 2D con una matriz de proyección simple
        float x = position.x * cosY * cosZ - position.y * cosY * sinZ + position.z * sinY;
        float y = position.x * (sinX * sinY * cosZ + cosX * sinZ) + position.y * (sinX * sinY * sinZ - cosX * cosZ) - position.z * cosX * cosY;

        // Proyección de la 3D a la 2D (ajustando el tamaño de la ventana)
        return sf::Vector2f(x + 400, y + 300);  // 400 y 300 para centrar en la ventana
    }

    // Dibujar la carta en la ventana
    void draw(sf::RenderWindow& window) {
        sf::Vector2f projPos = project();
        shape.setPosition(projPos);  // Actualiza la posición de la carta en la ventana
        window.draw(shape);
    }
};

class Windown {  // Mantengo el nombre de la clase como "Windown"
public:
    sf::RenderWindow* window;
    Card* card;  // Usamos la clase Card

    // Constructor de la clase Windown
    Windown(sf::RenderWindow* windowRef) : window(windowRef) {
        card = new Card(100, 150);  // Tamaño de la carta
        card->setPosition(static_cast<float>(window->getSize().x / 2), static_cast<float>(window->getSize().y / 2),  0);  // Posición inicial
    }

    // Actualizar la ventana y la carta
    void update() {
        while (window->isOpen()) {
            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window->close();
                }

                // Gira la carta cuando la tecla sea presionada
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Left) {
                        std::cout << "Izquierda presionada\n";  // Depuración
                        card->rotate(0.05f, 0);  // Gira la carta sobre el eje X (simulando 3D)
                    }
                    if (event.key.code == sf::Keyboard::Right) {
                        std::cout << "Derecha presionada\n";  // Depuración
                        card->rotate(-0.05f, 0);  // Gira la carta sobre el eje X
                    }
                    if (event.key.code == sf::Keyboard::Up) {
                        std::cout << "Arriba presionada\n";  // Depuración
                        card->rotate(0, 0.05f);  // Gira la carta sobre el eje Y
                    }
                    if (event.key.code == sf::Keyboard::Down) {
                        std::cout << "Abajo presionada\n";  // Depuración
                        card->rotate(0, -0.05f);  // Gira la carta sobre el eje Y
                    }
                }
            }

            // Actualiza la ventana
            window->clear();
            card->draw(*window);
            window->display();
        }
    }
};
