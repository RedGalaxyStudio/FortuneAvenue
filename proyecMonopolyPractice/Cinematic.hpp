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
    sf::Clock fadeClock;                  // Reloj para el control del desvanecimiento
    float alpha;
    bool fadeIn;
};

#endif

