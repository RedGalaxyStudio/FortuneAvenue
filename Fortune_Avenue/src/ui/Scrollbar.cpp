#include "Scrollbar.hpp"
#include "../core/ResourceGlobal.hpp"
#include <iostream>

// Constructor
Scrollbar::Scrollbar(float windowHeight, float scrollbarHeight, float width)
    : windowHeight(windowHeight), scrollbarHeight(scrollbarHeight), x(0), y(0), scrollOffset(0) {
 
    // Crear el fondo de la barra (track)
    scrollbarTrack.setSize(sf::Vector2f(width, windowHeight));
    scrollbarTrack.setFillColor(sf::Color(74, 84, 88));  // Color: #4a5458

     espacio = static_cast<float>(width * 0.2);
     thumbW = static_cast<float>(width * 0.6);
     bordetumbW = static_cast<float>(width * 0.2);
     conerPs = thumbW / 2;

    // Crear el pulgar de la barra (thumb)
    scrollbarThumb.setSize(sf::Vector2f(thumbW, scrollbarHeight));
    scrollbarThumb.setFillColor(sf::Color(81, 109, 255));  // Color: #516dff
    scrollbarThumb.setOutlineThickness(bordetumbW);
    scrollbarThumb.setOutlineColor(sf::Color(35, 46, 51));  // Borde color: #232E33

    // Crear los c�rculos para simular bordes redondeados
    float radius = thumbW / 2.0f;

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


    radius += bordetumbW;
    cornerTLB.setRadius(radius);
    cornerTLB.setFillColor(sf::Color(35, 46, 51));
    cornerTLB.setOrigin(radius, radius);

    cornerTRB.setRadius(radius);
    cornerTRB.setFillColor(sf::Color(35, 46, 51));
    cornerTRB.setOrigin(radius, radius);

    cornerBLB.setRadius(radius);
    cornerBLB.setFillColor(sf::Color(35, 46, 51));
    cornerBLB.setOrigin(radius, radius);

    cornerBRB.setRadius(radius);
    cornerBRB.setFillColor(sf::Color(35, 46, 51));
    cornerBRB.setOrigin(radius, radius);

    // Inicializar posiciones
    scrollbarTrack.setPosition(x, y);
    scrollbarThumb.setPosition(x, y);

    // Calcula el desplazamiento m�ximo
    maxScrollOffset = windowHeight - scrollbarHeight;
}

// M�todo para actualizar la posici�n del pulgar
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

    // Calcular la posici�n del pulgar
    float thumbPosition = (scrollOffset / maxScrollOffset) * (windowHeight - scrollbarHeight);
    thumbPosition += y;
    scrollbarThumb.setPosition(x, thumbPosition);

    // Ajustar las posiciones de los c�rculos
    cornerTL.setPosition(x + conerPs, thumbPosition);
    cornerTR.setPosition(x + scrollbarThumb.getSize().x - conerPs, thumbPosition);
    cornerBL.setPosition(x + conerPs, thumbPosition + scrollbarThumb.getSize().y);
    cornerBR.setPosition(x + scrollbarThumb.getSize().x - conerPs, thumbPosition + scrollbarThumb.getSize().y);

    cornerTLB.setPosition(x + conerPs, thumbPosition);
    cornerTRB.setPosition(x + scrollbarThumb.getSize().x - conerPs, thumbPosition);
    cornerBLB.setPosition(x + conerPs, thumbPosition + scrollbarThumb.getSize().y);
    cornerBRB.setPosition(x + scrollbarThumb.getSize().x - conerPs, thumbPosition + scrollbarThumb.getSize().y);
}

// M�todo para dibujar la barra de desplazamiento
void Scrollbar::draw(sf::RenderWindow& window) {
    window.draw(scrollbarTrack);
    window.draw(cornerTLB);
    window.draw(cornerTRB);
    window.draw(cornerBLB);
    window.draw(cornerBRB);
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
    renderTexture.draw(cornerTLB);
    renderTexture.draw(cornerTRB);
    renderTexture.draw(cornerBLB);
    renderTexture.draw(cornerBRB);
    renderTexture.draw(cornerTL);
    renderTexture.draw(cornerTR);
    renderTexture.draw(cornerBL);
    renderTexture.draw(cornerBR);
}

// M�todo para establecer la posici�n de la barra
void Scrollbar::setPosition(float xNew, float yNew) {
    x = xNew;
    y = yNew;

    scrollbarTrack.setPosition(x, y);

    x += espacio;
    scrollbarThumb.setPosition(x, y);

    // Ajustar las posiciones de los c�rculos
    cornerTL.setPosition(x + conerPs, y);
    cornerTR.setPosition(x + scrollbarThumb.getSize().x - conerPs, y);
    cornerBL.setPosition(x + conerPs, y + scrollbarThumb.getSize().y);
    cornerBR.setPosition(x + scrollbarThumb.getSize().x - conerPs, y + scrollbarThumb.getSize().y);

    cornerTLB.setPosition(x + conerPs, y);
    cornerTRB.setPosition(x + scrollbarThumb.getSize().x - conerPs, y);
    cornerBLB.setPosition(x + conerPs, y + scrollbarThumb.getSize().y);
    cornerBRB.setPosition(x + scrollbarThumb.getSize().x - conerPs, y + scrollbarThumb.getSize().y);
}

// M�todo para cambiar los colores
void Scrollbar::setColors(const sf::Color& trackColor, const sf::Color& thumbColor, const sf::Color& borderColor) {
    scrollbarTrack.setFillColor(trackColor);
    scrollbarThumb.setFillColor(thumbColor);
    scrollbarThumb.setOutlineColor(borderColor);

    cornerTL.setFillColor(thumbColor);
    cornerTR.setFillColor(thumbColor);
    cornerBL.setFillColor(thumbColor);
    cornerBR.setFillColor(thumbColor);
    cornerTLB.setFillColor(sf::Color(35, 46, 51));
    cornerTRB.setFillColor(sf::Color(35, 46, 51));
    cornerBLB.setFillColor(sf::Color(35, 46, 51));
    cornerBRB.setFillColor(sf::Color(35, 46, 51));
}

// M�todo para ajustar el grosor del borde
void Scrollbar::setOutlineThickness(float thickness) {
    scrollbarThumb.setOutlineThickness(thickness);
}

float Scrollbar::getScrollOffset() const {
    return scrollOffset;
}


void Scrollbar::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    auto mousePos = sf::Mouse::getPosition(window);

    if (event.type == sf::Event::MouseButtonPressed) {
        if (scrollbarThumb.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
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
