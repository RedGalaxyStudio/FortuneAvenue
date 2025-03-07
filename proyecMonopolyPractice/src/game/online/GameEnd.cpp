#include "GameEnd.hpp"
#include <iostream>
#include "../../core/ObjetosGlobal.hpp"
#include "../../ui/ResourceGeneral.hpp"

GameEnd::GameEnd(sf::RenderWindow* window, Client* clienT) : window(window),client(clienT) {

}


GameEnd::~GameEnd() {}



sf::Vector2i previousMousePosition;
sf::Vector2i currentMousePosition;

class SpiralConfetti {
public:
    SpiralConfetti(sf::Vector2f position, sf::Color color)
        : position(position), color(color) {
        generateSpiral();
    }

    void update(float deltaTime) {
        position.y += velocity * deltaTime;  
        angle += rotationSpeed * deltaTime;

        if (position.y > windowHeight) {
            position.y = -50;
            position.x = static_cast<float>(rand() % windowWidth);
        }
    }

    void draw(sf::RenderWindow& window) {
        sf::Transform transform;
        transform.translate(position);   
        transform.rotate(angle);        
        window.draw(spiral, transform); 
    }

private:
    sf::Vector2f position;
    sf::Color color;
    float angle = 0;                  
    float rotationSpeed = 50;          
    float velocity = 100;             
    sf::ConvexShape spiral;            

    const int windowWidth = 800;       
    const int windowHeight = 600;      

    void generateSpiral() {
        const int points = 10;         
        const float radiusStep = 2.0f; 
        const float angleStep = 0.5f;  

        std::vector<sf::Vector2f> vertices;
        float radius = 0;
        float theta = 0;

        for (int i = 0; i < points; ++i) {
            // Calcula coordenadas polares
            float x = radius * std::cos(theta);
            float y = radius * std::sin(theta);
            vertices.emplace_back(x, y);

            
            radius += radiusStep;
            theta += angleStep;
        }

        
        spiral.setPointCount(vertices.size());
        for (size_t i = 0; i < vertices.size(); ++i) {
            spiral.setPoint(i, vertices[i]);
        }

        spiral.setFillColor(color);
    }
};


class Confetti {
public:
    Confetti(sf::Vector2f startPosition, sf::Vector2f size, sf::Color color)
        : position(startPosition), size(size), color(color) {

        rect.setSize(size);
        angle = static_cast<float>(rand() % 360);  
        rotationSpeed = static_cast<float>((rand() % 2 == 0 ? -1 : 1) * (rand() % 100 + 50)); 
        velocity.y = static_cast<float>(rand() % 80 + 20); 
        velocity.x = 0;
        if (rand() % 30 == 0) {  
            rotateangle = -1;  
        }
        else {

            rotateangle = 1;
        }
    }


    int rotateangle;

    void update(float deltaTime, float screenHeight, float screenWidth, sf::Vector2i mousePositionn) {


        if (rect.getGlobalBounds().contains(static_cast<float>(mousePositionn.x), static_cast<float>(mousePositionn.y))) {


            if (colision) {
                position.y += velocity.y * deltaTime; 
                position.x += velocity.x * deltaTime;  
                angle += (rotationSpeed * deltaTime) * rotateangle;  

                
                if (position.y > screenHeight) {
                    position.y = screenHeight;  
                    velocity.y = -velocity.y * 0.8f;  
                }
                if (position.x > screenWidth || position.x < 0) {
                    position.x = std::clamp(position.x, 0.f, screenWidth);  
                    velocity.x = -velocity.x * 0.8f;  
                }

                
                velocity.y += 20.f * deltaTime;  

            }
            else {
                sf::Vector2f rectCenter(rect.getPosition().x + rect.getSize().x / 2, rect.getPosition().y + rect.getSize().y / 2);
                sf::Vector2f mouseDirection(mousePositionn.x - rectCenter.x, mousePositionn.y - rectCenter.y);

                float angleToMouse = std::atan2(mouseDirection.y, mouseDirection.x);
                velocity.x = std::cos(angleToMouse) * 150.f;  
                velocity.y = std::sin(angleToMouse) * 150.f;  
                colision = true;
               
                velocity.x *= 0.98f;
                velocity.y *= 0.98f;

            }


        }
        else if (!rect.getGlobalBounds().contains(static_cast<float>(mousePositionn.x), static_cast<float>(mousePositionn.y))) {
            position.y += velocity.y * deltaTime; 
            position.x += velocity.x * deltaTime;  
            angle += (rotationSpeed * deltaTime) * rotateangle;  
            colision = false;
            
            if (position.y > screenHeight) {
                position.y = screenHeight;  
                velocity.y = -velocity.y * 0.8f;  
            }
            if (position.x > screenWidth || position.x < 0) {
                position.x = std::clamp(position.x, 0.f, screenWidth);  
                velocity.x = -velocity.x * 0.8f;  
            }

            
            velocity.y += 20.f * deltaTime;  
        }

        if (position.y > screenHeight) {
            position.y = -size.y;  // Reaparece arriba
            position.x = static_cast<float>(rand() % static_cast<int>(screenWidth));
        }
    }

