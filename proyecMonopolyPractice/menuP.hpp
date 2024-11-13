#ifndef MENUP_HPP
#define MENUP_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "SettingsManager.hpp" 
#include <winsock2.h>
#include <Windows.h>
#include "ObjetosGlobal.hpp"
#include "GameMode.hpp"


class GameMode;

class menuP : public SettingsManager {
public:

    menuP();

    void setWindow(sf::RenderWindow& windowRef);
 
    void Resource();

    void Inicializar();
    void MenuJugar();

    void MenuPrincipal();

    void eventoMenuP();

    void eventoMenuO();


    void MenuOpcion();
    void MenuSalir();
    void MenuAcercaDe();
    void ValidarUser();
private:

   

    sf::RenderWindow* window;

    
    bool SesionValida;
    SettingsManager* musicSlider;
    SettingsManager* effectSlider;


    sf::Texture textureLogoFortuneAvenue;
    sf::Sprite spriteLogoFortuneAvenue;

    sf::Texture textureAcercaDeOn;
    sf::Texture textureAcercaDeOff;
    sf::Sprite spriteAcercaDe;


    sf::Texture TextureBotonJugarOff;
    sf::Texture TextureBotonJugarOn;
    sf::Sprite SpriteBotonJugar;


    sf::Texture TextureBotonOpcionesOff;
    sf::Texture TextureBotonOpcionesOn;
    sf::Sprite SpriteBotonOpciones;

    sf::Texture TextureBotonSalirOff;
    sf::Texture TextureBotonSalirOn;
    sf::Sprite SpriteBotonSalir;

    sf::Sprite SpriteFondoMenu;

    sf::Clock clock;



    

    sf::Texture TextureConfirmarSalir;
    sf::Sprite SpriteConfirmarSalir;


    sf::Font Fuente;
    sf::Text TextAcercaDe;
    sf::Sprite renderedSprite;

    sf::Music MenuMusicFondo;

    sf::Sprite* lastHoveredButton;
    sf::Shader Blur;
   
    sf::Vector2i mousePosition;
    sf::Vector2f mousePosFloat;

};

#endif 