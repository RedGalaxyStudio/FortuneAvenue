#include "Client.hpp"
#include "ResourceGlobal.hpp"
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include "Globals.hpp"
#include "ResourceGame.hpp"

std::vector<Jugador> jugadores;
std::vector<sf::Texture> avatarTextures; // Vector para almacenar las texturas de los avatares

AvatarNetworkHandler::AvatarNetworkHandler(const std::string& ip, unsigned short port)
{
    // Conexi�n al servidor
    sf::Socket::Status status = socket.connect(ip, port);
    if (status != sf::Socket::Done) {
        std::cerr << "Error al conectar con el servidor.\n";
        running = false;
    }
    else {
        std::cout << "Conectado al servidor.\n";
        socket.setBlocking(false); // No bloquear al recibir
    }
}

AvatarNetworkHandler::~AvatarNetworkHandler() {
    desconectar();
    if (hiloRecibir.joinable()) {
        running = false;  // Indica al hilo que debe detenerse
        hiloRecibir.join();  // Esperar a que el hilo termine
    }
}

void AvatarNetworkHandler::iniciar() {
    hiloRecibir = std::thread(&AvatarNetworkHandler::recibirMensajes, this); // Iniciar hilo de recepci�n
}

void AvatarNetworkHandler::enviarAvatarSeleccionado(const sf::CircleShape& avatarCircle) {
    const sf::Texture* avatarTexture = avatarCircle.getTexture();
    if (!avatarTexture) {
        std::cerr << "El c�rculo no tiene textura asociada.\n";
        return;
    }

    sf::Image avatarImage = avatarTexture->copyToImage();
    const sf::Uint8* datos = avatarImage.getPixelsPtr();
    std::size_t tama�oDatos = avatarImage.getSize().x * avatarImage.getSize().y * 4; // RGBA

    sf::Packet paquete;
    paquete << "AVATAR_IMAGE";
    paquete << static_cast<sf::Uint32>(tama�oDatos);
    paquete.append(datos, tama�oDatos);

    if (socket.send(paquete) != sf::Socket::Done) {
        std::cerr << "Error al enviar la textura del avatar al servidor.\n";
    }
}

void AvatarNetworkHandler::recibirMensajes() {
    while (running) {
        sf::Packet paqueteRecibido;
        sf::Socket::Status status = socket.receive(paqueteRecibido);

        if (status == sf::Socket::Done) {
            procesarPaquete(paqueteRecibido);
        }
        else if (status == sf::Socket::Disconnected) {
            std::cout << "Desconectado del servidor.\n";
            running = false; // Cambiar a false
            break; // Salir del bucle
        }
        else {
            std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Tiempo de espera breve
        }
    }
}



void AvatarNetworkHandler::procesarPaquete(sf::Packet& paqueteRecibido) {
    std::string tipoMensaje;
    paqueteRecibido >> tipoMensaje;

    if (tipoMensaje == "NEW_PLAYER" || tipoMensaje == "EXISTING_PLAYER") {
        std::string nombreJugador;
        int ficha;
        sf::Uint32 tama�oFoto, ancho, alto;
        paqueteRecibido >> nombreJugador >> ficha >> tama�oFoto >> ancho >> alto;

        // Leer los datos binarios de la imagen
        std::vector<sf::Uint8> fotoData(tama�oFoto);
        paqueteRecibido.append(fotoData.data(), tama�oFoto);

        sf::Texture avatarTexture;
        sf::Image imagen;
        imagen.create(ancho, alto, fotoData.data());  // Ancho y alto obtenidos del servidor
        avatarTexture.loadFromImage(imagen);

        avatarTextures.push_back(avatarTexture);

        sf::CircleShape avatarCircle(50); // Cambia el tama�o seg�n lo que necesites
        avatarCircle.setTexture(&avatarTextures.back());
        avatarCircle.setOrigin(50, 50);

        AvatarPlayers.push_back(avatarCircle);

        Jugador nuevoJugador;
        nuevoJugador.nombreUsuario = nombreJugador;
        nuevoJugador.ficha = ficha;
        nuevoJugador.textura = avatarTexture;
        jugadores.push_back(nuevoJugador);

        std::cout << "Jugador recibido: " << nombreJugador << "\n";
    }
}

void AvatarNetworkHandler::desconectar() {
    running = false; // Aseg�rate de que el hilo de recepci�n se detenga
    socket.disconnect();
}


