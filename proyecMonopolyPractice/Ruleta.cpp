#include "Ruleta.hpp"
#include "ResourceGame.hpp"
#include <cstdlib> // Para rand() y RAND_MAX


Ruleta::Ruleta(float width, float height, float centerX, float centerY)
	: width(width), height(height), centerX(centerX), centerY(centerY), blinkTimer(0.0f), blinkDuration(0.5f), giro(false), resultado(false), currentRotation(0.0f), isSpinning(false), rotationSpeed(6.0f), turno(true) {
	// Inicializar shaders
	if (!shader.loadFromFile("shaderlink.frag", sf::Shader::Fragment)) {
		std::cerr << "Error al cargar el shader" << std::endl;
	}

	if (!noise.loadFromFile("shader_noise.frag", sf::Shader::Fragment)) {
		std::cerr << "Error al cargar el shader" << std::endl;
	}
	if (!glowShader.loadFromFile("shader_glow.frag", sf::Shader::Fragment)) {
		std::cerr << "Error al cargar el shader de glow" << std::endl;
	}

	if (!shader_gradient.loadFromFile("shader_gradient.frag", sf::Shader::Fragment)) {
		std::cerr << "Error al cargar el shader de glow" << std::endl;
	}

	radius = std::min(width, height) / 2.0f - 20.0f;  // Deja un margen de 20 píxeles


	renderTexture1.create(static_cast<unsigned int>(radius * 2), static_cast<unsigned int>(radius * 2));

	renderTexture2.create(static_cast<unsigned int>(radius * 2), static_cast<unsigned int>(radius * 2));


	sf::Vector2f lightOrigin(640, 360); // Origen de la luz

	shader.setUniform("frag_LightColor", sf::Glsl::Vec3(1.5f, 1.5f, 1.5f)); // Color de luz más brillante
	shader.setUniform("frag_LightOrigin", lightOrigin);
	shader.setUniform("frag_LightAttenuation", 0.01f); // Atenuación de luz más baja
	shader.setUniform("frag_ScreenResolution", sf::Vector2f(1280, 720));

	// Crear segmentos
	createSegments();

	// Cargar texturas para los íconos
	loadIconTextures();

	// Configurar íconos
	setupIcons();

	// Agregar luces alrededor de la ruleta
	setupLights();

	setupBase();

	// Inicializar pointer
	createPointer();
}

