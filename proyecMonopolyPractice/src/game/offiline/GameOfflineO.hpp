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


	std::vector<sf::Vector2f> casillasRuleta = {
	sf::Vector2f(402, 157),
	sf::Vector2f(840, 476),
	sf::Vector2f(958, 372),
	sf::Vector2f(930, 231),
	sf::Vector2f(688, 137),
	sf::Vector2f(675, 40),
	sf::Vector2f(514, 141),
	sf::Vector2f(425,654),
	sf::Vector2f(556 , 544),
	sf::Vector2f(632 , 585),
	sf::Vector2f(923, 679),
	sf::Vector2f(328, 161),
	sf::Vector2f(790, 539),
	sf::Vector2f(325,523)
	};

	std::vector<sf::CircleShape> puntos;

	std::vector<sf::Vector2f> caminoimpuesto{
		sf::Vector2f(621 , 677),
		sf::Vector2f(694 ,582),
		sf::Vector2f(413, 253),
		sf::Vector2f(444, 42),
		sf::Vector2f(320, 118),
		sf::Vector2f(869, 679),
		sf::Vector2f(428, 517),
		sf::Vector2f(835, 540),
		sf::Vector2f(805, 450),
		sf::Vector2f(925, 396),
		sf::Vector2f(808, 257),
		sf::Vector2f(882, 238),
		sf::Vector2f(773, 190),
		sf::Vector2f(635, 37)


	};
	int NMapa;

	std::vector<sf::Vector2f> caminocasa{
		sf::Vector2f(807, 416),
		sf::Vector2f(881, 312),
		sf::Vector2f(842, 238),
		sf::Vector2f(874, 132),
		sf::Vector2f(819, 188),
		sf::Vector2f(595, 175),
		sf::Vector2f(505,586),
		sf::Vector2f(568,636),
		sf::Vector2f(694,636),
		sf::Vector2f(368, 339),
		sf::Vector2f(407, 98),
		sf::Vector2f(764, 577),
		sf::Vector2f(429, 566),
		sf::Vector2f(955, 609),
		sf::Vector2f(355, 40),
		sf::Vector2f(323,629),
		sf::Vector2f(394,678)

	};


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
	sf::Texture TextureArrowDer;
	sf::Texture TextureArrowIzq;
	sf::Texture TextureArrowArriba;
	sf::Texture TextureImpuesto;

	sf::Sprite SpriteImpuesto;
	sf::Sprite Settings;
	sf::Sprite renderedSprite;
	sf::Sprite SpriteChat;

};
#endif