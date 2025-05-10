#include "menuswicht.hpp"
#include <iostream>
#include "../core/ResourceGlobal.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>
#include <numbers>
  // requiere C++20
menuswicht::menuswicht(sf::RenderWindow& windowRef, sf::Vector2f Position) : window(windowRef),position(Position){

	float radius = 10.f;
	float M_PI = std::numbers::pi;
	backgroum.setFillColor(sf::Color(75, 75, 75));
	backgroum.setSize(sf::Vector2f( 50, (radius - 5.f)*2));
	backgroum.setOutlineColor(sf::Color(50, 50, 50));
	backgroum.setOutlineThickness(5);
	// Tamaño común


	// Fondo círculos
	backIzqCir.setRadius(radius);
	backIzqCir.setFillColor(sf::Color(50, 50, 50));
	backIzqCir.setOrigin(radius, radius);

	backDerCir.setRadius(radius);
	backDerCir.setFillColor(sf::Color(50, 50, 50));
	backDerCir.setOrigin(radius, radius);

	// Flechas círculos
	IzqCir.setRadius(radius - 5.f);
	IzqCir.setFillColor(sf::Color(75, 75, 75));
	IzqCir.setOrigin(radius - 5.f, radius - 5.f);

	DerCir.setRadius(radius - 5.f);
	DerCir.setFillColor(sf::Color(75, 75, 75));
	DerCir.setOrigin(radius - 5.f, radius - 5.f);

	// Selector
	CirSelec.setRadius(radius + 4.f);
	CirSelec.setFillColor(sf::Color::White);
	CirSelec.setOutlineColor(sf::Color(50, 50, 50));
	CirSelec.setOutlineThickness(2.f);
	CirSelec.setOrigin(radius + 4.f, radius + 4.f);

	// Posiciones (puedes ajustarlas)
	backIzqCir.setPosition(250.f, 400.f);
	backgroum.setOrigin(0,radius-5.f);
	backgroum.setPosition(250.f, 400.f);
	IzqCir.setPosition(250.f, 400.f);

	backDerCir.setPosition(backgroum.getPosition().x+ backgroum.getGlobalBounds().width- backgroum.getOutlineThickness(), 400.f);
	DerCir.setPosition(backDerCir.getPosition().x, 400.f);

	CirSelec.setPosition(400.f, 400.f); // centro del menú seleccionado




	const float length = 100.f; // largo del rectángulo
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
	capsule.setOrigin(length / 2.f, 0.f);

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

	position = Position;
	//backgroum.setPosition(position.x - 5, position.y );
	if (Menu.empty()) {
		std::cerr << "Error: El vector Menu está vacío." << std::endl;
		return;  // Salir si el vector está vacío
	}
	Selection = Menu[SelecIdio];
	Selection.setPosition(position);
	// const sf::Text text = Selection;
	float offsetY = position.y;  // Usamos offsetX para acumular el desplazamiento

	for (auto& tex : Menu) {
		if (tex.getFont() == nullptr) {
			std::cerr << "Error: Fuente no asignada a sf::Text." << std::endl;
			continue;  // Continuar si la fuente no está asignada
		}

		tex.setPosition( position.x,offsetY);

		offsetY += tex.getGlobalBounds().height;  // Actualizamos solo offsetX, no Position
		MaxSizeback += tex.getGlobalBounds().height;
	}
	MaxSizeback += 20;
	backgroum.setSize(sf::Vector2f(backgroum.getSize().x+10, Selection.getGlobalBounds().height + 10));


	
}
void menuswicht::event(const sf::Event event) {





}

void menuswicht::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(backIzqCir, states);
	target.draw(backDerCir, states);
	target.draw(backgroum, states);
	target.draw(IzqCir, states);
	target.draw(DerCir, states);
	target.draw(CirSelec, states);
	target.draw(capsule, states);


}