void Ruleta::draw(sf::RenderWindow& window, float deltaTime, bool Validar) {

	if (Validar && turno) {
		isSpinning = !isSpinning;
	    giro = true;
		resultado = true;
		int i = 0;
	//	for (auto& segment : segments) {
			//segment.getRotation();
			//segment.rotate(100);


	//	}
		for (auto& segment : segments) {
			segment.setFillColor(segmentColors[i % numSegments]);
			i++;
			//std::cout << "El rotationSpeed * deltaTime: " << rotationSpeed * deltaTime << std::endl;
		}
		turno = false;
		// Variables para variaciones aleatorias
		initialSpeed = static_cast<float>(rand() % 100 + 400); // Velocidad inicial aleatoria entre 400 y 500
		decelerationRate = static_cast<float>(rand() % 20 + 40); // Desaceleración aleatoria entre 40 y 60

		rotationSpeed = (isSpinning) ? 300.0f : 0.0f;
		clock.restart();  // Reiniciar el reloj para calcular el tiempo desde el inicio de la rotación
	}


	deltaTime = clock.restart().asSeconds();

	// Cambiar el estado de las luces cada 0.1 segundos
	if (lightClock.getElapsedTime().asSeconds() > 0.1f) {
		lightState = !lightState;
		lightClock.restart();
	}

	// Rotar la ruleta
	if (isSpinning) {
		currentRotation += rotationSpeed * deltaTime; // Aumenta el ángulo de rotación
		std::cout << "El currentRotation: " << currentRotation << std::endl;

		if (currentRotation >= 360.0f) {
			currentRotation = fmod(currentRotation, 360.0f); // Mantén el ángulo dentro de 0-360
		}

		// Rota cada segmento de la ruleta
		for (auto& segment : segments) {
			segment.rotate(rotationSpeed * deltaTime);
		}

		// Actualizar la posición de los íconos para que roten junto con la ruleta
		for (int i = 0; i < numSegments; ++i) {
			float iconAngle = static_cast<float>(i * 2 * M_PI / numSegments + M_PI / numSegments + currentRotation * (M_PI / 180.0f));
			icons[i].setPosition(centerX + (radius - 50) * cos(iconAngle), centerY + (radius - 50) * sin(iconAngle));  // 50 es un margen

			if (rotationSpeed == 0.0f) {
				isSpinning = false;
			}
			icons[i].rotate(rotationSpeed * deltaTime);
		}

		// Aumenta la velocidad inicialmente para que la ruleta gane velocidad
		if (rotationSpeed < initialSpeed) {
			rotationSpeed += 10.0f * deltaTime; // Aceleración inicial
		}

		// Disminuye gradualmente la velocidad con una tasa aleatoria en cada giro
		rotationSpeed = std::max(rotationSpeed - decelerationRate * deltaTime, 0.0f);

		// Verifica si el giro ha terminado y reinicia valores
		if (rotationSpeed == 0.0f) {
			isSpinning = false;
			initialSpeed = static_cast<float>(rand() % 100 + 400); // Nueva velocidad inicial aleatoria para el próximo giro
			decelerationRate = static_cast<float>(rand() % 20 + 40); // Nueva tasa de desaceleración aleatoria para el próximo giro
		}

		iconPositions.clear();
		for (const auto& icon : icons) {
			iconPositions.push_back(icon.getPosition());
		}
	}

	float segmentAngle = 360.0f / numSegments; // Cada segmento cubre este ángulo

	// Coordenadas del pointer
	float pointerX = centerX; // X del pointer
	float pointerY = centerY - radius; // Y del pointer

	// Calcular el ángulo usando atan2
	float angle = atan2(pointerY - centerY, pointerX - centerX); // Radianes
	float pointerAngle = static_cast<float>(angle * (180.0f / M_PI)); // Convertir a grados


	// Asegurarse de que el ángulo esté en el rango de 0 a 360
	if (pointerAngle < 0) {
		pointerAngle += 360.0f;
	}

	pointerAngle = fmod(pointerAngle - currentRotation + 360.0f, 360.0f);

	// Recorre cada segmento y verifica en cuál está el pointer
	int currentSegment = -1; // Segmento en el que está el pointer
	for (int i = 0; i < numSegments; ++i) {
		float startAngle = i * segmentAngle; // Inicio del segmento
		float endAngle = startAngle + segmentAngle; // Fin del segmento

		// Verificar si el ángulo del pointer está dentro del rango de este segmento
		if (pointerAngle >= startAngle && pointerAngle < endAngle) {
			currentSegment = i; // El pointer está en el segmento i
			// std::cout << "El pointer está en el segmento: toy pegao carnal  " << currentSegment << std::endl;
			break;
		}
	}

	// Manejar el caso del último segmento
	if (currentSegment == -1 && pointerAngle >= (numSegments - 1) * segmentAngle) {

		currentSegment = numSegments - 1; // El pointer está en el último segmento
	}

	// std::cout << "El pointer está en el segmento: " << currentSegment << std::endl;

	sf::Color currentSegmentColor;

	if (!isSpinning && rotationSpeed == 0.0f && giro == true && currentSegment != -1) {

		renderTexture1.clear(); // Limpia la textura
		currentSegmentColor = segments[currentSegment].getFillColor();
		for (auto& segment : segments) {
			segment.setFillColor(currentSegmentColor);
			segment.setOutlineColor(currentSegmentColor);

			fillColor = segment.getFillColor();

			renderTexture1.draw(segment); // Dibuja el sprite con shader1


		}
		renderTexture1.display(); // Finaliza el dibujo en la textura

		giro = false;

		shader.setUniform("segmentTexture", renderTexture1.getTexture());
		shader.setUniform("resolution", sf::Glsl::Vec2(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));

		window.draw(ruletaBase);
		textureCircule1.setTexture(&renderTexture1.getTexture()); // Crea un sprite a partir de la segunda textura

		window.draw(textureCircule1); // Dibuja en la ventana aplicando shader3
		window.draw(CentroCircule);
		//  std::cout << "\nruleta icon2";
		window.draw(icons[currentSegment]);
		
	}
	else if (!isSpinning && resultado == true) {


		window.draw(ruletaBase);

		renderTexture1.clear(); // Limpia la textura

		for (const auto& segment : segments) {

			fillColor = segment.getFillColor();

			renderTexture1.draw(segment); // Dibuja el sprite con shader1

		}
		particleSystem.addParticle(ruletaBase.getPosition(), fillColor, 50.0f);
		particleSystem.update(deltaTime);
		particleSystem.draw(window);

		renderTexture1.display(); // Finaliza el dibujo en la textura

		shader.setUniform("segmentTexture", renderTexture1.getTexture());
		shader.setUniform("resolution", sf::Glsl::Vec2(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));

		textureCircule1.setTexture(&renderTexture1.getTexture()); // Crea un sprite a partir de la segunda textura

		window.draw(textureCircule1); // Dibuja en la ventana aplicando shader3

		window.draw(CentroCircule);

		icons[currentSegment].setPosition(centerX, centerY);
		muerte = true;
		//    std::cout << "\nruleta icon1";
		window.draw(icons[currentSegment]);


	}
	else {

		particleSystem.reset();
		window.draw(ruletaBase);
		for (int i = 0; i < 7; i++)
		{
			segments[i].setFillColor(segmentColors[i]);
		}
		renderTexture1.clear(); // Limpia la textura
		for (const auto& segment : segments) {



			renderTexture1.draw(segment); // Dibuja el sprite con shader1
		}
		renderTexture1.display(); // Finaliza el dibujo en la textura

		shader.setUniform("segmentTexture", renderTexture1.getTexture());
		shader.setUniform("resolution", sf::Glsl::Vec2(static_cast<float>(radius * 2), static_cast<float>(radius * 2)));

		textureCircule1.setTexture(&renderTexture1.getTexture()); // Crea un sprite a partir de la segunda textura

		window.draw(textureCircule1); // Dibuja en la ventana aplicando shader3

		window.draw(CentroCircule);

		for (std::size_t i = 0; i < icons.size(); ++i) {
			icons[i].setPosition(iconPositions[i]); // Restaurar la posición original
			window.draw(icons[i]); // Dibujar el ícono en su posición original
		}
		


	}

	window.draw(borde);
	window.draw(pointer);

	drawLights(window, deltaTime);

}

