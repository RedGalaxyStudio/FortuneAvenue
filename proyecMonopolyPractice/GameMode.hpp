#ifndef GAMEMODE_HPP
#define GAMEMODE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <thread>
#include <atomic>
#include <winsock2.h>
//#include <windows.h> 
#include "Globals.hpp"
#include "ObjetosGlobal.hpp"
#include "WindowClass.h"
#include "Ruleta.hpp"
#include "MovePieces.hpp"
#include "ResourceGlobal.hpp"
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


    private:
        // Ventana de renderizado
        sf::RenderWindow* window;
        std::vector<std::vector<sf::Vector2f>> casillas0;
        std::vector<std::vector<sf::Vector2f>> casillas1;
        std::vector<std::vector<sf::Vector2f>> casillas2;
        std::vector<std::vector<sf::Vector2f>> casillas3;

        std::vector<sf::Vector2f> casillasRuleta = {
        sf::Vector2f(402, 157),
        sf::Vector2f(840, 476),
        sf::Vector2f(958, 372),
        sf::Vector2f(930, 231),
        sf::Vector2f(688, 137),
        sf::Vector2f(675, 40),
        sf::Vector2f(514, 141),
        sf::Vector2f(425,654),
        sf::Vector2f(556 , 544),
        sf::Vector2f(632 , 585),
        sf::Vector2f(923, 679),
        sf::Vector2f(328, 161),
        sf::Vector2f(790, 539),
        sf::Vector2f(325,523)
        };

        std::vector<std::vector<sf::Vector2f>> casillasimpuesto0;
        std::vector<std::vector<sf::Vector2f>> casillasimpuesto1;
        std::vector<std::vector<sf::Vector2f>> casillasimpuesto2;
        std::vector<std::vector<sf::Vector2f>> casillasimpuesto3;


        sf::FloatRect globalBounds;
        int posicionActual;
        int vectorActual;    // Índice del vector actual
        sf::Vector2i mousePosition;
        sf::Vector2f mousePosFloat;
        int resultadoDado;
        sf::Texture piecesTextures;
        sf::Sprite pieces;
        std::vector<MovePieces> moverFichas;
        sf::Clock TempoAnimacion;
        bool animacionIniciada;
        Window Dado;
        sf::Clock clock;
        bool ruledraw;
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

        sf::Texture TextureArrowArriba;


    };
#endif