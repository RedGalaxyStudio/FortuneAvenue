#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Globals.hpp"
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include "ResourceGlobal.hpp"
#include <SFML/Network.hpp>
#include "ResourceGame.hpp"


    struct Jugador {
        std::string nombreUsuario;
        int ficha;
        std::vector<char> foto; // Almacena los datos de la imagen
        sf::Texture textura; // Textura para el sprite
        sf::Sprite sprite; // Sprite del jugador
    };
    
    extern std::vector<Jugador> jugadores; // Declaración externa

class AvatarNetworkHandler {
public:
    AvatarNetworkHandler(const std::string& ip, unsigned short port);
    ~AvatarNetworkHandler();

    void enviarAvatarSeleccionado(const sf::CircleShape& avatarCircle);
    void recibirMensajes();
    void iniciar();
    void desconectar();

private:
    sf::TcpSocket socket;
    std::thread hiloRecibir;
    std::vector<sf::Texture> avatarTextures; // Vector para almacenar las texturas de los avatares
   


    // Métodos auxiliares
    void procesarPaquete(sf::Packet& paqueteRecibido);
};

#endif // PIECESELECTOR_HPP


