#include "RuletaO.hpp"
#include "ResourceGameO.hpp"
#include <random>
#include <cstdlib> // para rand() y RAND_MAX


RuletaO::RuletaO(float width, float height, float centerX, float centerY)
	: width(width), height(height), centerX(centerX), centerY(centerY), blinkTimer(0.0f), blinkDuration(0.5f), giro(false), resultado(false), currentRotation(0.0f), rotationSpeed(6.0f), turno(true), sincro(false), event(0){

	currentSegment = -1;


	isSpinning = false;
	radius = std::min(width, height) / 2.0f - 20.0f;  

	createSegments();

	loadIconTextures();

	setupIcons();

	setupLights();

	setupBase();

	createPointer();
}

void RuletaO::draw(sf::RenderWindow& window, float deltaTime, bool giroActivo) {

	if (firstTurn) {
		if (giroActivo&& turno) {
			isSpinning = !isSpinning;
			turnSound.play();
			giro = true;
			resultado = true;
			isSpinning = true;
			int i = 0;

			for (auto& segment : segments) {
				segment.setFillColor(segmentColors[i % numSegments]);
				i++;
			}
			turno = false;
			std::random_device rd; // Entropía del sistema
			std::mt19937 gen(rd()); // Generador basado en Mersenne Twister

			std::uniform_int_distribution<> initialSpeedDist(400, 1000);

			initialSpeed = static_cast<float>(initialSpeedDist(gen));
			decelerationRate = initialSpeed / 7.0f;
			rotationSpeed = initialSpeed;			
			clock.restart();
		}
	}
	
	if (!firstTurn) {
		if (giroActivo && turno) {
			isSpinning = !isSpinning;
			turnSound.play();
			giro = true;
			resultado = true;
			isSpinning = true;
			int i = 0;
			for (auto& segment : segments) {
				segment.setFillColor(segmentColors[i % numSegments]);
				i++;
			}
			turno = false;
			std::random_device rd; 
			std::mt19937 gen(rd()); 

			std::uniform_int_distribution<> initialSpeedDist(400, 1000); 

			initialSpeed = static_cast<float>(initialSpeedDist(gen));
			decelerationRate = initialSpeed / 7.0f; 
			rotationSpeed = initialSpeed;
			clock.restart();
		}
	}


	deltaTime = clock.restart().asSeconds();

	if (lightClock.getElapsedTime().asSeconds() > 0.1f) {
		lightState = !lightState;
		lightClock.restart();
	}

	if (isSpinning) {

		currentRotation += rotationSpeed * deltaTime;
		if (currentRotation >= 360.0f) {
			currentRotation = fmod(currentRotation, 360.0f);
		}

		for (auto& segment : segments) {
			segment.setRotation(currentRotation);
		}

		for (int i = 0; i < numSegments; ++i) {
			float iconAngle = static_cast<float>(i * 2 * M_PI / numSegments + M_PI / numSegments + currentRotation * (M_PI / 180.0f)); 
			icons[i].setPosition(centerX + (radius - 70) * cos(iconAngle), centerY + (radius - 70) * sin(iconAngle));
			icons[i].rotate(rotationSpeed * deltaTime);
		}

		rotationSpeed = std::max(rotationSpeed - decelerationRate * deltaTime, 0.0f);

		if (rotationSpeed <= 0.0f) {
			isSpinning = false;

			float finalAngle = fmod(currentRotation, 360.0f);
			int currentSegment = static_cast<int>(finalAngle / (360.0f / numSegments));
		}
	}

	float segmentAngle = 360.0f / numSegments; 

	float pointerX = centerX; 
	float pointerY = centerY - radius; 

	float angle = atan2(pointerY - centerY, pointerX - centerX);
	float pointerAngle = static_cast<float>(angle * (180.0f / M_PI));

	if (pointerAngle < 0) {
		pointerAngle += 360.0f;
	}

	pointerAngle = fmod(pointerAngle - currentRotation + 360.0f, 360.0f);

	currentSegment = -1; 
	for (int i = 0; i < numSegments; ++i) {
		float startAngle = i * segmentAngle; 
		float endAngle = startAngle + segmentAngle; 

		if (pointerAngle >= startAngle && pointerAngle < endAngle) {
			currentSegment = i; 
			break;
		}
	}

	if (currentSegment == -1 && pointerAngle >= (numSegments - 1) * segmentAngle) {
		currentSegment = numSegments - 1;
	}

	sf::Color currentSegmentColor;

	if (!isSpinning && rotationSpeed == 0.0f && giro == true && currentSegment != -1) {

		currentSegmentColor = segments[currentSegment].getFillColor();

		if(firstTurn){
			int totalRestado = 0;
			switch (currentSegment) {
			case 0://pierdes un turno
				GM.turnopermitido -= 1;
				break;

			case 1://roba a un jugador
				event = 3;
				break;

			case 2://comprar una casa
				event = 1;
				break;

			case 3://todos pierden 30 y se les da a el jugador

				for (size_t i = 0; i < ActiveUsers.size();i++) {  
					if (i != IndexTurn1) {

						playerGameInfo[i].money -= 30;

						totalRestado += 30;

					}
				}

				playerGameInfo[IndexTurn1].money += totalRestado;


				for (size_t i = 0; i < ActiveUsers.size(); i++) {

					playerGameOff[i].Money.setString(std::to_string(playerGameInfo[i].money));

					
				}
				break;

			case 4://ganas 150
				
				playerGameInfo[IndexTurn1].money += 150;
				playerGameOff[IndexTurn1].Money.setString(std::to_string(playerGameInfo[IndexTurn1].money));
				break;

			case 5://paga impuestos
				event = 2;
				break;

			case 6://inversion segura se te quitan 100 y 2 turnos despues se te dan 200

				playerGameInfo[IndexTurn1].money -= 100;
				playerGameInfo[IndexTurn1].inversionActiva = true;
				playerGameInfo[IndexTurn1].turnosInversion = 2;
				playerGameOff[IndexTurn1].Money.setString(std::to_string(playerGameInfo[IndexTurn1].money));
				break;

			default:
				break;
			}
		}

		giro = false;

		window.draw(ruletaBase);

		for (auto& segment : segments) {
			segment.setFillColor(currentSegmentColor);
			segment.setOutlineColor(currentSegmentColor);

			fillColor = segment.getFillColor();

			window.draw(segment);


		}

		window.draw(CentroCircule);
		window.draw(iconsResul[currentSegment]);

	}
	else if (!isSpinning && resultado == true) {

		particleSystem.addParticle(ruletaBase.getPosition(), fillColor, 50.0f);
		particleSystem.update(deltaTime);
		particleSystem.draw(window);

		window.draw(ruletaBase);


		for (const auto& segment : segments) {

			fillColor = segment.getFillColor();
			window.draw(segment); // Dibuja el sprite con shader1

		}

		window.draw(CentroCircule);

		rouletteAnimation = true;
		window.draw(iconsResul[currentSegment]);

	}
	else {

		particleSystem.reset();
		window.draw(ruletaBase);

		for (int i = 0; i < 7; i++) {
			segments[i].setFillColor(segmentColors[i]);
			segments[i].setOutlineColor(sf::Color::Black);
			window.draw(segments[i]); 
		}

		window.draw(CentroCircule);

		for (std::size_t i = 0; i < icons.size(); ++i) {
			window.draw(icons[i]);
		}

	}

	window.draw(borde);
	window.draw(pointer);

	drawLights(window, deltaTime);

}


