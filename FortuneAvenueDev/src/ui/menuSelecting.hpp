#ifndef MENUSELECTING_HPP
#define MENUSELECTING_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class menuSelecting : public sf::Drawable
{
public:
    explicit menuSelecting(sf::RenderWindow& windowRef, std::vector<std::string>InfoMenu);
    void setFont(sf::Font font);
    void setSize(float Size);
    void setColors(sf::Color color);
    void setPosition(sf::Vector2f Position);
    void event(const sf::Event);

    void setVector(std::vector<std::string>InfoMenu);
    std::string getSelected();
    bool haschanged();
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    sf::RenderWindow& window;
    std::vector<sf::Text> Menu;
    sf::Text Selection;
    float size;
    sf::RectangleShape backgroum;
    sf::Vector2f position;
    float MaxSizeback;
    sf::Font fontC;
    sf::Color Color;
    int SelecIdio=0;
    bool open = false;
    bool changed = false;
};

#endif // SETTINGSMANAGER_HPP
