#include "HouseBuy.hpp"
#include <sstream>
#include "../../../libs/nlohmann/json.hpp"
#include <filesystem>
#include <cstring>
#include <fstream>
#include "../../ui/cell.h"
#include "../../core/ObjetosGlobal.hpp"
#include "../../ui/ButtonG.hpp"
#include "../../ui/ResourceGeneral.hpp"
#include "OnlineVars.hpp"
#include <vector>
#include <algorithm>
using json = nlohmann::json;

HouseBuy::HouseBuy() :window(nullptr), IndexCAsa(-1) {}


void HouseBuy::setWindow(sf::RenderWindow& win, int indice, Client& clienT) {
	window = &win;
	index = indice;
	client = &clienT;
}
void HouseBuy::resource() {


	SpriteCasa.resize(17);
	if (!TextureXcOFF.loadFromFile("assets/image/Button/XOffC.png")) {
		std::cerr << "Error al cargar el botón de confirmación.\n";
	}
	if (!TextureXcOn.loadFromFile("assets/image/Button/XOnC.png")) {
		std::cerr << "Error al cargar el botón de confirmación.\n";
	}

	Xc.setTexture(TextureXcOFF);

	if (!TextureBotonComprar.loadFromFile("assets/image/Button/comprarcasa.png")) {
		std::cerr << "Error al cargar el botón de confirmación.\n";
	}
	SpriteBotonComprar.setTexture(TextureBotonComprar);
	SpriteBotonComprar.setPosition(640, 545);
	SpriteBotonComprar.setOrigin(101, 40);

	if (!ReversoCart.loadFromFile("assets/image/Game/Casas/reversocart.png")) {
		std::cerr << "Error al cargar la textura de la casa " << IndexCAsa << "\n";
	}

	std::ifstream file("assets/image/Game/Casas/CasasInfo.json");

	if (!file.is_open()) {
		char error_message[256];
		strerror_s(error_message, sizeof(error_message), errno);
		std::cerr << "Error: No se pudo abrir el archivo. Motivo: " << error_message << std::endl;
		return;
	}

	json jsonData;
	file >> jsonData;


	std::vector<std::pair<int, nlohmann::json>> houseList;

	// Extraer los datos y guardar el número de la casa
	for (auto& [key, value] : jsonData.items()) {
		int houseNumber = std::stoi(key.substr(4)); // Extrae el número de "casaX"
		houseList.push_back({ houseNumber, value });
	}

	// Ordenar por el número de la casa
	std::sort(houseList.begin(), houseList.end(), [](const auto& a, const auto& b) {
		return a.first < b.first;
		});

	for (auto& [number, value] : houseList) {
		houseInfo house;

		house.salario = std::stoi(value["salario"].get<std::string>().substr(0, value["salario"].get<std::string>().size() - 1));
		house.costo = std::stoi(value["costo"].get<std::string>().substr(0, value["costo"].get<std::string>().size() - 1));
		house.impuesto = std::stoi(value["impuesto"].get<std::string>().substr(0, value["impuesto"].get<std::string>().size() - 1));

		houses.push_back(house);
	}



	sf::FloatRect globalBounds = Xc.getGlobalBounds();
	Xc.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

}

