#include "SettingsManager.hpp"
#include <iostream>

SettingsManager::SettingsManager(sf::RenderWindow& windowRef) : window(windowRef), volume(100.0f), isDragging(false), music(nullptr), musicEnabled(true), effectsEnabled(true)
{
}

SettingsManager::SettingsManager()
    : window(*(new sf::RenderWindow())), volume(100.0f), isDragging(false), music(nullptr), musicEnabled(true), effectsEnabled(true)
{
    // Inicializa los miembros según sea necesario
    // Quizás quieras manejar la limpieza de la ventana de renderizado de marcador de posición si se usa
}

SettingsManager::SettingsManager(float x, float y, float width, float height, sf::Music* music, sf::RenderWindow& windowRef)
    : window(windowRef), volume(100.0f), isDragging(false), music(music), musicEnabled(true), effectsEnabled(true)
{
    if (music) {
        music->setVolume(volume);
    }

    bar.setSize(sf::Vector2f(width, height));
    bar.setPosition(x, y);
    bar.setFillColor(sf::Color(50, 50, 50));
    bar.setOutlineColor(sf::Color(200, 200, 200));
    bar.setOutlineThickness(2.0f);

    filledBar.setSize(sf::Vector2f(width, height));
    filledBar.setPosition(x, y);
    filledBar.setFillColor(sf::Color(0, 255, 0));
    filledBar.setOutlineColor(sf::Color(200, 200, 200));
    filledBar.setOutlineThickness(2.0f);

    thumb.setRadius(height / 2 + 5.f);
    thumb.setFillColor(sf::Color::Red);
    thumb.setOutlineColor(sf::Color::Black);
    thumb.setOutlineThickness(2.0f);
    thumb.setPosition(x + width - thumb.getRadius() * 2, y - thumb.getRadius());

    if (!font.loadFromFile("resource/fonts/Pixel Times Bold.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }
    volumeText.setFont(font);
    volumeText.setCharacterSize(20);
    volumeText.setPosition(x + width + 15.f, y - 5.f);
    volumeText.setFillColor(sf::Color::White);
    updateVolumeText();
}

SettingsManager::SettingsManager(float x, float y, float width, float height, std::vector<sf::Sound*>& effects, sf::RenderWindow& windowRef): window(windowRef), volume(100.0f), isDragging(false), effects(effects), music(nullptr), musicEnabled(true), effectsEnabled(true)
{
    for (auto* effect : effects) {
        if (effect) {
            effect->setVolume(volume);
        }
    }

    bar.setSize(sf::Vector2f(width, height));
    bar.setPosition(x, y);
    bar.setFillColor(sf::Color(50, 50, 50));
    bar.setOutlineColor(sf::Color(200, 200, 200));
    bar.setOutlineThickness(2.0f);

    filledBar.setSize(sf::Vector2f(width, height));
    filledBar.setPosition(x, y);
    filledBar.setFillColor(sf::Color(0, 255, 0));
    filledBar.setOutlineColor(sf::Color(200, 200, 200));
    filledBar.setOutlineThickness(2.0f);

    thumb.setRadius(height / 2 + 5.f);
    thumb.setFillColor(sf::Color::Red);
    thumb.setOutlineColor(sf::Color::Black);
    thumb.setOutlineThickness(2.0f);
    thumb.setPosition(x + width - thumb.getRadius() * 2, y - thumb.getRadius());

    if (!font.loadFromFile("resource/fonts/Pixel Times Bold.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }
    volumeText.setFont(font);
    volumeText.setCharacterSize(20);
    volumeText.setPosition(x + width + 15.f, y - 5.f);
    volumeText.setFillColor(sf::Color::White);
    updateVolumeText();
}

SettingsManager::~SettingsManager()
{
}

void SettingsManager::handleEvent(sf::Event& event, const sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    switch (event.type) {
    case sf::Event::MouseButtonPressed:
        if (thumb.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            isDragging = true;
        }
        break;

    case sf::Event::MouseButtonReleased:
        isDragging = false;
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

void SettingsManager::moveThumb(float mouseX) {
    float barLeft = bar.getPosition().x;
    float barRight = barLeft + bar.getSize().x;

    mouseX = clamp(mouseX, barLeft, barRight);

    thumb.setPosition(mouseX - thumb.getRadius(), thumb.getPosition().y);

    float percentage = (mouseX - barLeft) / bar.getSize().x;
    volume = percentage * 100.0f;

    filledBar.setSize(sf::Vector2f(percentage * bar.getSize().x, bar.getSize().y));

    if (music) {
        music->setVolume(volume);
    }

    for (auto* effect : effects) {
        if (effect) {
            effect->setVolume(volume);
        }
    }

    updateVolumeText();
}

void SettingsManager::draw(sf::RenderWindow& window) const {
    window.draw(bar);
    window.draw(filledBar);
    window.draw(thumb);
    window.draw(volumeText);
}

float SettingsManager::getVolume() const {
    return volume;
}

void SettingsManager::toggleMusic(bool enable) {
    musicEnabled = enable;
    if (music) {
        music->setVolume(enable ? volume : 0.0f);
    }
}

void SettingsManager::toggleEffects(bool enable) {
    effectsEnabled = enable;
    for (auto* effect : effects) {
        if (effect) {
            effect->setVolume(enable ? volume : 0.0f);
        }
    }
}

void SettingsManager::updateVolumeText() {
    volumeText.setString("Volume: " + std::to_string(static_cast<int>(volume)));
}

float SettingsManager::clamp(float value, float min, float max) const {
    return std::max(min, std::min(value, max));
}
