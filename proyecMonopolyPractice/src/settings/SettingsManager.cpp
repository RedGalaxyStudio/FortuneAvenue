#include "SettingsManager.hpp"
#include <iostream>
#include "../core/ResourceGlobal.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include "../../libs/nlohmann/json.hpp"

using json = nlohmann::json;

SettingsManager::SettingsManager(sf::RenderWindow& windowRef) : window(windowRef), volume(100.0f), isDragging(false), musicEnabled(true), effectsEnabled(true)
{
}

SettingsManager::SettingsManager()
    : window(*(new sf::RenderWindow())), volume(100.0f), isDragging(false), musicEnabled(true), effectsEnabled(true)
{
    // Inicializa los miembros según sea necesario
    // Quizás quieras manejar la limpieza de la ventana de renderizado de marcador de posición si se usa
}

SettingsManager::SettingsManager(float x, float y, float width, float height, std::vector<sf::Music*>&  music, sf::RenderWindow& windowRef)
    : window(windowRef), volume(100.0f), isDragging(false), music(music), musicEnabled(true), effectsEnabled(true)
{
    if (std::filesystem::exists("settings.json")) {

        std::ifstream inFile("settings.json");
        if (inFile.is_open()) {

            json settingData;

            inFile >> settingData;
            inFile.close();

            volume = settingData["Volumen_Music"];

            thumbPosition.x = settingData["thumbPosition_Music"]["x"];
            thumbPosition.y = settingData["thumbPosition_Music"]["y"];
            thumb.setPosition(thumbPosition);
            sizeFilledBar.x = settingData["sizeFilledBar_Music"]["x"];
            sizeFilledBar.y = settingData["sizeFilledBar_Music"]["y"];
            filledBar.setSize(sizeFilledBar);


        }

    }
    else {

        filledBar.setSize(sf::Vector2f(width, height));
        thumb.setPosition(x + width - thumb.getRadius(), y + (height / 2) - thumb.getRadius());
    }




    for (auto* fondo : music) {
        if (fondo) {
            fondo->setVolume(volume);
        }
    }
    loadVolumenIcon();
    bar.setSize(sf::Vector2f(width, height));
    bar.setPosition(x, y);
    bar.setFillColor(sf::Color(50, 50, 50));
    bar.setOutlineColor(sf::Color::Black);
    bar.setOutlineThickness(2.0f);

    
    filledBar.setPosition(x, y);
    filledBar.setFillColor(sf::Color(249, 108, 223));
    filledBar.setOutlineColor(sf::Color::Black);
    filledBar.setOutlineThickness(2.0f);

    thumb.setRadius((height + 5) / 2 + 5.f);
    thumb.setFillColor(sf::Color(95, 179, 255));
    thumb.setOutlineColor(sf::Color::Black);
    thumb.setOutlineThickness(2.0f);

    if (!font.loadFromFile("resource/fonts/Pixel Times Bold.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }
    volumeText.setFont(font);
    volumeText.setCharacterSize(20);
    volumeText.setPosition(x + width + 15.f, y - 5.f);
    volumeText.setFillColor(sf::Color::White);
    IdenVolumen.setFont(font);
    IdenVolumen.setCharacterSize(20);
    IdenVolumen.setPosition(width - 100, y - 10);
    IdenVolumen.setFillColor(sf::Color::White);
    IdenVolumen.setString("Musica");
    ImgVolumen.setTexture(TextureHigh);
    ImgVolumen.setOrigin(25, 25);
    ImgVolumen.setPosition(width + 310, y + 7);
    updateVolumeText();
}

SettingsManager::SettingsManager(float x, float y, float width, float height, std::vector<sf::Sound*>& effects, sf::RenderWindow& windowRef): window(windowRef), volume(100.0f), isDragging(false), effects(effects), musicEnabled(true), effectsEnabled(true)
{



    if (std::filesystem::exists("settings.json")) {

        std::ifstream inFile("settings.json");
        if (inFile.is_open()) {

            json settingData;

            inFile >> settingData;
            inFile.close();

            volume = settingData["Volumen_Effects"];

            thumbPosition.x = settingData["thumbPosition_Effects"]["x"];
            thumbPosition.y = settingData["thumbPosition_Effects"]["y"];
            thumb.setPosition(thumbPosition);
            sizeFilledBar.x = settingData["sizeFilledBar_Effects"]["x"];
            sizeFilledBar.y = settingData["sizeFilledBar_Effects"]["y"];
            filledBar.setSize(sizeFilledBar);

        }

    }
    else {

        filledBar.setSize(sf::Vector2f(width, height));
        thumb.setPosition(x + width - thumb.getRadius(), y + (height / 2) - thumb.getRadius());
    }

    for (auto* effect : effects) {
        if (effect) {
            effect->setVolume(volume);
        }
    }
    loadVolumenIcon();
    bar.setSize(sf::Vector2f(width, height));
    bar.setPosition(x, y);
    bar.setFillColor(sf::Color(50, 50, 50));
    bar.setOutlineColor(sf::Color::Black);
    bar.setOutlineThickness(2.0f);


    filledBar.setPosition(x, y);
    filledBar.setFillColor(sf::Color(249, 108, 223));
    filledBar.setOutlineColor(sf::Color::Black);
    filledBar.setOutlineThickness(2.0f);

    thumb.setRadius((height+ 5) / 2 + 5.f);
    thumb.setFillColor(sf::Color(95, 179, 255));
    thumb.setOutlineColor(sf::Color::Black);
    thumb.setOutlineThickness(2.0f);
    
    if (!font.loadFromFile("resource/fonts/Pixel Times Bold.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }
    volumeText.setFont(font);
    volumeText.setCharacterSize(20);
    volumeText.setPosition(x + width + 15.f, y - 5.f);
    volumeText.setFillColor(sf::Color::White);
    IdenVolumen.setFont(font);
    IdenVolumen.setPosition(width- 100, y-10);
    IdenVolumen.setCharacterSize(20);
    IdenVolumen.setFillColor(sf::Color::White);
    IdenVolumen.setString("Efectos");
    ImgVolumen.setTexture(TextureHigh);
    ImgVolumen.setOrigin(25, 25);
    ImgVolumen.setPosition(width + 310, y + 7);
    updateVolumeText();
}

SettingsManager::~SettingsManager()
{
}

void SettingsManager::handleEvent(sf::Event& event, const sf::RenderWindow& window) {
    mousePos = sf::Mouse::getPosition(window);
   
   
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
 
    // Limitar la posición del mouse entre el principio y el final de la barra
    mouseX = clamp(mouseX, barLeft, barRight);

    // Ajustar la posición del thumb para que se mueva hasta el borde final
    thumbPosition = sf::Vector2f(mouseX - thumb.getRadius(), thumb.getPosition().y);
    thumb.setPosition(thumbPosition);

    // Calcular el porcentaje del volumen basado en la posición del mouse
    float percentage = (mouseX - barLeft) / bar.getSize().x;
    volume = percentage * 100.0f;

    // Ajustar el tamaño de la barra llena
    sizeFilledBar = sf::Vector2f(percentage * bar.getSize().x, bar.getSize().y);
    filledBar.setSize(sizeFilledBar);

    // Actualizar el volumen de la música si está presente
    if (!music.empty()) {
        for (auto* fondo : music) {
            if (fondo) {
                fondo->setVolume(volume);
            }
        }
    }
    else if (!effects.empty()) {
        // Actualizar el volumen de los efectos
        for (auto* effect : effects) {
            if (effect) {
                effect->setVolume(volume);
            }
        }
    }

    // Actualizar el texto del volumen
    updateVolumeText();
}

void SettingsManager::draw(sf::RenderWindow& window) const {
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    if (thumb.getGlobalBounds().contains(mousePosF)) {
        if (currentCursor == &normalCursor) { // Solo cambiar si es el cursor normal
            currentCursor = &linkCursor;
        }
    }
    window.draw(bar);
    window.draw(filledBar);
    window.draw(thumb);
    window.draw(volumeText);
    window.draw(IdenVolumen);
    window.draw(ImgVolumen);
}

void SettingsManager::Printf() const {
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    if (thumb.getGlobalBounds().contains(mousePosF)) {
        if (currentCursor == &normalCursor) { // Solo cambiar si es el cursor normal
            currentCursor = &linkCursor;
        }
    }
  
     renderTexture.draw(bar);
     renderTexture.draw(filledBar);
     renderTexture.draw(thumb);
     renderTexture.draw(volumeText);
     renderTexture.draw(IdenVolumen);
     renderTexture.draw(ImgVolumen);
}

float SettingsManager::getVolume() const {
    return volume;
}

void SettingsManager::toggleMusic(bool enable) {
    musicEnabled = enable;
    for (auto* fondo : music) {
    
        if (fondo) {
            fondo->setVolume(enable ? volume : 0.0f);
        }
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
    
    volumeText.setString(std::to_string(static_cast<int>(volume))+"%");
    if (volume == 100) {
        ImgVolumen.setTexture(TextureHigh);
    }if (volume == 50) {
        ImgVolumen.setTexture(TextureMedium);
    }
    else if (volume == 0) {
        ImgVolumen.setTexture(TextureMuted);
    }
}

float SettingsManager::clamp(float value, float min, float max) const {
    return std::max(min, std::min(value, max));
}

void SettingsManager::saveSettings() {

         json settingData;

         std::ifstream inFile("settings.json");
         if (inFile.is_open()) {
             inFile >> settingData;  // Cargar el JSON existente
             inFile.close();
         }



         if (!music.empty()) {
             settingData["Volumen_Music"] = volume;
             settingData["thumbPosition_Music"] = { {"x", thumbPosition.x}, {"y", thumbPosition.y} };
             settingData["sizeFilledBar_Music"] = { {"x", sizeFilledBar.x}, {"y", sizeFilledBar.y} };
         }
         else if (!effects.empty()) {
             settingData["Volumen_Effects"] = volume;
             settingData["thumbPosition_Effects"] = { {"x", thumbPosition.x}, {"y", thumbPosition.y} };
             settingData["sizeFilledBar_Effects"] = { {"x", sizeFilledBar.x}, {"y", sizeFilledBar.y} };

         }
        std::ofstream outFile("settings.json");

        if (outFile.is_open()) {
                 outFile << settingData.dump(4);
                 outFile.close();
        }

}