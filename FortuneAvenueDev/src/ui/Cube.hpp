#ifndef CUBE_HPP
#define CUBE_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class UICube {
public:
    UICube(float size, float dotSize, float cornerRadius, sf::Vector2f position);

    void roll();  // Lanza el dado
    void update(float elapsedTime);  // Actualiza el estado del dado durante el lanzamiento
    void draw(sf::RenderWindow& window);  // Dibuja la cara actual del dado

private:
    struct CubeFace {
        sf::ConvexShape face;
        std::vector<sf::CircleShape> dots;
    };

    std::vector<CubeFace> faces;
    float cubeSize;
    float dotSize;
    float cornerRadius;
    sf::Vector2f position;
    sf::RectangleShape shadow;
    int currentFace;
    bool isRolling;
    float rollTime;
    sf::Clock clock;

    sf::ConvexShape createRoundedRectangle(float width, float height, float radius);
    void createDots(CubeFace& face, int number);
    void createCube();
};

#endif // CUBE_HPP
