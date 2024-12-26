#include "ResourceGame.hpp"
#include "ResourceGlobal.hpp"



sf::Texture &textureBoxPerfil= textureBox;
sf::Font &fontUserPerfil=fontUser ;
std::vector<sf::Texture> avatarTextures;
sf::Texture TextureFondoGame;
sf::Texture TextureMarco;
sf::Sprite spriteFondoGame;
int NumPlayers;
sf::SoundBuffer DiceBuffer;
std::string nameUser;
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

 sf::SoundBuffer girosBuffer;
 sf::Sound girosSound;
 bool nular;
int conteosuel;
sf::Sprite SpriteArrowIzq;
bool SelectingPiece = false; // Inicialmente en selección de pieza
bool Game = false;        // No en juego al principio
std::vector<PlayerInfo> playerInfos;
std::vector<PlayerGame> playersGame;
bool espera;
bool giroRule;
int CplayerIndex = -1;
int Opcioncami;

bool userRuleta;
bool userImpuesto;
bool userCasa;




std::vector<int> UsuariosActivos;

bool turn;
bool otherturn;
bool turn_dado;
bool turn_ruleta;
bool turn_casa;
bool turn_impuesto;
bool turn_Moviendo;
bool eventoActivo;
bool isSpinning;
int IndexTurn;
bool ruleta_draw;
bool impuesto_draw;
bool casa_draw;

void loadResourceGame(){

	if (!TextureFondoGame.loadFromFile("resource/texture/Game/FondoGame2.jpg")) return;
	if (!TextureMarco.loadFromFile("resource/texture/Avatars/MarcoTexture.png")) return;
	spriteFondoGame.setTexture(TextureFondoGame);
	fontUserPerfil = fontUser;
	espera=false;
}
void loadPieceGame(){}