#ifndef CLIENT_HPP
#define CLIENT_HPP

<<<<<<< HEAD
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
=======
/*#define WIN32_LEAN_AND_MEAN
#include <Winsock2.h>
#include <ws2tcpip.h>  // Puede ser necesario en algunos casos.
#include <boost/asio.hpp>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#pragma comment(lib, "Ws2_32.lib") // Vinculación de la librería de Winsock

using boost::asio::ip::tcp;

class Client {
public:
    Client(boost::asio::io_context& io_context, const std::string& server, short port);

private:
    void start_connect();
    void send_image();
    tcp::socket socket_;
    tcp::endpoint endpoint_;
};
*/
#endif // CLIENT_HPP
>>>>>>> f72d20990916be5037739544fb6b23cc6932def9


