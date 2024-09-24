#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "TextBox.hpp"
#include <SFML/Audio.hpp>
#include <string>
#include "ResourceGlobal.hpp"
#include "menuP.hpp"
#include "ObjetosGlobal.hpp"


// Constructor e inicialización
Game::Game(sf::RenderWindow& windowRef)
    : window(windowRef), currentIndex(0) {  // Inicializa el índice actual
    Resource();
    loadAvatars();
}
Game::~Game() {
}

// Carga de recursos (texturas y sprites)
void Game::Resource() {
    if (!sharedTexture.loadFromFile("resource/texture/Avatars/Vacio.jpg")) return;
    SpriteFondoMenu.setTexture(TextureFondoMenu);
}

// Actualización de la animación (desvanecimiento del logotipo y fondo animado)
void Game::Update() {

    sf::Texture Texrecua;
    sf::Sprite recua;

    Texrecua.loadFromFile("resource/texture/Avatars/recua2.png");
    recua.setTexture(Texrecua);
    recua.setOrigin(65, 65);
    recua.setPosition(300, 92);
    TextBox textBox(400, 50);  // Crear un cuadro de texto
    textBox.setPosition();  // Posicionar el cuadro de texto

    // Crear una nueva instancia de sf::CircleShape para la copia
    selectedAvatarCopy.setRadius(64);  // Ajusta el radio al tamaño esperado
    selectedAvatarCopy.setTexture(&sharedTexture);  // Usar la textura compartida
    selectedAvatarCopy.setOrigin(64, 64);  // Establece el origen al centro del círculo
    selectedAvatarCopy.setPosition(300, 92);  // Establecer la nueva posición para la copia

    while (window.isOpen()) {
        mousePosition = sf::Mouse::getPosition(window);
        mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                Menup.MenuSalir();
                window.close();
            }

            // Manejo del desplazamiento con la rueda del mouse
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0) {
                    currentIndex = std::max(0, currentIndex - 1); // Desplazar hacia arriba
                }
                else {
                    currentIndex = std::min(static_cast<int>(avatars.size()) - 2, currentIndex + 1); // Desplazar hacia abajo
                }
            }

            // Manejo de clics en avatares
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::CircleShape* newSelection = nullptr;
                for (int i = currentIndex; i < currentIndex + 2 && i < avatars.size(); ++i) {
                    if (avatars[i].getGlobalBounds().contains(mousePosFloat)) {
                        newSelection = &avatars[i];
                        break;
                    }
                }

                // Actualizar el borde del avatar seleccionado
                if (newSelection != selectedAvatar) {
                    if (selectedAvatar) {
                        selectedAvatar->setOutlineColor(sf::Color::Transparent);  // Quitar borde del avatar previamente seleccionado
                        selectedAvatar->setOutlineThickness(0);
                    }
                    if (newSelection) {
                        newSelection->setOutlineColor(sf::Color::Black);  // Aplicar borde al nuevo avatar seleccionado
                        newSelection->setOutlineThickness(4);
                        // Actualizar la textura de la copia del avatar
                        selectedAvatarCopy.setTexture(newSelection->getTexture());  // Copiar la textura
                    }
                    selectedAvatar = newSelection;
                }
            }
            // Manejar la entrada de texto
            textBox.handleInput(event);
        }

        botonX->update(mousePosFloat, currentCursor, linkCursor, normalCursor);

        window.clear();
        window.draw(SpriteFondoMenu);
        textBox.draw(window);  // Dibujar el cuadro de texto en la ventana

        // Dibujar solo los avatares visibles
        for (int i = currentIndex; i < currentIndex + 2 && i < avatars.size(); ++i) {
            window.draw(avatars[i]);
        }

        // Dibujar el avatar seleccionado en su posición original
        if (selectedAvatar != nullptr) {
            window.draw(*selectedAvatar);  // Dibujar el avatar seleccionado en su posición original
        }
        window.draw(selectedAvatarCopy);
        window.draw(recua);
        window.draw(spriteX);
        window.display();
    }
}
