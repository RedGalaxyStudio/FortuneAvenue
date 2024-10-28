#ifndef RESOURCEGAME_HPP
#define RESOURCEGAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>

extern std::vector<sf::CircleShape> AvatarPlayers; 
extern std::vector<std::string> StringNamePlayers;
extern std::vector<sf::Text> NamePlayers;
extern std::vector<sf::Sprite> boxPlayers;
extern sf::Texture TextureFondoGame;
extern  sf::Texture TextureMarco;
extern sf::Sprite spriteFondoGame;
extern std::vector<sf::Sprite> MarcoPlayers;
extern std::vector<sf::Sprite> PiecesSelect;
extern int NumPlayers;
extern sf::SoundBuffer DiceBuffer;
extern sf::Sound DiceSound;
extern sf::Sprite spriteMapa;
extern sf::Clock reloj;
extern sf::View view; 
extern sf::Sprite SpriteArrowDer;
extern std::vector<sf::Sprite> rastro;
extern sf::Sprite SpriteArrowIzq;
void loadResourceGame();
void loadPieceGame();


#endif 

