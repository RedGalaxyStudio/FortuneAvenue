#ifndef RESOURCEGAME_HPP
#define RESOURCEGAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "../../network/Client.hpp"
#include <vector>
class Client;

extern std::vector<sf::Texture> TextureCasa;
extern bool Resourceready;
extern sf::Texture TextureCash;
extern sf::Texture TextureHome;
extern  sf::Texture TextureMarco;

extern int NumPlayers;
extern sf::Font &fontUserPerfil;
extern sf::Texture &textureBoxPerfil;
extern sf::Sprite spriteMapa;
extern sf::Clock reloj;
extern sf::View view; 
extern sf::Sprite SpriteArrowDer;
extern std::vector<sf::Sprite> rastro;
extern sf::Sprite SpriteArrowIzq;
extern sf::Sprite SpriteArrowAbajo;
extern bool server;
extern std::vector<sf::Sprite> pieces;
extern sf::Sprite SpriteArrowArriba;
extern int previousSelectionIndex[4];
extern bool userRuleta;
extern bool userImpuesto;
extern bool userCasa;
extern std::vector<sf::Texture> piecesTextures;
extern int conteosuel;
extern bool nular;
extern std::string Code;
extern int CplayerIndex;
extern bool rolldiceJugador;
extern std::string nameUser;
extern sf::Texture CheckTexturesOn;
extern sf::Texture CheckTexturesOff;

extern bool chatOn;
struct PlayerInfo {
	std::string username;
	std::string image;
	int numCasas=0;
	int money = 300;
	int impuesto = 50;
	int roomconect;
	int Posicion;
	bool isSelectingPiece = false; 
	bool isInGame = false;        
	int indexPiece;
	std::vector<int> casasPorJugador;
	int Vueltas = 0;
	bool final= false;
	bool PiecUserme = false;

	PlayerInfo() : casasPorJugador(17) {}

	void reset() {
		username.clear();                     
		image.clear();                           
		money = 200;                            
		roomconect = 0;                       
		isSelectingPiece = false;             
		isInGame = false;                       
		indexPiece = -1;                         

	}
};

extern int Opcioncami;
extern bool espera;
extern bool giroRule;
extern bool SelectingPiece; 
extern bool Game;        
extern bool animacionRuleta;      

extern bool ChatOn;

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

struct MensajeMSG {
	sf::CircleShape AvatarEnviado;
	sf::Text SMSEnviado;
	sf::RectangleShape ContenidoEnviado;
	sf::Text NombreChat;
	sf::Vector2f positionSMSEnviado;
	sf::Vector2f positionContenidoEnviado;
	sf::Vector2f positionAvatarEnviado;
	sf::Vector2f positionNombreChat;
	
};
extern MensajeMSG PlantillaMensajeR;
extern std::vector <MensajeMSG> Mensajes;

struct PlayerGame {

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
	MensajeMSG plantillaMsg;
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

extern std::vector<PlayerInfo> playerInfos;
extern std::vector<PlayerGame> playersGame;

void loadResourceGame();
bool salirX(sf::Texture Pregunta,sf::RenderWindow* window, Client* cliente);


#endif 

