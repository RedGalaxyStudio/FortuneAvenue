#include "ResourceGameO.hpp"
#include "../../core/ResourceGlobal.hpp"



sf::Texture &textureBoxPerfil= textureBox;

std::vector<sf::Texture> TextureHouse; //texturecasa
sf::Texture TextureMoney1; //texturecash
sf::Texture TextureBuilding; //texturehome
sf::Font &fontUserProfile =fontUser ; //&fontUserPerfil
std::vector<sf::Texture> avatarTextures; 
sf::Texture TextureFondoGame; //TextureFondoGame
sf::Texture TextureFrame; //textureMarco
sf::Sprite spriteBackground;
int NumberPlayers;
sf::SoundBuffer DiceSoundBuffer;
std::string namePlayer;
sf::Sound DicesSound;
sf::View vision; // Declarar la vista //view
sf::Clock watch; //reloj
std::vector<sf::Sprite> trace;
sf::Sprite MapSprite;
std::vector<sf::Sprite> pieces;
//int previousSelectionIndex[4];
std::vector<sf::Texture> pieceShape;
sf::Texture CheckOn;
sf::Texture CheckOff;
std::string Code1; //code
sf::Sprite RightArrow;
bool rouletteAnimation; //animacionRuleta
sf::Sprite SpriteUpArrow;
bool plataform; //server
bool rolldicePlayer;
std::string playerName; //username
std::vector<char> image1; //image Store image data directly.

 sf::SoundBuffer turnBuffer; //girosBuffer
 sf::Sound turnSound; //girosSound
 bool zero;
int countsalary;
sf::Sprite LeftArrow;
bool SelectorPieces = false; // Inicialmente en selección de pieza
bool GamePlay = false;        // No en juego al principio
std::vector<PlayerInformation> playerGameInfo;
std::vector<PlayerGame> playerGame;
bool wait;
bool turnRule;
int CplayerIndex1 = -1;
int RoadOption;

bool userRulette;
bool userTax;
bool userHouse;




std::vector<int> ActiveUsers;

bool firstTurn;
bool secondTurn;
bool turn_dice;
bool turn_roulette;
bool turn_house;
bool turn_Tax;
bool turn_Move;
bool activeEvent;
bool isSpinning; //no cambie esta variable porque es parte de ruleta.hpp
int IndexTurn1;
bool draw_roulette;
bool draw_tax;
bool draw_house;

void loadResourceGameO(){

	if (!TextureFondoGame.loadFromFile("assets/image/Game/FondoGame2.jpg")) return;
	if (!TextureFrame.loadFromFile("assets/image/Avatars/MarcoTexture.png")) return;
	spriteBackground.setTexture(TextureFondoGame);
	fontUserProfile = fontUser;
	wait=false;
}
