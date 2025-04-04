#ifndef GAMEOFFLINEO_HPP
#define GAMEOFFLINEO_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <thread>
#include <atomic>
#include "../../core/ObjetosGlobal.hpp"
#include "WindowClassO.h"
#include "RuletaO.hpp"
#include "MovePiecesO.hpp"
#include "PieceSelectorO.hpp"
#include "ResourceGameO.hpp"
#include "GameManager.hpp"
#include "nuloO.hpp"
#include "HouseBuyO.hpp"
class RuletaO;
class HouseBuyO;

class GameOffline {
public:


	bool turnoGiro;
	GameOffline(sf::RenderWindow& win, int NumMapa);

	void resource();

	void update();
	void Event();
	void DrawPieceMoviendo();
	void DrawGame();
	void DrawGameRuleta();
	void DrawGameImpuesto();
	void InicioPartida();
	void positionPefil();

	
private:
	sf::Text Conteosuel;

	int auxHouse ;
	bool ActiveHouse ;

	Client* client;
	sf::Clock clockMensaje; 
	float currentScale = 1.0f; 
	float minScale = 0.8f;      
	float maxScale = 1.2f;    
	float duration = 2.0f;      
	bool increasing = true;    
	int impuestoCasa;
	
	sf::RenderWindow* window;
	std::vector<std::vector<std::vector<sf::Vector2f>>> casillas;
	std::vector<sf::Vector2f> origenS;


	std::vector<sf::Vector2f> casillasRuleta;

	std::vector<sf::CircleShape> puntos;

	std::vector<sf::Vector2f> caminoimpuesto;
	int NMapa;

	std::vector<sf::Vector2f> caminocasa;


	sf::Text Bienvenida;
	sf::Text DescripDado;

	sf::FloatRect globalBounds;
	int posicionActual;
	int vectorActual; 
	sf::Vector2i mousePosition;
	sf::Vector2f mousePosFloat;
	int resultadoDado;
	sf::Texture piecesTextures;
	sf::Sprite pieces;


	std::vector<MovePiecesO> moverFichas;
	std::vector<HouseBuyO> house;
	sf::Clock TempoAnimacion;
	bool animacionIniciada;
	WindowO Dado;
	sf::Clock clock;

	bool animacionImpuesto;
	bool animacionCasa;
	RuletaO* ruleta;
	sf::View viewTablero;
	sf::Text Impuesto;
	sf::Text ImpuestoCasa;
	
	sf::Texture TextureChat;
	sf::Texture TextureMapa;
	sf::Texture SettingsOn;
	sf::Texture SettingsOff;

	sf::Texture TextureImpuesto;

	sf::Sprite SpriteImpuesto;
	sf::Sprite Settings;
	sf::Sprite renderedSprite;
	sf::Sprite SpriteChat;

};
#endif