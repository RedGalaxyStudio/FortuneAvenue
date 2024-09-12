#ifndef CINEMATIC_HPP
#define CINEMATIC_HPP

#include <SFML/Graphics.hpp>
#include <thread>   // Para manejar el hilo
#include <atomic>   // Para manejar la variable que indicar� si las texturas est�n cargadas


class Cinematic {
public:
    // Constructor
    Cinematic(sf::RenderWindow& windowRef);

    ~Cinematic();

    // M�todo para cargar recursos
    void Resource();

    // M�todo para actualizar la animaci�n
    void Update();

private:
    // Referencia a la ventana
    sf::RenderWindow& window;

    // Texturas y sprites
    sf::Texture textures[6];
    sf::Sprite SpriteFondoLogo;
    sf::Sprite spriteLogoStudio;
    sf::Sprite spriteLogoJuego;
    sf::Texture textureLogoStudio;
    sf::Texture textureLogoJuego;

    // Variables para la animaci�n
    float alpha;
    bool fadeIn;
    int currentFrame;
    float frameTime;
    float tiempoAcumuladoFondo;
    int currentTextureIndex;
    sf::IntRect frameRect;

    // Relojes para la animaci�n
    sf::Clock fadeClock;
    sf::Clock clock;
    sf::Clock fondoClock;
    // ... resto de la clase
    std::atomic<bool> texturesLoaded;   // Para saber si las texturas est�n cargadas
    std::thread textureLoaderThread;    // Hilo para cargar texturas en segundo plano
    void loadTexturesInBackground();
    // M�todo para actualizar el fondo
    void updateFondo(sf::Time deltaTime);
};

#endif // CINEMATIC_HPP