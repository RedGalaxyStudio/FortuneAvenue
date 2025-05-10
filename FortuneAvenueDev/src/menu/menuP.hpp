 #ifndef MENUP_HPP
#define MENUP_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../settings/SettingsManager.hpp" 
#include "../ui/menuSelecting.hpp" 
#include "../network/Client.hpp"
#include <cmath>
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
			sf::Color(180, 180, 180, 255), // gris claro opaco
			sf::Color(180, 180, 180, 0)    // gris claro transparente
		);
	}

	void update(const sf::RenderWindow& window) {
		sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		if (m_text.getGlobalBounds().contains(mousePos)) {
			// Mouse encima → degradado azul
			setBorderColors(
				sf::Color(100, 149, 237, 255), // azul opaco (CornflowerBlue)
				sf::Color(100, 149, 237, 0)    // azul transparente
			);
		}
		else {
			// Mouse fuera → degradado gris claro
			setBorderColors(
				sf::Color(180, 180, 180, 255),
				sf::Color(180, 180, 180, 0)
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

class Client;
class menuP{
public:

    menuP();
    ~menuP();
    void Resource();
    void setWindow(sf::RenderWindow& windowRef);
    void MenuPrincipal();
    void MenuOpcion(bool fon);

    void MenuSalir(Client* client);
private:
    

    void Inicializar();
    void editPerfil();
    void MenuJugar();


  

    void eventoMenuP(GradientText& gt);


    void instruccionesGame();
    
    void MenuAcercaDe();
    void ValidarUser();


    sf::RenderWindow* window;

    
    bool SesionValida;
    SettingsManager* musicSlider;
    SettingsManager* effectSlider;
	menuSelecting* SelectingIdiome;
    sf::Texture textureLogoFortuneAvenue;
    sf::Sprite spriteLogoFortuneAvenue;


    sf::Texture Textureflechainstder;
    sf::Sprite flechainstder;

    sf::Texture Textureflechainstizq;
    sf::Sprite flechainstizq;

    sf::Texture textureInstruccionesOn;
    sf::Texture textureInstruccionesOff;
    sf::Sprite spriteInstrucciones;

    sf::Texture textureAcercaDeOn;
    sf::Texture textureAcercaDeOff;
    sf::Sprite spriteAcercaDe;

    sf::Texture TextureEditButton;
    sf::Sprite spriteEditButton;

    sf::Texture TextureBotonJugarOff;
    sf::Texture TextureBotonJugarOn;
    sf::Sprite SpriteBotonJugar;


    sf::Texture TextureBotonOpcionesOff;
    sf::Texture TextureBotonOpcionesOn;
    sf::Sprite SpriteBotonOpciones;

    sf::Texture TextureBotonSiOff;
    sf::Texture TextureBotonSiOn; 
    sf::Sprite SpriteBotonSi;

    sf::Texture TextureBotonNoOff;
    sf::Texture TextureBotonNoOn;
    sf::Sprite SpriteBotonNo;

    sf::Texture TextureBotonSalirOff;
    sf::Texture TextureBotonSalirOn;
    sf::Sprite SpriteBotonSalir;

    sf::Sprite SpriteFondoMenu;

    sf::Clock clock;

    sf::Texture TextureConfirmarSalir;

    sf::Texture TextureConfirmarSalirSala;

    sf::Texture TextureConfirmarSalirPartida;

    sf::Sprite SpriteConfirmarSalir;


    sf::Font Fuente;
    sf::Text TextAcercaDe;
    sf::Sprite renderedSprite;

    

    sf::Sprite* lastHoveredButton;
    sf::Shader Blur;
   
    sf::Vector2i mousePosition;
    sf::Vector2f mousePosFloat;

};


#endif 

