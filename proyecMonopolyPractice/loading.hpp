#ifndef LOADING_HPP
#define LOADING_HPP

#include <SFML/Graphics.hpp>
#include <thread>   
#include <atomic>   


class LoadingScreen {
public:
    LoadingScreen(sf::RenderWindow& windowRef);
    ~LoadingScreen();

    void LoadResources();
    void Update();

private:
    sf::RenderWindow& window;

    sf::Texture dice[8];
    sf::Texture textureFondo;
    sf::Sprite spriteBackground;
    sf::Sprite SpriteFondo;

    sf::Font font;
    sf::Text TextCargando;
   
    float beta;
    bool fade;
    int frame;
    float frametime;
    float timeAcumulado;
    int currentDiceIndex;

    sf::Clock fadeclock;
    sf::Clock animationClock;
    sf::Clock frameClock;

    std::atomic<bool> loadedTextures;
    std::thread loadedTexturesThread;

    void loadBackground();
    void updateDice(sf::Time deltaTiempo);
};

#endif