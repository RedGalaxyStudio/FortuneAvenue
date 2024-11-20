#include "HouseBuy.hpp"
#include <sstream>
#include "nlohmann/json.hpp"
#include "card.h"
#include <filesystem>
#include <cstring>
#include <fstream>
#include "cell.h"
#include "fileio.h"


using json = nlohmann::json;

HouseBuy::HouseBuy():window(nullptr){}


void HouseBuy::setWindow(sf::RenderWindow& win) {
	window = &win;
}
void HouseBuy::resource() {
    // Redimensionar los vectores para almacenar 17 texturas y sprites
    TextureCasa.resize(17);
    SpriteCasa.resize(17);

    // Cargar las texturas de las casas
    /*for (int i = 0; i < 17; ++i) {
  

        if (!TextureCasa[i].loadFromFile("resource/texture/Game/Casas/Casa" + std::to_string(i) + ".png")) {
            std::cerr << "Error al cargar la textura de la casa " << i << "\n";
        }
		std::cout << "\ntexture";

        // Crear el sprite para cada textura
    SpriteCasa[i].setTexture(TextureCasa[i]);
    }*/


    // Cargar la textura para el botón de confirmación de salida
    if (!TextureBotonComprar.loadFromFile("resource/texture/Button/comprarcasa.png")) {
        std::cerr << "Error al cargar el botón de confirmación.\n";
    }
	SpriteBotonComprar.setTexture(TextureBotonComprar);
	SpriteBotonComprar.setPosition(640,545);
	SpriteBotonComprar.setOrigin(101,40);

	if (!TextureCasa[0].loadFromFile("resource/texture/Game/Casas/Casa" + std::to_string(0) + ".png")) {
		std::cerr << "Error al cargar la textura de la casa " << 0 << "\n";
	}
	std::cout << "\ntexture";

	// Crear el sprite para cada textura
	SpriteCasa[0].setTexture(TextureCasa[0]);
	SpriteCasa[0].setPosition(640,360);
	SpriteCasa[0].setOrigin(186, 250);
	std::ifstream file("resource/texture/Game/Casas/CasasInfo.json");
	std::cout << "3";
	if (!file.is_open()) {
		char error_message[256];
		strerror_s(error_message, sizeof(error_message), errno);
		std::cerr << "Error: No se pudo abrir el archivo. Motivo: " << error_message << std::endl;
		return ;
	}

	std::cout << "4";
	// Cargar el contenido del archivo en un objeto JSON



	json jsonData;
	file >> jsonData;
	std::cout << "5";
	// Vector para almacenar las casas
	std::vector<houseInfo> houses;
	std::cout << "6";
	// Iterar sobre las entradas del JSON
	for (auto& [key, value] : jsonData.items()) {
		houseInfo house;
		//		house.nombre = value["nombre"];

		// Eliminar el símbolo '$' y convertir a entero
		house.salario = std::stoi(value["salario"].get<std::string>().substr(0, value["salario"].get<std::string>().size() - 1));
		house.costo = std::stoi(value["costo"].get<std::string>().substr(0, value["costo"].get<std::string>().size() - 1));
		house.impuesto = std::stoi(value["impuesto"].get<std::string>().substr(0, value["impuesto"].get<std::string>().size() - 1));

		// Agregar al vector
		houses.push_back(house);
	}
	std::cout << "7";
	// Mostrar las casas cargadas
	for (const auto& house : houses) {
		std::cout << "Nombre: " << house.nombre
			<< ", Salario: " << house.salario
			<< ", Costo: " << house.costo
			<< ", Impuesto: " << house.impuesto << std::endl;
	}

	
	float angle = 230.f;  // Ángulo de rotación inicial

	// Luego en tu bucle de rotación:
	for (int i = 0; i < 116; i++) {
		angle += 5.f;  // Incrementamos 5 grados por frame
		if (angle >= 360.f) {
			angle -= 360.f;  // Mantenemos el ángulo dentro de 0-360 grados
		}
		
		std::cout << "\nangulos: " << angle;
	}


	

}



void HouseBuy::update(sf::Vector2f posicionactuInicial) {
	float angle = 0.f;  // Ángulo de rotación
	float rotationSpeed = 45.f;  // Velocidad de rotación en grados por segundo
	std::cout << "\n1";
	std::vector<points> pp{ 0 };
	std::vector<cells> cc{ 0 };
	readData(pp, cc, "quad.vtk");
	std::cout << "\n2";
	/*
	ITER(pp, i) std::cout << pp.at(i).x << '\t' << pp.at(i).y << '\t' << pp.at(i).z << std::endl;
	ITER(cc, i) std::cout << cc.at(i).n[0] << '\t' << cc.at(i).n[1] << '\t' << cc.at(i).n[2] << '\t' << cc.at(i).n[3] << std::endl;
	*/
	std::vector<std::vector<sf::Vector3f>> q{ 6 };
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 4; j++)
			q.at(i).push_back({ pp.at(cc.at(i).n[j]).x, pp.at(cc.at(i).n[j]).y, pp.at(cc.at(i).n[j]).z });

	
	std::cout << "\n4";
	std::vector<Cell> cellQua; // (0, Cell(q0, sf::Color::Green));
	Cell c0(q.at(0), sf::Color(0, 255, 0, 255), posicionactuInicial); cellQua.push_back(c0);
	Cell c1(q.at(1), sf::Color(255, 0, 0, 255), posicionactuInicial); cellQua.push_back(c1);
	Cell c2(q.at(2), sf::Color(0, 0, 255, 255), posicionactuInicial); cellQua.push_back(c2);
	Cell c3(q.at(3), sf::Color(255, 255, 0, 255), posicionactuInicial); cellQua.push_back(c3);
	Cell c4(q.at(4), sf::Color(0, 255, 255, 255), posicionactuInicial); cellQua.push_back(c4);
	Cell c5(q.at(5), &TextureCasa[0], posicionactuInicial); cellQua.push_back(c5);
	std::cout << "\n5";
	pp.clear();
	cc.clear();
	

	
	std::cout << "\n55";

	renderedSprite.setTexture(renderTexture.getTexture());

	

	ITER(pp, i) { pp.at(i).x += 550.; pp.at(i).y += 100.; }


	std::cout << "\n122";
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	settings.depthBits = 24;
	settings.stencilBits = 8;


	const sf::Vector3f Wquad = { 1., 1., -1. }; // rotation vector components
	const sf::Vector3f Oquad = { 199., 350., -187.5 }; // rotation vector origin
	ITER(cellQua, i) cellQua.at(i).Rotate(Oquad, Wquad, 235.);
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

		// Obtener el tiempo transcurrido
	
		window->clear();

		window->draw(renderedSprite);

        ITER(cellQua, i) cellQua.at(i).Rotate(Oquad, Wquad, 5.);
  

        ITER(cellQua, i)
            if (cellQua.at(i).getN().z > 0.02){
                window->draw(cellQua.at(i).getCell());
			//	sf::Vector2f posicionactu = cellQua.at(i).getCell().getPosition(); 
		
			}


		if(cellQua[0].finAnimacion == true) {
				window->draw(SpriteBotonComprar);
		}
		
		window->display();

	}
	pp.clear();
	cc.clear();

	cellQua.clear();



	ITER(q, i) q.at(i).clear();
	q.clear();



}

