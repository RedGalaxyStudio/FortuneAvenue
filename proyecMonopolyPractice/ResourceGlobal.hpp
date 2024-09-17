#ifndef RESOURCEGLOBAL_HPP
#define RESOURCEGLOBAL_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
// Declarar la textura global
extern sf::Texture TextureFondoMenu;
extern sf::Cursor normalCursor;
extern sf::Cursor linkCursor;
extern sf::Cursor textCursor;
extern sf::Cursor moveCursor;
extern sf::SoundBuffer HoverBuffer;
extern sf::SoundBuffer ClickBuffer;
extern sf::Sound HoverSound;
extern sf::Sound ClickSound;

// Funciones para cargar las texturas y cursores
void loadSounds();
void loadTextures();
void loadCursors();

#endif // TEXTUREGLOBAL_HPP
