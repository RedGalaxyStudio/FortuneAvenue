#include "HouseBuyO.hpp"
#include <sstream>
#include "../../libs/nlohmann/json.hpp"
//#include "card.h"
#include "../../core/ObjetosGlobal.hpp"
#include <filesystem>
#include <cstring>
#include <fstream>
#include "../../ui/cell.h"
#include "../../ui/ResourceGeneral.hpp"
#include "../../ui/ButtonG.hpp"

using json = nlohmann::json;

HouseBuyO::HouseBuyO() :window(nullptr), IndexCAsa(-1) {}


void HouseBuyO::setWindow(sf::RenderWindow& win, int indice) {
	window = &win;
	index = indice;
}
void HouseBuyO::resource() {

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
		std::cerr << "Error: No se pudo abrir el archivo: " << error_message << std::endl;
		return;
	}

	json jsonData;
	file >> jsonData;

	for (auto& [key, value] : jsonData.items()) {
		houseInfo house;
		//		house.nombre = value["nombre"];

		house.salario = std::stoi(value["salario"].get<std::string>().substr(0, value["salario"].get<std::string>().size() - 1));
		house.costo = std::stoi(value["costo"].get<std::string>().substr(0, value["costo"].get<std::string>().size() - 1));
		house.impuesto = std::stoi(value["impuesto"].get<std::string>().substr(0, value["impuesto"].get<std::string>().size() - 1));

		houses.push_back(house);
	}

	sf::FloatRect globalBounds = Xc.getGlobalBounds();
	Xc.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);

}
void HouseBuyO::update(sf::Vector2f posicionactuInicial) {

	float angle = 0.f;
	float rotationSpeed = 45.f;
	std::vector<points> pp{ 0 };
	std::vector<cells> cc{ 0 };
	readData(pp, cc, "src/ui/quad.vtk");

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
	Cell c5(q.at(5), &TextureHouse[playerGameInfo[index].casasPorJugador[IndexCAsa]], posicionactuInicial); cellQua.push_back(c5);
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

			if (firstTurn) {

				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && cellQua[0].finAnimacion == true) {
					if (SpriteBotonComprar.getGlobalBounds().contains(mousePosFloat) && playerGameInfo[0].money >= houses[playerGameInfo[0].casasPorJugador[IndexCAsa]].costo) {
						playClickSound();

						std::string clavesita = "casa" + std::to_string(IndexCAsa);
						playerGameInfo[IndexTurn1].salario += houses[IndexCAsa].salario;
						playerGameInfo[IndexTurn1].impuesto += houses[IndexCAsa].impuesto;
						playerGameInfo[IndexTurn1].money -= houses[IndexCAsa].costo;
						playerGameOff[IndexTurn1].Money.setString(std::to_string(playerGameInfo[IndexTurn1].money));
						CasasCompradas CasasaCOMPRAR;
						CasasaCOMPRAR.CsCmpdrsSprite.setTexture(TextureHouse[playerGameInfo[ActiveUsers[0]].casasPorJugador[IndexCAsa]]);
						VCcompradas.push_back(CasasaCOMPRAR);
						CsCmpdrsindex.push_back(IndexCAsa);

						playerGameInfo[ActiveUsers[0]].numCasas += 1;
						playerGameOff[ActiveUsers[0]].CasasN.setString(std::to_string(playerGameInfo[ActiveUsers[0]].numCasas));
						cierre = true;
						playerGameInfo[ActiveUsers[0]].casasPorJugador.erase(playerGameInfo[ActiveUsers[0]].casasPorJugador.begin() + IndexCAsa);
						IndexCAsa--;

					}
					if (Xc.getGlobalBounds().contains(mousePosFloat)) {
						playClickSound();
						cierre = true;
		
					}
				}
			}

		}

		if (secondTurn) {
			if (GM.bot.roll()) {
				if (playerGameInfo[IndexTurn1].money >= houses[playerGameInfo[IndexTurn1].casasPorJugador[IndexCAsa]].costo) {
					playClickSound();

					CasasCompradas CasasaCOMPRAR;
					CasasaCOMPRAR.CsCmpdrsSprite.setTexture(TextureHouse[playerGameInfo[IndexTurn1].casasPorJugador[IndexCAsa]]);
					VCcompradas.push_back(CasasaCOMPRAR);
					CsCmpdrsindex.push_back(IndexCAsa);

					playerGameInfo[IndexTurn1].numCasas += 1;
					playerGameInfo[IndexTurn1].impuesto += houses[playerGameInfo[IndexTurn1].casasPorJugador[IndexCAsa]].impuesto;
					playerGameInfo[IndexTurn1].salario += houses[playerGameInfo[IndexTurn1].casasPorJugador[IndexCAsa]].salario;
					playerGameInfo[IndexTurn1].money -= houses[IndexCAsa].costo;
					playerGameOff[IndexTurn1].Money.setString(std::to_string(playerGameInfo[IndexTurn1].money));
					playerGameOff[IndexTurn1].CasasN.setString(std::to_string(playerGameInfo[IndexTurn1].numCasas));
					cierre = true;

				}
				else {

					playClickSound();
					cierre = true;
				}

			}
		}
		currentCursor = &normalCursor;
		botonXc.update(mousePosFloat, currentCursor, linkCursor, normalCursor);

		window->setMouseCursor(*currentCursor);
		window->clear();
		//if (client.accionCompra) {
		//
		//	playClickSound();
		//	cierre = true;
		//	client.accionCompra = false;
		//}
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

void HouseBuyO::ViewHouseBuysO() {

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
void HouseBuyO::ViewHouseBsaO(){

	CartaActiva = false;
	window->clear();

	window->draw(spriteBackgroundG);


	for (int i = 0; i < VCcompradas.size(); i++) {
		window->draw(VCcompradas[i].CsCmpdrsSprite);


	}
	window->draw(spriteX);
	//window->display();
}

void HouseBuyO::evenViewHouseCVO(sf::Event event) {

	while (window->pollEvent(event)) {
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
		sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

		if (event.type == sf::Event::Closed ||
			(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
			renderTexture.clear();
			renderTexture.draw(spriteBackgroundG);

			renderTexture.draw(spriteX);
			renderTexture.draw(overlay);
			Menup.MenuSalir(nullptr);
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