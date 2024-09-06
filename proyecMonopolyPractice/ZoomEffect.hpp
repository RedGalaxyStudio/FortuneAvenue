#ifndef ZOOM_EFFECT_HPP
#define ZOOM_EFFECT_HPP

#include <SFML/Graphics.hpp>

namespace EffectLib {

    class ZoomEffect {
    public:
        ZoomEffect(sf::Sprite& sprite, float minScale = 1.0f, float maxScale = 2.0f, float speed = 1.0f);
        void update(sf::Time deltaTime);

    private:
        sf::Sprite& sprite;
        float scale;
        bool zoomingIn;
        float minScale;
        float maxScale;
        float speed;
    };

}

#endif // ZOOM_EFFECT_HPP
