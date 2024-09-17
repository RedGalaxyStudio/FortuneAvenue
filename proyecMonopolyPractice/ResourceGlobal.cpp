#include "ResourceGlobal.hpp"

// Definir las texturas y cursores
sf::Texture TextureFondoMenu;
sf::Cursor normalCursor;
sf::Cursor linkCursor;
sf::Cursor textCursor;
sf::Cursor moveCursor;
sf::SoundBuffer HoverBuffer;
sf::SoundBuffer ClickBuffer;
sf::Sound HoverSound;  
sf::Sound ClickSound;  


// Función para cargar la textura del fondo del menú
void loadTextures() {
    if (!TextureFondoMenu.loadFromFile("resource/texture/Fondos/fondomenu.png")) return;
}

void loadSounds(){

    if (!HoverBuffer.loadFromFile("resource/sounds/HoverBoton.wav")) return;
    if (!ClickBuffer.loadFromFile("resource/sounds/ClickBoton.wav")) return;

    HoverSound.setBuffer(HoverBuffer);
    ClickSound.setBuffer(ClickBuffer);

};

// Función para cargar los cursores desde una imagen o textura
void loadCursors() {
    sf::Image cursorNormal;
    if (!cursorNormal.loadFromFile("resource/texture/Cursor/normal-select-0.png")) return;

    sf::Image cursorLink;
    if (!cursorLink.loadFromFile("resource/texture/Cursor/link-select-0.png")) return;

    sf::Image cursorText;
    if (!cursorText.loadFromFile("resource/texture/Cursor/text-select-0.png")) return;

    sf::Image cursorMove;
    if (!cursorMove.loadFromFile("resource/texture/Cursor/move-0.png")) return;

    // Tamaño de cada cursor (por ejemplo 32x32)
    sf::Vector2u cursorSize(32, 32);

    // Crear cursores
    if (!normalCursor.loadFromPixels(cursorNormal.getPixelsPtr(), cursorSize, sf::Vector2u(0, 0))) return;

    if (!linkCursor.loadFromPixels(cursorLink.getPixelsPtr(), cursorSize, sf::Vector2u(0, 0))) return;

    if (!textCursor.loadFromPixels(cursorText.getPixelsPtr(), cursorSize, sf::Vector2u(0, 0))) return;

    if (!moveCursor.loadFromPixels(cursorMove.getPixelsPtr(), cursorSize, sf::Vector2u(0, 0))) return;
}
