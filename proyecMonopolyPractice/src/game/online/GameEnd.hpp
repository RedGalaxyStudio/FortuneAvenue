#ifndef GAMEEND_HPP
#define GAMEEND_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include "../../network/Client.hpp"


class GameEnd {
private:
    sf::RenderWindow* window;                 
    sf::Text fingame12;
    sf::Text funciona;
    std::vector<sf::Text> posicionesGanadores;
    std::vector<int>posiGndrs;
    Client* client;

    sf::Texture TBotonMenu;
    sf::Texture TBotonPieces;
    sf::Sprite SBotonMenu;
    sf::Sprite SBotonPieces;


public:
    GameEnd(sf::RenderWindow* window, Client* clienT);        
    ~GameEnd();                               
    void resource();
    void update();

};



class Confetti {
public:
	Confetti(sf::Vector2f startPosition, sf::Vector2f size, sf::Color color);


	int rotateangle;
	float lifetime = 5.0f;         // vive 5 segundos
	//float timeAlive = 0.0f;
	//bool alive = true;

	void reset(float screenWidth);

	void update(float deltaTime, float screenHeight, float screenWidth, sf::Vector2i mousePositionn);

	void draw(sf::RenderWindow& window);

private:
	sf::RectangleShape rect;
	bool colision = false;
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Vector2f velocity;
	sf::Color color;
	float angle;
	float rotationSpeed;
		sf::Clock lifeClock;
	//	sf::Clock Vida;
};
class ConfettiRain {
public:
    ConfettiRain(size_t confettiCount, float screenWidth, float screenHeight);

	void update(float deltaTime, float screenWidth, float screenHeight, sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
private:
	std::vector<Confetti> confettiList;
};
#endif
