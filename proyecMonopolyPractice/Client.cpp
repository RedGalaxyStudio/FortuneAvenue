#include "Client.hpp"
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include "Globals.hpp"


void recibirMensajes(sf::TcpSocket& socket); // Declaración de la función

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