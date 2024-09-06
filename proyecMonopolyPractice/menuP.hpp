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
    sf::Sprite SpriteBotonOpciones;          // Sprite para el bot�n Opciones
    sf::Texture TexturaBotonSalirOff;
    sf::Sprite SpriteBotonSalir;  // Sprite para el bot�n Salir
    sf::Texture TexturaBotonJugarOn;
    sf::Texture TexturaBotonOpcionesOn;
    sf::Texture TexturaBotonSalirOn;
};

#endif

