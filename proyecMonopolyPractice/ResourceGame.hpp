#ifndef RESOURCEGAME_HPP
#define RESOURCEGAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>


extern sf::Texture TextureFondoGame;
extern sf::Texture TextureCash;
extern  sf::Texture TextureMarco;
extern sf::Sprite spriteFondoGame;
extern int NumPlayers;
extern sf::SoundBuffer DiceBuffer;
extern sf::Sound DiceSound;
extern sf::Font &fontUserPerfil;
extern sf::Texture &textureBoxPerfil;
extern sf::Sprite spriteMapa;
extern sf::Clock reloj;
extern sf::View view; 
extern sf::Sprite SpriteArrowDer;
extern std::vector<sf::Sprite> rastro;
extern sf::Sprite SpriteArrowIzq;
extern bool server;

extern sf::Sprite SpriteArrowArriba;

extern bool userRuleta;
extern bool userImpuesto;
extern bool userCasa;

extern sf::SoundBuffer girosBuffer;
extern sf::Sound girosSound;
extern int conteosuel;
extern bool nular;
extern std::string Code;
extern int CplayerIndex;
extern bool rolldiceJugador;
extern std::string nameUser;
struct PlayerInfo {
	std::string username;
	std::string image;
	int money = 200;
	int roomconect;
	bool isSelectingPiece = false; 
	bool isInGame = false;        
	int indexPiece;
	int casasPorJugador[17];
	void reset() {
		username.clear();                        // Vaciar el nombre de usuario
		image.clear();                           // Vaciar la imagen
		money = 200;                             // Restablecer dinero al valor inicial
		roomconect = 0;                          // Restablecer a 0 (o el valor que desees)
		isSelectingPiece = false;                // Reiniciar a falso
		isInGame = false;                        // Reiniciar a falso
		indexPiece = -1;                         // Usar -1 para indicar que no hay pieza seleccionada
		//std::fill(std::begin(casasPorJugador),   // Reiniciar todas las casas a 0
		//	std::end(casasPorJugador), 0);
	}
};

extern int Opcioncami;
extern bool espera;
extern bool giroRule;
extern bool SelectingPiece; 
extern bool Game;        
extern bool animacionRuleta;        

extern int IndexTurn;

extern bool ruleta_draw;
extern bool impuesto_draw;
extern bool casa_draw;
extern std::vector<int> UsuariosActivos;
extern bool turn;        
extern bool otherturn;        
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
	bool Activo;

	sf::Texture TextureCash;
	sf::Sprite CashSprite;

	void reset() {
		textureAvatarPLayer = sf::Texture();  // Reasignar un objeto nuevo
		AvatarPlayer = sf::CircleShape();    // Reasignar un objeto nuevo
		//MarcoPlayer = sf::Sprite();          // Reasignar un objeto nuevo
		NamePlayer = sf::Text();             // Reasignar un objeto nuevo
		//boxPlayer = sf::Sprite();            // Reasignar un objeto nuevo
		PieceSelect = sf::Sprite();          // Reasignar un objeto nuevo
		Money = sf::Text();                  // Reasignar un objeto nuevo
		Activo = false;                      // Restablecer a falso
	}

};

extern std::vector<PlayerInfo> playerInfos;
extern std::vector<PlayerGame> playersGame;

void loadResourceGame();
void loadPieceGame();


#endif 

