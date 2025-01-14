#include "HouseBuy.hpp"
#include <sstream>
#include "nlohmann/json.hpp"
//#include "card.h"
#include <filesystem>
#include <cstring>
#include <fstream>
#include "cell.h"

#include "ButtonG.hpp"

using json = nlohmann::json;

HouseBuy::HouseBuy() :window(nullptr), IndexCAsa(-1){}


void HouseBuy::setWindow(sf::RenderWindow& win,int indice) {
	window = &win;
	index = indice;
	//std::cout << "\n\n" << index;
}
void HouseBuy::resource(Client* client) {
	// Redimensionar los vectores para almacenar 17 texturas y sprites
	
	SpriteCasa.resize(17);
	if (!TextureXcOFF.loadFromFile("resource/texture/Button/XOffC.png")) {
		std::cerr << "Error al cargar el botón de confirmación.\n";
	}
	if (!TextureXcOn.loadFromFile("resource/texture/Button/XOnC.png")) {
		std::cerr << "Error al cargar el botón de confirmación.\n";
	}

	Xc.setTexture(TextureXcOFF);

	// Cargar la textura para el botón de confirmación de salida
	if (!TextureBotonComprar.loadFromFile("resource/texture/Button/comprarcasa.png")) {
		std::cerr << "Error al cargar el botón de confirmación.\n";
	}
	SpriteBotonComprar.setTexture(TextureBotonComprar);
	SpriteBotonComprar.setPosition(640, 545);
	SpriteBotonComprar.setOrigin(101, 40);

	if (!ReversoCart.loadFromFile("resource/texture/Game/Casas/reversocart.png")) {
			std::cerr << "Error al cargar la textura de la casa " << IndexCAsa << "\n";
	}
	// Crear el sprite para cada textura

	std::ifstream file("resource/texture/Game/Casas/CasasInfo.json");

	if (!file.is_open()) {
		char error_message[256];
		strerror_s(error_message, sizeof(error_message), errno);
		std::cerr << "Error: No se pudo abrir el archivo. Motivo: " << error_message << std::endl;
		return;
	}
	// Carga el contenido del archivo en un objeto JSON



	json jsonData;
	file >> jsonData;

	// Vector para almacenar las casas

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

	sf::FloatRect globalBounds = Xc.getGlobalBounds();
	Xc.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);


}



void HouseBuy::update(sf::Vector2f posicionactuInicial) {
	float angle = 0.f;  // Ángulo de rotación
	float rotationSpeed = 45.f;  // Velocidad de rotación en grados por segundo

	std::vector<points> pp{ 0 };
	std::vector<cells> cc{ 0 };
	readData(pp, cc, "quad.vtk");

	IndexCAsa += 1;

	std::vector<std::vector<sf::Vector3f>> q{ 6 };
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 4; j++)
			q.at(i).push_back({ pp.at(cc.at(i).n[j]).x, pp.at(cc.at(i).n[j]).y, pp.at(cc.at(i).n[j]).z });

	std::vector<Cell> cellQua; 
	Cell c0(q.at(0), sf::Color(0, 255, 0, 255), posicionactuInicial); cellQua.push_back(c0);
	Cell c1(q.at(1), sf::Color(255, 0, 0, 255), posicionactuInicial); cellQua.push_back(c1);
	Cell c2(q.at(2), sf::Color(0, 0, 255, 255), posicionactuInicial); cellQua.push_back(c2);
	Cell c3(q.at(3), sf::Color(255, 255, 0, 255), posicionactuInicial); cellQua.push_back(c3);
	Cell c4(q.at(4), &ReversoCart, posicionactuInicial); cellQua.push_back(c4);
	Cell c5(q.at(5), &TextureCasa[playerInfos[index].casasPorJugador[IndexCAsa]], posicionactuInicial); cellQua.push_back(c5);
	std::cout << "\nIndexCAsa" << IndexCAsa;
	
	ButtonG botonXc(Xc, TextureXcOFF, TextureXcOn);

	pp.clear();
	cc.clear();


	Xc.setPosition(790,148);

	renderedSprite.setTexture(renderTexture.getTexture());

	ITER(pp, i) { pp.at(i).x += 550.; pp.at(i).y += 100.; }

	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	settings.depthBits = 24;
	settings.stencilBits = 8;

	bool cierre = false;
	const sf::Vector3f Wquad = { 1., 1., -1. }; // rotation vector components
	const sf::Vector3f Oquad = { 199., 350., -187.5 }; // rotation vector origin
	ITER(cellQua, i) cellQua.at(i).Rotate(Oquad, Wquad, 235.);
	while (window->isOpen() && !cierre) {


		sf::Event event;
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
		sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

		while (window->pollEvent(event)) {
			//std::cout << "\n\n12222222222222222222";

			
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

			if (turn) {
				
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left&& cellQua[0].finAnimacion == true) {
					if (SpriteBotonComprar.getGlobalBounds().contains(mousePosFloat)&&playerInfos[0].money>= houses[playerInfos[0].casasPorJugador[IndexCAsa]].costo) {
						playClickSound();
						client.networkMessage.buyHouse(playerInfos[0].casasPorJugador[IndexCAsa]);

						CasasCompradas CasasaCOMPRAR;
						CasasaCOMPRAR.CsCmpdrsSprite.setTexture(TextureCasa[playerInfos[index].casasPorJugador[IndexCAsa]]);
						VCcompradas.push_back(CasasaCOMPRAR);
						CsCmpdrsindex.push_back(IndexCAsa);

						playerInfos[UsuariosActivos[0]].numCasas += 1;
						playersGame[UsuariosActivos[0]].CasasN.setString(std::to_string(playerInfos[UsuariosActivos[0]].numCasas));
						cierre = true;
					}
					if (Xc.getGlobalBounds().contains(mousePosFloat)) {
						playClickSound();
						cierre = true;
						client.networkMessage.sendXHouse();
					}
				}
			}
			

			

		}   // Asegura que el bucle se repita mientras haya eventos pendientes

		
		currentCursor = &normalCursor;
		botonXc.update(mousePosFloat, currentCursor, linkCursor, normalCursor);

		window->setMouseCursor(*currentCursor);
		// Obtener el tiempo transcurrido
		window->clear();
		if (client.accionCompra) {

			playClickSound();
			cierre = true;
			client.accionCompra = false;
		}
		window->draw(renderedSprite);

		ITER(cellQua, i) cellQua.at(i).Rotate(Oquad, Wquad, 5.);


		ITER(cellQua, i)
			if (cellQua.at(i).getN().z > 0.02) {
				window->draw(cellQua.at(i).getCell());
			
			}


		if (cellQua[0].finAnimacion == true) {
			window->draw(SpriteBotonComprar);
			window->draw(Xc);
		}
		
		window->display();

	}
	pp.clear();
	cc.clear();

	cellQua.clear();



	ITER(q, i) q.at(i).clear();
	q.clear();



}

