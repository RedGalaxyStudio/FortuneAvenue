#include <SFML/Graphics.hpp>
#include "IniciaUser.hpp"
#include "TextBox.hpp"
#include <SFML/Audio.hpp>
#include "Scrollbar.hpp"
#include <string>
#include "ResourceGlobal.hpp"
#include "menuP.hpp"
#include "ObjetosGlobal.hpp"
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

// Constructor e inicialización
IniciaUser::IniciaUser(sf::RenderWindow& windowRef)
    : window(windowRef), currentIndex(0) {  // Inicializa el índice actual
    Resource();
    loadAvatars();
}
IniciaUser::~IniciaUser() {
}

// Carga de recursos (texturas y sprites)
void IniciaUser::Resource() {
    SpriteFondoMenu.setTexture(TextureFondoMenu);
}

// Actualización de la animación (desvanecimiento del logotipo y fondo animado)
void IniciaUser::Update() {
    if (!ckeck.loadFromFile("resource/texture/Avatars/cheeke2.png")) return;
    spriteCkeck.setTexture(ckeck);
    if (!std::filesystem::exists("perfil.json")) {
        IniciAcion();
    }else{
        loadSelectedAvatar();
    }
    
}

void IniciaUser::IniciAcion(){
    spriteCkeck.setPosition(850, 70);

    // Posiciones base calculadas fuera del bucle
    float baseXPos = 92.0f;
    float baseYPos = 472.0f;
    
    // Calcular solo una vez fuera del bucle

        // Definir las dimensiones y límites
    const float avatarWidth = 128.0f;
    const float avatarHeight = 128.0f;
    const float avatarSeparation = 28.0f;
    const float visibleAreaHeight = 248.0f;
    const float maxScrollOffset = 156.0f;  // Límite máximo de desplazamiento

    float widthSeparation = avatarWidth + avatarSeparation;
    float heightSeparation = avatarHeight + avatarSeparation;

    recua.setPosition(400, 112);
    TextBox textBox(496, 50);  // Crear un cuadro de texto
    textBox.setPosition();  // Posicionar el cuadro de texto
    // Definir la altura total del contenido y la altura de la ventana
    const float totalContentHeight = 440.0f; // Cambia esto según el total que necesites
    const float scrollbarHeight = 340.0f;

    // Calcular la proporción y la altura del pulgar
    float proportion = visibleAreaHeight / totalContentHeight;
    float thumbHeight = scrollbarHeight * proportion;

    // Asegúrate de que el pulgar tenga una altura mínima
    const float minThumbHeight = 14.0f; // altura mínima para el pulgar
    thumbHeight = std::max(thumbHeight, minThumbHeight);

    // Ahora puedes crear tu scrollbar
    Scrollbar scrollbar(340, thumbHeight, 14); // 340 es la altura 

    scrollbar.setPosition(1260, 340);  // Colocar la barra a la derecha

    // Crear una nueva instancia de sf::CircleShape para la copia
 
    selectedAvatarCopy.setPosition(400, 112);  // Establecer la nueva posición para la copia
    for (int i = 0; i < avatars.size(); i++) {
        sf::Vector2f pos = avatars[i].getPosition();
     
    }
    float avatarYOffset = 0.0f; // Declarar fuera del bucle

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
                avatarYOffset = scrollbar.getScrollOffset();

            }


            if (avatarYOffset > maxScrollOffset) {
                avatarYOffset = maxScrollOffset;  // Límite máximo
            }
            else if (avatarYOffset < 0) {
                avatarYOffset = 0;  // No permitir desplazarse más allá del inicio
            }

            if (avatarYOffset != 0) {
                std::vector<sf::FloatRect> avatarBounds(avatars.size());
                for (int i = 0; i < avatars.size(); ++i) {
                    int column = i % 8;  // Calcular la columna
                    int row = i / 8;     // Calcular la fila

                    float xPos = baseXPos + column * widthSeparation;

                    float yPos = (baseYPos + row * heightSeparation) - avatarYOffset;

                    avatarBounds[i] = sf::FloatRect(xPos, yPos, avatars[i].getGlobalBounds().width, avatars[i].getGlobalBounds().height);

                    avatars[i].setPosition(xPos, yPos);

                }
            }
                // Manejo de clics en avatares
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // Verificar el click en "si" y cerrar la vetana
                if (spriteCkeck.getGlobalBounds().contains(mousePosFloat)) {
                    playClickSound();
                    saveSelectedAvatar();
                    Menup.MenuPrincipal();
                }


                sf::CircleShape* newSelection = nullptr;


                // Obtener el desplazamiento actual de la barra de scroll

                for (int i = 0; i < avatars.size(); ++i) {
                    //sf::Vector2f originalPosition = avatars[i].getPosition();
                  //  sf::FloatRect bounds = avatars[i].getGlobalBounds();
                //    bounds.top -= avatarYOffset;

                    // Verificar si el mouse está sobre el avatar desplazado
                    if (avatars[i].getGlobalBounds().contains(mousePosFloat)) {
                        newSelection = &avatars[i];
                        break;
                    }
                }

                // Lógica para manejar la selección del avatar
                if (spriteX.getGlobalBounds().contains(mousePosFloat)) {
                    playClickSound();
                    Menup.MenuPrincipal();
                }
                if (newSelection != nullptr) {  // Solo actualiza si hay una nueva selección
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
            }
                    // Manejar la entrada de texto
                    textBox.handleInput(event);
                }

                botonX->update(mousePosFloat, currentCursor, linkCursor, normalCursor);

                // ButtonG BotonNo(SpriteBotonNo, TextureBotonNoOff, TextureBotonNoOn);

                window.clear();
                window.draw(SpriteFondoMenu);
                textBox.draw(window);  // Dibujar el cuadro de texto en la ventana

                for (int i = 0; i < avatars.size(); ++i) {

                    sf::Vector2f pos = avatars[i].getPosition();

                    window.draw(avatars[i]);
                }

                // Dibujar solo la copia del avatar seleccionado en la posición del perfil
                if (selectedAvatar != nullptr) {
                    window.draw(selectedAvatarCopy);  // Dibujar solo la copia del avatar seleccionado en su perfil
                }
                scrollbar.draw(window);

                window.draw(recua);
                window.draw(spriteX);
                window.draw(spriteCkeck);
                window.display();
            }
        }
    
