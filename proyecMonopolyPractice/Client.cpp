#include "Client.hpp"
<<<<<<< HEAD
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
    // Conexión al servidor
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
    hiloRecibir = std::thread(&AvatarNetworkHandler::recibirMensajes, this); // Iniciar hilo de recepción
}

void AvatarNetworkHandler::enviarAvatarSeleccionado(const sf::CircleShape& avatarCircle) {
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
        sf::Uint32 tamañoFoto, ancho, alto;
        paqueteRecibido >> nombreJugador >> ficha >> tamañoFoto >> ancho >> alto;

        // Leer los datos binarios de la imagen
        std::vector<sf::Uint8> fotoData(tamañoFoto);
        paqueteRecibido.append(fotoData.data(), tamañoFoto);

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

void AvatarNetworkHandler::desconectar() {
    running = false; // Asegúrate de que el hilo de recepción se detenga
    socket.disconnect();
}


=======

/*using boost::asio::ip::tcp;

Client::Client(boost::asio::io_context& io_context, const std::string& server, short port)
    : socket_(io_context), endpoint_(tcp::endpoint(boost::asio::ip::address::from_string(server), port)) {
    start_connect();
}

void Client::start_connect() {
    socket_.async_connect(endpoint_, [this](const boost::system::error_code& error) {
        if (!error) {
            std::cout << "Conectado al servidor. Enviando imagen..." << std::endl;
            send_image();
        }
        else {
            std::cerr << "Error al conectar: " << error.message() << std::endl;
        }
        });
}

void Client::send_image() {
    std::ifstream image_file("image_to_send.png", std::ios::binary | std::ios::ate); // Abrir archivo de imagen

    if (!image_file) {
        std::cerr << "No se pudo abrir el archivo de imagen." << std::endl;
        return;
    }

    std::streamsize image_size = image_file.tellg(); // Obtener el tamaño del archivo
    image_file.seekg(0, std::ios::beg);

    auto buffer = std::make_shared<std::vector<char>>(image_size); // Buffer para la imagen
    if (image_file.read(buffer->data(), image_size)) {
        boost::asio::async_write(socket_, boost::asio::buffer(*buffer),
            [this, buffer](const boost::system::error_code& error, std::size_t bytes_transferred) {
                if (!error) {
                    std::cout << "Imagen enviada correctamente, bytes enviados: " << bytes_transferred << std::endl;
                    socket_.close();  // Cerrar el socket después de enviar
                }
                else {
                    std::cerr << "Error al enviar la imagen: " << error.message() << std::endl;
                }
            }
        );
    }
    else {
        std::cerr << "Error al leer el archivo de imagen." << std::endl;
    }
}*/
>>>>>>> f72d20990916be5037739544fb6b23cc6932def9
