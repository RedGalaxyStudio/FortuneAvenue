#include "Client.hpp"
#include "ResourceGlobal.hpp"
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include "Globals.hpp"
#include "ResourceGame.hpp"

std::vector<Jugador> jugadores;
std::vector<sf::Texture> avatarTextures; // Vector para almacenar las texturas de los avatares

void enviarAvatarSeleccionado(sf::TcpSocket& socket, const sf::CircleShape& avatarCircle) {
    const sf::Texture* avatarTexture = avatarCircle.getTexture();
    if (!avatarTexture) {
        std::cerr << "El círculo no tiene textura asociada.\n";
        return;
    }

    sf::Image avatarImage = avatarTexture->copyToImage();
    const sf::Uint8* datos = avatarImage.getPixelsPtr();
    std::size_t tamañoDatos = avatarImage.getSize().x * avatarImage.getSize().y * 4; // RGBA

    sf::Packet paquete;
    paquete << "AVATAR_IMAGE";
    paquete << static_cast<sf::Uint32>(tamañoDatos);
    paquete.append(datos, tamañoDatos);

    if (socket.send(paquete) != sf::Socket::Done) {
        std::cerr << "Error al enviar la textura del avatar al servidor.\n";
    }
}

void recibirMensajes(sf::TcpSocket& socket) {
    while (running) {
        sf::Packet paqueteRecibido;
        sf::Socket::Status status = socket.receive(paqueteRecibido);
        if (status == sf::Socket::Done) {
            std::string tipoMensaje;
            paqueteRecibido >> tipoMensaje;

            if (tipoMensaje == "NEW_PLAYER" || tipoMensaje == "EXISTING_PLAYER") {
                std::string nombreJugador;
                int ficha;
                sf::Uint32 tamañoFoto, ancho, alto;
                paqueteRecibido >> nombreJugador >> ficha >> tamañoFoto >> ancho >> alto;

                // Leer los datos binarios de la imagen
                std::vector<sf::Uint8> fotoData(tamañoFoto);
                paqueteRecibido.append(&fotoData[0], tamañoFoto);

                sf::Texture avatarTexture;
                sf::Image imagen;
                imagen.create(ancho, alto, fotoData.data());  // Ancho y alto obtenidos del servidor
                avatarTexture.loadFromImage(imagen);

                avatarTextures.push_back(avatarTexture);

                sf::CircleShape avatarCircle(50); // Cambia el tamaño según lo que necesites
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
        else if (status == sf::Socket::Disconnected) {
            std::cout << "Desconectado del servidor.\n";
            running = false;
            break;
        }
    }
}

int Juan() {
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("192.168.3.114", PORT);
    if (status != sf::Socket::Done) {
        std::cerr << "Error al conectar con el servidor.\n";
        return -1;
    }
    std::cout << "Conectado al servidor.\n";

    std::thread hiloRecibir(recibirMensajes, std::ref(socket));

    std::string input;
    while (running && std::getline(std::cin, input)) {
        if (input == "exit") {
            running = false;
            break;
        }

        if (input == "send_avatar") {
            enviarAvatarSeleccionado(socket, selectedAvatarCopy);
        }
        else {
            socket.send(input.c_str(), input.size());
        }
    }

    socket.disconnect();
    hiloRecibir.join();
    return 0;
}

