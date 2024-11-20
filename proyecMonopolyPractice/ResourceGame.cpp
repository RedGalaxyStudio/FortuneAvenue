#include "ResourceGame.hpp"
#include "ResourceGlobal.hpp"

std::vector<sf::Texture> avatarTextures;
sf::Texture TextureFondoGame;
sf::Texture TextureMarco;
sf::Sprite spriteFondoGame;
int NumPlayers;
sf::SoundBuffer DiceBuffer;
sf::Sound DiceSound;
sf::View view; // Declarar la vista
sf::Clock reloj;
std::vector<sf::Sprite> rastro;
sf::Sprite spriteMapa;
std::string Code;
sf::Sprite SpriteArrowDer;
bool animacionRuleta;
sf::Sprite SpriteArrowArriba;
bool server;
bool rolldiceJugador;
std::string username;
std::vector<char> image; // Store image data directly.

sf::Sprite SpriteArrowIzq;
bool SelectingPiece = false; // Inicialmente en selección de pieza
bool Game = false;        // No en juego al principio
std::vector<PlayerInfo> playerInfos;
std::vector<PlayerGame> playersGame;
bool espera;
bool giroRule;
int CplayerIndex;
int Opcioncami;

bool turn;
bool turn_dado;
bool turn_ruleta;
bool turn_casa;
bool turn_impuesto;
bool turn_Moviendo;

int IndexTurn;


void loadResourceGame(){

	if (!TextureFondoGame.loadFromFile("resource/texture/Game/FondoGame2.jpg")) return;
	if (!TextureMarco.loadFromFile("resource/texture/Avatars/MarcoTexture.png")) return;
	spriteFondoGame.setTexture(TextureFondoGame);

	playerInfos.resize(4);
	playersGame.resize(4);
	espera=false;
	for (int i = 0; i < 4; i++)
	{
		playersGame[i].boxPlayer.setTexture(textureBox);
		playersGame[i].boxPlayer.setOrigin(125, 40);
		playersGame[i].boxPlayer.setScale(0.9f, 0.9f);
		playersGame[i].MarcoPlayer.setTexture(TextureMarco);
		playersGame[i].NamePlayer.setCharacterSize(17);
		playersGame[i].NamePlayer.setFont(fontUser);
		playersGame[i].NamePlayer.setFillColor(sf::Color::White);
		playersGame[i].NamePlayer.setOutlineThickness(2);
		playersGame[i].NamePlayer.setOutlineColor(sf::Color(135, 135, 135));
		
	}



}
void loadPieceGame(){}