void RuletaO::trurntrue() {

	turno = true;
	resultado = false;

}


void RuletaO::update(float deltaTime) {
	blinkTimer += deltaTime;
	if (blinkTimer >= blinkDuration) {
		blinkTimer = 0.0f;
	}
}

void RuletaO::createSegments() {
	float angleStep = static_cast<float>(2 * M_PI / numSegments);
	for (int i = 0; i < numSegments; ++i) {
		sf::ConvexShape segment;
		segment.setPointCount(13);

		segment.setPoint(0, sf::Vector2f(0, 0));
		segment.setPoint(1, sf::Vector2f(radius * cos(i * angleStep), radius * sin(i * angleStep)));

		for (int j = 0; j <= 10; ++j) {
			float angle = i * angleStep + (j / 10.0f) * angleStep;
			segment.setPoint(j + 2, sf::Vector2f(radius * cos(angle), radius * sin(angle)));
		}

		segment.setPoint(12, sf::Vector2f(radius * cos((i + 1) * angleStep), radius * sin((i + 1) * angleStep)));

		segment.setFillColor(segmentColors[i % numSegments]);
		segment.setOrigin(0.0f, 0.0f);
		segment.setPosition(640, 360);
		segment.setOutlineThickness(2);
		segment.setOutlineColor(sf::Color::Black);
		segments.push_back(segment);
	}

}

void RuletaO::loadIconTextures() {
	iconTextures.resize(numSegments);
	std::string iconPaths[] = {
		"assets/image/IconRulette/icono11.png", "assets/image/IconRulette/icon2.png", "assets/image/IconRulette/icono333.png",
		"assets/image/IconRulette/icon4.png", "assets/image/IconRulette/icono55.png", "assets/image/IconRulette/icono666.png",
		"assets/image/IconRulette/icono7.png" 
	}
	;

	for (int i = 0; i < numSegments; ++i) {
		if (!iconTextures[i].loadFromFile(iconPaths[i])) {
			std::cerr << "Error al cargar la textura del icono" << std::endl;
		}
	}
}

