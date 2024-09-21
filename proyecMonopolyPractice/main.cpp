#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <thread>

// Función para recibir mensajes del servidor
void receiveMessages(sf::TcpSocket* socket, std::vector<std::string>& messages, bool& newMessage) {
    char buffer[1024];
    std::size_t received;

    while (true) {
        if (socket->receive(buffer, sizeof(buffer), received) == sf::Socket::Done) {
            messages.push_back(std::string(buffer));  // Almacenar mensaje
            newMessage = true;  // Indicar que hay un nuevo mensaje
        }
    }
}

int main() {
    // Conectar al servidor
    sf::TcpSocket socket;
    if (socket.connect("192.168.3.156", 53000) != sf::Socket::Done) {
        std::cerr << "No se pudo conectar al servidor." << std::endl;
        return -1;
    }

    std::cout << "Conectado al servidor." << std::endl;

    // Crear una ventana SFML para el chat
    sf::RenderWindow window(sf::VideoMode(600, 400), "Chat SFML");

    // Fuente para el texto
    sf::Font font;
    if (!font.loadFromFile("resource/fonts/ARCADEPI.ttf")) {  // Asegúrate de tener esta fuente en tu directorio
        std::cerr << "No se pudo cargar la fuente." << std::endl;
        return -1;
    }

    // Entrada de texto (donde el usuario escribe su mensaje)
    sf::RectangleShape inputBox(sf::Vector2f(400, 30));
    inputBox.setFillColor(sf::Color(200, 200, 200));
    inputBox.setPosition(10, 350);

    // Botón de enviar
    sf::RectangleShape sendButton(sf::Vector2f(100, 30));
    sendButton.setFillColor(sf::Color(100, 100, 250));
    sendButton.setPosition(420, 350);

    // Texto del botón "Enviar"
    sf::Text sendText("Enviar", font, 18);
    sendText.setPosition(440, 352);
    sendText.setFillColor(sf::Color::White);

    // Lista de mensajes
    std::vector<std::string> messages;
    bool newMessage = false;  // Bandera para saber si hay un mensaje nuevo

    // Iniciar un hilo para recibir mensajes
    std::thread receiveThread(receiveMessages, &socket, std::ref(messages), std::ref(newMessage));
    receiveThread.detach();

    // Variable para capturar la entrada de texto
    std::string currentMessage;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Cerrar la ventana
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Capturar entrada de texto
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b' && !currentMessage.empty()) {
                    // Eliminar el último carácter si es "backspace"
                    currentMessage.pop_back();
                }
                else if (event.text.unicode < 128 && event.text.unicode != '\b') {
                    // Añadir caracteres al mensaje si no es "backspace"
                    currentMessage += static_cast<char>(event.text.unicode);
                }
            }

            // Enviar mensaje cuando el botón de enviar es presionado
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (sendButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        // Enviar mensaje al servidor
                        if (!currentMessage.empty()) {
                            if (socket.send(currentMessage.c_str(), currentMessage.size() + 1) != sf::Socket::Done) {
                                std::cerr << "No se pudo enviar el mensaje." << std::endl;
                            }
                            messages.push_back("Tú: " + currentMessage);  // Mostrar el mensaje del usuario
                            currentMessage.clear();  // Limpiar el campo de entrada
                        }
                    }
                }
            }
        }

        // Limpiar la ventana
        window.clear(sf::Color::Black);

        // Dibujar la caja de entrada y el botón de enviar
        window.draw(inputBox);
        window.draw(sendButton);
        window.draw(sendText);

        // Mostrar el texto que se está escribiendo
        sf::Text inputText(currentMessage, font, 18);
        inputText.setFillColor(sf::Color::Black);
        inputText.setPosition(15, 355);
        window.draw(inputText);

        // Dibujar los mensajes en la ventana
        int yPosition = 10;
        for (const auto& msg : messages) {
            sf::Text messageText(msg, font, 18);
            messageText.setFillColor(sf::Color::White);
            messageText.setPosition(10, yPosition);
            window.draw(messageText);
            yPosition += 25;
        }

        // Ver si hay un nuevo mensaje recibido y actualizar la lista
        if (newMessage) {
            newMessage = false;
        }

        // Mostrar todo en la ventana
        window.display();
    }

    return 0;
}