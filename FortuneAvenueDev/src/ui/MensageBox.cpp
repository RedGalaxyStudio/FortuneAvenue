#include "MensageBox.hpp"
#include <algorithm>
#include <iostream>
#include <cmath> 

MensageBox::MensageBox(const std::string& text, const sf::Font& font, unsigned int fontSize)
    : isVisible(false), isFading(false) {

    this->font = font;
    message.setFont(this->font);
    message.setString(text);
    message.setCharacterSize(fontSize);
    message.setFillColor(sf::Color::White);

    message.setOutlineThickness(2);
    message.setOutlineColor(sf::Color(135, 135, 135));

    // Inicializa las posiciones
    startX = 1280 - 224; // 200 es el ancho de la caja
    startY = 10; // margen superior

    setupRoundedBox();

    targetPosition = sf::Vector2f(600, 10);
}

void MensageBox::setupRoundedBox() {
    float radius = 15.0f; // Radio de las esquinas redondeadas
    sf::Vector2f boxSize(200, 50); // Tama�o del cuadro
    int numSegments = 8; // N�mero de segmentos para cada esquina

    // Configura el n�mero de puntos (4 esquinas, cada una con numSegments puntos)
    roundedBox.setPointCount(4 * numSegments);

    // Coordenadas para cada una de las cuatro esquinas redondeadas
    int index = 0;

    // Esquina superior izquierda
    for (int i = 0; i < numSegments; ++i) {
        float angle = 3.14159f / 2 * i / (numSegments - 1);
        roundedBox.setPoint(index++, sf::Vector2f(radius * (1 - cos(angle)), radius * (1 - sin(angle))));
    }

    // Esquina superior derecha
    for (int i = 0; i < numSegments; ++i) {
        float angle = 3.14159f / 2 * i / (numSegments - 1);
        roundedBox.setPoint(index++, sf::Vector2f(boxSize.x - radius + radius * sin(angle), radius * (1 - cos(angle))));
    }

    // Esquina inferior derecha
    for (int i = 0; i < numSegments; ++i) {
        float angle = 3.14159f / 2 * i / (numSegments - 1);
        roundedBox.setPoint(index++, sf::Vector2f(boxSize.x - radius + radius * cos(angle), boxSize.y - radius + radius * sin(angle)));
    }

    // Esquina inferior izquierda
    for (int i = 0; i < numSegments; ++i) {
        float angle = 3.14159f / 2 * i / (numSegments - 1);
        roundedBox.setPoint(index++, sf::Vector2f(radius * (1 - sin(angle)), boxSize.y - radius + radius * cos(angle)));
    }

    // Posiciona `roundedBox` en la pantalla y establece un color visible
    roundedBox.setPosition(startX, startY);
    roundedBox.setFillColor(sf::Color(0, 0, 0, 140)); // Color s�lido para pruebas
}




void MensageBox::showMessage() {
    isVisible = true;
    isFading = false;
    clock.restart();
    roundedBox.setFillColor(sf::Color(0, 0, 0, 140)); // Color s�lido para pruebas
    message.setFillColor(sf::Color::White);

    message.setOutlineThickness(2);
    message.setOutlineColor(sf::Color(135, 135, 135));
}

void MensageBox::update() {
    if (!isVisible) return;

    float elapsed = clock.getElapsedTime().asSeconds();

    // Animaci�n de subida y bajada (solo ocurre una vez)
    if (!isFading && elapsed < 0.5f) {
        float t = elapsed / 0.5f;
        roundedBox.setPosition(startX + 15, targetPosition.y - 35 * (1 - t)); // Ajusta para bajar una vez
        message.setPosition(startX + 15, targetPosition.y - 35 * (1 - t)); // Ajusta para bajar una vez
        centerText();
    }
    else if (elapsed >= 0.5f && elapsed <= 2.0f) {
        // Mantener la posici�n sin realizar ning�n movimiento adicional
        roundedBox.setPosition(startX + 15, targetPosition.y);
        message.setPosition(startX + 15, targetPosition.y);
        centerText();
    }
    else if (elapsed > 2.0f && !isFading) {
        // Inicia el desvanecimiento
        isFading = true;
        clock.restart();
    }

    // L�gica para desvanecimiento
    if (isFading) {
        float alpha = std::max(0.0f, 180 - (clock.getElapsedTime().asSeconds() * 180));
        sf::Color newColor(0, 0, 0, static_cast<sf::Uint8>(alpha));
        roundedBox.setFillColor(newColor);

        sf::Color textColor = message.getFillColor();
        textColor.a = static_cast<sf::Uint8>(alpha);
        message.setFillColor(textColor);

        if (alpha <= 0) {
            isVisible = false; // Termina al final del desvanecimiento
        }
    }
}


void MensageBox::centerText() {
    sf::FloatRect textBounds = message.getLocalBounds();
    sf::FloatRect boxBounds = roundedBox.getGlobalBounds();

    // Centrar el texto dentro de `roundedBox`
    float centeredX = boxBounds.left + (boxBounds.width - textBounds.width) / 2.0f - textBounds.left;
    float centeredY = boxBounds.top + (boxBounds.height - textBounds.height) / 2.0f - textBounds.top;
    message.setPosition(centeredX, centeredY);
}


void MensageBox::draw(sf::RenderWindow& window) {
    if (isVisible) {
        window.draw(roundedBox);
        window.draw(message);
    }
}
