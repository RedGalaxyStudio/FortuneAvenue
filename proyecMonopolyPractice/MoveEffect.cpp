#include "MoveEffect.hpp"

namespace EffectLib {

    MoveEffect::MoveEffect(sf::Sprite& sprite, const sf::Vector2f& startPos, const sf::Vector2f& endPos, float speed)
        : sprite(sprite), startPos(startPos), endPos(endPos), speed(speed) {
        sprite.setPosition(startPos);
    }

    void MoveEffect::update(sf::Time deltaTime) {
        sf::Vector2f currentPos = sprite.getPosition();
        sf::Vector2f direction = endPos - startPos;
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 0.0f) {
            sf::Vector2f normalizedDirection = direction / length;
            sprite.move(normalizedDirection * speed * deltaTime.asSeconds());

            // Detener el movimiento cuando llegue al final
            if ((endPos - sprite.getPosition()).x * direction.x <= 0 &&
                (endPos - sprite.getPosition()).y * direction.y <= 0) {
                sprite.setPosition(endPos);
            }
        }
    }

}