void HouseBuy::ViewHouseBuys() {
	//for (int i = 0; i < 6; i++)
	//{
	//	CasasCompradas CasasaCOMPRAR;
	//	CasasaCOMPRAR.CsCmpdrsSprite.setTexture(TextureCasa[playerInfos[index].casasPorJugador[i]]);
	//	VCcompradas.push_back(CasasaCOMPRAR);
	//	CsCmpdrsindex.push_back(i);
	//}
	// Configurar perfiles
	float perfilWidth = 200.0f; // Ancho estimado de cada perfil
	float separacion = 20.0f;   // Espaciado entre perfiles
	int totalPerfiles = static_cast<int>(CsCmpdrsindex.size()); // Usar el número real de perfiles


	if (totalPerfiles > 0) {
		// Calcular ancho total ocupado por perfiles y separaciones
		float totalWidth = (totalPerfiles * perfilWidth) + ((totalPerfiles - 1) * separacion);

		// Calcular inicio X para centrar los perfiles horizontalmente
		float startX = (1280.0f - totalWidth) / 2.0f + (perfilWidth / 2.0f); // Desplaza para centrar el origen

		float startY = 360.0f; // Centrado verticalmente

		for (int i = 0; i < totalPerfiles; i++) {
			float xPos = startX + i * (perfilWidth + separacion); // Calcula la posición en X para cada perfil
			float yPos = startY;


			sf::FloatRect globalBounds = VCcompradas[i].CsCmpdrsSprite.getGlobalBounds();
			VCcompradas[i].CsCmpdrsSprite.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
			VCcompradas[i].CsCmpdrsSprite.setPosition(xPos, startY);
			VCcompradas[i].ocultaCasa=sf::Vector2f(xPos, startY);
			VCcompradas[i].mostrarCasa=sf::Vector2f(xPos-40, startY);
			VCcompradas[i].CsCmpdrsSprite.setScale(0.7f,0.7f);

		}
	}
	bool seleccionlista = false;
	bool CartaActiva = false;
	int indexMouseOver = -1;
	int cartaActivaIndex = -1; // Índice de la carta activa, -1 si ninguna está activa

	while (window->isOpen() && !seleccionlista) {
		sf::Event event;
		while (window->pollEvent(event)) {
			sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
			sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
				renderTexture.clear();
				renderTexture.draw(spriteFondoGame);

				renderTexture.draw(spriteX);
				renderTexture.draw(overlay);
				Menup.MenuSalir();
			}



			// Resetear todas las cartas a su posición oculta al inicio del bucle
			for (int i = 0; i < VCcompradas.size(); i++) {
				VCcompradas[i].CsCmpdrsSprite.setPosition(VCcompradas[i].ocultaCasa);
			}

			// Verificar colisión en orden inverso y actualizar la carta activa
			cartaActivaIndex = -1; // Reinicia la carta activa
			for (int i = VCcompradas.size() - 1; i >= 0; i--) {
				if (VCcompradas[i].CsCmpdrsSprite.getGlobalBounds().contains(mousePosFloat)) {
					VCcompradas[i].CsCmpdrsSprite.setPosition(VCcompradas[i].mostrarCasa);
					cartaActivaIndex = i; // Guarda el índice de la carta activa
					break; // Termina el bucle una vez que encuentra una carta activa
				}
			}
	




			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				if (spriteX.getGlobalBounds().contains(mousePosFloat)) {

					playClickSound();
					seleccionlista = true;

				}


			}


		}
		CartaActiva = false;
		window->clear();

		window->draw(spriteFondoGame);

		for (int i = 0; i < VCcompradas.size(); i++) {
			window->draw(VCcompradas[i].CsCmpdrsSprite);

		}
		window->draw(spriteX);
		window->display();
	}
}