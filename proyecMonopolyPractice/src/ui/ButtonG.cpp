#include "ButtonG.hpp"
#include ".././core/ResourceGlobal.hpp"
// Inicializar el puntero estático
sf::Sprite* ButtonG::lastHoveredButton = nullptr;

ButtonG::ButtonG(sf::Sprite& sprite, sf::Texture& textureNormal, sf::Texture& textureHover)
    : sprite(&sprite), textureNormal(textureNormal), textureHover(textureHover), Borde(nullptr){}

ButtonG::ButtonG(sf::Sprite& sprite, sf::Texture& textureNormal, sf::Texture& textureHover,sf::RectangleShape& borde, sf::Vector2f vectorpeque, sf::Vector2f vectorMax)
    : sprite(&sprite), textureNormal(textureNormal), textureHover(textureHover),Borde(&borde), VectorMax(vectorMax),Vectorpeque(vectorpeque){}


ButtonG::ButtonG(sf::Texture& textureNormal, sf::Texture& textureHover)
    :  textureNormal(textureNormal), textureHover(textureHover) , sprite(nullptr), Borde(nullptr) {}

void ButtonG::spriteAsig(sf::Sprite& Sprite) {

    this->sprite = &Sprite;
    
}

// Implementación del método update
void ButtonG::update(const sf::Vector2f& mousePos, sf::Cursor*& currentCursor, sf::Cursor& linkCursor, sf::Cursor& normalCursor) {
    if (sprite->getGlobalBounds().contains(mousePos)) {
        sprite->setTexture(textureHover);
        if (currentCursor == &normalCursor) { // Solo cambiar si es el cursor normal
            currentCursor = &linkCursor;
        }
        handleHover();
    }
    else {
        sprite->setTexture(textureNormal);
        resetLastHoveredButton();
    }
}

void ButtonG::Update(const sf::Vector2f& mousePos, sf::Cursor*& currentCursor, sf::Cursor& linkCursor, sf::Cursor& normalCursor) {
    if (sprite->getGlobalBounds().contains(mousePos)) {
        sprite->setTexture(textureHover);
        Borde->setSize(VectorMax);

        sf::FloatRect globalBounds = Borde->getGlobalBounds();
        Borde->setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);


        if (currentCursor == &normalCursor) { // Solo cambiar si es el cursor normal
            currentCursor = &linkCursor;
        }
        handleHover();
    }
    else {
        Borde->setSize(Vectorpeque);
        sf::FloatRect globalBounds = Borde->getGlobalBounds();
        Borde->setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);


        sprite->setTexture(textureNormal);
        resetLastHoveredButton();
    }
}

void ButtonG::resetLastHoveredButton() {
    if (lastHoveredButton == sprite) {
        lastHoveredButton = nullptr;
    }
}

void ButtonG::handleHover() {
    if (lastHoveredButton != sprite) {
        playHoverSound();
        lastHoveredButton = sprite;
    }
}

void ButtonG::playHoverSound() {
    if (HoverSound.getStatus() != sf::Sound::Playing) {
        HoverSound.play();
    }
}
