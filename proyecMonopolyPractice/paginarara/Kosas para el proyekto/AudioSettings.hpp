#ifndef AUDIOSETTINGS_HPP
#define AUDIOSETTINGS_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class AudioSettings {
public:
    AudioSettings(float x, float y, float width, float height, sf::Music* music);
    AudioSettings(float x, float y, float width, float height, std::vector<sf::Sound*>& effects);

    void handleEvent(sf::Event& event, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window) const;
    float getVolume() const;

    void toggleMusic(bool enable);
    void toggleEffects(bool enable);

private:
    float volume, effectsVolume;
    bool isDragging;
    bool musicEnabled, enable, effectsEnabled;
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




#endif

