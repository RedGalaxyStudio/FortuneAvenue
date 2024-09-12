#ifndef CINEMATIC_HPP
#define CINEMATIC_HPP

#include <SFML/Graphics.hpp>

class Cinematic {
public:
    // Constructor
    Cinematic(sf::RenderWindow& windowRef);

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

    // Método para actualizar el fondo
    void updateFondo(sf::Time deltaTime);
};

#endif // CINEMATIC_HPP
