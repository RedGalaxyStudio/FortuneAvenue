#include "Scrollbar.hpp"
#include <iostream>
// Constructor
Scrollbar::Scrollbar(float windowHeight, float scrollbarHeight, float width)
    : windowHeight(windowHeight), scrollbarHeight(scrollbarHeight) ,x(0),y(0){
    conerPs = width / 2;

    // Crear el fondo de la barra (track)
    scrollbarTrack.setSize(sf::Vector2f(width, windowHeight));
    scrollbarTrack.setFillColor(sf::Color(74, 84, 88));  // Color: #4a5458

    // Crear el pulgar de la barra (thumb)
    scrollbarThumb.setSize(sf::Vector2f(width, scrollbarHeight));
    scrollbarThumb.setFillColor(sf::Color(81, 109, 255));  // Color: #516dff
    scrollbarThumb.setOutlineThickness(4);
    scrollbarThumb.setOutlineColor(sf::Color(35, 46, 51));  // Borde color: #232E33

    // Crear los círculos para simular bordes redondeados
    float radius = width / 2.0f;

    cornerTL.setRadius(radius);
    cornerTL.setFillColor(scrollbarThumb.getFillColor());  // Mismo color que el pulgar
    cornerTL.setOrigin(radius, radius);
    cornerTL.setOutlineThickness(4);
    cornerTL.setOutlineColor(sf::Color(35, 46, 51));  // Borde color: #232E33

    cornerTR.setRadius(radius);
    cornerTR.setFillColor(scrollbarThumb.getFillColor());
    cornerTR.setOrigin(radius, radius);
    cornerTR.setOutlineThickness(4);
    cornerTR.setOutlineColor(sf::Color(35, 46, 51));  // Borde color: #232E33

    cornerBL.setRadius(radius);
    cornerBL.setFillColor(scrollbarThumb.getFillColor());
    cornerBL.setOrigin(radius, radius);
    cornerBL.setOutlineThickness(4);
    cornerBL.setOutlineColor(sf::Color(35, 46, 51));  // Borde color: #232E33

    cornerBR.setRadius(radius);
    cornerBR.setFillColor(scrollbarThumb.getFillColor());
    cornerBR.setOrigin(radius, radius);
    cornerBR.setOutlineThickness(4);
    cornerBR.setOutlineColor(sf::Color(35, 46, 51));  // Borde color: #232E33
   // windowHeight = 720;
}

// Método para actualizar la posición del pulgar
void Scrollbar::update(float deltaScroll) {
    scrollOffset += deltaScroll * 10.0f;  // Ajusta la sensibilidad del scroll

    // Asegúrate de que el scrollOffset no sea menor al límite inferior o mayor al límite superior
    if (scrollOffset < 0) {
        scrollOffset = 0;
    }
    else if (scrollOffset > maxScrollOffset) {
        scrollOffset = maxScrollOffset;
    }

    // Calcula la posición del pulgar basado en el desplazamiento actual
    float thumbPosition = (scrollOffset / maxScrollOffset) * (windowHeight - scrollbarHeight);
    thumbPosition += y;
    scrollbarThumb.setPosition(x, thumbPosition);
    // Ajustar las posiciones de los círculos (esquinas redondeadas)
    cornerTL.setPosition(x + conerPs, thumbPosition);  // Esquina superior izquierda
    cornerTR.setPosition(x + scrollbarThumb.getSize().x - conerPs, thumbPosition);  // Esquina superior derecha
    cornerBL.setPosition(x + conerPs, thumbPosition + scrollbarThumb.getSize().y);  // Esquina inferior izquierda
    cornerBR.setPosition(x + scrollbarThumb.getSize().x - conerPs, thumbPosition + scrollbarThumb.getSize().y);  // Esquina inferior derecha

}

// Método para dibujar la barra de desplazamiento
void Scrollbar::draw(sf::RenderWindow& window) {
    window.draw(scrollbarTrack);
    window.draw(scrollbarThumb);

    // Dibujar los bordes redondeados
    window.draw(cornerTL);
    window.draw(cornerTR);
    window.draw(cornerBL);
    window.draw(cornerBR);
}

// Método para establecer la posición de la barra
void Scrollbar::setPosition(float xNew, float yNew) {
    x = xNew;
    y = yNew;

    scrollbarTrack.setPosition(x, y);
    scrollOffset = y;
   
    maxScrollOffset = y + windowHeight;
    cornerTL.setPosition(x + conerPs, y);  // Esquina superior izquierda
    cornerTR.setPosition(conerPs - x + scrollbarThumb.getSize().x, y);  // Esquina superior derecha
    cornerBL.setPosition(x + conerPs, y + scrollbarThumb.getSize().y);  // Esquina inferior izquierda
    cornerBR.setPosition(conerPs - x + scrollbarThumb.getSize().x, y + scrollbarThumb.getSize().y);  // Esquina inferior derecha
    scrollbarThumb.setPosition(x, scrollOffset);  // Pulgar debe estar alineado con scrollOffset
}

// Método para cambiar los colores
void Scrollbar::setColors(const sf::Color& trackColor, const sf::Color& thumbColor, const sf::Color& borderColor) {
    scrollbarTrack.setFillColor(trackColor);
    scrollbarThumb.setFillColor(thumbColor);
    scrollbarThumb.setOutlineColor(borderColor);

    // También cambiar los colores de los bordes redondeados
    cornerTL.setFillColor(thumbColor);
    cornerTR.setFillColor(thumbColor);
    cornerBL.setFillColor(thumbColor);
    cornerBR.setFillColor(thumbColor);
}

// Método para ajustar el grosor del borde
void Scrollbar::setOutlineThickness(float thickness) {
    scrollbarThumb.setOutlineThickness(thickness);
}

float Scrollbar::getScrollOffset() const {
    return scrollOffset;
}
