#include <SFML/Graphics.hpp>
#include "loading.hpp"


LoadingScreen::LoadingScreen(sf::RenderWindow& windowRef)
    : window(windowRef), beta(0.0f), fade(true), frame(0),
    frametime(1.0f / 12.0f), timeAcumulado(0.0f), currentDiceIndex(0), loadedTextures(false) {
}

LoadingScreen::~LoadingScreen() {
    if (loadedTexturesThread.joinable()) {
        loadedTexturesThread.join();
    }
}

void LoadingScreen::loadBackground() {
    for (int i = 0; i < 8; ++i) {
        sf::Texture texture;
        if (!texture.loadFromFile("assets/image/Dice/cara" + std::to_string(i) + ".png")) {
        }
        dice[i] = texture;
    }
    spriteBackground.setTexture(dice[currentDiceIndex]);

    loadedTextures = true;
}

void LoadingScreen::LoadResources() {

    if (!textureFondo.loadFromFile("assets/image/Fondos/fondomenu.png")) return;
    SpriteFondo.setTexture(textureFondo);

    if (!font.loadFromFile("assets/fonts/ARCADEPI.ttf")) {
        return;
    }

    TextCargando.setString("Cargando...");
    TextCargando.setFont(font);
    TextCargando.setCharacterSize(35);
    TextCargando.setFillColor(sf::Color::White);
    TextCargando.setPosition(795, 270);

    loadedTexturesThread = std::thread(&LoadingScreen::loadBackground, this);
}


void LoadingScreen::Update() {
    sf::Clock frameClock;

    while (window.isOpen()) {
        sf::Time deltaTiempo = fadeclock.restart();
        sf::Time deltaTiempoFrame = frameClock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        }

        window.clear();

        if (loadedTextures) {
            updateDice(deltaTiempoFrame);
            window.draw(SpriteFondo);
            window.draw(TextCargando);
            window.draw(spriteBackground);
        }
        else {
            break;
        }

        window.display();
    }
}

void LoadingScreen::updateDice(sf::Time deltaTime) {
    timeAcumulado += deltaTime.asSeconds();

    if (timeAcumulado >= frametime) {
        timeAcumulado = 0.0f;
        frame = (frame + 1) % 12;

        if (frame == 0) {
            currentDiceIndex = (currentDiceIndex + 1) % 6;
            spriteBackground.setTexture(dice[currentDiceIndex]);
        }
    }

    window.draw(spriteBackground);
}