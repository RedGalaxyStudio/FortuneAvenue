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
extern bool server;

extern sf::Sprite SpriteArrowArriba;

extern std::string Code;
extern int CplayerIndex;
extern bool rolldiceJugador;
struct PlayerInfo {
	std::string username;
	std::string image;
	int money = 200;
	int roomconect;
	bool isSelectingPiece = false; 
	bool isInGame = false;        
	int indexPiece;

};

extern int Opcioncami;
extern bool espera;
extern bool giroRule;
extern bool SelectingPiece; 
extern bool Game;        
extern bool animacionRuleta;        

extern int IndexTurn;

extern bool turn;        
extern bool turn_dado;
extern bool turn_ruleta;
extern bool turn_casa;
extern bool turn_impuesto;
extern bool turn_Moviendo;
extern bool eventoActivo;







struct PlayerGame {

	sf::Texture textureAvatarPLayer;
	sf::CircleShape AvatarPlayer;  
	sf::Sprite MarcoPlayer;
	sf::Text NamePlayer;
	sf::Sprite boxPlayer;
	sf::Sprite PieceSelect;
	sf::Text Money;
};

extern std::vector<PlayerInfo> playerInfos;
extern std::vector<PlayerGame> playersGame;

void loadResourceGame();
void loadPieceGame();


#endif 

