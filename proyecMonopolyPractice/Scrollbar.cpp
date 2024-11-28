#include "Scrollbar.hpp"
#include "ResourceGlobal.hpp"
#include <iostream>

// Constructor
Scrollbar::Scrollbar(float windowHeight, float scrollbarHeight, float width)
    : windowHeight(windowHeight), scrollbarHeight(scrollbarHeight), x(0), y(0), scrollOffset(0) {
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
    cornerTL.setFillColor(scrollbarThumb.getFillColor());
    cornerTL.setOrigin(radius, radius);

    cornerTR.setRadius(radius);
    cornerTR.setFillColor(scrollbarThumb.getFillColor());
    cornerTR.setOrigin(radius, radius);

    cornerBL.setRadius(radius);
    cornerBL.setFillColor(scrollbarThumb.getFillColor());
    cornerBL.setOrigin(radius, radius);

    cornerBR.setRadius(radius);
    cornerBR.setFillColor(scrollbarThumb.getFillColor());
    cornerBR.setOrigin(radius, radius);

    // Inicializar posiciones
    scrollbarTrack.setPosition(x, y);
    scrollbarThumb.setPosition(x, y);

    // Calcula el desplazamiento máximo
    maxScrollOffset = windowHeight - scrollbarHeight;
}

// Método para actualizar la posición del pulgar
void Scrollbar::update(float deltaScroll) {
    deltaScroll = std::clamp(deltaScroll, -1.0f, 1.0f);
    scrollOffset += deltaScroll * 10.0f;  // Ajustado a 1-.0f para reducir la velocidad del desplazamiento

    // Limitar el desplazamiento
    if (scrollOffset < 0) {
        scrollOffset = 0;
    }
    else if (scrollOffset > maxScrollOffset) {
        scrollOffset = maxScrollOffset;
    }

    // Calcular la posición del pulgar
    float thumbPosition = (scrollOffset / maxScrollOffset) * (windowHeight - scrollbarHeight);
    thumbPosition += y;
    scrollbarThumb.setPosition(x, thumbPosition);

    // Ajustar las posiciones de los círculos
    cornerTL.setPosition(x + conerPs, thumbPosition);
    cornerTR.setPosition(x + scrollbarThumb.getSize().x - conerPs, thumbPosition);
    cornerBL.setPosition(x + conerPs, thumbPosition + scrollbarThumb.getSize().y);
    cornerBR.setPosition(x + scrollbarThumb.getSize().x - conerPs, thumbPosition + scrollbarThumb.getSize().y);
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


void Scrollbar::Prinft() {
    renderTexture.draw(scrollbarTrack);
    renderTexture.draw(scrollbarThumb);

    // Dibujar los bordes redondeados
    renderTexture.draw(cornerTL);
    renderTexture.draw(cornerTR);
    renderTexture.draw(cornerBL);
    renderTexture.draw(cornerBR);
}

// Método para establecer la posición de la barra
void Scrollbar::setPosition(float xNew, float yNew) {
    x = xNew;
    y = yNew;

    scrollbarTrack.setPosition(x, y);
    scrollbarThumb.setPosition(x, y);

    // Ajustar las posiciones de los círculos
    cornerTL.setPosition(x + conerPs, y);
    cornerTR.setPosition(x + scrollbarThumb.getSize().x - conerPs, y);
    cornerBL.setPosition(x + conerPs, y + scrollbarThumb.getSize().y);
    cornerBR.setPosition(x + scrollbarThumb.getSize().x - conerPs, y + scrollbarThumb.getSize().y);
}

// Método para cambiar los colores
void Scrollbar::setColors(const sf::Color& trackColor, const sf::Color& thumbColor, const sf::Color& borderColor) {
    scrollbarTrack.setFillColor(trackColor);
    scrollbarThumb.setFillColor(thumbColor);
    scrollbarThumb.setOutlineColor(borderColor);

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


void Scrollbar::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    auto mousePos = sf::Mouse::getPosition(window);

    if (event.type == sf::Event::MouseButtonPressed) {
        if (scrollbarThumb.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            dragging = true;
            dragOffset = mousePos.y - scrollbarThumb.getPosition().y;
        }
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        dragging = false;
    }

    if (event.type == sf::Event::MouseMoved && dragging) {
        float newThumbY = mousePos.y - dragOffset;
        scrollOffset = ((newThumbY - y) / (windowHeight - scrollbarHeight)) * maxScrollOffset;
        scrollOffset = std::clamp(scrollOffset, 0.0f, maxScrollOffset);
        update(0);  // Update the thumb position after dragging
    }
}