    void draw(sf::RenderWindow& window) {

        rect.setPosition(position);
        rect.setFillColor(color);
        rect.setRotation(angle);

        window.draw(rect);
    }

private:
    sf::RectangleShape rect;
    bool colision = false;
    sf::Vector2f position;   
    sf::Vector2f size;       
    sf::Vector2f velocity;  
    sf::Color color;         
    float angle;             
    float rotationSpeed;    
};

class ConfettiRain {
public:
    ConfettiRain(size_t confettiCount, float screenWidth, float screenHeight) {
        for (size_t i = 0; i < confettiCount; ++i) {
            // Posición aleatoria inicial
            sf::Vector2f startPosition(
                static_cast<float>(rand() % static_cast<int>(screenWidth)),
                static_cast<float>(rand() % static_cast<int>(screenHeight))
            );

            sf::Vector2f size(
                static_cast<float>(rand() % 15 + 5),  
                static_cast<float>(rand() % 15 + 5)   
            );

            sf::Color color(
                rand() % 256,
                rand() % 256,
                rand() % 256
            );

            confettiList.emplace_back(startPosition, size, color);
        }
    }

    void update(float deltaTime, float screenWidth, float screenHeight, sf::RenderWindow& window) {

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        for (auto& confetti : confettiList) {
            confetti.update(deltaTime, screenHeight, screenWidth, mousePosition);
        }
    }

    void draw(sf::RenderWindow& window) {
        for (auto& confetti : confettiList) {
            confetti.draw(window);
        }
    }

private:
    std::vector<Confetti> confettiList; 
};

/*int main() {
    srand(static_cast<unsigned>(time(nullptr)));  // Semilla para números aleatorios

    // Configuración de la ventana
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Juego en Pantalla Completa", sf::Style::Fullscreen); "Lluvia de Confeti en SFML");
    window.setFramerateLimit(60);

    // Dimensiones del lienzo
    float screenWidth = window.getSize().x;
    float screenHeight = window.getSize().y;

    // Crea una lluvia de confeti
    size_t confettiCount = 400;  // Número de confetis
    ConfettiRain confettiRain(confettiCount, screenWidth, screenHeight);
    std::vector<SpiralConfetti> confettiListt;
    for (int i = 0; i < 50; ++i) {
        sf::Vector2f pos(rand() % 800, rand() % 600);
        sf::Color color(rand() % 256, rand() % 256, rand() % 256);
        confettiListt.emplace_back(pos, color);
    }




    sf::Clock clock;  // Reloj para deltaTime

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float deltaTime = clock.restart().asSeconds() * 1.5;

        for (auto& confetti : confettiListt) {
            confetti.update(deltaTime);
        }

        // Actualización

        previousMousePosition = currentMousePosition;
        currentMousePosition = sf::Mouse::getPosition(window);

        sf::Vector2i deltaMouse = currentMousePosition - previousMousePosition;
        float speed = std::sqrt(deltaMouse.x * deltaMouse.x + deltaMouse.y * deltaMouse.y);

        confettiRain.update(deltaTime, screenWidth, screenHeight, window);


        // Renderizado



        window.clear(sf::Color::Black);


        for (auto& confetti : confettiListt) {
            confetti.draw(window);
        }
        confettiRain.draw(window);
        window.display();
    }

    return 0;
}

*/







void assignPositions(const std::vector<PlayerInfo>& players, std::vector<int>& positions) {
	// Crear un vector de índices
	std::vector<size_t> indices(players.size());
	for (size_t i = 0; i < players.size(); ++i) {
		indices[i] = i;
	}

	std::sort(indices.begin(), indices.end(), [&players](size_t a, size_t b) {
		return players[a].money > players[b].money;
		});

	int currentRank = 1; 
	int playersInSameRank = 0; 
	positions.resize(players.size(), 0);

	for (size_t i = 0; i < indices.size(); ++i) {
		if (i > 0 && players[indices[i]].money == players[indices[i - 1]].money) {
			positions[indices[i]] = currentRank;
			playersInSameRank++;
		}
		else {
			currentRank += playersInSameRank;
			positions[indices[i]] = currentRank;
			playersInSameRank = 1; 
		}
	}
}


