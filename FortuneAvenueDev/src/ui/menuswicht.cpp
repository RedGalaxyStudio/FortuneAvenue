#include "menuswicht.hpp"
#include <iostream>
#include "../core/ResourceGlobal.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>
#include <numbers>
  // requiere C++20
menuswicht::menuswicht(sf::RenderWindow& windowRef, sf::Vector2f Position) : window(windowRef),position(Position){


	float M_PI = std::numbers::pi;

	// Selector
	CirSelec.setRadius(radius - 4.f);
	CirSelec.setFillColor(sf::Color(200,200,200));
	CirSelec.setOutlineColor(sf::Color(60, 60, 60));
	CirSelec.setOutlineThickness(2.f);
	CirSelec.setOrigin(radius - 4.f, radius - 4.f);


	CirSelec.setPosition(531, 333); // centro del menú seleccionado

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
	capsule.setPosition(500, 333);
	// Centra origen en el medio de la cápsula
	
	capsule.setOrigin( 0.f,0.f);

}

void menuswicht::setFont(sf::Font font) {
	
	for (auto& tex : Menu) {
		tex.setFont(font);

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


	switch (event.type) {
	case sf::Event::MouseButtonPressed:
		if (CirSelec.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
			isDragging = true;
	
		}
		break;

	case sf::Event::MouseButtonReleased:
		isDragging = false;

		break;

	case sf::Event::MouseMoved:
		//On ? false : true;

		if (isDragging) {
			moveThumb(static_cast<float>(mousePos.x));
		}
		break;

	default:
		break;
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
	if (On) {
		CirSelec.setPosition(barRight, CirSelec.getPosition().y);
	}
	else {
		CirSelec.setPosition(barLeft, CirSelec.getPosition().y);
	}

}

void menuswicht::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	
	target.draw(capsule, states);
	target.draw(CirSelec, states);
	std::cout << "\n" << CirSelec.getPosition().x;
}