#ifndef SETTINGSMANAGER_HPP
#define SETTINGSMANAGER_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class SettingsManager
{
public:
    explicit SettingsManager(sf::RenderWindow& windowRef);
    ~SettingsManager();
    SettingsManager();

    SettingsManager(float x, float y, float width, float height, std::vector<sf::Music*>& music, sf::RenderWindow& windowRef);
    SettingsManager(float x, float y, float width, float height, std::vector<sf::Sound*>& effects, sf::RenderWindow& windowRef);

    void handleEvent(sf::Event& event, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window) const;
    void Printf()const;
    void saveSettings();
private:
    sf::RenderWindow& window;
    sf::Vector2f sizeFilledBar;
    sf::Vector2f thumbPosition;
    float volume;
    bool isDragging;
    bool musicEnabled;
    bool effectsEnabled;
    sf::RectangleShape bar;
    sf::RectangleShape filledBar;
    sf::CircleShape thumb;
    sf::Font font;
    sf::Text volumeText;
    sf::Vector2i mousePos;
    std::vector <sf::Music*> music;
    std::vector<sf::Sound*> effects;
    sf::Text TextpantallaCompleta;

    sf::Text IdenVolumen;
    sf::Sprite ImgVolumen;

    void moveThumb(float mouseX);
    void updateVolumeText();
    float clamp(float value, float min, float max) const;
};

#endif // SETTINGSMANAGER_HPP