void GameEnd::resource() {
	fingame12.setCharacterSize(40);
	fingame12.setFont(fontUser);
	fingame12.setFillColor(sf::Color::White);
	fingame12.setOutlineThickness(2);
	fingame12.setOutlineColor(sf::Color(135, 135, 135));

	fingame12.setString("Fin de la Partida");
	//fingame12.setPosition(640,100);
	//s//f::FloatRect globalBounds = fingame12.getGlobalBounds();
	//fingame12.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
	fingame12.setPosition(440, 70);

	fingame12.setString("Fin de la partida");
	fingame12.setPosition(640,70);
	sf::FloatRect globalBounds = fingame12.getGlobalBounds();
	fingame12.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);


	posicionesGanadores.resize(UsuariosActivos.size());

	assignPositions(playerInfos, posiGndrs);

	for (int i = 0; i < posicionesGanadores.size(); i++) {


		

		posicionesGanadores[i].setCharacterSize(40);
		posicionesGanadores[i].setFont(fontUser);
		posicionesGanadores[i].setFillColor(sf::Color::White);
		posicionesGanadores[i].setOutlineThickness(2);
		posicionesGanadores[i].setOutlineColor(sf::Color(135, 135, 135));
		posicionesGanadores[i].setString(std::to_string(posiGndrs[i])+"°");
		sf::FloatRect globalBounds = posicionesGanadores[i].getGlobalBounds();
		posicionesGanadores[i].setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	}
}

