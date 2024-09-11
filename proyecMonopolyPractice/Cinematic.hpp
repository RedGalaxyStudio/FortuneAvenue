#ifndef CINEMATIC_HPP
#define CINEMATIC_HPP

#include <SFML/Graphics.hpp>

class Cinematic {
public:
    Cinematic(sf::RenderWindow& window);  // Constructor que acepta una ventana por referencia
    void Resource();                      // Carga de recursos
    void Update();                        // Actualización de la animación
    void Draw();                          // Dibujado de elementos (si es necesario)

private:
    sf::Texture textureLogoStudio;        // Textura del logotipo
    sf::Sprite spriteLogoStudio;          // Sprite para el logotipo
    sf::Texture textureLogoJuego;         // Textura del logotipo
    sf::Sprite spriteLogoJuego;           // Sprite para el logotipo
    sf::Font fuente;                      // Fuente para la lluvia de caracteres
    sf::RenderWindow& window;             // Referencia a la ventana de renderizado
    sf::Clock clock;                      // Reloj para controlar el tiempo de la animación
    sf::Clock controlframe;
    sf::Clock fadeClock;                  // Reloj para el control del desvanecimiento
    sf::Texture TextureFondoLogo;         // Textura del fondo
    sf::Sprite SpriteFondoLogo;

    float alpha;
    bool fadeIn;

    // Nuevas variables para el control de la animación de spritesheet
    int currentFrame;                     // Frame actual de la animación
    float tiempoAcumulado;                // Acumulador de tiempo para la animación de frames
    const int frameWidth = 1280;          // Ancho de cada frame
    const int frameHeight = 720;          // Altura de cada frame
    const int columns = 6;                // Columnas del spritesheet
    const int rows = 12;                  // Filas del spritesheet
    const int totalFrames = columns * rows;  // Total de frames
    const float fps = 12.0f;              // Frames por segundo
    const float frameTime = 1.0f / fps;   // Tiempo por frame (para la animación del spritesheet)
};

#endif
