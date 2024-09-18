#include "ResourceGlobal.hpp"

// Definir las texturas y cursores

sf::Texture TextureFondoMenu;
sf::Cursor normalCursor;
sf::Cursor linkCursor;
sf::Cursor textCursor;
sf::Cursor moveCursor;
sf::SoundBuffer HoverBuffer;
sf::SoundBuffer ClickBuffer;
std::string nombre;
std::string inpu;
sf::Sound HoverSound;  
sf::Sound ClickSound;  
sf::Cursor* currentCursor;
sf::Texture TextureMuted;
sf::Texture TextureMedium;
sf::Texture TextureHigh;
sf::RenderTexture renderTexture;
sf::Texture textureXOn;
sf::Texture textureXOff;
sf::Sprite spriteX;
ButtonG* botonX = nullptr; // Definici�n de la variable
menuP Menup;

// Funci�n para cargar la textura del fondo del men�
void loadTextures() {
    if (!TextureFondoMenu.loadFromFile("resource/texture/Fondos/fondomenu.png")) return;
    if (!textureXOn.loadFromFile("resource/texture/Button/XOn.png")) return;
    if (!textureXOff.loadFromFile("resource/texture/Button/XOff.png")) return;
    spriteX.setTexture(textureXOff);
    // Ahora que las texturas est�n cargadas, se puede crear el bot�n
    botonX = new ButtonG(spriteX, textureXOff, textureXOn);
}

void loadSounds(){

    if (!HoverBuffer.loadFromFile("resource/sounds/HoverBoton.wav")) return;
    if (!ClickBuffer.loadFromFile("resource/sounds/ClickBoton.wav")) return;

    HoverSound.setBuffer(HoverBuffer);
    ClickSound.setBuffer(ClickBuffer);

};

void loadVolumenIcon() {

    if (!TextureMuted.loadFromFile("resource/texture/Button/VolumeMuted.png")) return;
    if (!TextureMedium.loadFromFile("resource/texture/Button/VolumeMedium.png")) return;
    if (!TextureHigh.loadFromFile("resource/texture/Button/VolumeHigh.png")) return;
}

// Funci�n para cargar los cursores desde una imagen o textura
void loadCursors() {
    sf::Image cursorNormal;
    if (!cursorNormal.loadFromFile("resource/texture/Cursor/normal-select-0.png")) return;

    sf::Image cursorLink;
    if (!cursorLink.loadFromFile("resource/texture/Cursor/link-select-0.png")) return;

    sf::Image cursorText;
    if (!cursorText.loadFromFile("resource/texture/Cursor/text-select-0.png")) return;

    sf::Image cursorMove;
    if (!cursorMove.loadFromFile("resource/texture/Cursor/move-0.png")) return;

    // Tama�o de cada cursor (por ejemplo 32x32)
    sf::Vector2u cursorSize(32, 32);

    // Crear cursores
    if (!normalCursor.loadFromPixels(cursorNormal.getPixelsPtr(), cursorSize, sf::Vector2u(0, 0))) return;

    if (!linkCursor.loadFromPixels(cursorLink.getPixelsPtr(), cursorSize, sf::Vector2u(0, 0))) return;

    if (!textCursor.loadFromPixels(cursorText.getPixelsPtr(), cursorSize, sf::Vector2u(0, 0))) return;

    if (!moveCursor.loadFromPixels(cursorMove.getPixelsPtr(), cursorSize, sf::Vector2u(0, 0))) return;
}
void playClickSound() {
    ClickSound.play();
}
