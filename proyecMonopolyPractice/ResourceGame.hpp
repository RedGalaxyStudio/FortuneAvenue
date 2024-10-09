#ifndef RESOURCEGAME_HPP
#define RESOURCEGAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>



//extern std::vector<sf::CircleShape> avatars;
//extern std::vector<sf::Texture> avatarTextures;
extern std::vector<sf::CircleShape> AvatarPlayers;  // Dinámico para el número de jugadores
extern std::vector<std::string> StringNamePlayers;
extern std::vector<sf::Text> NamePlayers;
extern std::vector<sf::Sprite> boxPlayers;
extern sf::Texture TextureFondoGame;
extern sf::Sprite spriteFondoGame;
extern int NumPlayers;
void loadResourceGame();
void loadPieceGame();
//void playClickSound();


#endif // TEXTUREGLOBAL_HPP

