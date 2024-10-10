#ifndef GAMEMODE_HPP
#define GAMEMODE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <atomic>
#include <windows.h> // Necesario para HRESULT y COM
#include "Client.hpp"
#include "Globals.hpp"


    class GameMode {
    public:
        GameMode(sf::RenderWindow* windowRef);
       
        
        // Método para actualizar el estado del botón según la posición del mouse
        void update();
        void resource();
        void moverSprite(sf::Sprite& sprite, int resultadoDado);
        void setPlayerProfile(int index, float x, float y);
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

        
        sf::Texture TextureMapa;
        sf::Sprite spriteMapa;
    };
#endif