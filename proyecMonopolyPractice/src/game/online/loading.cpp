#include <SFML/Graphics.hpp>
#include "loading.hpp"
#include "ResourceGame.hpp"

LoadingScreen::LoadingScreen(sf::RenderWindow& windowRef)
    : window(windowRef),  beta(0.0f), fade(true), frame(0),
    frametime(1.0f / 12.0f), timeAcumulado(0.0f), currentDiceIndex(0), loadedTextures(false) {
}

LoadingScreen::~LoadingScreen() {
    if (loadedTexturesThread.joinable()) {
        loadedTexturesThread.join();
    }
}

void LoadingScreen::loadBackground() {

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

    loadedTexturesThread = std::thread(&LoadingScreen::Update, this);
}


void LoadingScreen::Update() {

    for (int i = 0; i < 8; ++i) {
        sf::Texture texture;
        if (!texture.loadFromFile("assets/image/Dice/cara" + std::to_string(i+1) + ".png")) {
        }
        dice[i] = texture;
    }
    spriteBackground.setTexture(dice[currentDiceIndex]);

    loadedTextures = true;

    sf::Clock frameClock;
    window.setActive(true);

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

        if (loadedTextures&& !Resourceready) {
            updateDice(deltaTiempoFrame);
            window.draw(SpriteFondo);
            window.draw(TextCargando);
            window.draw(spriteBackground);
        }
        else {
     
            std::lock_guard<std::mutex> lock(mtx);
            timeReady = true;
            window.setActive(false);
            cv.notify_one();
            break;
        }

        window.display();
    }
}

void LoadingScreen::updateDice(sf::Time deltaTime) {
    timeAcumulado += deltaTime.asSeconds();

    if (timeAcumulado >= frametime) {
        timeAcumulado = 0.0f;
        frame = (frame + 1) % 8;

       // if (frame == 0) {
      //      currentDiceIndex = (currentDiceIndex + 1) % 6;
      // 
      Resourceready = true;
            spriteBackground.setTexture(dice[frame]);
            for (size_t i = 0; i < playersGame.size(); i++) {

                // Verificar la carga de la textura del avatar
                if (playersGame[i].textureAvatarPLayer.getSize().x == 0) {
                    std::cout << "\nHONLA no se cargo:" << i;
                    Resourceready = false;
                }
                
            }
     
    }
}