void Ruleta::trurntrue() {

	turno = true;
	resultado = false;
}

void Ruleta::update(float deltaTime) {
	blinkTimer += deltaTime;
	if (blinkTimer >= blinkDuration) {
		blinkTimer = 0.0f; // Reiniciar el temporizador
	}
}

void Ruleta::createSegments() {
	float angleStep = static_cast<float>(2 * M_PI / numSegments);
	for (int i = 0; i < numSegments; ++i) {
		sf::ConvexShape segment;
		segment.setPointCount(13);

		// Vértice del triángulo (punto inferior)
		segment.setPoint(0, sf::Vector2f(0, 0));

		// Primer punto en la base del triángulo
		segment.setPoint(1, sf::Vector2f(radius * cos(i * angleStep), radius * sin(i * angleStep)));

		// Puntos del semicírculo
		for (int j = 0; j <= 10; ++j) {
			float angle = i * angleStep + (j / 10.0f) * angleStep;
			segment.setPoint(j + 2, sf::Vector2f(radius * cos(angle), radius * sin(angle)));
		}

		// Segundo punto en la base del triángulo
		segment.setPoint(12, sf::Vector2f(radius * cos((i + 1) * angleStep), radius * sin((i + 1) * angleStep)));

		segment.setFillColor(segmentColors[i % numSegments]);
		segment.setOrigin(0.0f, 0.0f);
		segment.setPosition(radius, radius);
		segment.setOutlineThickness(2);
		segment.setOutlineColor(sf::Color::Black);
		segments.push_back(segment);
	}



}

