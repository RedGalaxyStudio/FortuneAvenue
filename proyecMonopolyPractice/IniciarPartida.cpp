#include "IniciarPartida.hpp"
#include "ObjetosGlobal.hpp"
#include "ButtonG.hpp"
#include "TextBox.hpp"

IniciarPartida::IniciarPartida(sf::RenderWindow& win) : window(&win), pieceselector(window) {
    loadResourceGame();
    resource();
}

void IniciarPartida::resource() {
    TextureCrearPartidaOff.loadFromFile("resource/texture/Game/CrearPartidaOff.png");
    TextureCrearPartidaOn.loadFromFile("resource/texture/Game/CrearPartidaOn.png");

    TextureUnirsePartidaOff.loadFromFile("resource/texture/Game/UnirsePartidaOff.png");
    TextureUnirsePartidaOn.loadFromFile("resource/texture/Game/UnirsePartidaOn.png");

    SpriteCrearPartida.setTexture(TextureCrearPartidaOff);
    SpriteCrearPartida.setOrigin(150, 59);
    SpriteCrearPartida.setPosition(640, 300);

    SpriteUnirsePartida.setTexture(TextureUnirsePartidaOff);
    SpriteUnirsePartida.setOrigin(150, 59);
    SpriteUnirsePartida.setPosition(640, 500);
}

void IniciarPartida::update() {
    client.initialize();
    std::cout << "1";
    client.connectToServer("208.68.36.50", 1234);
    std::cout << "2";
    Valida = false;
    
    ButtonG botonCrearPartida(SpriteCrearPartida, TextureCrearPartidaOff, TextureCrearPartidaOn);
    ButtonG botonUnirsePartida(SpriteUnirsePartida, TextureUnirsePartidaOff, TextureUnirsePartidaOn);

    while (window->isOpen()&&Valida==false) {
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
                    updatejoinRoom();
     
                }

                if (SpriteCrearPartida.getGlobalBounds().contains(mousePosFloat)) {
                    Code= client.createRoom();
                    std::cout << Code;
                    pieceselector.Resource();
                    pieceselector.updateSelection();
                }
            }
        }
        


        currentCursor = &normalCursor;

        botonCrearPartida.update(mousePosFloat, currentCursor, linkCursor, normalCursor);
        botonUnirsePartida.update(mousePosFloat, currentCursor, linkCursor, normalCursor);

        window->setMouseCursor(*currentCursor);


        window->clear();
        window->draw(spriteFondoGame); // Dibuja el fondo
        window->draw(SpriteUnirsePartida); // Dibuja el fondo
        window->draw(SpriteCrearPartida); // Dibuja el fondo
        window->display();
    }
}

void IniciarPartida::updatejoinRoom() {
    std::string code;

    TextBox textBoxRoom(496, 50, "Ingresa el codigo: ");  // Crear un cuadro de texto
    textBoxRoom.setPosition();  // Posicionar el cuadro de texto
    while (window->isOpen()) {
        sf::Event event;

        mousePosition = sf::Mouse::getPosition(*window);
        mousePosFloat = static_cast<sf::Vector2f>(mousePosition);
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {      

                textBoxRoom.Prinf();  // Dibujar el cuadro de texto en la ventana

                window->close();
            }


            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                
                if (SpriteUnirsePartida.getGlobalBounds().contains(mousePosFloat)) {
                    playClickSound();

                    client.joinRoom(code);
                    client.sendImage(TextureAvatarPath);
                }
            }

            textBoxRoom.handleInput(event,5);

        }

        window->clear();
        window->draw(spriteFondoGame); // Dibuja el fondo
        textBoxRoom.draw(*window);  // Dibujar el cuadro de texto en la ventana
        window->display();
    }
}

