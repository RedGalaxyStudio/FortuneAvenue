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
    sf::Clock clock;                      // Reloj para medir el tiempo
    sf::Clock fadeClock;                  // Reloj para el efecto de desvanecimiento
    sf::Texture textureLogoStudio;        // Textura del logotipo
    sf::Sprite spriteLogoStudio;          // Sprite para el logotipo
    sf::RenderWindow& window;             // Referencia a la ventana de renderizado
};

#endif
