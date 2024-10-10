#pragma once

#include <SFML/Graphics.hpp>
#include "CubeClass.h"//#include <iostream>
#include <cstdlib>
#include <ctime>

class Window {

	std::vector<int> textureIndices; // Vector para almacenar los �ndices de textura


	sf::RenderWindow* window = nullptr;
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
		textureIndices.clear();  // Limpiar el vector en cada actualizaci�n

		for (int i = 0; i < cube->show.size(); i++) {
			std::vector<int> faceid = cube->show[i];
			sf::Vertex* face = &Cube3D[i * 4];  // Obtenemos los 4 v�rtices de la cara

			// Asignar la textura correcta seg�n la cara que se est� mostrando
			int textureIndex = -1;
			for (int j = 0; j < 6; j++) {
				if (cube->faces[j] == faceid) {
					textureIndex = j;  // Asignar el �ndice de textura correspondiente a la cara
					break;
				}
			}

			if (textureIndex == -1) continue;  // Si no se encuentra una textura, saltamos

			textureIndices.push_back(textureIndex);  // Guarda el �ndice de la textura para esta cara

			for (int j = 0; j < 4; j++) {
				// Asignar la posici�n en 2D de los v�rtices
				face[j].position = sf::Vector2f(cube->C3D[faceid[j]].x, cube->C3D[faceid[j]].y);
				face[j].color = sf::Color::White;  // No se aplica color

				// Asignar las coordenadas de textura seg�n el v�rtice
				if (j == 0)
					face[j].texCoords = sf::Vector2f(0, 0);  // Esquina superior izquierda
				else if (j == 1)
					face[j].texCoords = sf::Vector2f(static_cast<float>(cube->textures[textureIndex].getSize().x), 0);  // Esquina superior derecha
				else if (j == 2)
					face[j].texCoords = sf::Vector2f(static_cast<float>(cube->textures[textureIndex].getSize().x),
						static_cast<float>(cube->textures[textureIndex].getSize().y));  // Esquina inferior derecha
				else if (j == 3)
					face[j].texCoords = sf::Vector2f(0, static_cast<float>(cube->textures[textureIndex].getSize().y));  // Esquina inferior izquierda

			}
		}
	}

	bool isDiceInUse = false;


	// Actualiza la apariencia del dado
	void updateDiceAppearance() {
		// Dibujar el dado
		//cube->draw(static_cast<float>(window->getSize().x) / 2, static_cast<float>(window->getSize().y) / 2, static_cast<float>(posz));
		

		// Si el dado no est� en uso, dibuja la sombra encima
		if (!isDiceInUse) {
			shadowOverlay.setPosition(sf::Vector2f(cube->getPosition().x, cube->getPosition().y)); // Coloca la sombra sobre el dado
			window->draw(shadowOverlay);                    // Dibuja la sombra
		}
	}


	void update() {
		// Crear una sombra semitransparente
		shadowOverlay.setPosition(sf::Vector2f(cube->getPosition().x, cube->getPosition().y));
		shadowOverlay.setFillColor(sf::Color(0, 0, 0, 100)); // Color negro semitransparente

		updateDraw();

		window->clear(sf::Color::White);

		// Crear el vertex array para la sombra
		sf::VertexArray shadow(sf::Quads, cube->show.size() * 4); // Aseg�rate de que el tama�o sea correcto

		// Dibuja la sombra del cubo
		for (int i = 0; i < cube->show.size(); i++) {
			sf::Vertex* face = &Cube3D[i * 4];  // Obtiene los 4 v�rtices de la cara

			// Crea un color negro para la sombra, puedes ajustar la opacidad aqu�
			sf::Color shadowColor(0, 0, 0, 150); // Negro con un poco de transparencia

			// Calcula la posici�n de la sombra basada en la posici�n del cubo
			for (int j = 0; j < 4; j++) {
				sf::Vector2f shadowPosition = face[j].position + sf::Vector2f(5.0f, 5.0f); // Cambia los valores de 5.0f a lo que desees para la direcci�n de la sombra

				// Asigna la posici�n y color a los v�rtices de la sombra
				shadow[i * 4 + j].position = shadowPosition;
				shadow[i * 4 + j].color = shadowColor;
			}
		}

		// Dibuja la sombra
		window->draw(shadow);

		for (int i = 0; i < cube->show.size(); i++) {
			sf::RenderStates states;
			if (i < textureIndices.size()) {  // Aseg�rate de que el �ndice es v�lido
				int textureIndex = textureIndices[i];  // Usa el �ndice de textura calculado previamente
				if (textureIndex == -1) continue;  // Si no hay textura v�lida, saltamos

				states.texture = &cube->textures[textureIndex];  // Asigna la textura correcta

				// Dibuja cada cara individualmente
				sf::Vertex* face = &Cube3D[i * 4];  // Obtiene los 4 v�rtices de la cara
				window->draw(face, 4, sf::TrianglesFan, states);  // Dibuja la cara
			}
		}

		//updateDiceAppearance();

		window->display();
	}

	void close(){

		delete window;
	}

	bool ok = 0;
	void loop()
	{
		srand(static_cast<unsigned int>(time(0))); // Inicializar semilla
		int faceIndex;
		sf::Event event;
		while (window->isOpen())
		{
			while (window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window->close();

				}

				if (event.type == sf::Event::MouseButtonPressed)
				{
					updateDiceAppearance();

					eventStarted = true;
					faceIndex = rand() % 6 + 1;
					mouseStart.x = rand() % 400 + 1;  // Valor aleatorio para la coordenada x
					mouseStart.y = rand() % 600 + 1;  // Valor aleatorio para la coordenada y
				ok = 1;
				}
				//if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
				//{
			

					/*}
				if (ok == 1)
				{
					mouseEnd.x = rand() % 400 + 1;  // Valor aleatorio para la coordenada x
					mouseEnd.y = rand() % 600 + 1;  // Valor aleatorio para la coordenada y

					float dx = static_cast<float>(mouseEnd.x) - static_cast<float>(mouseStart.x);
					float dy = static_cast<float>(mouseEnd.y) - static_cast<float>(mouseStart.y);
					float disP1 = cube->distanceTo(static_cast<float>(mouseStart.x), static_cast<float>(mouseStart.y), static_cast<float>(posz));

					float alfaX = atan2f(dx, disP1);
					float alfaY = atan2f(dy, disP1);

					cube->rotate(-alfaY, alfaX, 0);
					cube->draw(static_cast<float>(window->getSize().x) / 2, static_cast<float>(window->getSize().y) / 2, static_cast<float>(posz));
					Cube3D.resize(cube->show.size() * 4);
					mouseStart = mouseEnd;

				}*/

			}

			if (eventStarted) {
				sf::Time elapsed = clock.getElapsedTime();  // Tiempo transcurrido desde que se inici� el evento

				if (elapsed.asSeconds() < 5.0f) {
					mouseEnd.x = rand() % 400 + 1;  // Valor aleatorio para la coordenada x
					mouseEnd.y = rand() % 600 + 1;  // Valor aleatorio para la coordenada y

					float dx = static_cast<float>(mouseEnd.x - mouseStart.x);
					float dy = static_cast<float>(mouseEnd.y - mouseStart.y);


					//float dx = static_cast<float>(rand() % 100 + 1);
					//float dy = static_cast<float>(rand() % 100 + 1);


					//int randomNumber1 = ; // N�mero aleatorio entre 1 y 100
					//int randomNumber2 = rand() % 100 + 1;

					float disP1 = cube->distanceTo(static_cast<float>(mouseStart.x), static_cast<float>(mouseStart.y), static_cast<float>(posz));


					float alfaX = atan2f(dx, disP1);
					float alfaY = atan2f(dy, disP1);

					cube->rotate(alfaY, alfaX, 0);
					cube->draw(static_cast<float>(window->getSize().x) / 2, static_cast<float>(window->getSize().y) / 2, static_cast<float>(posz));
					Cube3D.resize(cube->show.size() * 4);


					ok = 0;
				}
				else {
					
					cube->resetPosition(faceIndex);

					cube->draw(static_cast<float>(window->getSize().x) / 2, static_cast<float>(window->getSize().y) / 2, static_cast<float>(posz));
					Cube3D.resize(cube->show.size() * 4);
					eventStarted = false;
					std::cout << "El evento de la tecla A ha terminado." << std::endl;
				}
			}

			

			update();


		}
		close();


	}


public :
	sf::Clock clock;  // Reloj para medir el tiempo transcurrido
	bool eventStarted = false;  // Bandera para saber si el evento ha comenzado
	sf::RectangleShape shadowOverlay;

	
	
	void start(unsigned int Width, unsigned int Height, const char* Title)
	{

		window = new sf::RenderWindow(sf::VideoMode(Width, Height), Title);
		cube = new Cube(100);
		Cube3D.setPrimitiveType(sf::Quads);
		cube->move(static_cast<float>(Width) / 2, static_cast<float>(Height) / 2, -100.0f);
		cube->draw(static_cast<float>(Width) / 2, static_cast<float>(Height) / 2, static_cast<float>(posz));

		// Inicializar la sombra
		shadowOverlay.setSize(sf::Vector2f(100, 100)); // Cambia el tama�o seg�n sea necesario
		shadowOverlay.setFillColor(sf::Color(0, 0, 0, 100)); // Color negro semitransparente
		sf::Vector2f size = shadowOverlay.getSize();
		shadowOverlay.setOrigin(size.x / 2, size.y / 2); // Centra el origen

		Cube3D.resize(cube->show.size() * 4);
		

		loop();

	}

};
