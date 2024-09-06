#include "FadeEffect.hpp"

namespace EffectLib {

    FadeEffect::FadeEffect(sf::Sprite& sprite, float speed)
        : sprite(sprite), alpha(0.0f), fadingIn(true), speed(speed) {}

    void FadeEffect::update(sf::Time deltaTime) {
        if (fadingIn) {
            alpha += speed * deltaTime.asSeconds();
            if (alpha >= 255.0f) {
                alpha = 255.0f;
                fadingIn = false;
            }
        }
        else {
            alpha -= speed * deltaTime.asSeconds();
            if (alpha <= 0.0f) {
                alpha = 0.0f;
                fadingIn = true;
            }
        }

        sprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
    }

}
