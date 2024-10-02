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
    if (!sharedTexture.loadFromFile("resource/texture/Avatars/Vacio.jpg")) return;
    SpriteFondoMenu.setTexture(TextureFondoMenu);
}

// Actualización de la animación (desvanecimiento del logotipo y fondo animado)
void IniciaUser::Update() {
    if (!std::filesystem::exists("perfil.json")) {
        IniciAcion();
    }else{
        loadSelectedAvatar();
    }
    
}



void IniciaUser::IniciAcion() {
    SpriteBotonSi.setPosition(800, 50);

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
    Scrollbar scrollbar(340, 290, 14);  // Altura de la ventana, altura del thumb
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
                std::cout << avatarWidth << "   " << avatarSeparation << "   " << avatarYOffset;
                float yPos = 472.0f + row * (avatarHeight + avatarSeparation) - avatarYOffset;

                // Establecer la nueva posición del avatar
                avatars[i].setPosition(xPos, yPos);
            }



            // Manejo de clics en avatares
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
          

                // Verificar el click en "si" y cerrar la vetana
                if (SpriteBotonSi.getGlobalBounds().contains(mousePosFloat)) {
                    playClickSound();
                    void saveSelectedAvatar();
                    Menup.MenuPrincipal();
                }
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
                    saveSelectedAvatar();
                }
            }

            // Manejar la entrada de texto
            textBox.handleInput(event);
        }

        botonX->update(mousePosFloat, currentCursor, linkCursor, normalCursor);
        ButtonG BotonSi(SpriteBotonSi, TextureBotonSiOff, TextureBotonSiOn);
       // ButtonG BotonNo(SpriteBotonNo, TextureBotonNoOff, TextureBotonNoOn);

        window.clear();
        window.draw(SpriteFondoMenu);
        textBox.draw(window);  // Dibujar el cuadro de texto en la ventana

        for (int i = 0; i < avatars.size(); ++i) {
            window.draw(avatars[i]);
        }

        // Dibujar solo la copia del avatar seleccionado en la posición del perfil
        if (selectedAvatar != nullptr) {
            window.draw(selectedAvatarCopy);  // Dibujar solo la copia del avatar seleccionado en su perfil
        }
        scrollbar.draw(window);
        window.draw(SpriteBotonSi);
        window.draw(recua);
        window.draw(spriteX);
        window.display();
    }



}

void IniciaUser::saveSelectedAvatar() {
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
            avatarData["username"] = input;  // Guardar el username (variable input)

            // Guardar en un archivo JSON
            std::ofstream outFile("perfil.json");

            // Verificar si el archivo se puede abrir
            if (outFile.is_open()) {
                outFile << avatarData.dump(4);  // Indentar con 4 espacios para mejor legibilidad
                outFile.close();
                std::cout << "Perfil guardado con éxito: Avatar " << selectedIndex << ", Username: " << input << std::endl;
            }
            else {
                std::cerr << "Error: No se pudo abrir el archivo para guardar el perfil." << std::endl;
            }
        }
        else {
            std::cerr << "Error: No se encontró un avatar seleccionado válido para guardar." << std::endl;
        }
    }
    else {
        std::cerr << "Error: No hay avatar seleccionado para guardar." << std::endl;
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
            selectedAvatar->setOutlineColor(sf::Color::Black);  // Añadir borde para indicarlo
            selectedAvatar->setOutlineThickness(4);
            selectedAvatarCopy.setTexture(selectedAvatar->getTexture());  // Copiar la textura
        }
    }
}

