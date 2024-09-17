#ifndef VOLUMESLIDER_HPP
#define VOLUMESLIDER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>

class VolumeSlider {
public:
    VolumeSlider(float x, float y, float width, float height, sf::Music* music);
    VolumeSlider(float x, float y, float width, float height, std::vector<sf::Sound*>& effects);

    void handleEvent(sf::Event& event, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window) const;
    float getVolume() const;

private:
    float volume;
    bool isDragging;
    sf::RectangleShape bar, filledBar;
    sf::CircleShape thumb;
    sf::Font font;
    sf::Text volumeText;

    sf::Music* music = nullptr;
    std::vector<sf::Sound*> effects;

    void moveThumb(float mouseX);
    void updateVolumeText();
    float clamp(float value, float min, float max) const;
};

#endif // VOLUMESLIDER_HPP

