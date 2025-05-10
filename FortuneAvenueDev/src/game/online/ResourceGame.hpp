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
extern sf::Texture textureBoxPerfiloff;
extern int NumPlayers;
extern sf::Font &fontUserPerfil;
extern sf::Texture &textureBoxPerfil;
extern sf::Sprite spriteMapa;
extern sf::Clock reloj;
extern sf::View view; 
extern std::vector<sf::Sprite> rastro;
extern bool server;
extern std::vector<sf::Sprite> pieces;
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

extern bool ReturnMenu;
extern bool ReturnPieces;
extern bool chatOn;
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
	bool Activo=false;
	sf::Vector2f origen;
	sf::Texture TextureCash;
	sf::Sprite CashSprite;
	sf::Sprite Check;
	MensajeMSG plantillaMsg;
	void reset() {    
		PieceSelect = sf::Sprite();
		Money = sf::Text();
		origen= sf::Vector2f();
		MarcoPlayer.setScale(0.9f, 0.9f);
	}

};

struct PlayerInfo {
	std::string username;
	std::string image;
	int numCasas = 0;
	int money = 300;
	int impuesto = 50;
	int roomconect=-0;
	int Posicion=-1;
	bool isSelectingPiece = false;
	bool isInGame = false;
	int indexPiece=-1;
	std::vector<int> casasPorJugador;
	int Vueltas = 0;
	bool final = false;
	bool PiecUserme = false;


	PlayerInfo() : casasPorJugador(17) {}

	void reset() {
		numCasas = 0;
		money = 300;
		impuesto = 50;
		Vueltas = 0;
		isSelectingPiece = false;
		isInGame = false;
		indexPiece = -1;
		final = false;
		PiecUserme = false;
		casasPorJugador.clear();
		casasPorJugador.resize(17);
	}

};


extern std::vector<PlayerInfo> playerInfos;
extern std::vector<PlayerGame> playersGame;

void loadResourceGame();
bool salirX(sf::Texture Pregunta,sf::RenderWindow* window, Client* cliente);
void resetGameResources();

#endif 

