#ifndef FADEEFFECT_HPP
#define FADEEFFECT_HPP

#include <SFML/Graphics.hpp>

namespace EffectLib {

    class FadeEffect {
    public:
        FadeEffect(sf::Sprite& sprite, float speed);
        void update(sf::Time deltaTime);

    private:
        sf::Sprite& sprite;
        float alpha;
        bool fadingIn;
        float speed;
    };

}

#endif
