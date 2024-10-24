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
extern  sf::Texture TextureMarco;
extern sf::Sprite spriteFondoGame;
extern std::vector<sf::Sprite> MarcoPlayers;
extern std::vector<sf::Sprite> PiecesSelect;
extern int NumPlayers;
extern sf::SoundBuffer DiceBuffer;
extern sf::Sound DiceSound;
<<<<<<< HEAD
=======
extern sf::Sprite spriteMapa;
extern sf::Clock reloj;
extern sf::View view; // Declarar la vista
extern sf::Sprite SpriteArrowDer;
extern std::vector<sf::Sprite> rastro;
extern sf::Sprite SpriteArrowIzq;

>>>>>>> f72d20990916be5037739544fb6b23cc6932def9

void loadResourceGame();
void loadPieceGame();


#endif // TEXTUREGLOBAL_HPP

