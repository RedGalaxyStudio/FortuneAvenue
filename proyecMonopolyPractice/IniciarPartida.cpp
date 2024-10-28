#include "IniciarPartida.hpp"
#include "ObjetosGlobal.hpp"


IniciarPartida::IniciarPartida(sf::RenderWindow& win) : window(&win){
    loadResourceGame();
    resource();
}

void IniciarPartida::resource() {
    TextureCrearPartida.loadFromFile("resource/texture/Game/CrearPartida.jpg");
    TextureUnirsePartida.loadFromFile("resource/texture/Game/UnirsePartida.jpg");

    SpriteCrearPartida.setTexture(TextureCrearPartida);
    SpriteCrearPartida.setOrigin(103.5f, 40);
    SpriteCrearPartida.setPosition(383, 560);

    SpriteUnirsePartida.setTexture(TextureUnirsePartida);
    SpriteUnirsePartida.setOrigin(103.5f, 40);
    SpriteUnirsePartida.setPosition(1000, 560);
}

void IniciarPartida::update() {
    client.initialize();
    std::cout << "1";
    client.connectToServer("192.168.3.114", 1234);
    std::cout << "2";

    while (window->isOpen()) {
        sf::Event event;

        mousePosition = sf::Mouse::getPosition(*window);
        mousePosFloat = static_cast<sf::Vector2f>(mousePosition);
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window->close();
            }
                
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // Verificar el click en "si" y cerrar la vetana
                if (SpriteUnirsePartida.getGlobalBounds().contains(mousePosFloat)) {
                    playClickSound();

                    client.joinRoom("32243");
                }

                if (SpriteCrearPartida.getGlobalBounds().contains(mousePosFloat)) {
                    playClickSound();
                    client.createRoom();
                }
            }
        }
        
        window->clear();
        window->draw(spriteFondoGame); // Dibuja el fondo
        window->draw(SpriteUnirsePartida); // Dibuja el fondo
        window->draw(SpriteCrearPartida); // Dibuja el fondo
        window->display();
    }
}

void IniciarPartida::updatejoinRoom() {
    client.sendImage(TextureAvatarPath);
    while (window->isOpen()) {
        sf::Event event;

        mousePosition = sf::Mouse::getPosition(*window);
        mousePosFloat = static_cast<sf::Vector2f>(mousePosition);
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window->close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // Verificar el click en "si" y cerrar la vetana
                if (SpriteUnirsePartida.getGlobalBounds().contains(mousePosFloat)) {
                    playClickSound();

                    client.joinRoom("32243");
                }

                if (SpriteCrearPartida.getGlobalBounds().contains(mousePosFloat)) {
                    playClickSound();
                    client.createRoom();
                }
            }
        }

        window->clear();
        window->draw(spriteFondoGame); // Dibuja el fondo
        window->draw(SpriteUnirsePartida); // Dibuja el fondo
        window->draw(SpriteCrearPartida); // Dibuja el fondo
        window->display();
    }
}

void IniciarPartida::updatecreateRoom() {
    client.sendImage(TextureAvatarPath);
    while (window->isOpen()) {
        sf::Event event;

        mousePosition = sf::Mouse::getPosition(*window);
        mousePosFloat = static_cast<sf::Vector2f>(mousePosition);
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window->close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // Verificar el click en "si" y cerrar la vetana
                if (SpriteUnirsePartida.getGlobalBounds().contains(mousePosFloat)) {
                    playClickSound();

                    client.joinRoom("32243");
                }

                if (SpriteCrearPartida.getGlobalBounds().contains(mousePosFloat)) {
                    playClickSound();
                    client.createRoom();
                }
            }
        }

        window->clear();
        window->draw(spriteFondoGame); // Dibuja el fondo
        window->draw(SpriteUnirsePartida); // Dibuja el fondo
        window->draw(SpriteCrearPartida); // Dibuja el fondo
        window->display();
    }
}