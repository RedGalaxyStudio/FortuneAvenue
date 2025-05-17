#ifndef BUTTONG_HPP
#define BUTTONG_HPP

#include <SFML/Graphics.hpp>
#include "GradientText.h"
class ButtonG {
public:
    ButtonG(sf::Sprite& sprite, sf::Texture& textureNormal, sf::Texture& textureHover);
    ButtonG(sf::Sprite& sprite, sf::Texture& textureNormal, sf::Texture& textureHover, sf::RectangleShape& borde, sf::Vector2f vectorpeque, sf::Vector2f vectorMax);

    ButtonG( sf::Texture& textureNormal, sf::Texture& textureHover);

    void update(const sf::Vector2f& mousePos, sf::Cursor*& currentCursor, sf::Cursor& linkCursor, sf::Cursor& normalCursor,GradientText *TextButton=nullptr);
    void Update(const sf::Vector2f& mousePos, sf::Cursor*& currentCursor, sf::Cursor& linkCursor, sf::Cursor& normalCursor,bool Selec);
    void handleHover(sf::Sprite& currentButton);
    void resetLastHoveredButton();
    void handleHover();
    void playHoverSound();
    void asignarSprite(sf::Sprite& Sprite);
private:
    sf::Sprite* sprite;
    sf::RectangleShape *bordeMapaHover;
    sf::Vector2f Vectorpeque;
    sf::Vector2f VectorMax;
    sf::Texture& textureNormal;
    sf::Texture& textureHover;
    static sf::Sprite* lastHoveredButton;

};

#endif 