void HouseBuy::update(sf::Vector2f posicionactuInicial) {

	float angle = 0.f;
	float rotationSpeed = 45.f;

	std::vector<points> pp{ 0 };
	std::vector<cells> cc{ 0 };
	readData(pp, cc, "src/ui/quad.vtk");

	IndexCAsa += 1;
	if (IndexCAsa >= playerInfos[index].casasPorJugador.size()) {
		IndexCAsa = 0;
	}
	std::vector<std::vector<sf::Vector3f>> q{ 6 };

	for (int i = 0; i < 6; i++) {

		for (int j = 0; j < 4; j++) {

			q.at(i).push_back({ pp.at(cc.at(i).n[j]).x, pp.at(cc.at(i).n[j]).y, pp.at(cc.at(i).n[j]).z });
		}
	}

	std::vector<Cell> cellQua;
	Cell c0(q.at(0), sf::Color(0, 255, 0, 255), posicionactuInicial); cellQua.push_back(c0);
	Cell c1(q.at(1), sf::Color(255, 0, 0, 255), posicionactuInicial); cellQua.push_back(c1);
	Cell c2(q.at(2), sf::Color(0, 0, 255, 255), posicionactuInicial); cellQua.push_back(c2);
	Cell c3(q.at(3), sf::Color(255, 255, 0, 255), posicionactuInicial); cellQua.push_back(c3);
	Cell c4(q.at(4), &ReversoCart, posicionactuInicial); cellQua.push_back(c4);
	Cell c5(q.at(5), &TextureCasa[playerInfos[index].casasPorJugador[IndexCAsa]], posicionactuInicial); cellQua.push_back(c5);

	ButtonG botonXc(Xc, TextureXcOFF, TextureXcOn);

	pp.clear();
	cc.clear();
	
	Xc.setPosition(790, 148);

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

			if (turn) {

				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && cellQua[0].finAnimacion == true) {

					if (SpriteBotonComprar.getGlobalBounds().contains(mousePosFloat) && playerInfos[UsuariosActivos[0]].money >= houses[playerInfos[UsuariosActivos[0]].casasPorJugador[IndexCAsa]].costo) {
						playClickSound();
						client->networkMessage.buyHouse(playerInfos[UsuariosActivos[0]].casasPorJugador[IndexCAsa]);

						CasasCompradas CasasaCOMPRAR;
						CasasaCOMPRAR.CsCmpdrsSprite.setTexture(TextureCasa[playerInfos[UsuariosActivos[0]].casasPorJugador[IndexCAsa]]);
						VCcompradas.push_back(CasasaCOMPRAR);
						CsCmpdrsindex.push_back(IndexCAsa);

						playerInfos[UsuariosActivos[0]].numCasas += 1;
						playersGame[UsuariosActivos[0]].CasasN.setString(std::to_string(playerInfos[UsuariosActivos[0]].numCasas));
						cierre = true;
						playerInfos[UsuariosActivos[0]].casasPorJugador.erase(playerInfos[UsuariosActivos[0]].casasPorJugador.begin() + IndexCAsa);
						IndexCAsa--;
					}
					if (Xc.getGlobalBounds().contains(mousePosFloat)) {
						playClickSound();
						cierre = true;
						client->networkMessage.sendXHouse();
					}
				}
			}
		}

		currentCursor = &normalCursor;
		botonXc.update(mousePosFloat, currentCursor, linkCursor, normalCursor);

		window->setMouseCursor(*currentCursor);
		window->clear();
		if (accionCompra) {

			playClickSound();
			cierre = true;
			accionCompra = false;
		}
		if (accionXhouse) {

			playClickSound();

			CasasCompradas CasasaCOMPRAR;
			CasasaCOMPRAR.CsCmpdrsSprite.setTexture(TextureCasa[playerInfos[index].casasPorJugador[IndexCAsa]]);
			VCcompradas.push_back(CasasaCOMPRAR);
			CsCmpdrsindex.push_back(IndexCAsa);

			playerInfos[index].numCasas += 1;
			playersGame[index].CasasN.setString(std::to_string(playerInfos[index].numCasas));
			cierre = true;
			playerInfos[index].casasPorJugador.erase(playerInfos[index].casasPorJugador.begin() + IndexCAsa);
			IndexCAsa--;
			cierre = true;
			accionCompra = false;
			accionXhouse = false;


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

	perfilWidth = 200.0f;
	separacion = 20.0f;
	totalPerfiles = static_cast<int>(CsCmpdrsindex.size());
	seleccionlista = false;
	CartaActiva = false;
	indexMouseOver = -1;
	cartaActivaIndex = -1;

	if (totalPerfiles > 0) {
		float totalWidth = (totalPerfiles * perfilWidth) + ((totalPerfiles - 1) * separacion);

		float startX = (1280.0f - totalWidth) / 2.0f + (perfilWidth / 2.0f);
		float startY = 360.0f;

		for (int i = 0; i < totalPerfiles; i++) {
			float xPos = startX + i * (perfilWidth + separacion);
			float yPos = startY;

			sf::FloatRect globalBounds = VCcompradas[i].CsCmpdrsSprite.getGlobalBounds();
			VCcompradas[i].CsCmpdrsSprite.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
			VCcompradas[i].CsCmpdrsSprite.setPosition(xPos, startY);
			VCcompradas[i].ocultaCasa = sf::Vector2f(xPos, startY);
			VCcompradas[i].mostrarCasa = sf::Vector2f(xPos - 40, startY);
			VCcompradas[i].CsCmpdrsSprite.setScale(0.7f, 0.7f);

		}
	}
}
void HouseBuy::ViewHouseBs() {

	CartaActiva = false;
	window->clear();

	window->draw(spriteBackgroundG);


	for (int i = 0; i < VCcompradas.size(); i++) {
		window->draw(VCcompradas[i].CsCmpdrsSprite);


	}
	window->draw(spriteX);
	//window->display();
}

void HouseBuy::evenViewHouseCV(sf::Event event) {

	while (window->pollEvent(event)) {
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
		sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

		if (event.type == sf::Event::Closed ||
			(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
			renderTexture.clear();
			renderTexture.draw(spriteBackgroundG);

			renderTexture.draw(spriteX);
			renderTexture.draw(overlay);
			Menup.MenuSalir(client);
		}


		for (int i = 0; i < VCcompradas.size(); i++) {
			VCcompradas[i].CsCmpdrsSprite.setPosition(VCcompradas[i].ocultaCasa);
		}

		cartaActivaIndex = -1;
		for (int i = static_cast<int>(VCcompradas.size()) - 1; i >= 0; i--) {
			if (VCcompradas[i].CsCmpdrsSprite.getGlobalBounds().contains(mousePosFloat)) {
				VCcompradas[i].CsCmpdrsSprite.setPosition(VCcompradas[i].mostrarCasa);
				cartaActivaIndex = i;
				break;
			}








		}
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			if (spriteX.getGlobalBounds().contains(mousePosFloat)) {

				playClickSound();
				seleccionlista = true;

			}


		}
	}
	
}