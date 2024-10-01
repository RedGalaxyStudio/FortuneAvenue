#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "TextBox.hpp"
#include <SFML/Audio.hpp>
#include "Scrollbar.hpp"
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

    // Definir las dimensiones y límites
    const float avatarWidth = 128.0f;
    const float avatarHeight = 128.0f;
    const float avatarSeparation = 28.0f;
    const float visibleAreaHeight = 170.0f;
    const float maxScrollOffset = 270.0f;  // Límite máximo de desplazamiento

    Texrecua.loadFromFile("resource/texture/Avatars/recua2.png");
    recua.setTexture(Texrecua);
    recua.setOrigin(65, 65);
    recua.setPosition(300, 92);
    TextBox textBox(400, 50);  // Crear un cuadro de texto
    textBox.setPosition();  // Posicionar el cuadro de texto
    Scrollbar scrollbar(340, 233.5f,14);  // Altura de la ventana, altura del thumb
    scrollbar.setPosition(1240, 340);  // Colocar la barra a la derecha

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
                scrollbar.update(event.mouseWheelScroll.delta);  // Actualizar el desplazamiento
            }

            // Manejo de clics en avatares
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::CircleShape* newSelection = nullptr;

                // Obtener el desplazamiento actual de la barra de scroll
                float avatarYOffset = scrollbar.getScrollOffset();

                for (int i = 0; i < avatars.size(); ++i) {
                    // Obtener la posición original del avatar
                    sf::Vector2f originalPosition = avatars[i].getPosition();

                    // Calcular la posición desplazada del avatar según el scroll
                    sf::FloatRect bounds = avatars[i].getGlobalBounds();
                    bounds.top -= avatarYOffset;

                    // Verificar si el mouse está sobre el avatar desplazado
                    if (bounds.contains(mousePosFloat)) {
                        newSelection = &avatars[i];
                        break;
                    }
                }

                // Lógica para manejar la selección del avatar
                if (spriteX.getGlobalBounds().contains(mousePosFloat)) {
                    playClickSound();
                    Menup.MenuPrincipal();
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


        // Obtener el desplazamiento actual de la barra de scroll
        float avatarYOffset = scrollbar.getScrollOffset();

        // Limitar el desplazamiento a un valor razonable
      
        if (avatarYOffset > maxScrollOffset) avatarYOffset = maxScrollOffset;  // Límite máximo
        if (avatarYOffset < 0) avatarYOffset = 0;  // No permitir desplazarse más allá del inicio
        // Dibujar todos los avatares, excepto el seleccionado
        for (int i = 0; i < avatars.size(); ++i) {


            // Obtener la posición original del avatar (posiciones basadas en una cuadrícula)
            int column = i % 8;  // Calcular la columna
            int row = i / 8;  // Calcular la fila

            float xPos = 92.0f + column * (avatarWidth + avatarSeparation);
            std::cout << avatarWidth <<"   "<< avatarSeparation <<"   "  << avatarYOffset;
            float yPos = 472.0f + row * (avatarHeight + avatarSeparation) - avatarYOffset;

            // Establecer la nueva posición del avatar
            avatars[i].setPosition(xPos, yPos);

            // Dibujar el avatar con la nueva posición
            window.draw(avatars[i]);
        }

        // Dibujar solo la copia del avatar seleccionado en la posición del perfil
        if (selectedAvatar != nullptr) {
            window.draw(selectedAvatarCopy);  // Dibujar solo la copia del avatar seleccionado en su perfil
        }

        scrollbar.draw(window);
        window.draw(recua);
        window.draw(spriteX);
        window.display();
    }
}

