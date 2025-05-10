#ifndef MENUSWICHT_HPP
#define MENUSWICHT_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class menuswicht : public sf::Drawable
{
public:
    explicit menuswicht(sf::RenderWindow& windowRef, sf::Vector2f Position);
    void setFont(sf::Font font);
    void setSize(float Size);
    void setColors(sf::Color color);
    void setPosition(sf::Vector2f Position);
    void event(const sf::Event);
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    void moveThumb(float mouseX);
    float clamp(float value, float min, float max) const;
    sf::Vector2f sizeFilledBar;
    sf::Vector2f thumbPosition;
    sf::ConvexShape capsule;
    sf::RenderWindow& window;
    std::vector<sf::Text> Menu;
    sf::Vector2i mousePos;
    sf::Text Selection;
    float size;
    bool isDragging;
    float radius = 15.f;
    sf::RectangleShape backgroum;
    sf::Vector2f position;
    float MaxSizeback;
    sf::Color Color;
    int SelecIdio=0;
    bool On = false;
    sf::CircleShape backIzqCir, backDerCir, IzqCir, DerCir,CirSelec;
};

#endif 
