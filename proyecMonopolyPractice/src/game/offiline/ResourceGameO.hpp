#ifndef RESOURCEGAMEO_HPP
#define RESOURCEGAMEO_HPP

#include "GameManager.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>

extern std::vector<sf::Texture> TextureHouse; //texturecasa
extern sf::Texture TextureBackground; //textureFondoGame
extern sf::Texture TextureMoney1; //TextureCash

extern int index;

extern sf::Texture TextureBuilding; //TextureHome
extern  sf::Texture TextureFrame; //TextureMarco
extern sf::Sprite spriteBackground; //spriteFondoGame
extern int NumberPlayers; // numplayers
extern sf::SoundBuffer DiceSoundBuffer; //DiceBuffer
extern sf::Sound DicesSound; //DiceSound
extern sf::Font &fontUserProfile; //&fontUserPerfil
extern sf::Texture &textureBoxPerfilOff; 
extern sf::Sprite MapSprite; //spriteMapa
extern sf::Clock watch; //reloj
extern sf::View vision; //view 
extern sf::Sprite RightArrow; //SpriteArrowDer
extern std::vector<sf::Sprite> trace; //rastro
extern sf::Sprite LeftArrow; //SpriteArrowIzq
extern bool plataform; //server
extern std::vector<sf::Sprite> piecesOff; //pieces
extern sf::Sprite SpriteUpArrow; //SpriteArrowArriba
//extern int previousSelectionIndex[4];
extern bool userRulette; //userRuleta
extern bool userTax; //userImpuesto
extern bool userHouse; //userCasa
extern std::vector<sf::Texture> pieceShape; //piecesTextures
extern sf::SoundBuffer turnBuffer; //girosBuffer
extern sf::Sound turnSound; //girosSound
extern int countsalary; //conteosuel
extern bool zero; //nular
extern std::string Code1; //Code
extern int CplayerIndex1; //CplayerIndex1
extern bool rolldicePlayer; //rolldiceJugador
extern std::string namePlayer; //nameUser
extern sf::Texture CheckOn; //CheckTexturesOn
extern sf::Texture CheckOff; //CheckTexturesOff
struct PlayerInformation {
	std::string playerName; //username
	std::string image1; //image
	int numCasas=0;
	int money = 200;
	int impuesto = 50;
	int roomconect;
	int Posicion;
	bool isSelectingPiece = false; 
	bool isInGame = false;        
	int indexPiece;
	int casasPorJugador[17];
	int Vueltas = 0;
	bool final= false;
	bool PiecUserme = false;
	void reset() {
		playerName.clear();                        // Vaciar el nombre de usuario
		image1.clear();                           // Vaciar la imagen
		money = 200;                             // Restablecer dinero al valor inicial
		roomconect = 0;                          // Restablecer a 0 (o el valor que desees)
		isSelectingPiece = false;                // Reiniciar a falso
		isInGame = false;                        // Reiniciar a falso
		indexPiece = -1;                         // Usar -1 para indicar que no hay pieza seleccionada

	}
};
extern int RoadOption; //Opcioncami
extern bool wait; //espera
extern bool turnRule; //giroRule
extern bool SelectorPieces; //SelectingPiece 
extern bool GamePlay; //Game     
extern bool rouletteAnimation; //animacionRuleta  

extern int IndexTurn1; //IndexTurn

extern bool draw_roulette; //ruleta_draw
extern bool draw_tax; //impuesto_draw
extern bool draw_house; //casa_draw
extern std::vector<int> ActiveUsers; //UsuariosActivos
extern bool firstTurn; // turn       
extern bool secondTurn; //otherturn    
extern bool turn_dice; //turn_dado
extern bool turn_roulette; //turn_ruleta
extern bool turn_house; //turn_casa
extern bool turn_Tax; //turn_impuesto
extern bool turn_Move; //turn_Moviendo
extern bool activeEvent; //eventoActivo

extern GameManager GM;

struct PlayerGameOff {

	sf::Texture textureAvatarPLayer;
	sf::CircleShape AvatarPlayer;  
	sf::Sprite MarcoPlayer;
	sf::Text NamePlayer;
	sf::Text CasasN;
	sf::Sprite Home;
	sf::Sprite boxPlayer;
	sf::Sprite PieceSelect;
	sf::Text Money;
	bool Activo;
	sf::Vector2f origen;
	sf::Texture TextureCash;
	sf::Sprite CashSprite;
	sf::Sprite Check;

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

extern std::vector<PlayerInformation> playerGameInfo; //playersInfo
extern std::vector<PlayerGameOff> playerGameOff; //playersGame

void loadResourceGame();
void loadPieceGame();


#endif 

