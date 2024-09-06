#ifndef MENUP_HPP
#define MENUP_HPP

#include <SFML/Graphics.hpp>

class menuP {
public:
    menuP(sf::RenderWindow& window); // Constructor
    void Resource();                 // Carga de recursos
    void Update();                   // Actualización de la animación
    void Draw();                     // Dibujado de elementos (si es necesario)

private:
    sf::RenderWindow& window;        // Referencia a la ventana de renderizado
    sf::Texture textureLogoFortuneAvenue;  // Textura del logotipo
    sf::Sprite spriteLogoFortuneAvenue;    // Sprite para el logotipo
    sf::Texture TexturaBotonJugarOff;         // Textura del botón Jugar
    sf::Sprite SpriteBotonJugar;           // Sprite para el botón Jugar
    sf::Texture TexturaBotonOpcionesOff;      // Textura del botón Opciones
    sf::Sprite SpriteBotonOpcion;          // Sprite para el botón Opciones
    sf::Texture TexturaBotonSalirOff;
    sf::Texture texturaBotonJugarOn;// Textura del botón Salir
    sf::Sprite SpriteBotonSalir;           // Sprite para el botón Salir
};

#endif

