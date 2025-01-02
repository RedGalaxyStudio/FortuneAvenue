#ifndef MENUP_HPP
#define MENUP_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "SettingsManager.hpp" 
#include "ObjetosGlobal.hpp"
#include "MultiplayerGame.hpp"

class MultiplayerGame;


class menuP : public SettingsManager {
public:

    menuP();
    void Resource();
    void setWindow(sf::RenderWindow& windowRef);
    void MenuPrincipal();
    void MenuOpcion();

    void MenuSalir();
private:
    

    void Inicializar();
    void editPerfil();
    void MenuJugar();


  

    void eventoMenuP();

    void eventoMenuO();
 
    void instruccionesGame();
    
    void MenuAcercaDe();
    void ValidarUser();
    sf::RectangleShape editorPerfil;

    sf::RenderWindow* window;

    
    bool SesionValida;
    SettingsManager* musicSlider;
    SettingsManager* effectSlider;


    sf::Texture textureLogoFortuneAvenue;
    sf::Sprite spriteLogoFortuneAvenue;


    sf::Texture Textureflechainstder;
    sf::Sprite flechainstder;

    sf::Texture Textureflechainstizq;
    sf::Sprite flechainstizq;

    sf::Texture textureInstruccionesOn;
    sf::Texture textureInstruccionesOff;
    sf::Sprite spriteInstrucciones;

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

    

    sf::Sprite* lastHoveredButton;
    sf::Shader Blur;
   
    sf::Vector2i mousePosition;
    sf::Vector2f mousePosFloat;

};

#endif 