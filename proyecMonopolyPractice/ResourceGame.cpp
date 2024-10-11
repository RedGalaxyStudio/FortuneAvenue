#include "ResourceGame.hpp"
#include "ResourceGlobal.hpp"

std::vector<sf::CircleShape> AvatarPlayers;  // Dinámico para el número de jugadores
std::vector<std::string> StringNamePlayers;
std::vector<sf::Text> NamePlayers;
std::vector<sf::Sprite> boxPlayers;
std::vector<sf::Sprite> PiecesSelect;
 sf::Texture TextureFondoGame;
 sf::Texture TextureMarco;
 sf::Sprite spriteFondoGame;
 int NumPlayers;
 sf::SoundBuffer DiceBuffer;
 sf::Sound DiceSound;
 std::vector<sf::Sprite> MarcoPlayers;

void loadResourceGame(){


	if (!TextureFondoGame.loadFromFile("resource/texture/Game/FondoGame.jpg")) return;
	if (!TextureMarco.loadFromFile("resource/texture/Avatars/MarcoTexture.png")) return;
	spriteFondoGame.setTexture(TextureFondoGame);
	// Ajustar el tamaño de los vectores según el número de jugadores
	AvatarPlayers.resize(4);
	StringNamePlayers.resize(4);
	MarcoPlayers.resize(4);
	NamePlayers.resize(4);
	boxPlayers.resize(4);
	PiecesSelect.resize(4);

	for (int i = 0; i < 4; i++)
	{
		boxPlayers[i].setTexture(textureBox);
		boxPlayers[i].setOrigin(125, 40);
		boxPlayers[i].setScale(0.9f, 0.9f);
		MarcoPlayers[i].setTexture(TextureMarco);
		NamePlayers[i].setCharacterSize(17);
		NamePlayers[i].setFont(fontUser);
		NamePlayers[i].setFillColor(sf::Color::White);
		NamePlayers[i].setOutlineThickness(2);
		NamePlayers[i].setOutlineColor(sf::Color(135, 135, 135));
		
	}



}
void loadPieceGame(){}