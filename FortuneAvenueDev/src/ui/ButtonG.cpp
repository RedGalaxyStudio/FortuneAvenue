#include "ButtonG.hpp"

#include ".././core/ResourceGlobal.hpp"
// Inicializar el puntero est�tico
sf::Sprite* ButtonG::lastHoveredButton = nullptr;

ButtonG::ButtonG(sf::Sprite& sprite, sf::Texture& textureNormal, sf::Texture& textureHover)
    : sprite(&sprite), bordeMapaHover(nullptr), textureNormal(textureNormal), textureHover(textureHover){}

ButtonG::ButtonG(sf::Sprite& sprite, sf::Texture& textureNormal, sf::Texture& textureHover,sf::RectangleShape& borde, sf::Vector2f vectorpeque, sf::Vector2f vectorMax)
    : sprite(&sprite),bordeMapaHover(&borde),Vectorpeque(vectorpeque),VectorMax(vectorMax), textureNormal(textureNormal), textureHover(textureHover){}


ButtonG::ButtonG(sf::Texture& textureNormal, sf::Texture& textureHover)
    : sprite(nullptr), bordeMapaHover(nullptr), textureNormal(textureNormal), textureHover(textureHover)  {}

void ButtonG::asignarSprite(sf::Sprite& Sprite){
    this->sprite = &Sprite;
}

// Implementaci�n del m�todo update
void ButtonG::update(const sf::Vector2f& mousePos, sf::Cursor*& currentCursor, sf::Cursor& linkCursor, sf::Cursor& normalCursor,GradientText *TextButton) {

    if (sprite->getGlobalBounds().contains(mousePos)) {
        sprite->setTexture(textureHover);
        if (currentCursor == &normalCursor) { // Solo cambiar si es el cursor normal
            currentCursor = &linkCursor;
        }
        if(TextButton){
            TextButton->update(true);
        }
        handleHover();
    }
    else {
        sprite->setTexture(textureNormal);
        if(TextButton){
            TextButton->update(false);
        }
        resetLastHoveredButton();
    }
}

void ButtonG::Update(const sf::Vector2f& mousePos, sf::Cursor*& currentCursor, sf::Cursor& linkCursor, sf::Cursor& normalCursor, bool Selec) {

    if (Selec) {
        return;
    }

    if (sprite->getGlobalBounds().contains(mousePos)) {
        sprite->setTexture(textureHover);
        bordeMapaHover->setSize(VectorMax);

        sf::FloatRect globalBounds = bordeMapaHover->getGlobalBounds();
        bordeMapaHover->setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

        if (currentCursor == &normalCursor) { // Solo cambiar si es el cursor normal
            currentCursor = &linkCursor;
        }
        handleHover();
    }
    else {
        bordeMapaHover->setSize(Vectorpeque);
        sf::FloatRect globalBounds = bordeMapaHover->getGlobalBounds();
        bordeMapaHover->setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);


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
