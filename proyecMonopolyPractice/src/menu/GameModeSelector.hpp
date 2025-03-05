#ifndef GAMEMODESELECTOR_HPP
#define GAMEMODESELECTOR_HPP

#include "../core/ResourceGlobal.hpp"
#include <SFML/Graphics.hpp>

class GameModeSelector  {
public:

    GameModeSelector (sf::RenderWindow& win);
    void updatejoinRoom();
    void resource();

    void update();

private:
    sf::RenderWindow* window;
    sf::Texture texturaFondo;
    sf::Sprite spriteFondo;
    bool isWebViewOpen;
    bool sesionValida;
    bool Valida;
    sf::Texture TextureOfflineOff;
    sf::Texture TextureOfflineOn;
    sf::Texture TextureOnlineOff;
    sf::Texture TextureOnlineOn;
    sf::Texture TextureUnirse;
    sf::Clock LimTimeBotton;
    sf::Text enunciado;
    sf::Sprite SpriteOffline;
    sf::Sprite SpriteOnline;

    sf::Vector2i mousePosition;
    sf::Vector2f mousePosFloat;

};

#endif 


