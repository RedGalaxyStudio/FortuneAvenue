// === Paso 1: Separación de responsabilidades inicial ===

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <vector>
#include <memory>

//-------------------------------------------
// ResourceLoader: Carga texturas, fuentes, sonidos
//-------------------------------------------
class ResourceLoader {
public:
    bool loadAll();

    const sf::Texture& getTexture(const std::string& id);
    const sf::Font& getFont(const std::string& id);
    const sf::SoundBuffer& getSoundBuffer(const std::string& id);
    const sf::Shader& getShader(const std::string& id);

private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;
    std::map<std::string, sf::SoundBuffer> sounds;
    std::map<std::string, sf::Shader> shaders;
};

//-------------------------------------------
// MenuRenderer: Dibuja menú y elementos
//-------------------------------------------
class MenuRenderer {
public:
    void drawMainMenu(sf::RenderWindow& window);
    void drawOptionsMenu(sf::RenderWindow& window);
    void drawInstructions(sf::RenderWindow& window);
    void drawAbout(sf::RenderWindow& window);

    void setResources(std::shared_ptr<ResourceLoader> resources);

private:
    std::shared_ptr<ResourceLoader> res;
};

//-------------------------------------------
// MenuEvents: Lógica de entrada y selección
//-------------------------------------------
class MenuEvents {
public:
    void handleEvent(const sf::Event& e);
    void updateState();

    int getSelectedOption() const;
};

//-------------------------------------------
// CursorManager: Cambia el cursor visual
//-------------------------------------------
class CursorManager {
public:
    void loadCursors();
    void updateCursorState(bool isHovering);
    void applyCursor(sf::RenderWindow& window);

private:
    sf::Cursor cursorNormal;
    sf::Cursor cursorHover;
    bool hovering = false;
};

//-------------------------------------------
// UIStateManager: Controla el estado actual del menú
//-------------------------------------------
enum class MenuState {
    Principal,
    Opciones,
    Instrucciones,
    AcercaDe,
    Salir
};

class UIStateManager {
public:
    void setState(MenuState s);
    MenuState getState() const;

    void nextOption();
    void previousOption();
    int getSelectedIndex() const;

private:
    MenuState currentState = MenuState::Principal;
    int selectedIndex = 0;
};
