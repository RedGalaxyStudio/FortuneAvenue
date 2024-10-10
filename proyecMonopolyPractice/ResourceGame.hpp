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
<<<<<<< HEAD
=======
extern std::vector<sf::Sprite> MarcoPlayers;
>>>>>>> cc130ce5fcb8d024f4fbcf6ddc1a896c7e1b6582
extern std::vector<sf::Sprite> PiecesSelect;
extern int NumPlayers;
void loadResourceGame();
void loadPieceGame();
//void playClickSound();


#endif // TEXTUREGLOBAL_HPP