void Ruleta::loadIconTextures() {
	iconTextures.resize(numSegments);
	std::string iconPaths[] = {
		"icon1.png", "icon2.png", "icon3.png",
		"icon4.png", "icon5.png", "icon6.png", "icon7.png"
	};

	for (int i = 0; i < numSegments; ++i) {
		if (!iconTextures[i].loadFromFile(iconPaths[i])) {
			std::cerr << "Error al cargar la textura del icono" << std::endl;
		}
	}
}

void Ruleta::setupIcons() {

	icons.resize(numSegments);
	float angleStep = static_cast<float>(2 * M_PI / numSegments);
	float ScaleIcon = radius / 200;
	for (int i = 0; i < numSegments; ++i) {
		icons[i].setTexture(iconTextures[i]);
		icons[i].setOrigin(static_cast<float>(iconTextures[i].getSize().x / 2), static_cast<float>(iconTextures[i].getSize().y / 2));

		// Posición del ícono, escalada al radio de la ruleta
		float iconAngle = i * angleStep + angleStep / 2;
		icons[i].setPosition(centerX + (radius - 50) * cos(iconAngle), centerY + (radius - 50) * sin(iconAngle));  // 50 es un margen
		icons[i].setScale(ScaleIcon, ScaleIcon);  // 50 es un margen
		icons[i].setRotation(static_cast<float>(iconAngle * (180.0f / M_PI) + 90.0f));
	}

	iconPositions.clear();
	for (const auto& icon : icons) {
		iconPositions.push_back(icon.getPosition());
	}
}

void Ruleta::setupLights() {

	int numLuces = 14;
	float radioLuces = (radius * 0.04f) + radius;  // Ajusta las luces al radio

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

void Ruleta::drawLights(sf::RenderWindow& window, float deltaTime) {
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

void Ruleta::setupBase() {

	textureCircule1.setRadius(radius);
	textureCircule1.setOrigin(radius, radius);
	textureCircule1.setPosition(640, 360);

	CentroCircule.setRadius(static_cast<float>(radius * 0.2));
	CentroCircule.setOrigin(static_cast<float>(radius * 0.2), static_cast<float>(radius * 0.2));
	CentroCircule.setPosition(centerX, centerY);
	CentroCircule.setFillColor(sf::Color(248, 249, 249));
	CentroCircule.setOutlineThickness(radius * 0.015f);
	CentroCircule.setOutlineColor(sf::Color::Black);  // Glow effect en el borde

	borde.setRadius(radius);
	borde.setOrigin(radius, radius);
	borde.setPosition(centerX, centerY);
	borde.setFillColor(sf::Color(0, 0, 0, 0));  // Fondo oscuro para mejor contraste
	borde.setOutlineThickness(radius * 0.08f);
	borde.setOutlineColor(sf::Color(255, 194, 10));  // Glow effect en el borde

	ruletaBase.setRadius(radius);
	ruletaBase.setOrigin(radius, radius);
	ruletaBase.setPosition(centerX, centerY);
	ruletaBase.setFillColor(sf::Color(50, 50, 50));  // Fondo oscuro para mejor contraste
	ruletaBase.setOutlineThickness(radius * 0.02f);
	ruletaBase.setOutlineColor(sf::Color(255, 255, 255));  // Glow effect en el borde


}

void Ruleta::createPointer() {
	pointer.setPointCount(5);
	pointer.setPoint(0, sf::Vector2f(10, 0));
	pointer.setPoint(1, sf::Vector2f(20, 20));
	pointer.setPoint(2, sf::Vector2f(20, 50));
	pointer.setPoint(3, sf::Vector2f(0, 50));
	pointer.setPoint(4, sf::Vector2f(0, 20));
	pointer.setFillColor(sf::Color::Red);
	pointer.setOrigin(10, 28);
	pointer.setPosition(centerX, centerY - radius);
	pointer.setRotation(180);  // Para que apunte hacia abajo

}

void Ruleta::animatePointer() {
	static float bounce = 0.0f;
	if (!isSpinning) {
		bounce += 0.1f; // Incrementar para el efecto de rebote
		pointer.setPosition(centerX, centerY - radius + std::sin(bounce) * 5.0f);
	}
	else {
		pointer.setPosition(centerX, centerY - radius);
	}
}