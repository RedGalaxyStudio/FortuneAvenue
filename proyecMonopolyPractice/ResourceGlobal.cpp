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
std::vector<sf::CircleShape> avatars;
std::vector<sf::Texture> avatarTextures;
sf::CircleShape selectedAvatarCopy; // Copia del avatar seleccionado




ButtonG* botonX = nullptr; // Definición de la variable
menuP Menup;



void loadAvatars() {

    int avatarCount = 20;  // Si tienes 17 avatares
    avatars.resize(avatarCount);
    avatarTextures.resize(avatarCount);

    for (int i = 0; i < avatarCount; ++i) {
        if (!avatarTextures[i].loadFromFile("resource/texture/Avatars/avatar" + std::to_string(i) + ".png"))
            return;

        float radio = avatarTextures[i].getSize().x / 2.0f;
        avatars[i].setRadius(radio);
        avatars[i].setTexture(&avatarTextures[i]);
        avatars[i].setOrigin(radio, radio);


    }

  for (int i = 0; i < avatars.size(); ++i) {
            int row = i / 8;  // Determina la fila (0 para la primera, 1 para la segunda, etc.)
            int col = i % 8;  // Determina la columna (0 a 7)

            float x = 92.0f + col * 156.0f;  // 28 es la posición inicial en x, 156 es la separación entre columnas
            float y = 472.0f + row * 156.0f;  // 500 es la posición inicial en y, y 156 es la separación entre filas

            avatars[i].setPosition(x, y);
      }
}


// Función para cargar la textura del fondo del menú
void loadTextures() {
    if (!TextureFondoMenu.loadFromFile("resource/texture/Fondos/fondomenu.png")) return;
    if (!textureXOn.loadFromFile("resource/texture/Button/XOn.png")) return;
    if (!textureXOff.loadFromFile("resource/texture/Button/XOff.png")) return;
    spriteX.setTexture(textureXOff);
    // Ahora que las texturas están cargadas, se puede crear el botón
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
void playClickSound() {
    ClickSound.play();
}
