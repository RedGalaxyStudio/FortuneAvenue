#ifndef BUTTONG_HPP
#define BUTTONG_HPP

#include <SFML/Graphics.hpp>

class ButtonG {
public:
    ButtonG(sf::Sprite& sprite, sf::Texture& textureNormal, sf::Texture& textureHover);

    void update(const sf::Vector2f& mousePos, sf::Cursor*& currentCursor, sf::Cursor& linkCursor, sf::Cursor& normalCursor);
    void handleHover(sf::Sprite& currentButton);
    void resetLastHoveredButton();
    void handleHover();
    void playHoverSound();
private:
    sf::Sprite& sprite;
    sf::Texture& textureNormal;
    sf::Texture& textureHover;
    static sf::Sprite* lastHoveredButton;

};

#endif 
