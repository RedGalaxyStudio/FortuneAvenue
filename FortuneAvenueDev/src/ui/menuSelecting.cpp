#include "menuSelecting.hpp"
#include <iostream>
#include "../core/ResourceGlobal.hpp"
#include <SFML/Graphics.hpp>
menuSelecting::menuSelecting(sf::RenderWindow& windowRef, std::vector<std::string>InfoMenu) : window(windowRef)
{
	Menu.resize(InfoMenu.size());
	for (size_t i = 0; i < InfoMenu.size(); ++i) {
		Menu[i].setString(InfoMenu[i]);
		Menu[i].setCharacterSize(20);
	}

	backgroum.setFillColor(sf::Color(65, 65, 65));
	backgroum.setSize(sf::Vector2f( 160,30));
	backgroum.setOutlineColor(sf::Color(35, 35, 35));
	backgroum.setOutlineThickness(2);
}

void menuSelecting::setFont(sf::Font font) {
	fontC = font;
	for (auto& tex : Menu) {
		tex.setFont(fontC);

	}
}
void menuSelecting::setSize(float Size) {
	size = Size;
	for (auto& tex : Menu) {
		tex.setCharacterSize(Size);
	}
}
void menuSelecting::setColors(sf::Color color) {
	Color = color;
	for (auto& tex : Menu) {
		tex.setFillColor(Color);
	}
}
void menuSelecting::setPosition(sf::Vector2f Position) {

	position = Position;
	backgroum.setPosition(position.x - 5, position.y );
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
void menuSelecting::event(const sf::Event event) {

	if (!open) {
	
		
			if (event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		
					if (Selection.getGlobalBounds().contains(mousePos)) {
						
						if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
							open = true;  // Se clickeó
							backgroum.setSize(sf::Vector2f(backgroum.getSize().x, MaxSizeback));

						}
					}
					
				
			}
	
	
	}
	else {

		if (event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseButtonPressed) {
			sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

			for (size_t i = 0; i < Menu.size(); ++i) {
				bool hovered = Menu[i].getGlobalBounds().contains(mousePos);

				if (hovered) {
					Menu[i].setCharacterSize(30); // Resalta

					if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
						SelecIdio = i;
						Selection = Menu[SelecIdio];
						Selection.setPosition(position);
						Selection.setCharacterSize(size);
						backgroum.setSize(sf::Vector2f(backgroum.getSize().x, Selection.getGlobalBounds().height+10));

						open = false;  // Se clickeó
					}
				}
				else {
					Menu[i].setCharacterSize(23); // Tamaño normal
				}
			}
		}
	}



}

void menuSelecting::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (!open) {

		target.draw(backgroum, states);
		target.draw(Selection, states);
	}
	else {
		target.draw(backgroum, states);
		for (const auto& text : Menu) {
			target.draw(text, states);
		}
	}
}