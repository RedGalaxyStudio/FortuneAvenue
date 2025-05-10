#ifndef RESOURCEGAMEO_HPP
#define RESOURCEGAMEO_HPP


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "GameManager.hpp"

class GameManager;
extern bool giroActivoO;
extern sf::Texture textureBoxPerfilOn;
extern float initialSpeedActiO;
extern float decelerationRateActiO;
extern bool BotTurn;
extern GameManager GM;
extern std::vector<sf::Texture> TextureHouse; //texturecasa
extern sf::Texture TextureMoney1; //TextureCash
extern int customIndex;
extern sf::Texture TextureBuilding; //TextureHome
extern sf::Texture TextureFrame; //TextureMarco
extern int NumberPlayers; // numplayers
extern sf::Font &fontUserProfile; //&fontUserPerfil
extern sf::Texture &textureBoxPerfilOff; 
extern sf::Sprite MapSprite; //spriteMapa
extern sf::Clock watch; //reloj
extern sf::View vision; //view 
extern std::vector<sf::Sprite> trace; //rastro
extern bool plataform; //server
extern std::vector<sf::Sprite> piecesOff; //pieces
extern int previousSelectionIndex[4];
extern bool userRulette; //userRuleta
extern bool userTax; //userImpuesto
extern bool userHouse; //userCasa
extern std::vector<sf::Texture> pieceShape; //piecesTextures
extern int countsalary; //conteosuel
extern bool zero; //nular
extern std::string Code1; //Code
extern int CplayerIndex1; //CplayerIndex1
extern bool rolldicePlayer; //rolldicePlayer
extern std::string namePlayer; //nameUser
extern sf::Texture CheckOn; //CheckTexturesOn
extern sf::Texture CheckOff; //CheckTexturesOff
struct PlayerInformation {
	int impuesto = 50;
	int salario = 60;
	int controlSalario = 0;
	bool inversionActiva = false;
	int turnosInversion = 0;
	bool GameFinal = false;
	bool GameTerm = false;

	std::string playerName; //username
	std::string image; //image
	int numCasas=0;
	int money = 200;

	int turnopermitido = 0;

	int roomconect=00000;
	int Posicion=0;
	bool isSelectingPiece = false; 
	bool isInGame = false;        
	int indexPiece=-1;
	std::vector<int> casasPorJugador;
	int Vueltas = 0;
	bool final= false;
	bool PiecUserme = false;
	void reset() {
		playerName.clear();                      
		image.clear();                           
		money = 200;                            
		roomconect = 0;                         
		isSelectingPiece = false;                
		isInGame = false;                       
		indexPiece = -1; 
		turnopermitido = 0;

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
extern bool turn_diceB; //turn_dado
extern bool turn_roulette; //turn_ruleta
extern bool turn_house; //turn_casa
extern bool turn_Tax; //turn_impuesto
extern bool turn_Move; //turn_Moviendo
extern bool activeEvent; //eventoActivo
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
	bool Activo=false;
	sf::Vector2f origen;
	sf::Texture TextureCash;
	sf::Sprite CashSprite;
	sf::Sprite Check;

	void reset() {
		textureAvatarPLayer = sf::Texture();  
		AvatarPlayer = sf::CircleShape();    
		//MarcoPlayer = sf::Sprite();          
		NamePlayer = sf::Text();             
		//boxPlayer = sf::Sprite();            
		PieceSelect = sf::Sprite();          
		Money = sf::Text();                  
		Activo = false;                     
	}

};

extern std::vector<PlayerInformation> playerGameInfo; //playersInfo
extern std::vector<PlayerGameOff> playerGameOff; //playersGame

void loadResourceGameO();
bool salirXoff(sf::Texture Pregunta, sf::RenderWindow* window);
void resetGameResourcesO();
#endif 