void GameEnd::update() {

	float perfilWidth = 200.0f; 
	float separacion = 20.0f;   
	int totalPerfiles = static_cast<int>(UsuariosActivos.size());      

	if (totalPerfiles > 0) {
		float totalWidth = (totalPerfiles * perfilWidth) + ((totalPerfiles - 1) * separacion);

		float startX = (1280.0f - totalWidth) / 2.0f + (perfilWidth / 2.0f);
        float startY = 290.f;

		for (int i = 0; i < totalPerfiles; i++) {
			float xPos = startX + i * (perfilWidth + separacion); 
			float yPos = startY;
			posicionesGanadores[i].setPosition(xPos, startY- 90);
			playersGame[i].NamePlayer.setPosition(xPos, startY + 70);
			playersGame[i].boxPlayer.setPosition(xPos, startY + 70);
			playersGame[i].AvatarPlayer.setPosition(xPos, startY);
			playersGame[i].MarcoPlayer.setPosition(xPos, startY);
			if (playersGame[i].PieceSelect.getTexture() != nullptr) {
				playersGame[i].PieceSelect.setScale(2.0f, 2.0f);
				sf::FloatRect pieceSelectBounds = playersGame[i].PieceSelect.getGlobalBounds();
				playersGame[i].PieceSelect.setOrigin(pieceSelectBounds.width / 2.0f, pieceSelectBounds.height / 2.0f);
				playersGame[i].PieceSelect.setPosition(xPos + (pieceSelectBounds.width / 2.0f), startY + 220);
			}

			sf::FloatRect moneyBounds = playersGame[i].Money.getGlobalBounds();
			playersGame[i].Money.setOrigin(moneyBounds.width / 2.0f, moneyBounds.height / 2.0f);
			playersGame[i].Money.setPosition(xPos, startY + 120);


		}
	}


	while (window->isOpen()) {


		sf::Event event;

		while (window->pollEvent(event)) {



			sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
			sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

					renderTexture.clear();
					renderTexture.draw(spriteBackgroundG);
					for (int i = 0; i < UsuariosActivos.size(); i++) {
						renderTexture.draw(playersGame[i].NamePlayer);
						renderTexture.draw(playersGame[i].boxPlayer);
						renderTexture.draw(playersGame[i].MarcoPlayer);
						renderTexture.draw(playersGame[i].AvatarPlayer);
					}
					renderTexture.draw(spriteX);
					renderTexture.draw(overlay);


			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {

				renderTexture.clear();
				renderTexture.draw(spriteBackgroundG);
				for (int i = 0; i < 4; i++) {
					renderTexture.draw(playersGame[i].NamePlayer);
					renderTexture.draw(playersGame[i].boxPlayer);
					renderTexture.draw(playersGame[i].MarcoPlayer);
					renderTexture.draw(playersGame[i].AvatarPlayer);
				}
				renderTexture.draw(spriteX);
				renderTexture.draw(overlay);

				Menup.MenuSalir(client);
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				//if (Settings.getGlobalBounds().contains(mousePosFloat)) {
				playClickSound();
				//	Menup.MenuOpcion();
			//	}

			}



				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
					//if (Settings.getGlobalBounds().contains(mousePosFloat)) {
						playClickSound();
	
					
				}
			


		}  

		window->setMouseCursor(*currentCursor);


		window->clear();

		window->draw(spriteBackgroundG);


		window->draw(fingame12);




		float perfilWidth = 200.0f; 
		float separacion = 20.0f;   
		int totalPerfiles = static_cast<int>(UsuariosActivos.size()); 

	
		float totalWidth = (totalPerfiles * perfilWidth) + ((totalPerfiles - 1) * separacion);

		
		float startX = ((1280.0f - totalWidth) / 2.0f) + 100;
		float startY = (720.0f - (180.0f + 70.0f + 50.0f)) / 2.0f;

		if (totalPerfiles > 0) {
			
			float totalWidth = (totalPerfiles * perfilWidth) + ((totalPerfiles - 1) * separacion);

			
			float startX = (1280.0f - totalWidth) / 2.0f + (perfilWidth / 2.0f); 
			float startY = 100.0f; 

			for (int i = 0; i < totalPerfiles; i++) {
				float xPos = startX + i * (perfilWidth + separacion); 
				float yPos = startY;

				playersGame[UsuariosActivos[i]].NamePlayer.setPosition(xPos, startY+170);
				playersGame[UsuariosActivos[i]].boxPlayer.setPosition(xPos, startY+170);
				//playersGame[UsuariosActivos[i]].PieceSelect.setPosition(xPos+ 30, startY + 330);
				playersGame[UsuariosActivos[i]].AvatarPlayer.setPosition(xPos, yPos+100);
				playersGame[UsuariosActivos[i]].AvatarPlayer.setScale(1,1);
				playersGame[UsuariosActivos[i]].MarcoPlayer.setPosition(xPos, yPos+100);

				if (playersGame[UsuariosActivos[i]].PieceSelect.getTexture() != nullptr) {
					playersGame[UsuariosActivos[i]].PieceSelect.setScale(2.0f, 2.0f);
					sf::FloatRect pieceSelectBounds = playersGame[UsuariosActivos[i]].PieceSelect.getGlobalBounds();
					playersGame[UsuariosActivos[i]].PieceSelect.setOrigin(pieceSelectBounds.width / 2.0f, pieceSelectBounds.height / 2.0f);
					playersGame[UsuariosActivos[i]].PieceSelect.setPosition(xPos + (pieceSelectBounds.width / 2.0f), startY + 310);
				}

				sf::FloatRect moneyBounds = playersGame[i].Money.getGlobalBounds();
				playersGame[UsuariosActivos[i]].Money.setOrigin(moneyBounds.width / 2.0f, moneyBounds.height / 2.0f);
				playersGame[UsuariosActivos[i]].Money.setPosition(xPos, yPos + 210);

				if (playersGame[UsuariosActivos[i]].PieceSelect.getTexture() != nullptr) {
		
					playersGame[UsuariosActivos[i]].PieceSelect.setScale(2.0f, 2.0f);

					sf::FloatRect pieceSelectBounds = playersGame[UsuariosActivos[i]].PieceSelect.getGlobalBounds();
					playersGame[UsuariosActivos[i]].PieceSelect.setOrigin(pieceSelectBounds.width / 2.0f, pieceSelectBounds.height / 2.0f);
					
				}
				
				window->draw(playersGame[UsuariosActivos[i]].NamePlayer);
				window->draw(playersGame[UsuariosActivos[i]].boxPlayer);
				window->draw(playersGame[UsuariosActivos[i]].AvatarPlayer);
				window->draw(playersGame[UsuariosActivos[i]].MarcoPlayer);
				window->draw(playersGame[UsuariosActivos[i]].Money);
				window->draw(playersGame[UsuariosActivos[i]].PieceSelect);
			}
		}


		
		for(int i=0;i<UsuariosActivos.size();i++){

		window->draw(playersGame[i].NamePlayer);
		window->draw(playersGame[i].boxPlayer);
		window->draw(playersGame[i].AvatarPlayer);
		window->draw(playersGame[i].MarcoPlayer);
		window->draw(playersGame[i].Money);
		window->draw(playersGame[i].PieceSelect);
		window->draw(posicionesGanadores[i]);
		}
			
		window->draw(fingame12);


		window->display();

	}
}
		




