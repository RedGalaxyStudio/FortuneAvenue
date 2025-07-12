#include "menuswicht.hpp"
#include <iostream>
#include "../core/ResourceGlobal.hpp"
#include <SFML/Graphics.hpp>
#include <numbers>
#include <fstream>
#include "../../libs/nlohmann/json.hpp"
#include <shlobj.h>
using json = nlohmann::json;
  // requiere C++20
menuswicht::menuswicht(sf::RenderWindow& windowRef, sf::Vector2f Position,std::string Name) : window(windowRef),position(Position),sumador(0.f),nameSwich(Name){


	float M_PI = std::numbers::pi;

	// Selector
	CirSelec.setRadius(radius - 4.f);
	CirSelec.setFillColor(sf::Color(200,200,200));
	CirSelec.setOutlineColor(sf::Color(60, 60, 60));
	CirSelec.setOutlineThickness(2.f);
	CirSelec.setOrigin(radius - 4.f, radius - 4.f);


	CirSelec.setPosition(Position.x+31, Position.y); // centro del menú seleccionado

	const float length = 30.f; // largo del rectángulo
	const int pointCount = 10;  // más puntos = más redondeado
	capsule.setPointCount(pointCount * 2 + 2);

	// Semicírculo izquierdo
	for (int i = 0; i <= pointCount; ++i) {
		float angle = M_PI / 2 + (i * M_PI / pointCount); // 90° a 270°
		capsule.setPoint(i, sf::Vector2f(
			std::cos(angle) * radius,
			std::sin(angle) * radius
		));
	}

	// Semicírculo derecho
	for (int i = 0; i <= pointCount; ++i) {
		float angle = 3 * M_PI / 2 + (i * M_PI / pointCount); // 270° a 450° (equivale a 90°)
		capsule.setPoint(i + pointCount + 1, sf::Vector2f(
			length + std::cos(angle) * radius,
			std::sin(angle) * radius
		));
	}

	capsule.setFillColor(sf::Color(75, 75, 75));
	capsule.setOutlineColor(sf::Color(50, 50, 50));
	capsule.setOutlineThickness(5.f);
	capsule.setPosition(Position.x, Position.y);
	// Centra origen en el medio de la cápsula
	
	capsule.setOrigin( 0.f,0.f);

	char appDataPath[MAX_PATH];
	if (SHGetFolderPathA(nullptr, CSIDL_APPDATA, nullptr, 0, appDataPath) != S_OK) {
		std::cerr << "No se pudo obtener la ruta de AppData." << std::endl;
		return;
	}

	std::string rutaFinalC = std::string(appDataPath) + "\\Fortune Avenue\\";
	std::string documente = rutaFinalC + "settings.json";

	if (std::filesystem::exists(documente)) {

		std::ifstream inFile(documente);
		if (inFile.is_open()) {
			json settingData;

			inFile >> settingData;
			inFile.close();

			On = settingData.value(nameSwich, true);

			if (On){
				float barRight = capsule.getPosition().x + 31.f;
				sumador=31.f;
				thumbPosition = sf::Vector2f(barRight , CirSelec.getPosition().y);
				CirSelec.setPosition(thumbPosition);
			}else {
				float barLeft = capsule.getPosition().x ;
				thumbPosition = sf::Vector2f(barLeft , CirSelec.getPosition().y);
				CirSelec.setPosition(thumbPosition);
			}
		}
	}

}

void menuswicht::Funcions() {
	
	if (On&&(sumador<31.f)){
		sumador+=1.9375f;
		float mouseX=capsule.getPosition().x +sumador;

		moveThumb(mouseX);


	}else if (!On&&(sumador>0.f)) {
		sumador-=1.9375f;
		float mouseX=capsule.getPosition().x +sumador;


		moveThumb(mouseX);


	}
}
void menuswicht::setSize(float Size) {
	size = Size;
	for (auto& tex : Menu) {
		tex.setCharacterSize(Size);
	}
}
void menuswicht::setColors(sf::Color color) {
	Color = color;
	for (auto& tex : Menu) {
		tex.setFillColor(Color);
	}
}
void menuswicht::setPosition(sf::Vector2f Position) {


	
}
void menuswicht::event(const sf::Event event) {
	mousePos = sf::Mouse::getPosition(window);
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

		if (CirSelec.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
			On=!On;
			stateChanged=true;
			char appDataPath[MAX_PATH];
			if (SHGetFolderPathA(nullptr, CSIDL_APPDATA, nullptr, 0, appDataPath) != S_OK) {
				std::cerr << "No se pudo obtener la ruta de AppData." << std::endl;
				return;
			}

			std::string rutaFinalC = std::string(appDataPath) + "\\Fortune Avenue\\";

			if (!std::filesystem::exists(rutaFinalC)) {
				std::error_code ec;
				std::filesystem::create_directories(rutaFinalC, ec);
			}
			std::string documente = rutaFinalC + "settings.json";
			json settingData;

			std::ifstream inFile(documente);
			if (inFile.is_open()) {
				inFile >> settingData;  // Cargar el JSON existente
				inFile.close();
			}
			settingData[nameSwich] = On;


			std::ofstream outFile(documente);

			if (outFile.is_open()) {
				outFile << settingData.dump(4);
				outFile.close();
			}

		}
	}

}
float menuswicht::clamp(float value, float min, float max) const {
	return std::max(min, std::min(value, max));
}

void menuswicht::moveThumb(float mouseX) {
	float barLeft = capsule.getPosition().x;
	float barRight = barLeft + 31.f;

	mouseX = clamp(mouseX, barLeft, barRight);

	thumbPosition = sf::Vector2f(mouseX , CirSelec.getPosition().y);
	CirSelec.setPosition(thumbPosition);
	/*if (On) {
		CirSelec.setPosition(barRight, CirSelec.getPosition().y);
	}
	else {
		CirSelec.setPosition(barLeft, CirSelec.getPosition().y);
	}
	*/

}

void menuswicht::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	
	target.draw(capsule, states);
	target.draw(CirSelec, states);
	std::cout << "\n" << CirSelec.getPosition().x;
}
bool menuswicht::isOnState() const {
	return On;
}

bool menuswicht::hasStateChanged() {
	bool result = stateChanged;
	stateChanged = false;  // auto-reset
	return result;
}