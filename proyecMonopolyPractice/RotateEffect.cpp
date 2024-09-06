#include "RotateEffect.hpp"

namespace EffectLib {

    RotateEffect::RotateEffect(sf::Sprite& sprite, float speed)
        : sprite(sprite), angle(0.0f), speed(speed) {}

    void RotateEffect::update(sf::Time deltaTime) {
        angle += speed * deltaTime.asSeconds();
        sprite.setRotation(angle);
    }

}
