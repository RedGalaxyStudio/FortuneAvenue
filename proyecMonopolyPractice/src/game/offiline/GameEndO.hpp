#ifndef GAMEENDO_HPP
#define GAMEENDO_HPP

#include <SFML/Graphics.hpp>
#include <string>

#include <vector>
#include <algorithm>
#include <iostream>


class GameEndO {
private:
    sf::RenderWindow* window;          
    sf::Text fingame12;
    sf::Text funciona;
    std::vector<sf::Text> posicionesGanadores;
    std::vector<int>posiGndrs;

    sf::Vector2i previousMousePosition;
    sf::Vector2i currentMousePosition;

public:
    GameEndO(sf::RenderWindow* window);       
    ~GameEndO();                              
    void resource();
    void update();

};
class ConfettiO {
public:
	ConfettiO(sf::Vector2f startPosition, sf::Vector2f size, sf::Color color);


	int rotateangle;
	//float lifetime = 5.0f;         // vive 5 segundos
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
	//	sf::Clock lifeClock;
	//	sf::Clock Vida;
};
class ConfettiRainO {
public:
	ConfettiRainO(size_t confettiCount, float screenWidth, float screenHeight);

	void update(float deltaTime, float screenWidth, float screenHeight, sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
private:
	std::vector<ConfettiO> confettiList;
};
#endif 
