#ifndef SCROLLBAR_HPP
#define SCROLLBAR_HPP

#include <SFML/Graphics.hpp>

class Scrollbar {
public:
    // Constructor
    Scrollbar(float windowHeight, float scrollbarHeight, float width);

    // Método para actualizar la posición del pulgar
    void update(float deltaScroll);

    // Método para dibujar la barra de desplazamiento
    void draw(sf::RenderWindow& window);

    // Método para establecer la posición de la barra
    void setPosition(float xNew, float yNew);

    // Método para cambiar los colores
    void setColors(const sf::Color& trackColor, const sf::Color& thumbColor, const sf::Color& borderColor);

    // Método para ajustar el grosor del borde
    void setOutlineThickness(float thickness);

    // Método para obtener el desplazamiento de scroll
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


