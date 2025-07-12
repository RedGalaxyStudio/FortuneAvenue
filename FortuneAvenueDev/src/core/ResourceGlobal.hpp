#ifndef RESOURCEGLOBAL_HPP
#define RESOURCEGLOBAL_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../ui/ButtonG.hpp"
#include "../menu/menuP.hpp"
#include <string>
#include <iostream>
extern sf::Music MenuMusicFondo;
extern sf::Music GameMusicFondo;
extern sf::Music SelectingMusicFondo;
extern sf::Text Sesion;
extern sf::RectangleShape overlay;
extern sf::Texture sharedTexture; 
extern sf::Texture Texrecua;
extern sf::Sprite recua;
extern std::string nombre;
extern std::string input1;
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
extern sf::CircleShape selectedAvatarCopy; 
extern sf::Texture textselectedAvatarCopy;
extern sf::Texture textureBox;
extern sf::Sprite box;
extern sf::Font fontUser;
extern sf::Font fontEnd;
extern std::wstring Token;
extern std::string email;
extern std::string id;
extern std::string pictureUrl;
extern sf::Texture TextureBotonSiOn;
extern sf::Texture TextureBotonSiOff;
extern sf::Sprite SpriteBotonSi;
extern sf::Texture TextureAvatarSelec;
extern std::string TextureAvatarPath;
extern sf::Texture TextureBotonNoOn;
extern sf::Texture TextureBotonNoOff;
extern sf::Sprite SpriteBotonNo;
void printMemoryUsage();
void playClickSound();
void createtheWindow(sf::RenderWindow* window, bool fullscreen, const std::string& title = "Fortune Avenue");

#endif 
