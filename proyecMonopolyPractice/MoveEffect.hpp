#ifndef MOVE_EFFECT_HPP
#define MOVE_EFFECT_HPP

#include <SFML/Graphics.hpp>

namespace EffectLib {

    class MoveEffect {
    public:
        MoveEffect(sf::Sprite& sprite, const sf::Vector2f& startPos, const sf::Vector2f& endPos, float speed = 100.0f);
        void update(sf::Time deltaTime);

    private:
        sf::Sprite& sprite;
        sf::Vector2f startPos;
        sf::Vector2f endPos;
        float speed;
    };

}

#endif // MOVE_EFFECT_HPP
