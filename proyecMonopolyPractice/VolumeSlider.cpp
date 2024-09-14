#include "VolumeSlider.hpp"
#include <SFML/Audio.hpp>
#include <sstream>
#include <algorithm>

// Constructor
VolumeSlider::VolumeSlider(float x, float y, float width, float height, sf::Music* music)
    : volume(100.0f), isDragging(false), music(music) {
    if (music != nullptr) {
        music->setVolume(volume);
    }
    // Configurar la barra de fondo del slider
    bar.setSize(sf::Vector2f(width, height));
    bar.setPosition(x, y);
    bar.setFillColor(sf::Color(50, 50, 50)); // Color gris oscuro para la barra
    bar.setOutlineColor(sf::Color(200, 200, 200)); // Color del borde
    bar.setOutlineThickness(2.0f); // Grosor del borde

    // Configurar la barra pintada
    filledBar.setSize(sf::Vector2f(width, height));
    filledBar.setPosition(x, y);
    filledBar.setFillColor(sf::Color(0, 255, 0)); // Color verde para la barra pintada
    filledBar.setOutlineColor(sf::Color(200, 200, 200)); // Color del borde
    filledBar.setOutlineThickness(2.0f); // Grosor del borde

    // Configurar el mango del slider (thumb) como círculo
    thumb.setRadius(height / 2 + 5.f); // Un poco más grande que la barra para ser más visible
    thumb.setFillColor(sf::Color::Red);
    thumb.setOutlineColor(sf::Color::Black); // Color del borde del mango
    thumb.setOutlineThickness(2.0f); // Grosor del borde
    thumb.setPosition(x + width - thumb.getRadius() * 2, 6 + y - thumb.getRadius());  // Inicialmente en el 100% de la barra

    // Configurar el texto para mostrar el volumen
    if (!font.loadFromFile("resource/fonts/Pixel Times Bold.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }
    volumeText.setFont(font);
    volumeText.setCharacterSize(20);
    volumeText.setPosition(x + width + 15.f, y - 5.f);
    volumeText.setFillColor(sf::Color::White);
    updateVolumeText();
}

VolumeSlider::VolumeSlider(float x, float y, float width, float height, std::vector<sf::Sound*>& effects)
    : volume(100.0f), isDragging(false), effects(effects) {
    for (auto* effect : effects) {
        if (effect != nullptr) {
            effect->setVolume(volume);
        }
    }
    // Configurar la barra de fondo del slider
    bar.setSize(sf::Vector2f(width, height));
    bar.setPosition(x, y);
    bar.setFillColor(sf::Color(50, 50, 50)); // Color gris oscuro para la barra
    bar.setOutlineColor(sf::Color(200, 200, 200)); // Color del borde
    bar.setOutlineThickness(2.0f); // Grosor del borde

    // Configurar la barra pintada
    filledBar.setSize(sf::Vector2f(width, height));
    filledBar.setPosition(x, y);
    filledBar.setFillColor(sf::Color(0, 255, 0)); // Color verde para la barra pintada
    filledBar.setOutlineColor(sf::Color(200, 200, 200)); // Color del borde
    filledBar.setOutlineThickness(2.0f); // Grosor del borde

    // Configurar el mango del slider (thumb) como círculo
    thumb.setRadius(height / 2 + 5.f); // Un poco más grande que la barra para ser más visible
    thumb.setFillColor(sf::Color::Red);
    thumb.setOutlineColor(sf::Color::Black); // Color del borde del mango
    thumb.setOutlineThickness(2.0f); // Grosor del borde
    thumb.setPosition(x + width - thumb.getRadius() * 2, 6 + y - thumb.getRadius());  // Inicialmente en el 100% de la barra

    // Configurar el texto para mostrar el volumen
    if (!font.loadFromFile("resource/fonts/Pixel Times Bold.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }
    volumeText.setFont(font);
    volumeText.setCharacterSize(20);
    volumeText.setPosition(x + width + 15.f, y - 5.f);
    volumeText.setFillColor(sf::Color::White);
    updateVolumeText();
}


// Manejar los eventos del ratón
void VolumeSlider::handleEvent(sf::Event& event, const sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    switch (event.type) {
    case sf::Event::MouseButtonPressed:
        if (thumb.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            isDragging = true;  // Comienza a arrastrar el mango
        }
        break;

    case sf::Event::MouseButtonReleased:
        isDragging = false;  // Termina de arrastrar el mango
        break;

    case sf::Event::MouseMoved:
        if (isDragging) {
            moveThumb(static_cast<float>(mousePos.x));
        }
        break;

    default:
        break;
    }
}

// Movimiento del mango del slider (se aplica a música o efectos)
void VolumeSlider::moveThumb(float mouseX) {
    float barLeft = bar.getPosition().x;
    float barRight = barLeft + bar.getSize().x;

    mouseX = clamp(mouseX, barLeft, barRight);

    thumb.setPosition(mouseX - thumb.getRadius(), thumb.getPosition().y);

    float percentage = (mouseX - barLeft) / bar.getSize().x;
    volume = percentage * 100.0f;

    filledBar.setSize(sf::Vector2f(percentage * bar.getSize().x, bar.getSize().y));

    // Ajustar el volumen de la música
    if (music != nullptr) {
        music->setVolume(volume);
    }

    // Ajustar el volumen de los efectos
    for (auto* effect : effects) {
        if (effect != nullptr) {
            effect->setVolume(volume);
        }
    }

    updateVolumeText();
}


// Dibujar el slider en la pantalla
void VolumeSlider::draw(sf::RenderWindow& window) const {
    window.draw(bar);
    window.draw(filledBar); // Dibuja la parte pintada de la barra
    window.draw(thumb);
    window.draw(volumeText);
}

// Obtener el volumen actual
float VolumeSlider::getVolume() const {
    return volume;
}

// Actualizar el texto del volumen
void VolumeSlider::updateVolumeText() {
    std::ostringstream oss;
    oss << "Vol: " << static_cast<int>(volume) << "%";
    volumeText.setString(oss.str());
}

// Función de ayuda para clamping
float VolumeSlider::clamp(float value, float min, float max) const {
    return std::max(min, std::min(value, max));
}