void RuletaO::setupIcons() {

	icons.resize(numSegments);
	iconsResul.resize(numSegments);
	float angleStep = static_cast<float>(2 * M_PI / numSegments);
	float ScaleIcon = radius / 200;
	for (int i = 0; i < numSegments; ++i) {
		icons[i].setTexture(iconTextures[i]);
		icons[i].setOrigin(static_cast<float>(iconTextures[i].getSize().x / 2), static_cast<float>(iconTextures[i].getSize().y / 2));

		float iconAngle = i * angleStep + angleStep / 2;
		icons[i].setPosition(centerX + (radius - 70) * cos(iconAngle), centerY + (radius - 70) * sin(iconAngle));  // 50 es un margen

		icons[i].setRotation(static_cast<float>(iconAngle * (180.0f / M_PI) + 90.0f));

		iconsResul[i].setTexture(iconTextures[i]);
		iconsResul[i].setOrigin(static_cast<float>(iconTextures[i].getSize().x / 2), static_cast<float>(iconTextures[i].getSize().y / 2));
		iconsResul[i].setPosition(centerX, centerY);  // 50 es un margen

	}
}

void RuletaO::setupLights() {

	int numLuces = 14;
	float radioLuces = (radius * 0.04f) + radius;

	for (int i = 0; i < numLuces; ++i) {
		sf::CircleShape luz(4);
		luz.setOutlineThickness(2);
		int alpha = (i % 2 == 0) ? 150 : 100;
		luz.setOutlineColor(sf::Color(255, 255, 255, alpha));
		luz.setOrigin(4, 4);
		float angle = static_cast<float>(2 * M_PI * i / numLuces);
		luz.setPosition(centerX + radioLuces * cos(angle), centerY + radioLuces * sin(angle));
		luces.push_back(luz);
	}
}

void RuletaO::drawLights(sf::RenderWindow& window, float deltaTime) {
	float brightness = static_cast<float>((sin(blinkTimer * (2 * M_PI / blinkDuration)) + 1) * 127.5);

	for (size_t i = 0; i < luces.size(); ++i) {
		sf::CircleShape luz = luces[i];
		luz.setFillColor(sf::Color(255, 255, 255, static_cast<int>(brightness)));

		if (i % 2 == 0) {
			luz.setOutlineColor(sf::Color(255, 0, 0, 150)); // Rojo
		}
		else {
			luz.setOutlineColor(sf::Color(0, 0, 255, 150)); // Azul
		}

		window.draw(luz);
	}
}

void RuletaO::setupBase() {

	CentroCircule.setRadius(static_cast<float>(radius * 0.2));
	CentroCircule.setOrigin(static_cast<float>(radius * 0.2), static_cast<float>(radius * 0.2));
	CentroCircule.setPosition(centerX, centerY);
	CentroCircule.setFillColor(sf::Color(248, 249, 249));
	CentroCircule.setOutlineThickness(radius * 0.015f);
	CentroCircule.setOutlineColor(sf::Color::Black);  

	borde.setRadius(radius);
	borde.setOrigin(radius, radius);
	borde.setPosition(centerX, centerY);
	borde.setFillColor(sf::Color(0, 0, 0, 0));  
	borde.setOutlineThickness(radius * 0.08f);
	borde.setOutlineColor(sf::Color(255, 194, 10)); 

	ruletaBase.setRadius(radius);
	ruletaBase.setOrigin(radius, radius);
	ruletaBase.setPosition(centerX, centerY);
	ruletaBase.setFillColor(sf::Color(50, 50, 50));  
	ruletaBase.setOutlineThickness(radius * 0.02f);
	ruletaBase.setOutlineColor(sf::Color(255, 255, 255)); 


}

void RuletaO::createPointer() {
	pointer.setPointCount(5);
	pointer.setPoint(0, sf::Vector2f(10, 0));
	pointer.setPoint(1, sf::Vector2f(20, 20));
	pointer.setPoint(2, sf::Vector2f(20, 50));
	pointer.setPoint(3, sf::Vector2f(0, 50));
	pointer.setPoint(4, sf::Vector2f(0, 20));
	pointer.setFillColor(sf::Color::Red);
	pointer.setOrigin(10, 28);
	pointer.setPosition(centerX, centerY - radius);
	pointer.setRotation(180); 

}

void RuletaO::animatePointer() {
	static float bounce = 0.0f;
	if (!isSpinning) {
		bounce += 0.1f;
		pointer.setPosition(centerX, centerY - radius + std::sin(bounce) * 5.0f);
	}
	else {
		pointer.setPosition(centerX, centerY - radius);
	}
}