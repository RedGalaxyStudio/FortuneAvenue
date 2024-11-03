#ifndef RESOURCEGAME_HPP
#define RESOURCEGAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>


extern sf::Texture TextureFondoGame;
extern  sf::Texture TextureMarco;
extern sf::Sprite spriteFondoGame;
extern int NumPlayers;
extern sf::SoundBuffer DiceBuffer;
extern sf::Sound DiceSound;
extern sf::Sprite spriteMapa;
extern sf::Clock reloj;
extern sf::View view; 
extern sf::Sprite SpriteArrowDer;
extern std::vector<sf::Sprite> rastro;
extern sf::Sprite SpriteArrowIzq;

extern sf::Sprite SpriteArrowArriba;

extern std::string Code;
extern int CplayerIndex;

struct PlayerInfo {
	std::string username;
	std::vector<char> image;
	int money = 200;
	int roomconect;
	bool isSelectingPiece = true; // Inicialmente en selección de pieza
	bool isInGame = false;        // No en juego al principio
	int indexPiece;

};

extern bool espera;
extern bool SelectingPiece; // Inicialmente en selección de pieza
extern bool Game;        // No en juego al principio
extern bool muerte;        // No en juego al principio

struct PlayerGame {


	sf::CircleShape AvatarPlayer;  // Dinámico para el número de jugadores
	sf::Sprite MarcoPlayer;
	sf::Text NamePlayer;
	sf::Sprite boxPlayer;
	sf::Sprite PieceSelect;
};

extern std::vector<PlayerInfo> playerInfos;
extern std::vector<PlayerGame> playersGame;

void loadResourceGame();
void loadPieceGame();


#endif 

