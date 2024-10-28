#ifndef GAMEMODE_HPP
#define GAMEMODE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <thread>
#include <atomic>
#include <winsock2.h>
#include <windows.h> 
#include "Client.hpp"
#include "Globals.hpp"
#include "WindowClass.h"
#include "Ruleta.hpp"
#include "MovePieces.hpp"
#include "ResourceGlobal.hpp"
#include "ObjetosGlobal.hpp"
#include "PieceSelector.hpp"
#include "ResourceGame.hpp"

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

    private:
        // Ventana de renderizado
        sf::RenderWindow* window;
        std::vector<std::vector<sf::Vector2f>> casillas;
        sf::FloatRect globalBounds;
        int posicionActual;
        int vectorActual;    // Índice del vector actual
        sf::Vector2i mousePosition;
        sf::Vector2f mousePosFloat;
        int resultadoDado;
        sf::Texture piecesTextures;
        sf::Sprite pieces;

        sf::Clock TempoAnimacion;

        Window Dado;
        sf::Clock clock;

        Ruleta ruleta; 
        bool validar;

        sf::View viewTablero; 
        sf::Sprite renderedSprite;

        sf::Texture TextureMapa;
      

        sf::Texture SettingsOn;
        sf::Texture SettingsOff;
        sf::Sprite Settings;


        sf::Texture TextureArrowDer;


        sf::Texture TextureArrowIzq;
        std::vector<sf::Text> Dinero;
        int money[4];
    };
#endif