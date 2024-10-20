#include "Client.hpp"

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
