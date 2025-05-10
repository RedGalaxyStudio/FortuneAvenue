#ifndef CINEMATIC_HPP
#define CINEMATIC_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <thread>   
#include <atomic>   

class Cinematic {
public:
   
    explicit Cinematic(sf::RenderWindow& windowRef);
    ~Cinematic();
    void Resource();
    void Update();

private:

    sf::RenderWindow& window;
    sf::Texture textures[6];
    sf::Sprite SpriteFondoLogo;
    sf::Sprite spriteLogoStudio;
    sf::Sprite spriteLogoJuego;
    sf::Texture textureLogoStudio;
    sf::Texture textureLogoJuego;

    float alpha;
    bool fadeIn;
    int currentFrame;
    float frameTime;
    float tiempoAcumuladoFondo;
    int currentTextureIndex;
    bool soundOne;
    sf::IntRect frameRect;

    sf::SoundBuffer FondoBuffer;
    sf::Sound FondoSound;
    

    sf::Clock fadeClock;
    sf::Clock clock;
    sf::Clock fondoClock;

    std::atomic<bool> texturesLoaded;  
    std::thread textureLoaderThread;    
    void loadTexturesInBackground();
 
    void updateFondo(sf::Time deltaTime);
};

#endif 