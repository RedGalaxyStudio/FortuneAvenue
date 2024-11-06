#ifndef MENSAGE_BOX_HPP
#define MENSAGE_BOX_HPP

#include <SFML/Graphics.hpp>
#include <string>

class MensageBox {
private:
    sf::RectangleShape Center, Bottom, Top;
    sf::CircleShape topLeft, topRight, bottomLeft, bottomRight;
    sf::Text message;
    sf::Font font;
    sf::Clock clock;
    sf::Vector2f targetPosition;
    bool isVisible;
    bool isFading;
    float startX;
    sf::ConvexShape roundedBox;
    float startY;

public:
    MensageBox(const std::string& text, const sf::Font& font, unsigned int fontSize);
    void centerText();
    void showMessage();
    void update();
    void setupRoundedBox();
    void draw(sf::RenderWindow& window);
};

#endif 

