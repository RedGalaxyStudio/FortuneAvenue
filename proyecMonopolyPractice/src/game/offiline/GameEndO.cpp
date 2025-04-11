#include "GameEndO.hpp"
#include <iostream>
#include "../../core/ObjetosGlobal.hpp"
#include "../../ui/ResourceGeneral.hpp"
#include "ResourceGameO.hpp"
#include "../../core/ResourceGlobal.hpp"
GameEndO::GameEndO(sf::RenderWindow* window) : window(window) {

}

GameEndO::~GameEndO() {}

ConfettiRainO::ConfettiRainO(size_t confettiCount, float screenWidth, float screenHeight) {
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

void ConfettiRainO::update(float deltaTime, float screenWidth, float screenHeight, sf::RenderWindow& window) {

	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

	for (auto& confetti : confettiList) {
		confetti.update(deltaTime, screenHeight, screenWidth, mousePosition);
	}
}

void ConfettiRainO::draw(sf::RenderWindow& window) {
	for (auto& confetti : confettiList) {
		confetti.draw(window);
	}
}

ConfettiO::ConfettiO(sf::Vector2f startPosition, sf::Vector2f size, sf::Color color)
	: position(startPosition), size(size), color(color) {
	//Vida.restart();
	std::cout << "\nInicio de vida: ";
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


void ConfettiO::reset(float screenWidth) {
	position.y = -size.y;
	position.x = static_cast<float>(rand() % static_cast<int>(screenWidth));
	velocity.y = static_cast<float>(rand() % 80 + 20);
	velocity.x = 0;
	angle = static_cast<float>(rand() % 360);
	rotationSpeed = static_cast<float>((rand() % 2 == 0 ? -1 : 1) * (rand() % 100 + 50));
	//timeAlive = 0.f;
	colision = false;
	color = sf::Color(rand() % 256, rand() % 256, rand() % 256);
	size = sf::Vector2f(static_cast<float>(rand() % 15 + 5), static_cast<float>(rand() % 15 + 5));
	rect.setSize(size);
	//Vida.restart();
}

void ConfettiO::update(float deltaTime, float screenHeight, float screenWidth, sf::Vector2i mousePositionn) {

	//float tiempoVivo = Vida.getElapsedTime().asSeconds();
	//std::cout << "Tiempo actual de vida: " << tiempoVivo << " segundos\n";


	//if (tiempoVivo >= lifetime) {
	//	std::cout << "\n888112" << Vida.getElapsedTime().asSeconds();
	//	reset(screenWidth);
	//	return;
	//}

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

void ConfettiO::draw(sf::RenderWindow& window) {

	rect.setPosition(position);
	rect.setFillColor(color);
	rect.setRotation(angle);

	window.draw(rect);
}

void assignPositions(const std::vector<PlayerInformation>& players, std::vector<int>& positions) {
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


void GameEndO::resource() {

	if (!fontEnd.loadFromFile("assets/fonts/Pixels.ttf")) {
		//   std::cerr << "Error loading font\n";
	}

	fingame12.setCharacterSize(40);
	fingame12.setFont(fontUser);
	fingame12.setFillColor(sf::Color::White);
	fingame12.setOutlineThickness(2);
	fingame12.setOutlineColor(sf::Color(135, 135, 135));

	fingame12.setString("Fin de la Partida");
	fingame12.setPosition(440, 70);

	fingame12.setString("Fin de la partida");
	fingame12.setPosition(640,70);
	sf::FloatRect globalBounds = fingame12.getGlobalBounds();
	fingame12.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);


	posicionesGanadores.resize(ActiveUsers.size());

	assignPositions(playerGameInfo, posiGndrs);

	for (int i = 0; i < posicionesGanadores.size(); i++) {

		posicionesGanadores[i].setCharacterSize(80);
		posicionesGanadores[i].setFont(fontEnd);
		posicionesGanadores[i].setFillColor(sf::Color::White);
		posicionesGanadores[i].setOutlineThickness(2);
		posicionesGanadores[i].setOutlineColor(sf::Color(135, 135, 135));
		posicionesGanadores[i].setString(std::to_string(posiGndrs[i])+"©");
		sf::FloatRect globalBounds = posicionesGanadores[i].getGlobalBounds();
		posicionesGanadores[i].setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	}
}

void GameEndO::update() {

	float perfilWidth = 200.0f; 
	float separacion = 20.0f;  
	int totalPerfiles = static_cast<int>(ActiveUsers.size());    

	if (totalPerfiles > 0) {
		float totalWidth = (totalPerfiles * perfilWidth) + ((totalPerfiles - 1) * separacion);

		float startX = (1280.0f - totalWidth) / 2.0f + (perfilWidth / 2.0f);

		float startY = 290.f;

		for (int i = 0; i < totalPerfiles; i++) {
			float xPos = startX + i * (perfilWidth + separacion);
			float yPos = startY;
			posicionesGanadores[i].setPosition(xPos + 80, startY - 210);
			playerGameOff[i].NamePlayer.setPosition(xPos, startY + 70);
			playerGameOff[i].boxPlayer.setPosition(xPos, startY + 70);
			playerGameOff[i].AvatarPlayer.setPosition(xPos, startY);
			playerGameOff[i].MarcoPlayer.setPosition(xPos, startY);
			if (playerGameOff[i].PieceSelect.getTexture() != nullptr) {
				playerGameOff[i].PieceSelect.setScale(2.0f, 2.0f);
				sf::FloatRect pieceSelectBounds = playerGameOff[i].PieceSelect.getGlobalBounds();
				playerGameOff[i].PieceSelect.setOrigin(pieceSelectBounds.width / 2.0f, pieceSelectBounds.height / 2.0f);
				playerGameOff[i].PieceSelect.setPosition(xPos + (pieceSelectBounds.width / 2.0f), startY + 250);
			}

			sf::FloatRect moneyBounds = playerGameOff[i].Money.getGlobalBounds();
			playerGameOff[i].Money.setOrigin(moneyBounds.width / 2.0f, moneyBounds.height / 2.0f);
			playerGameOff[i].Money.setPosition(xPos, startY + 120);


		}
	}

	srand(static_cast<unsigned>(time(nullptr)));  // Semilla para números aleatorios

	// Dimensiones del lienzo
	float screenWidth = static_cast<float>(window->getSize().x);
	float screenHeight = static_cast<float>(window->getSize().y);

	// Crea una lluvia de confeti
	size_t confettiCount = 400;  // Número de confetis
	ConfettiRainO confettiRain(confettiCount, screenWidth, screenHeight);

	sf::Clock clock;


	while (window->isOpen()) {


		sf::Event event;

		while (window->pollEvent(event)) {



			sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
			sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

					renderTexture.clear();
					renderTexture.draw(spriteBackgroundG);
					for (int i = 0; i < ActiveUsers.size(); i++) {
						renderTexture.draw(playerGameOff[i].NamePlayer);
						renderTexture.draw(playerGameOff[i].boxPlayer);
						renderTexture.draw(playerGameOff[i].MarcoPlayer);
						renderTexture.draw(playerGameOff[i].AvatarPlayer);
					}
					renderTexture.draw(spriteX);
					renderTexture.draw(overlay);


			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {

				renderTexture.clear();
				renderTexture.draw(spriteBackgroundG);
				for (int i = 0; i < ActiveUsers.size(); i++) {
					renderTexture.draw(playerGameOff[i].NamePlayer);
					renderTexture.draw(playerGameOff[i].boxPlayer);
					renderTexture.draw(playerGameOff[i].MarcoPlayer);
					renderTexture.draw(playerGameOff[i].AvatarPlayer);
				}
				renderTexture.draw(spriteX);
				renderTexture.draw(overlay);

				Menup.MenuSalir(nullptr);
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				playClickSound();
			}

				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
						playClickSound();
				}
			
		}  


		float deltaTime = static_cast<float>(clock.restart().asSeconds() * 1.5);

		//for (auto& confetti : confettiListt) {
			//confetti.update(deltaTime);
		//}

		previousMousePosition = currentMousePosition;
		currentMousePosition = sf::Mouse::getPosition(*window);

		sf::Vector2i deltaMouse = currentMousePosition - previousMousePosition;
		float speed = static_cast<float>(std::sqrt(deltaMouse.x * deltaMouse.x + deltaMouse.y * deltaMouse.y));

		confettiRain.update(deltaTime, screenWidth, screenHeight, *window);

		window->setMouseCursor(*currentCursor);


		window->clear();

		window->draw(spriteBackgroundG);


		window->draw(fingame12);

		confettiRain.draw(*window);

		float perfilWidth = 200.0f; 
		float separacion = 20.0f;  
		int totalPerfiles = static_cast<int>(ActiveUsers.size());
		float totalWidth = (totalPerfiles * perfilWidth) + ((totalPerfiles - 1) * separacion);
		float startX = ((1280.0f - totalWidth) / 2.0f) + 100;
		float startY = (720.0f - (180.0f + 70.0f + 50.0f)) / 2.0f;


		if (totalPerfiles > 0) {
			
			float totalWidth = (totalPerfiles * perfilWidth) + ((totalPerfiles - 1) * separacion);
			float startX = (1280.0f - totalWidth) / 2.0f + (perfilWidth / 2.0f);
			float startY = 100.0f;


			for (int i = 0; i < totalPerfiles; i++) {
				float xPos = startX + i * (perfilWidth + separacion); // Calcula la posición en X para cada perfil
				float yPos = startY;

				playerGameOff[ActiveUsers[i]].NamePlayer.setPosition(xPos, startY+198);
				playerGameOff[ActiveUsers[i]].boxPlayer.setPosition(xPos, startY+200);
				//playerGameOff[ActiveUsers[i]].PieceSelect.setPosition(xPos+ 30, startY + 330);
				playerGameOff[ActiveUsers[i]].AvatarPlayer.setPosition(xPos, yPos+100);
				playerGameOff[ActiveUsers[i]].AvatarPlayer.setScale(0.8f, 0.8f);
				playerGameOff[ActiveUsers[i]].MarcoPlayer.setScale(1.3f, 1.3f);
				playerGameOff[ActiveUsers[i]].MarcoPlayer.setPosition(xPos, yPos+100);

				if (playerGameOff[ActiveUsers[i]].PieceSelect.getTexture() != nullptr) {
					playerGameOff[ActiveUsers[i]].PieceSelect.setScale(2.0f, 2.0f);
					sf::FloatRect pieceSelectBounds = playerGameOff[ActiveUsers[i]].PieceSelect.getGlobalBounds();
					playerGameOff[ActiveUsers[i]].PieceSelect.setOrigin(pieceSelectBounds.width / 2.0f, pieceSelectBounds.height / 2.0f);
					playerGameOff[ActiveUsers[i]].PieceSelect.setPosition(xPos + (pieceSelectBounds.width / 2.0f), startY + 340);
				}

				sf::FloatRect moneyBounds = playerGameOff[i].Money.getGlobalBounds();
				playerGameOff[ActiveUsers[i]].Money.setOrigin(moneyBounds.width / 2.0f, moneyBounds.height / 2.0f);
				playerGameOff[ActiveUsers[i]].Money.setPosition(xPos, yPos + 240);

				if (playerGameOff[ActiveUsers[i]].PieceSelect.getTexture() != nullptr) {

					playerGameOff[ActiveUsers[i]].PieceSelect.setScale(2.0f, 2.0f);
					sf::FloatRect pieceSelectBounds = playerGameOff[ActiveUsers[i]].PieceSelect.getGlobalBounds();
					playerGameOff[ActiveUsers[i]].PieceSelect.setOrigin(pieceSelectBounds.width / 2.0f, pieceSelectBounds.height / 2.0f);
					std::cout << "\npiece: " << pieceSelectBounds.width / 2.0f << "," << pieceSelectBounds.height / 2.0f;
					
				}
				
				window->draw(playerGameOff[ActiveUsers[i]].NamePlayer);
				window->draw(playerGameOff[ActiveUsers[i]].boxPlayer);
				window->draw(playerGameOff[ActiveUsers[i]].AvatarPlayer);
				window->draw(playerGameOff[ActiveUsers[i]].MarcoPlayer);
				window->draw(playerGameOff[ActiveUsers[i]].Money);
				window->draw(playerGameOff[ActiveUsers[i]].PieceSelect);
			}
		}
		
		for(int i=0;i<ActiveUsers.size();i++){
		// Dibujar los elementos en la ventana
		window->draw(playerGameOff[i].NamePlayer);
		window->draw(playerGameOff[i].boxPlayer);
		window->draw(playerGameOff[i].AvatarPlayer);
		window->draw(playerGameOff[i].MarcoPlayer);
		window->draw(playerGameOff[i].Money);
		window->draw(playerGameOff[i].PieceSelect);
		window->draw(posicionesGanadores[i]);
		}
			
		window->draw(fingame12);

		window->display();

	}
}
		




