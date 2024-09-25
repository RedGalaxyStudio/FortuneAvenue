#ifndef SCROLLBAR_HPP
#define SCROLLBAR_HPP

#include <SFML/Graphics.hpp>

class Scrollbar {
public:
    // Constructor
    Scrollbar(float windowHeight, float scrollbarHeight, float width);

    // M�todo para actualizar la posici�n del pulgar
    void update(float deltaScroll);

    // M�todo para dibujar la barra de desplazamiento
    void draw(sf::RenderWindow& window);

    // M�todo para establecer la posici�n de la barra
    void setPosition(float xNew, float yNew);

    // M�todo para cambiar los colores
    void setColors(const sf::Color& trackColor, const sf::Color& thumbColor, const sf::Color& borderColor);

    // M�todo para ajustar el grosor del borde
    void setOutlineThickness(float thickness);

    // M�todo para obtener el desplazamiento de scroll
    float getScrollOffset() const;

private:
    // Variables de la barra
    sf::RectangleShape scrollbarTrack; // Fondo de la barra
    sf::RectangleShape scrollbarThumb; // Pulgar de la barra
    sf::CircleShape cornerTL, cornerTR, cornerBL, cornerBR; // Esquinas redondeadas
    float conerPs,x,y;
    float maxScrollOffset;
    // Variables para el control del scroll
    float width;
    float windowHeight;      // Altura de la ventana
    float scrollbarHeight;   // Altura del pulgar
    float scrollOffset;      // Desplazamiento actual
    //void updateCornerPositions(); // Actualizar las posiciones de los bordes redondeados
};

#endif // SCROLLBAR_HPP


