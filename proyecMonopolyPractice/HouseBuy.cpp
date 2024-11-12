/*#include "HouseBuy.hpp"
#include <sstream>

HouseBuy::HouseBuy()
    {

  


}

void HouseBuy::resource() {
    // Redimensionar los vectores para almacenar 17 texturas y sprites
    TextureCasa.resize(17);
    SpriteCasa.resize(17);

    // Cargar las texturas de las casas
    for (int i = 0; i < 17; ++i) {
  

        if (!TextureCasa[i].loadFromFile("resource/texture/Game/Casas/Casa" + std::to_string(i) + ".png")) {
            std::cerr << "Error al cargar la textura de la casa " << i << "\n";
        }

        


        // Crear el sprite para cada textura
    SpriteCasa[i].setTexture(TextureCasa[i]);






    }


    // Cargar la textura para el botón de confirmación de salida
    if (!TextureBotonComprar.loadFromFile("resource/texture/Button/boton2.png")) {
        std::cerr << "Error al cargar el botón de confirmación.\n";
    }


}



void HouseBuy::update() {

	while (window->isOpen()) {


		sf::Event event;

		while (window->pollEvent(event)) {


			sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
			sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {

				renderTexture.clear();
				renderTexture.draw(spriteFondoGame);
				for (int i = 0; i < 4; i++) {
					renderTexture.draw(playersGame[i].NamePlayer);
					renderTexture.draw(playersGame[i].boxPlayer);
					renderTexture.draw(playersGame[i].MarcoPlayer);
					renderTexture.draw(playersGame[i].AvatarPlayer);
				}
				renderTexture.draw(spriteX);
				renderTexture.draw(overlay);

				Menup.MenuSalir();
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				//if (Settings.getGlobalBounds().contains(mousePosFloat)) {
				playClickSound();
				//	Menup.MenuOpcion();
			//	}

			}


		}   // Asegura que el bucle se repita mientras haya eventos pendientes

		window->setMouseCursor(*currentCursor);


		window->clear();

		window->draw(spriteFondoGame);



		float perfilWidth = 200.0f; // Ancho estimado para cada perfil
		float separacion = 20.0f;   // Espaciado entre perfiles
		int totalPerfiles = 4;      // Número total de perfiles

		// Ancho total ocupado por los perfiles y separaciones
		float totalWidth = totalPerfiles * perfilWidth + (totalPerfiles - 1) * separacion;

		// Calcular el punto inicial en X para centrar los perfiles horizontalmente
		float startX = (1280.0f - totalWidth) / 2.0f;

		// Posición Y fija para centrar verticalmente
		float startY = (720.0f - (180.0f + 70.0f + 50.0f)) / 2.0f; // Ajusta según las alturas estimadas

		for (int i = 0; i < totalPerfiles; i++) {
			float xPos = startX + i * (perfilWidth + separacion); // Calcula la posición en X para cada perfil
			float yPos = startY;                                 // Calcula la posición en Y para centrar

			// Ajustar las posiciones de los elementos del perfil
			playersGame[i].NamePlayer.setPosition(xPos, yPos + 70);
			playersGame[i].boxPlayer.setPosition(xPos, yPos + 70); // Ajusta posición relativa
			playersGame[i].AvatarPlayer.setPosition(xPos, yPos);
			playersGame[i].MarcoPlayer.setPosition(xPos, yPos);
			playersGame[i].Money.setPosition(xPos, yPos + 140);
			playersGame[i].PieceSelect.setPosition(xPos, yPos + 180);
			playersGame[i].PieceSelect.setScale(2.0f, 2.0f);

			// Dibujar los elementos en la ventana
			window->draw(playersGame[i].NamePlayer);
			window->draw(playersGame[i].boxPlayer);
			window->draw(playersGame[i].AvatarPlayer);
			window->draw(playersGame[i].MarcoPlayer);
			window->draw(playersGame[i].Money);
			window->draw(playersGame[i].PieceSelect);
		}





		window->display();

	}


}

