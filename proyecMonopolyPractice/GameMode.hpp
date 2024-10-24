#ifndef GAMEMODE_HPP
#define GAMEMODE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <thread>
#include <atomic>
#include <windows.h> // Necesario para HRESULT y COM
#include "Client.hpp"
#include "Globals.hpp"
<<<<<<< HEAD


    class GameMode {
    public:
        GameMode(sf::RenderWindow* windowRef);
       
        
        // M�todo para actualizar el estado del bot�n seg�n la posici�n del mouse
        void update();
        void resource();
        void moverSprite(sf::Sprite& sprite, int resultadoDado);
=======
#include "WindowClass.h"
#include "Ruleta.hpp"
#include "MovePieces.hpp"

//class MovePieces;
    class GameMode{
    public:
        GameMode(sf::RenderWindow& win);
 
        void resource();
   
        void update();
        void Event();
        void DrawPieceMoviendo();
        void DrawGame();
        void DrawGameRuleta();
        MovePieces moverFicha1;
>>>>>>> f72d20990916be5037739544fb6b23cc6932def9
    private:
        // Ventana de renderizado
        sf::RenderWindow* window;
        std::vector<std::vector<sf::Vector2f>> casillas;
        sf::FloatRect globalBounds;
        int posicionActual;
        int vectorActual;    // �ndice del vector actual
        sf::Vector2i mousePosition;
        sf::Vector2f mousePosFloat;
        int resultadoDado;
        sf::Texture piecesTextures;
        sf::Sprite pieces;
<<<<<<< HEAD

        
        sf::Texture TextureMapa;
        sf::Sprite spriteMapa;
=======
        sf::Clock TempoAnimacion;

        Window Dado;
        sf::Clock clock;

        Ruleta ruleta; // Crear la ruleta en el centro de la ventana
        bool validar;

        sf::View viewTablero; // Declarar la vista
        sf::Sprite renderedSprite;

        sf::Texture TextureMapa;
      

        sf::Texture SettingsOn;
        sf::Texture SettingsOff;
        sf::Sprite Settings;


        sf::Texture TextureArrowDer;


        sf::Texture TextureArrowIzq;

        
>>>>>>> f72d20990916be5037739544fb6b23cc6932def9
    };
#endif