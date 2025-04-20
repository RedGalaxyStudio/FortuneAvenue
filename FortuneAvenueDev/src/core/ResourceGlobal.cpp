#include "ResourceGlobal.hpp"
#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#endif

#include <iostream>

sf::Music MenuMusicFondo;
sf::Music SelectingMusicFondo;
sf::Music GameMusicFondo;
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


sf::CircleShape selectedAvatarCopy; // Copia del avatar seleccionado
sf::Texture textselectedAvatarCopy;
sf::Texture textureBox;
sf::Sprite box;
sf::Font fontUser;
sf::Font fontEnd;
std::wstring Token;
std::string email;
std::string id;
std::string pictureUrl;
sf::RectangleShape overlay;
ButtonG* botonX = nullptr; // Definici�n de la variable
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


void playClickSound() {
    ClickSound.play();
}

