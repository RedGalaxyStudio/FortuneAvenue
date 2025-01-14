#include "Cube.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>

Cube::Cube(float size, float dotSize, float cornerRadius, sf::Vector2f position)
    : cubeSize(size), dotSize(dotSize), cornerRadius(cornerRadius), position(position),
    currentFace(0), isRolling(false), rollTime(0) {

    shadow.setSize(sf::Vector2f(cubeSize, cubeSize));
    shadow.setFillColor(sf::Color(0, 0, 0, 100));  // Sombra con transparencia
    shadow.setPosition(position.x + 20, position.y + 20);  // Desplazar la sombra

    // Crear las 6 caras del dado
    createCube();

    for (auto& face : faces) {
        face.face.setPosition(position);
        for (auto& dot : face.dots) {
            dot.setPosition(dot.getPosition() + position);
        }
    }

    // Inicializar rand
    std::srand(static_cast<unsigned int>(std::time(0)));

}

// Función para crear un rectángulo con bordes redondeados
sf::ConvexShape Cube::createRoundedRectangle(float width, float height, float radius) {
    sf::ConvexShape roundedRect;
    roundedRect.setPointCount(8);

    roundedRect.setPoint(0, sf::Vector2f(radius, 0));
    roundedRect.setPoint(1, sf::Vector2f(width - radius, 0));
    roundedRect.setPoint(2, sf::Vector2f(width, radius));
    roundedRect.setPoint(3, sf::Vector2f(width, height - radius));
    roundedRect.setPoint(4, sf::Vector2f(width - radius, height));
    roundedRect.setPoint(5, sf::Vector2f(radius, height));
    roundedRect.setPoint(6, sf::Vector2f(0, height - radius));
    roundedRect.setPoint(7, sf::Vector2f(0, radius));

    roundedRect.setFillColor(sf::Color::White);
    roundedRect.setOutlineThickness(3);
    roundedRect.setOutlineColor(sf::Color::Black);

    return roundedRect;
}

// Función para crear los puntos del dado
void Cube::createDots(CubeFace& face, int number) {
    face.dots.clear();
    float grid[3][3] = {
        {cubeSize / 4, cubeSize / 4},
        {cubeSize / 2, cubeSize / 2},
        {3 * cubeSize / 4, 3 * cubeSize / 4}
    };

    int layout[6][6][2] = {
        {{1, 1}},
        {{0, 0}, {2, 2}},
        {{0, 0}, {1, 1}, {2, 2}},
        {{0, 0}, {0, 2}, {2, 0}, {2, 2}},
        {{0, 0}, {0, 2}, {1, 1}, {2, 0}, {2, 2}},
        {{0, 0}, {0, 2}, {1, 0}, {1, 2}, {2, 0}, {2, 2}}
    };

    for (int i = 0; i < number; ++i) {
        sf::CircleShape dot(dotSize / 2);
        dot.setFillColor(sf::Color::Black);

        int x = layout[number - 1][i][0];
        int y = layout[number - 1][i][1];

        dot.setPosition(grid[x][0] - dotSize / 2, grid[y][1] - dotSize / 2);
        face.dots.push_back(dot);
    }
}

// Función para crear las 6 caras del dado
void Cube::createCube() {
    faces.resize(6);
    for (auto& face : faces) {
        face.face = createRoundedRectangle(cubeSize, cubeSize, cornerRadius);
    }
    for (int i = 0; i < 6; ++i) {
        createDots(faces[i], i + 1);
    }
}

// Actualiza el estado del dado mientras está rodando
void Cube::update(float elapsedTime) {

    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;

    if (isRolling) {
        if (elapsedTime < rollTime) {
            currentFace = (std::rand() % 6);
        }
        else {
            isRolling = false;
        }
    }

    sf::Vector2f lightPos(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);  // Fuente de luz
    for (auto& face : faces) {
        sf::Vector2f faceCenter = face.face.getPosition() + sf::Vector2f(cubeSize / 2, cubeSize / 2);
        float distance = std::hypot(lightPos.x - faceCenter.x, lightPos.y - faceCenter.y);
        float brightness = std::max(0.f, 255.f - distance / 2);
        face.face.setFillColor(sf::Color(static_cast<sf::Uint8>(brightness), static_cast<sf::Uint8>(brightness), static_cast<sf::Uint8>(brightness)));

    }
}

// Lanza el dado
void Cube::roll() {
    isRolling = true;
    rollTime = 2.0f;
    clock.restart();
}

// Dibuja la cara actual del dado
void Cube::draw(sf::RenderWindow& window) {
    window.draw(shadow);
    window.draw(faces[currentFace].face);
    for (auto& dot : faces[currentFace].dots) {
        window.draw(dot);
    }
}
