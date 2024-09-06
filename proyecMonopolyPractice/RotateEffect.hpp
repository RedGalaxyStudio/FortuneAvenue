#ifndef ROTATE_EFFECT_HPP
#define ROTATE_EFFECT_HPP

#include <SFML/Graphics.hpp>

namespace EffectLib {

    class RotateEffect {
    public:
        RotateEffect(sf::Sprite& sprite, float speed = 90.0f);  // 90 grados por segundo por defecto
        void update(sf::Time deltaTime);

    private:
        sf::Sprite& sprite;
        float angle;
        float speed;
    };

}

#endif // ROTATE_EFFECT_HPP
