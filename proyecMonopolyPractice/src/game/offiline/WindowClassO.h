#pragma once
#include "CubeClassO.h"
#include <SFML/Graphics.hpp>
#include "ResourceGameO.hpp"
#include <cstdlib>
#include <ctime>
#include <random>
class WindowO {

	std::vector<int> textureIndices; 

	float posz = 0;
	
	sf::Vector2i mouseStart;
	sf::Vector2i mouseEnd;
	sf::Mouse mouse;
	sf::VertexArray Cube3D;
	Cube* cube;
	

	float calcdis(sf::Vector2i p1, sf::Vector2i p2)
	{
		float xcb = (static_cast<float>(p2.x) - static_cast<float>(p1.x)) * (static_cast<float>(p2.x) - static_cast<float>(p1.x));
		float ycb = (static_cast<float>(p2.y) - static_cast<float>(p1.y)) * (static_cast<float>(p2.y) - static_cast<float>(p1.y));
		return sqrt(xcb + ycb);
	}





	void updateDraw() {
		textureIndices.clear();  

		for (int i = 0; i < cube->show.size(); i++) {
			std::vector<int> faceid = cube->show[i];
			sf::Vertex* face = &Cube3D[i * 4];  

			
			int textureIndex = -1;
			for (int j = 0; j < 6; j++) {
				if (cube->faces[j] == faceid) {
					textureIndex = j;  
					break;
				}
			}

			if (textureIndex == -1) continue;  

			textureIndices.push_back(textureIndex); 

			for (int j = 0; j < 4; j++) {
				
				face[j].position = sf::Vector2f(cube->C3D[faceid[j]].x, cube->C3D[faceid[j]].y);
				face[j].color = sf::Color::White; 

				
				if (j == 0)
					face[j].texCoords = sf::Vector2f(0, 0);  
				else if (j == 1)
					face[j].texCoords = sf::Vector2f(static_cast<float>(cube->textures[textureIndex].getSize().x), 0);  
				else if (j == 2)
					face[j].texCoords = sf::Vector2f(static_cast<float>(cube->textures[textureIndex].getSize().x),
						static_cast<float>(cube->textures[textureIndex].getSize().y));  
				else if (j == 3)
					face[j].texCoords = sf::Vector2f(0, static_cast<float>(cube->textures[textureIndex].getSize().y));  

			}
		}
	}

	bool isDiceInUse = false;


	void updateDiceAppearance() {

		if (!isDiceInUse) {
			shadowOverlay.setPosition(sf::Vector2f(cube->getPosition().x, cube->getPosition().y));
			window->draw(shadowOverlay);                   
		}
	}


	bool ok = 0;
	


public :
	sf::Clock clock;  
	bool eventStarted = false;  
	sf::RectangleShape shadowOverlay;
	int faceIndex;

	sf::RenderWindow* window;

	WindowO(sf::RenderWindow* windowRef) : window(windowRef) {}


	void start(unsigned int Width, unsigned int Height){

		cube = new Cube(100);
		Cube3D.setPrimitiveType(sf::Quads);
		cube->move(static_cast<float>(Width) / 2, static_cast<float>(Height) / 2, -100.0f);
		cube->draw(static_cast<float>(Width) / 2, static_cast<float>(Height) / 2, static_cast<float>(posz));
		srand(static_cast<unsigned int>(time(0))); 

		
		shadowOverlay.setSize(sf::Vector2f(100, 100)); 
		shadowOverlay.setFillColor(sf::Color(0, 0, 0, 100)); 
		sf::Vector2f size = shadowOverlay.getSize();
		shadowOverlay.setOrigin(size.x / 2, size.y / 2); 

		Cube3D.resize(cube->show.size() * 4);

	}



	void update() {
		
		shadowOverlay.setPosition(sf::Vector2f(cube->getPosition().x, cube->getPosition().y));
		shadowOverlay.setFillColor(sf::Color(0, 0, 0, 100)); 

		updateDraw();


		sf::VertexArray shadow(sf::Quads, cube->show.size() * 4); 


		for (int i = 0; i < cube->show.size(); i++) {
			sf::Vertex* face = &Cube3D[i * 4];  

			
			sf::Color shadowColor(0, 0, 0, 150); 

			
			for (int j = 0; j < 4; j++) {
				sf::Vector2f shadowPosition = face[j].position + sf::Vector2f(5.0f, 5.0f); 

				
				shadow[i * 4 + j].position = shadowPosition;
				shadow[i * 4 + j].color = shadowColor;
			}
		}


		window->draw(shadow);

		for (int i = 0; i < cube->show.size(); i++) {
			sf::RenderStates states;
			if (i < textureIndices.size()) {  
				int textureIndex = textureIndices[i];  
				if (textureIndex == -1) continue;  

				states.texture = &cube->textures[textureIndex];  

				
				sf::Vertex* face = &Cube3D[i * 4];  
				window->draw(face, 4, sf::TrianglesFan, states);  
			}
		}

	}


	void loop(sf::Event event, Client* client)
	{

		if (event.type == sf::Event::Closed) {
			window->close();
		}

		if (turn_dice) {

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
				turn_dice = false;
				DiceSound.play();
				updateDiceAppearance();
				eventStarted = true;
	
	
				mouseStart.x = rand() % 400 + 1;
				mouseStart.y = rand() % 600 + 1;
				ok = 1;
				clock.restart();
	
				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_int_distribution<> dis(1, 6);
				faceIndex =dis(gen);
					
			
				
			}
		}

		

	};
		void loopP(Client* client)
	    {

		
		if (rolldiceJugador) {
			std::unique_lock<std::mutex> lock(client->mtx);

			while (client->lastRollResult == -1) {
				client->cv.wait(lock);
			}

			DiceSound.play();
			updateDiceAppearance();
			eventStarted = true;

			mouseStart.x = rand() % 400 + 1;
			mouseStart.y = rand() % 600 + 1;
			ok = 1;
			clock.restart();

			faceIndex = client->lastRollResult;
			client->lastRollResult = -1;
			//std::cout << "\nResultado en clase dado:" << faceIndex << "\n";
			espera = false;
			rolldiceJugador = false;
			otherturn = false;
		}
	};


	int logica(){
		if (eventStarted) {
			sf::Time elapsed = clock.getElapsedTime(); 

			if (elapsed.asSeconds() < 1.0f) { 
				mouseEnd.x = rand() % 400 + 1; 
				mouseEnd.y = rand() % 600 + 1;  

				float dx = static_cast<float>(mouseEnd.x - mouseStart.x);
				float dy = static_cast<float>(mouseEnd.y - mouseStart.y);

				float disP1 = cube->distanceTo(static_cast<float>(mouseStart.x), static_cast<float>(mouseStart.y), static_cast<float>(posz));

				float alfaX = atan2f(dx, disP1);
				float alfaY = atan2f(dy, disP1);

				cube->rotate(alfaY, alfaX, 0);
				cube->draw(static_cast<float>(window->getSize().x) / 2, static_cast<float>(window->getSize().y) / 2, static_cast<float>(posz));
				Cube3D.resize(cube->show.size() * 4);

				ok = 0; 
				return 0;
			}
			else {
				
				cube->resetPosition(faceIndex);

				cube->draw(static_cast<float>(window->getSize().x) / 2, static_cast<float>(window->getSize().y) / 2, static_cast<float>(posz));
				Cube3D.resize(cube->show.size() * 4);
				eventStarted = false;
				
				return faceIndex;
			}

		}else{ return 0; }
	};
};


