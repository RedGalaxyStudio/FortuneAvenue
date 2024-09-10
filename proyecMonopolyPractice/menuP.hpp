#ifndef MENUP_HPP
#define MENUP_HPP


#include <SFML/Graphics.hpp>

#include <SFML/Audio.hpp>

class menuP {
public:
    menuP(sf::RenderWindow& window); // Constructor
    void Resource();                 // Carga de recursos
    void Update();
    void evento();  // Actualización de la animación
    void Draw();                   // Dibujado de elementos (si es necesario)

private:
    sf::RenderWindow& window;        // Referencia a la ventana de renderizado
    sf::Texture textureLogoFortuneAvenue;  // Textura del logotipo
    sf::Sprite spriteLogoFortuneAvenue;    // Sprite para el logotipo
    sf::Texture TextureBotonJugarOff;         // Textura del botón Jugar
    sf::Sprite SpriteBotonJugar;           // Sprite para el botón Jugar
    sf::Texture TextureBotonOpcionesOff;      // Textura del botón Opciones
    sf::Sprite SpriteBotonOpciones;          // Sprite para el botón Opciones
    sf::Texture TextureBotonSalirOff;
    sf::Sprite SpriteBotonSalir;  // Sprite para el botón Salir
    sf::Texture TextureBotonJugarOn;
    sf::Texture TextureBotonOpcionesOn;
    sf::Texture TextureBotonSalirOn;
    sf::Texture TextureFondoMenu;
    sf::Sprite SpriteFondoMenu;
    sf::SoundBuffer HoverBuffer;
    sf::Sound HoverSound;
    sf::SoundBuffer ClickBuffer;
    sf::Sound ClickSound;
    void playHoverSound();
    void playClickSound();
};

#endif

