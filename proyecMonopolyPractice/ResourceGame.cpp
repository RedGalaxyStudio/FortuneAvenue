#include "ResourceGame.hpp"
#include "ResourceGlobal.hpp"

std::vector<sf::CircleShape> AvatarPlayers;  // Din�mico para el n�mero de jugadores
std::vector<std::string> StringNamePlayers;
std::vector<sf::Text> NamePlayers;
std::vector<sf::Sprite> boxPlayers;
std::vector<sf::Sprite> PiecesSelect;
<<<<<<< HEAD
 sf::Texture TextureFondoGame;
 sf::Texture TextureMarco;
 sf::Sprite spriteFondoGame;
 int NumPlayers;
 sf::SoundBuffer DiceBuffer;
 sf::Sound DiceSound;
 std::vector<sf::Sprite> MarcoPlayers;
=======
std::vector<sf::Texture> avatarTextures;
sf::Texture TextureFondoGame;
sf::Texture TextureMarco;
sf::Sprite spriteFondoGame;
int NumPlayers;
sf::SoundBuffer DiceBuffer;
sf::Sound DiceSound;
std::vector<sf::Sprite> MarcoPlayers;
sf::View view; // Declarar la vista
sf::Clock reloj;
std::vector<sf::Sprite> rastro;
sf::Sprite spriteMapa;

sf::Sprite SpriteArrowDer;


sf::Sprite SpriteArrowIzq;

>>>>>>> f72d20990916be5037739544fb6b23cc6932def9

void loadResourceGame(){


<<<<<<< HEAD
	if (!TextureFondoGame.loadFromFile("resource/texture/Game/FondoGame.jpg")) return;
=======
	if (!TextureFondoGame.loadFromFile("resource/texture/Game/FondoGame2.jpg")) return;
>>>>>>> f72d20990916be5037739544fb6b23cc6932def9
	if (!TextureMarco.loadFromFile("resource/texture/Avatars/MarcoTexture.png")) return;
	spriteFondoGame.setTexture(TextureFondoGame);
	// Ajustar el tama�o de los vectores seg�n el n�mero de jugadores
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