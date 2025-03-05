#include "ResourceGlobal.hpp"
#include <windows.h>
#include <psapi.h>
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

// Función para cargar los cursores desde una imagen o textura
void printMemoryUsage() {
    PROCESS_MEMORY_COUNTERS memInfo;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo))) {
        std::cout << "Memoria en uso: " << (memInfo.WorkingSetSize / 1024) << " KB" << std::endl;
        std::cout << "Memoria Peak: " << (memInfo.PeakWorkingSetSize / 1024) << " KB" << std::endl;
        std::cout << "Memoria Virtual: " << (memInfo.PagefileUsage / 1024) << " KB" << std::endl;
    }
}

void playClickSound() {
    ClickSound.play();
}

