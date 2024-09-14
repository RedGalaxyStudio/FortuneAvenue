#ifndef MENUP_HPP
#define MENUP_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class menuP {
public:
    // Constructor: inicializa la variable y la ventana
    menuP(sf::RenderWindow& windowRef);

    // Carga de recursos (texturas y sprites)
    void Resource();

    // Actualizaci�n de la animaci�n (desvanecimiento del logotipo)
    void Update();

    // M�todo para manejar eventos
    void evento();

    // M�todo para dibujar (implementa seg�n sea necesario)
    void Draw();

private:
    // Ventana de renderizado
    sf::RenderWindow& window;

    // Texturas y sprites para el men�
    sf::Texture textureLogoFortuneAvenue;
    sf::Sprite spriteLogoFortuneAvenue;

    sf::Texture TextureBotonJugarOff;
    sf::Texture TextureBotonJugarOn;
    sf::Sprite SpriteBotonJugar;

    sf::Texture TextureBotonOpcionesOff;
    sf::Texture TextureBotonOpcionesOn;
    sf::Sprite SpriteBotonOpciones;

    sf::Texture TextureBotonSalirOff;
    sf::Texture TextureBotonSalirOn;
    sf::Sprite SpriteBotonSalir;

    sf::Texture TextureFondoMenu;
    sf::Sprite SpriteFondoMenu;

    // Sonidos
    sf::SoundBuffer HoverBuffer;
    sf::SoundBuffer ClickBuffer;
    sf::Sound HoverSound;
    sf::Sound ClickSound;

    // Puntero al �ltimo bot�n que se hizo hover
    sf::Sprite* lastHoveredButton;

    // M�todos para manejar el sonido
    void playHoverSound();
    void playClickSound();

    // M�todos para manejar el hover
    void handleHover(sf::Sprite* currentButton);
    void resetLastHoveredButton(sf::Sprite* currentButton);
};

#endif // MENUP_HPP


