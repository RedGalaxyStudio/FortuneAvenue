#ifndef MENUP_HPP
#define MENUP_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "AudioSettings.hpp"
#include "SettingsManager.hpp" 

class menuP  : public SettingsManager {
public:
    // Constructor: inicializa la variable y la ventana
    menuP(sf::RenderWindow& windowRef);

    // Carga de recursos (texturas y sprites)
    void Resource();

    // Actualización de la animación (desvanecimiento del logotipo)
    void MenuPrincipal();

    // Método para manejar eventos
    void eventoMenuP();
    void eventoMenuO();
    // Método para dibujar (implementa según sea necesario)
    void Draw();

    void MenuJugar();
    //Ventana de opciones
    void MenuOpcion();

    void MenuSalir();

    void MenuAcercaDe();


private:
    // Ventana de renderizado
    sf::RenderWindow& window;

    SettingsManager* musicSlider;   
    SettingsManager* effectSlider;

    // Texturas y sprites para el menú
    sf::Texture textureLogoFortuneAvenue;
    sf::Sprite spriteLogoFortuneAvenue;

    sf::Texture textureAcercaDeOn;
    sf::Texture textureAcercaDeOff;
    sf::Sprite spriteAcercaDe;

    sf::Texture textureXOn;
    sf::Texture textureXOff;
    sf::Sprite spriteX;

    sf::Texture TextureBotonJugarOff;
    sf::Texture TextureBotonJugarOn;
    sf::Sprite SpriteBotonJugar;

    sf::RenderTexture renderTexture;

    sf::Texture TextureBotonOpcionesOff;
    sf::Texture TextureBotonOpcionesOn;
    sf::Sprite SpriteBotonOpciones;

    sf::Texture TextureBotonSalirOff;
    sf::Texture TextureBotonSalirOn;
    sf::Sprite SpriteBotonSalir;

    sf::Texture TextureFondoMenu;
    sf::Sprite SpriteFondoMenu;
    sf::Clock clock;
    // Sonidos
    sf::SoundBuffer HoverBuffer;
    sf::SoundBuffer ClickBuffer;
    sf::Sound HoverSound;
    sf::Sound ClickSound;
    sf::Music MenuMusicFondo;


    // Puntero al último botón que se hizo hover
    sf::Sprite* lastHoveredButton;
    sf::Shader Blur;
    // Métodos para manejar el sonido
    void playHoverSound();
    void playClickSound();

    // Métodos para manejar el hover
    void handleHover(sf::Sprite* currentButton);
    void resetLastHoveredButton(sf::Sprite* currentButton);

    sf::Vector2i mousePosition;
    sf::Vector2f mousePosFloat;

    
};

#endif // MENUP_HPP


