#include "ResourceGlobal.hpp"
#include <fstream>
#include  "nlohmann/json.hpp"
// Definir las texturas y cursores

using json = nlohmann::json;

sf::Text Sesion;
sf::Texture TextureFondoMenu;
sf::Cursor normalCursor;
sf::Cursor linkCursor;
sf::Cursor textCursor;
sf::Cursor moveCursor;
sf::SoundBuffer HoverBuffer;
sf::SoundBuffer ClickBuffer;
std::string nombre;
std::string input1;
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


sf::CircleShape selectedAvatarCopy; // Copia del avatar seleccionado

sf::Texture textureBox;
sf::Sprite box;
sf::Font fontUser;
std::wstring Token;
std::string email;
std::string id;
std::string pictureUrl;
sf::RectangleShape overlay;
ButtonG* botonX = nullptr; // Definición de la variable
sf::Texture TextureAvatarSelec;
sf::Texture sharedTexture; // Textura compartida para los avatares
sf::Texture TextureBotonSiOn;
sf::Texture TextureBotonSiOff;
sf::Sprite SpriteBotonSi;

sf::Texture TextureBotonNoOn;
sf::Texture TextureBotonNoOff;
sf::Sprite SpriteBotonNo;
std::string TextureAvatarPath;
sf::Texture Texrecua;
sf::Sprite recua;




// Función para cargar la textura del fondo del menú
void loadTextures() {
    if (!TextureFondoMenu.loadFromFile("resource/texture/Fondos/fondomenu.png")) return;
    if (!textureXOn.loadFromFile("resource/texture/Button/XOn.png")) return;
    if (!textureXOff.loadFromFile("resource/texture/Button/XOff.png")) return;
    if (!TextureBotonSiOn.loadFromFile("resource/texture/Button/BotonSiOn.png")) return;
    if (!TextureBotonSiOff.loadFromFile("resource/texture/Button/BotonSiOff.png")) return;
    if (!TextureBotonNoOn.loadFromFile("resource/texture/Button/BotonNoOn.png")) return;
    if (!TextureBotonNoOff.loadFromFile("resource/texture/Button/BotonNoOff.png")) return;
    spriteX.setTexture(textureXOff);
    SpriteBotonNo.setTexture(TextureBotonNoOff);   
    SpriteBotonSi.setTexture(TextureBotonSiOff);
    // Ahora que las texturas están cargadas, se puede crear el botón
    botonX = new ButtonG(spriteX, textureXOff, textureXOn);
    if (!fontUser.loadFromFile("resource/fonts/ARCADEPI.ttf")) {
        std::cerr << "Error loading font\n";
    }
    if (!textureBox.loadFromFile("resource/texture/Button/rectanguloEncendido.png")) return;
    box.setTexture(textureBox);
    box.setOrigin(125,40);
    
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

