#include "GameEnd.hpp"
#include <iostream>
#include "../../core/ObjetosGlobal.hpp"
#include "../../ui/ResourceGeneral.hpp"
#include "ResourceGame.hpp"
#include "../../core/ResourceGlobal.hpp"
GameEnd::GameEnd(sf::RenderWindow* window, Client* clienT) : window(window), client(clienT) {

}


GameEnd::~GameEnd() {}
sf::Vector2i previousMousePosition;
sf::Vector2i currentMousePosition;

ConfettiRain::ConfettiRain(size_t confettiCount, float screenWidth, float screenHeight) {
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

void ConfettiRain::update(float deltaTime, float screenWidth, float screenHeight, sf::RenderWindow& window) {

	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

	for (auto& confetti : confettiList) {
		confetti.update(deltaTime, screenHeight, screenWidth, mousePosition);
	}
}

void ConfettiRain::draw(sf::RenderWindow& window) {
	for (auto& confetti : confettiList) {
		confetti.draw(window);
	}
}

Confetti::Confetti(sf::Vector2f startPosition, sf::Vector2f size, sf::Color color)
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


	void Confetti::reset(float screenWidth) {
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
	
	}

	void Confetti::update(float deltaTime, float screenHeight, float screenWidth, sf::Vector2i mousePositionn) {


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

	void Confetti::draw(sf::RenderWindow& window) {

		rect.setPosition(position);
		rect.setFillColor(color);
		rect.setRotation(angle);

		window.draw(rect);
	}



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

	if (!fontEnd.loadFromFile("assets/fonts/Pixels.ttf")) {
		//   std::cerr << "Error loading font\n";
	}

	if (!TBotonMenu.loadFromFile("assets/image/Button/volveramenu.png")) return;
	if (!TBotonPieces.loadFromFile("assets/image/Button/volverajugar.png")) return;


	SBotonMenu.setTexture(TBotonMenu);
	//SBotonMenu.setScale(0.1f, 0.1f);
	SBotonMenu.setPosition(1160 - 70, 650);
	sf::FloatRect globalBounds = SBotonMenu.getGlobalBounds();

	SBotonMenu.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

	SBotonPieces.setTexture(TBotonPieces);
	//SBotonPieces.setScale(0.1f, 0.1f);
	SBotonPieces.setPosition(120 + 70, 650);
	globalBounds = SBotonPieces.getGlobalBounds();
	SBotonPieces.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

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
	fingame12.setPosition(640, 70);
	globalBounds = fingame12.getGlobalBounds();
	fingame12.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);


	posicionesGanadores.resize(UsuariosActivos.size());

	assignPositions(playerInfos, posiGndrs);

	for (int i = 0; i < posicionesGanadores.size(); i++) {




		posicionesGanadores[i].setCharacterSize(80);
		posicionesGanadores[i].setFont(fontEnd);
		posicionesGanadores[i].setFillColor(sf::Color::White);
		posicionesGanadores[i].setOutlineThickness(2);
		posicionesGanadores[i].setOutlineColor(sf::Color(135, 135, 135));
		posicionesGanadores[i].setString(std::to_string(posiGndrs[i]) + "©");
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
			posicionesGanadores[i].setPosition(xPos + 80, startY - 210);
			playersGame[i].NamePlayer.setPosition(xPos, startY + 70);
			playersGame[i].boxPlayer.setPosition(xPos, startY + 70);
			playersGame[i].AvatarPlayer.setPosition(xPos, startY);
			playersGame[i].MarcoPlayer.setPosition(xPos, startY);
			if (playersGame[i].PieceSelect.getTexture() != nullptr) {
				playersGame[i].PieceSelect.setScale(2.0f, 2.0f);
				sf::FloatRect pieceSelectBounds = playersGame[i].PieceSelect.getGlobalBounds();
				playersGame[i].PieceSelect.setOrigin(pieceSelectBounds.width / 2.0f, pieceSelectBounds.height / 2.0f);
				playersGame[i].PieceSelect.setPosition(xPos + (pieceSelectBounds.width / 2.0f), startY + 250);
			}

			sf::FloatRect moneyBounds = playersGame[i].Money.getGlobalBounds();
			playersGame[i].Money.setOrigin(moneyBounds.width / 2.0f, moneyBounds.height / 2.0f);
			playersGame[i].Money.setPosition(xPos, startY + 120);


		}
	}
	srand(static_cast<unsigned>(time(nullptr)));  // Semilla para números aleatorios

	// Dimensiones del lienzo
	float screenWidth = static_cast<float>(window->getSize().x);
	float screenHeight = static_cast<float>(window->getSize().y);

	// Crea una lluvia de confeti
	size_t confettiCount = 400;  // Número de confetis
	ConfettiRain confettiRain(confettiCount, screenWidth, screenHeight);
	//std::vector<SpiralConfetti> confettiListt;
	//for (int i = 0; i < 50; ++i) {
	//	sf::Vector2f pos(rand() % 800, rand() % 600);
	//	sf::Color color(rand() % 256, rand() % 256, rand() % 256);
	//	confettiListt.emplace_back(pos, color);
	//}

	sf::Clock clock;  // Reloj para deltaTime

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
				for (int i = 0; i < UsuariosActivos.size(); i++) {
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
				if (SBotonMenu.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					ReturnMenu = true;

				}
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
					if (SBotonPieces.getGlobalBounds().contains(mousePosFloat)) {
						playClickSound();
						ReturnPieces = true;
					}
				}

				if (ReturnPieces) {
					return;
				}

				if (ReturnMenu) {
					return;
				}
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

				playersGame[UsuariosActivos[i]].NamePlayer.setPosition(xPos, startY + 198);
				playersGame[UsuariosActivos[i]].boxPlayer.setPosition(xPos, startY + 200);
				//playersGame[UsuariosActivos[i]].PieceSelect.setPosition(xPos+ 30, startY + 330);
				playersGame[UsuariosActivos[i]].AvatarPlayer.setPosition(xPos, yPos + 100);
				playersGame[UsuariosActivos[i]].AvatarPlayer.setScale(0.8f, 0.8f);
				playersGame[UsuariosActivos[i]].MarcoPlayer.setScale(1.3f, 1.3f);
				playersGame[UsuariosActivos[i]].MarcoPlayer.setPosition(xPos, yPos + 100);

				if (playersGame[UsuariosActivos[i]].PieceSelect.getTexture() != nullptr) {
					playersGame[UsuariosActivos[i]].PieceSelect.setScale(2.0f, 2.0f);
					sf::FloatRect pieceSelectBounds = playersGame[UsuariosActivos[i]].PieceSelect.getGlobalBounds();
					playersGame[UsuariosActivos[i]].PieceSelect.setOrigin(pieceSelectBounds.width / 2.0f, pieceSelectBounds.height / 2.0f);
					playersGame[UsuariosActivos[i]].PieceSelect.setPosition(xPos + (pieceSelectBounds.width / 2.0f), startY + 340);
				}

				sf::FloatRect moneyBounds = playersGame[i].Money.getGlobalBounds();
				playersGame[UsuariosActivos[i]].Money.setOrigin(moneyBounds.width / 2.0f, moneyBounds.height / 2.0f);
				playersGame[UsuariosActivos[i]].Money.setPosition(xPos, yPos + 240);

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


		for (int i = 0; i < UsuariosActivos.size(); i++) {

			window->draw(playersGame[i].NamePlayer);
			window->draw(playersGame[i].boxPlayer);
			window->draw(playersGame[i].AvatarPlayer);
			window->draw(playersGame[i].MarcoPlayer);
			window->draw(playersGame[i].Money);
			window->draw(playersGame[i].PieceSelect);
			window->draw(posicionesGanadores[i]);
		}

		window->draw(SBotonMenu);
		window->draw(SBotonPieces);

		window->draw(fingame12);
		//for (auto& confetti : confettiListt) {
		//	confetti.draw(*window);
		//}


		window->display();

	}

}





