#ifndef CLIENT_HPP
#define CLIENT_HPP
#include "Globals.hpp"
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>

struct Jugador {
    std::string nombreUsuario;
    int ficha;
    std::vector<char> foto; // Almacena los datos de la imagen
    sf::Texture textura; // Textura para el sprite
    sf::Sprite sprite; // Sprite del jugador
};


// Declaraci�n de la funci�n para recibir mensajes
void recibirMensajes(sf::TcpSocket& socket);

// Vector para almacenar los jugadores
extern std::vector<Jugador> jugadores; // Declaraci�n externa


int Juan();

#endif // PIECESELECTOR_HPP


