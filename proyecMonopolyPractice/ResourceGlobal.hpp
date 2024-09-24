#ifndef RESOURCEGLOBAL_HPP
#define RESOURCEGLOBAL_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ButtonG.hpp"
#include "menuP.hpp"
#include <string>
#include <iostream>
#include <curl/curl.h>



// Declarar la textura global
extern std::string nombre;
extern std::string inpu;
extern menuP Menup;
extern sf::Texture TextureFondoMenu;
extern sf::Cursor normalCursor;
extern sf::Cursor linkCursor;
extern sf::Cursor textCursor;
extern sf::Cursor moveCursor;
extern sf::SoundBuffer HoverBuffer;
extern sf::SoundBuffer ClickBuffer;
extern sf::Sound HoverSound;
extern sf::Sound ClickSound;
extern sf::Cursor* currentCursor;
extern sf::Texture TextureMuted;
extern sf::Texture TextureMedium;
extern sf::Texture TextureHigh;
extern sf::RenderTexture renderTexture;
extern sf::Texture textureXOn;
extern sf::Texture textureXOff;
extern sf::Sprite spriteX;
extern ButtonG* botonX;
extern std::vector<sf::CircleShape> avatars;
extern std::vector<sf::Texture> avatarTextures;
extern sf::CircleShape selectedAvatarCopy; // Copia del avatar seleccionado
extern sf::Texture textureBox;
extern sf::Sprite box;
extern sf::Font fontUser;
extern  std::wstring Token;
extern  std::string email;
extern  std::string id;
extern  std::string pictureUrl;
// Funciones para cargar las texturas y cursores
void loadAvatars();
void playClickSound();
void loadVolumenIcon();
void loadSounds();
void loadTextures();
void loadCursors();
void GetUserEmail();
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);

#endif // TEXTUREGLOBAL_HPP
