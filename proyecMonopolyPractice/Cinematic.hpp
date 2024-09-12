#ifndef CINEMATIC_HPP
#define CINEMATIC_HPP

#include <SFML/Graphics.hpp>
#include <thread>   // Para manejar el hilo
#include <atomic>   // Para manejar la variable que indicará si las texturas están cargadas


class Cinematic {
public:
    // Constructor
    Cinematic(sf::RenderWindow& windowRef);

    ~Cinematic();

    // Método para cargar recursos
    void Resource();

    // Método para actualizar la animación
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

    // Variables para la animación
    float alpha;
    bool fadeIn;
    int currentFrame;
    float frameTime;
    float tiempoAcumuladoFondo;
    int currentTextureIndex;
    sf::IntRect frameRect;

    // Relojes para la animación
    sf::Clock fadeClock;
    sf::Clock clock;
    sf::Clock fondoClock;
    // ... resto de la clase
    std::atomic<bool> texturesLoaded;   // Para saber si las texturas están cargadas
    std::thread textureLoaderThread;    // Hilo para cargar texturas en segundo plano
    void loadTexturesInBackground();
    // Método para actualizar el fondo
    void updateFondo(sf::Time deltaTime);
};

#endif // CINEMATIC_HPP