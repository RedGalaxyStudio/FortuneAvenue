#include "ZoomEffect.hpp"

namespace EffectLib {

    ZoomEffect::ZoomEffect(sf::Sprite& sprite, float minScale, float maxScale, float speed)
        : sprite(sprite), scale(minScale), zoomingIn(true), minScale(minScale), maxScale(maxScale), speed(speed) {
        sprite.setScale(minScale, minScale);
    }

    void ZoomEffect::update(sf::Time deltaTime) {
        if (zoomingIn) {
            scale += speed * deltaTime.asSeconds();
            if (scale >= maxScale) {
                scale = maxScale;
                zoomingIn = false;
            }
        }
        else {
            scale -= speed * deltaTime.asSeconds();
            if (scale <= minScale) {
                scale = minScale;
                zoomingIn = true;
            }
        }

        sprite.setScale(scale, scale);
    }

}

