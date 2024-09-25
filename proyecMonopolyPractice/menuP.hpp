#ifndef MENUP_HPP
#define MENUP_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "SettingsManager.hpp" 
#include "WebViewManager.hpp"
#include <Windows.h>
#include "ObjetosGlobal.hpp"

class WebViewManager;

class menuP : public SettingsManager {
public:
    // Constructor: inicializa la variable y la ventana
    menuP();

    void setWindow(sf::RenderWindow& windowRef);
    // Carga de recursos (texturas y sprites)
    void Resource();

    // Actualizaci�n de la animaci�n (desvanecimiento del logotipo)
    void MenuPrincipal();

    // M�todo para manejar eventos
    void eventoMenuP();

    void eventoMenuO();
    // M�todo para dibujar (implementa seg�n sea necesario)

    //void updateButtonState(sf::Sprite& buttonSprite, const sf::Texture& hoverTexture, const sf::Texture& defaultTexture);
    //void handleCursorChange();
    void MenuJugar();
    void OpenWebView();
    void CloseWebView(bool Vali);
    //Ventana de opciones
    void MenuOpcion();
    void MenuSalir();
    void MenuAcercaDe();
    void ValidarUser();
private:

    HWND hwnd;
    WebViewManager* webviewManager;
    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    bool isWebViewOpen;

    // Ventana de renderizado
    sf::RenderWindow* window;

    sf::Text Sesion;
    bool SesionValida;
    SettingsManager* musicSlider;
    SettingsManager* effectSlider;

    // Texturas y sprites para el men�
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

    sf::Texture TextureBotonSiOn;
    sf::Texture TextureBotonSiOff;
    sf::Sprite SpriteBotonSi;

    sf::Texture TextureBotonNoOn;
    sf::Texture TextureBotonNoOff;
    sf::Sprite SpriteBotonNo;

    sf::Font Fuente;
    sf::Text TextAcercaDe;
    sf::Sprite renderedSprite;

    sf::RectangleShape overlay;
    // Sonidos
    sf::Music MenuMusicFondo;

    // Puntero al �ltimo bot�n que se hizo hover
    sf::Sprite* lastHoveredButton;
    sf::Shader Blur;
   
    

    // M�todos para manejar el hover

    sf::Vector2i mousePosition;
    sf::Vector2f mousePosFloat;

};

#endif // MENUP_HPP
