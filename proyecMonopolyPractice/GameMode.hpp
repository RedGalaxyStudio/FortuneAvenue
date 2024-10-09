#ifndef GAMEMODE_HPP
#define GAMEMODE_HPP

#include <SFML/Graphics.hpp>

    class GameMode {
    public:
        GameMode(sf::RenderWindow* windowRef);
        
        // M�todo para actualizar el estado del bot�n seg�n la posici�n del mouse
        void update();
        void resource();
        void moverSprite(sf::Sprite& sprite, int resultadoDado);
    private:
        // Ventana de renderizado
        sf::RenderWindow* window;
        std::vector<sf::Vector2f> casillas;
        int posicionActual;
        sf::Vector2i mousePosition;
        sf::Vector2f mousePosFloat;
        int resultadoDado;
        sf::Texture piecesTextures;
        sf::Sprite pieces;

        
        sf::Texture TextureMapa;
        sf::Sprite spriteMapa;
    };
#endif