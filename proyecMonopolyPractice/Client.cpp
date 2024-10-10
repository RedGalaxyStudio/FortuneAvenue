#include "Client.hpp"
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include "Globals.hpp"

std::vector<Jugador> jugadores;

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
                sf::Uint32 tamañoFoto;
                paquete >> nuevoJugador.nombreUsuario >> nuevoJugador.ficha >> tamañoFoto;
                nuevoJugador.foto.resize(tamañoFoto);
                paquete.append(nuevoJugador.foto.data(), tamañoFoto);

                // Almacenar el nuevo jugador en el vector
                jugadores.push_back(nuevoJugador);
                std::cout << "Nuevo jugador recibido: " << nuevoJugador.nombreUsuario << "\n";
            }
            else if (tipoMensaje == "EXISTING_PLAYER") {
                Jugador jugadorExistente;
                sf::Uint32 tamañoFoto;
                paquete >> jugadorExistente.nombreUsuario >> jugadorExistente.ficha >> tamañoFoto;
                jugadorExistente.foto.resize(tamañoFoto);
                paquete.append(jugadorExistente.foto.data(), tamañoFoto);

                // Almacenar el jugador existente en el vector
                jugadores.push_back(jugadorExistente);
                std::cout << "Jugador existente recibido: " << jugadorExistente.nombreUsuario << "\n";
            }
            // Manejar otros tipos de mensajes según sea necesario
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
    sf::Socket::Status status = socket.connect("192.168.3.192", PORT);
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
        socket.send(input.c_str(), input.size());
    }

    socket.disconnect();
    hiloRecibir.join();
    return 0;
}