void IniciaUser::saveSelectedAvatar(){
    if (selectedAvatar != nullptr) {
        // Encuentra el índice del avatar seleccionado
        int selectedIndex = -1;
        for (int i = 0; i < avatars.size(); ++i) {
            if (&avatars[i] == selectedAvatar) {
                selectedIndex = i;
                break;
            }
        }

        // Verificar si se encontró un índice válido
        if (selectedIndex != -1) {
            // Crear un objeto JSON
            json avatarData;
            avatarData["selected_avatar_index"] = selectedIndex;
            std::cout << "\nInput antes de guardar en Json: " << input << std::endl;

            avatarData["username"] = input;  // Guardar el username (variable input)

            // Guardar en un archivo JSON
            std::ofstream outFile("perfil.json");

            // Verificar si el archivo se puede abrir
            if (outFile.is_open()) {
                outFile << avatarData.dump(4);  // Indentar con 4 espacios para mejor legibilidad
                outFile.close();
                std::cout << "Perfil guardado con éxito: Avatar " << selectedIndex << ", Username: " << input << std::endl;
            }
        }
    }
}

void IniciaUser::loadSelectedAvatar() {


    std::ifstream inFile("perfil.json");
    if (inFile.is_open()) {
        json avatarData;
        inFile >> avatarData;
        inFile.close();

        int selectedIndex = avatarData["selected_avatar_index"];
        input = avatarData["username"];  // Cargar el username desde el archivo

       std::cout << "Perfil cargado: Avatar " << selectedIndex << ", Username: " << input << std::endl;

        // Asegúrate de que el índice sea válido
        if (selectedIndex >= 0 && selectedIndex < avatars.size()) {
            // Establecer el avatar seleccionado
            selectedAvatar = &avatars[selectedIndex];
           // selectedAvatar->setOutlineColor(sf::Color::Black);  // Añadir borde para indicarlo
           // selectedAvatar->setOutlineThickness(4);
            selectedAvatarCopy.setTexture(selectedAvatar->getTexture());  // Copiar la textura
        }
    }
}

