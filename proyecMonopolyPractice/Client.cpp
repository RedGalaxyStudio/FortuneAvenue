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
    // Obtener la textura del c�rculo
    const sf::Texture* avatarTexture = avatarCircle.getTexture();
    if (!avatarTexture) {
        std::cerr << "El c�rculo no tiene textura asociada.\n";
        return;
    }

    // Crear una sf::Image a partir de la textura
    sf::Image avatarImage = avatarTexture->copyToImage();

    // Obtener los datos de la imagen
    const sf::Uint8* datos = avatarImage.getPixelsPtr();
    std::size_t tama�oDatos = avatarImage.getSize().x * avatarImage.getSize().y * 4; // 4 bytes por p�xel (RGBA)

    // Crear un paquete para enviar al servidor
    sf::Packet paquete;
    paquete << "AVATAR_IMAGE"; // Tipo de mensaje
    paquete << static_cast<sf::Uint32>(tama�oDatos); // Tama�o de los datos
    paquete.append(datos, tama�oDatos); // Agregar los datos de la imagen al paquete

    // Enviar el paquete al servidor
    if (socket.send(paquete) != sf::Socket::Done) {
        std::cerr << "Error al enviar la textura del avatar al servidor.\n";
    }
}

void recibirMensajes(sf::TcpSocket& socket) {
    while (running) {
        char buffer[1024];
        std::size_t received;
        sf::Socket::Status status = socket.receive(buffer, sizeof(buffer), received);
        if (status == sf::Socket::Done) {
            std::string mensaje(buffer, received);
            std::cout << "Mensaje del servidor: " << mensaje << "\n";

            // Procesar el mensaje
            sf::Packet paquete;
            paquete.append(buffer, received);
            std::string tipoMensaje;
            paquete >> tipoMensaje;

            if (tipoMensaje == "NEW_PLAYER") {
                Jugador nuevoJugador;
                sf::Uint32 tama�oFoto;
                paquete >> nuevoJugador.nombreUsuario >> nuevoJugador.ficha >> tama�oFoto;
                nuevoJugador.foto.resize(tama�oFoto);
                paquete.append(nuevoJugador.foto.data(), tama�oFoto);

                // Almacenar el nuevo jugador en el vector
                jugadores.push_back(nuevoJugador);
                std::cout << "Nuevo jugador recibido: " << nuevoJugador.nombreUsuario << "\n";

                // Cargar la textura de la foto y almacenarla
                sf::Texture avatarTexture;
                if (!avatarTexture.loadFromMemory(nuevoJugador.foto.data(), tama�oFoto)) {
                    std::cerr << "Error al cargar la textura del avatar.\n";
                    return;
                }

                // Almacenar la textura en el vector para que no se destruya
                avatarTextures.push_back(avatarTexture);

                // Crea el c�rculo para el avatar
                sf::CircleShape avatarCircle(50); // Cambia el tama�o seg�n lo que necesites
                avatarCircle.setTexture(&avatarTextures.back()); // Usa la �ltima textura cargada
                avatarCircle.setOrigin(50, 50); // Para centrar el c�rculo si es necesario

                // Guarda el c�rculo en el vector
                AvatarPlayers.push_back(avatarCircle); // Guardar el c�rculo en el vector
            }
            else if (tipoMensaje == "EXISTING_PLAYER") {
                Jugador jugadorExistente;
                sf::Uint32 tama�oFoto;
                paquete >> jugadorExistente.nombreUsuario >> jugadorExistente.ficha >> tama�oFoto;
                jugadorExistente.foto.resize(tama�oFoto);
                paquete.append(jugadorExistente.foto.data(), tama�oFoto);

                // Cargar la textura para el jugador existente
                if (jugadorExistente.textura.loadFromMemory(jugadorExistente.foto.data(), tama�oFoto)) {
                    // Aqu� puedes crear un sf::CircleShape tambi�n si es necesario
                    sf::CircleShape existingAvatarCircle(50); // Cambia el tama�o seg�n lo que necesites
                    existingAvatarCircle.setTexture(&jugadorExistente.textura); // Asigna la textura del jugador existente
                    existingAvatarCircle.setOrigin(50, 50); // Para centrar el c�rculo si es necesario

                    // Almacenar el avatar existente en el vector
                    AvatarPlayers.push_back(existingAvatarCircle);
                }
                else {
                    std::cerr << "Error al cargar la textura para el jugador existente: " << jugadorExistente.nombreUsuario << "\n";
                }

                // Almacenar el jugador existente en el vector
                jugadores.push_back(jugadorExistente);
                std::cout << "Jugador existente recibido: " << jugadorExistente.nombreUsuario << "\n";
            }
            // Manejar otros tipos de mensajes seg�n sea necesario
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

    // Hilo para recibir mensajes
    std::thread hiloRecibir(recibirMensajes, std::ref(socket));

    // Enviar mensajes al servidor
    std::string input;
    while (running && std::getline(std::cin, input)) {
        if (input == "exit") {
            running = false;
            break;
        }

        // Llama a la funci�n para enviar el avatar
        if (input == "send_avatar") {
            enviarAvatarSeleccionado(socket, selectedAvatarCopy);
        }
        else {
            socket.send(input.c_str(), input.size());
        }
        socket.send(input.c_str(), input.size());
    }

    socket.disconnect();
    hiloRecibir.join();
    return 0;
}
