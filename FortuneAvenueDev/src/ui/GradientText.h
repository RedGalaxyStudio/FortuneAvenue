#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

class GradientText : public sf::Drawable {
public:
	GradientText(const std::string& text, const sf::Font& font, unsigned int characterSize) {
		m_text.setFont(font);
		m_text.setString(text);
		m_text.setCharacterSize(characterSize);
		m_text.setFillColor(sf::Color(185, 185, 185));

		//   m_text.setOutlineColor();
		  // m_text.setOutlineThickness(0.6f);


		m_border.setFont(font);
		m_border.setString(text);
		m_border.setCharacterSize(characterSize);

		// borde interior rojo sólido → borde exterior rojo transparente
		setBorderColors(
			sf::Color(95, 95, 95, 255), // gris claro opaco
			sf::Color(95, 95, 95, 0)    // gris claro transparente
		);
	}

	void update(bool band) {

		if (band) {
			// Mouse encima → degradado azul
			setBorderColors(
				sf::Color(100, 149, 237, 255), // azul opaco (CornflowerBlue)
				sf::Color(100, 149, 237, 0)    // azul transparente
			);
		}
		else {
			// Mouse fuera → degradado gris claro
			setBorderColors(
				sf::Color(95, 95, 95, 255),
				sf::Color(95, 95, 95, 0)
			);
		}
	}
	void setPosition(float x, float y) {
		m_text.setPosition(x, y);
		m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);

		m_border.setPosition(x, y);
		m_border.setOrigin(m_border.getGlobalBounds().width / 2, m_border.getGlobalBounds().height / 2);
	}

	void setBorderThickness(float thickness) {
		m_borderThickness = thickness;
	}

	void setBorderColors(const sf::Color& inner, const sf::Color& outer) {
		m_borderColor1 = inner;
		m_borderColor2 = outer;
	}


	// Función que ajusta los colores en función de la entrada de teclado
	void ajustarColores(sf::Event::KeyEvent keyEvent) {
		if (keyEvent.code == sf::Keyboard::Up) {
			// Oscurecer el gris
			m_borderColor1 = sf::Color(
				std::max(0, m_borderColor1.r - 10),  // Disminuir el valor de rojo
				std::max(0, m_borderColor1.g - 10),  // Disminuir el valor de verde
				std::max(0, m_borderColor1.b - 10),  // Disminuir el valor de azul
				m_borderColor1.a
			);
			m_borderColor2 = sf::Color(
				std::max(0, m_borderColor2.r - 10),
				std::max(0, m_borderColor2.g - 10),
				std::max(0, m_borderColor2.b - 10),
				m_borderColor2.a
			);
		}
		else if (keyEvent.code == sf::Keyboard::Down) {
			// Aclarar el gris
			m_borderColor1 = sf::Color(
				std::min(255, m_borderColor1.r + 10),  // Aumentar el valor de rojo
				std::min(255, m_borderColor1.g + 10),  // Aumentar el valor de verde
				std::min(255, m_borderColor1.b + 10),  // Aumentar el valor de azul
				m_borderColor1.a
			);
			m_borderColor2 = sf::Color(
				std::min(255, m_borderColor2.r + 10),
				std::min(255, m_borderColor2.g + 10),
				std::min(255, m_borderColor2.b + 10),
				m_borderColor2.a
			);
		}
		std::cout << "Color 1: ("
			<< (int)m_borderColor1.r << ", "
			<< (int)m_borderColor1.g << ", "
			<< (int)m_borderColor1.b << ", "
			<< (int)m_borderColor1.a << ")\n";
	}





protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		// Dibuja un anillo 1px a 1px desde -thickness hasta +thickness
		for (int dx = -static_cast<int>(m_borderThickness); dx <= static_cast<int>(m_borderThickness); ++dx) {
			for (int dy = -static_cast<int>(m_borderThickness); dy <= static_cast<int>(m_borderThickness); ++dy) {
				if (dx == 0 && dy == 0) continue;
				float dist = std::sqrt(float(dx * dx + dy * dy));
				if (dist > m_borderThickness) continue;

				// copia local para no mutar miembros
				sf::Text copy = m_border;
				copy.setFillColor(interpolateColor(dist));
				copy.setPosition(m_text.getPosition() + sf::Vector2f(float(dx), float(dy)));

				target.draw(copy, states);
			}
		}

		target.draw(m_text, states);
	}

private:
	sf::Text m_text, m_border;
	float   m_borderThickness = 4.f;
	sf::Color m_borderColor1, m_borderColor2;

	// Mezcla solo el canal alfa entre inner.a y outer.a según dist/thickness
	sf::Color interpolateColor(float dist) const {
		float t = std::min(dist / m_borderThickness, 1.f);

		sf::Uint8 r = static_cast<sf::Uint8>(m_borderColor1.r * (1.f - t) + m_borderColor2.r * t);
		sf::Uint8 g = static_cast<sf::Uint8>(m_borderColor1.g * (1.f - t) + m_borderColor2.g * t);
		sf::Uint8 b = static_cast<sf::Uint8>(m_borderColor1.b * (1.f - t) + m_borderColor2.b * t);
		sf::Uint8 a = static_cast<sf::Uint8>(m_borderColor1.a * (1.f - t) + m_borderColor2.a * t);

		return sf::Color(r, g, b, a);
	}
};