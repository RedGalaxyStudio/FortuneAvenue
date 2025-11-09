#ifndef MENUP_HPP
#define MENUP_HPP

#include <SFML/Graphics.hpp>
#include "../settings/SettingsManager.hpp"
#include "../ui/menuSelecting.hpp"
#include "../network/Client.hpp"
#include "ResourceLoader.h"

class Client;
class GradientText;
class menuP{
public:

    menuP();
    ~menuP();
    void Resource();
    void setWindow(sf::RenderWindow& windowRef);
    void MenuPrincipal();
    void MenuOpcion(bool fon);

    void MenuSalir(Client* client);
private:


    void Inicializar();
    void editPerfil();
    void MenuJugar();




    void eventoMenuP(GradientText &ButtonSalirM,GradientText &ButtonOpcionesM,GradientText &ButtonJugarM,GradientText &ButtonAcercaDe );


    void instruccionesGame();

    void MenuAcercaDe();
    void ValidarUser();
    std::map<sf::Keyboard::Key, int> keyToShaderIndex = {
        {sf::Keyboard::Num1, 0},
        {sf::Keyboard::Num2, 1},
        {sf::Keyboard::Num3, 2},
        {sf::Keyboard::Num4, 3},
        {sf::Keyboard::Num5, 4},
        {sf::Keyboard::Num6, 5},
        {sf::Keyboard::Num7, 6},
        {sf::Keyboard::Num8, 7},
        {sf::Keyboard::Num9, 8},
        {sf::Keyboard::Num0, 9}, // tecla 0 para shader 10
        {sf::Keyboard::Q, 10},
        {sf::Keyboard::W, 11},
        {sf::Keyboard::E, 12},
        {sf::Keyboard::R, 13},
        {sf::Keyboard::T, 14},
        {sf::Keyboard::Y, 15},
        {sf::Keyboard::U, 16},
        {sf::Keyboard::I, 17},
        {sf::Keyboard::O, 18},
        {sf::Keyboard::P, 19}
    };
    int current = 0;

    sf::RenderWindow* window;


    bool SesionValida;
    SettingsManager* musicSlider;
    SettingsManager* effectSlider;
	menuSelecting* SelectingIdiome;
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

    sf::Texture TextureEditButton;
    sf::Sprite spriteEditButton;

    sf::Texture TextureBotonJugarOff;
    sf::Texture TextureBotonJugarOn;
    sf::Sprite SpriteBotonJugar;


    sf::Texture TextureBotonOpcionesOff;
    sf::Texture TextureBotonOpcionesOn;
    sf::Sprite SpriteBotonOpciones;

    sf::Texture TextureBotonSiOff;
    sf::Texture TextureBotonSiOn;
    sf::Sprite SpriteBotonSi;

    sf::Texture TextureBotonNoOff;
    sf::Texture TextureBotonNoOn;
    sf::Sprite SpriteBotonNo;

    sf::Texture TextureBotonSalirOff;
    sf::Texture TextureBotonSalirOn;
    sf::Sprite SpriteBotonSalir;

    sf::Sprite SpriteFondoMenu;

    sf::Clock clock;

    sf::Texture TextureConfirmarSalir;

    sf::Texture TextureConfirmarSalirSala;

    sf::Texture TextureConfirmarSalirPartida;

    sf::Sprite SpriteConfirmarSalir;


    sf::Font Fuente;
    sf::Text TextAcercaDe;
    sf::Sprite renderedSprite;



    sf::Sprite* lastHoveredButton;
    sf::Shader Blur;
   
    sf::Vector2i mousePosition;
    sf::Vector2f mousePosFloat;

    sf::Font fontMenu;
    ResourceLoader* resourceLoad;

};


#endif 

