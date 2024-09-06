#ifndef MENUP_HPP
#define MENUP_HPP

#include <SFML/Graphics.hpp>

class menuP {
public:
    menuP(sf::RenderWindow& window); // Constructor
    void Resource();                 // Carga de recursos
    void Update();                   // Actualizaci�n de la animaci�n
    void Draw();                     // Dibujado de elementos (si es necesario)

private:
    sf::RenderWindow& window;        // Referencia a la ventana de renderizado
    sf::Texture textureLogoFortuneAvenue;  // Textura del logotipo
    sf::Sprite spriteLogoFortuneAvenue;    // Sprite para el logotipo
    sf::Texture TexturaBotonJugarOff;         // Textura del bot�n Jugar
    sf::Sprite SpriteBotonJugar;           // Sprite para el bot�n Jugar
    sf::Texture TexturaBotonOpcionesOff;      // Textura del bot�n Opciones
    sf::Sprite SpriteBotonOpcion;          // Sprite para el bot�n Opciones
    sf::Texture TexturaBotonSalirOff;
    sf::Texture texturaBotonJugarOn;// Textura del bot�n Salir
    sf::Sprite SpriteBotonSalir;           // Sprite para el bot�n Salir
};

#endif

