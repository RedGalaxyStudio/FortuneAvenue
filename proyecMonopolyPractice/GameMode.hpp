#pragma once
class GameMode
{
#ifndef GAMEMODE_HPP
#define GAMEMODE_HPP

#include <SFML/Graphics.hpp>

    class GameMode {
    public:
        GameMode(sf::RenderWindow& windowRef);

        // M�todo para actualizar el estado del bot�n seg�n la posici�n del mouse
        void update();
        void resource();
    private:
        // Ventana de renderizado
        sf::RenderWindow* window;

        sf::Sprite& sprite;
        sf::Texture& textureNormal;
        sf::Texture& textureHover;
        static sf::Sprite* lastHoveredButton;

    };

#endif // BUTTON_HPP
};

