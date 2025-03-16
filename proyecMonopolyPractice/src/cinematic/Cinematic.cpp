#include <SFML/Graphics.hpp>
#include "Cinematic.hpp"
#include <SFML/Audio.hpp>


Cinematic::Cinematic(sf::RenderWindow& windowRef)
    : window(windowRef), alpha(0.0f), fadeIn(true), currentFrame(0),
    frameTime(1.0f / 12.0f), tiempoAcumuladoFondo(0.0f), currentTextureIndex(0), texturesLoaded(false) {
}
Cinematic::~Cinematic() {
    if (textureLoaderThread.joinable()) {
        textureLoaderThread.join();
    }
}

void Cinematic::loadTexturesInBackground() {
    for (int i = 0; i < 6; ++i) {
        sf::Texture texture;
        if (!texture.loadFromFile("assets/image/Fondos/part" + std::to_string(i) + ".tjpg")) {
        }
        textures[i] = texture;
    }
    SpriteFondoLogo.setTexture(textures[currentTextureIndex]);
    frameRect = sf::IntRect(0, 0, 1280, 720);

    if (!FondoBuffer.loadFromFile("assets/sounds/IntroA.wav")) {
        return;
    }

    FondoSound.setBuffer(FondoBuffer);

 
    texturesLoaded = true;
}


void Cinematic::Resource() {


    if (!textureLogoStudio.loadFromFile("assets/image/Logos/imagelogopresa.png")) return;

    if (!textureLogoJuego.loadFromFile("assets/image/Logos/logojuego14.png")) return;

    spriteLogoStudio.setTexture(textureLogoStudio);
    spriteLogoStudio.setOrigin(500, 238.5f);
    spriteLogoStudio.setPosition(640, 360);

    spriteLogoJuego.setTexture(textureLogoJuego);
    spriteLogoJuego.setOrigin(256.5f, 209.4f);
    spriteLogoJuego.setPosition(640, 360);

    textureLoaderThread = std::thread(&Cinematic::loadTexturesInBackground, this);
    soundOne = false;
}


void Cinematic::Update() {
    sf::Clock fondoClock;

    while (window.isOpen()) {
        sf::Time deltaTime = fadeClock.restart();
        sf::Time deltaTimeFondo = fondoClock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        }

        window.clear();

        
        if (clock.getElapsedTime().asSeconds() <= 6) {
            if (fadeIn) {
                alpha += 200.0f * deltaTime.asSeconds();
                if (alpha >= 255.0f) {
                    alpha = 255.0f;
                    fadeIn = false;
                }
            }
            else {
                alpha -= 200.0f * deltaTime.asSeconds();
                if (alpha <= 0.0f) {
                    alpha = 0.0f;
                    fadeIn = true;
                }
            }
            spriteLogoStudio.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
            window.draw(spriteLogoStudio);
        }


        else if (clock.getElapsedTime().asSeconds() <= 12 && texturesLoaded) {
            if (soundOne != true) {

                FondoSound.play();
                soundOne = true;
            }
            updateFondo(deltaTimeFondo);
            window.draw(spriteLogoJuego);
        }else{
            
            FondoSound.stop();
            break;

        
        }

        window.display();
    }
}

void Cinematic::updateFondo(sf::Time deltaTime) {
    tiempoAcumuladoFondo += deltaTime.asSeconds();

    if (tiempoAcumuladoFondo >= frameTime) {
        tiempoAcumuladoFondo = 0.0f;
        currentFrame = (currentFrame + 1) % 12;  

        if (currentFrame == 0) {  
            currentTextureIndex = (currentTextureIndex + 1) % 6;
            SpriteFondoLogo.setTexture(textures[currentTextureIndex]);
        }

        int frameX = (currentFrame % 3) * 1280;  
        int frameY = (currentFrame / 3) * 720;   
        frameRect.left = frameX;
        frameRect.top = frameY;
        SpriteFondoLogo.setTextureRect(frameRect);
    }

    window.draw(SpriteFondoLogo);
}
