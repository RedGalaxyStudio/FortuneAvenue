#include <SFML/Graphics.hpp>
#include "Cinematic.hpp"
#include <SFML/Audio.hpp>

// Constructor e inicialización
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
        if (!texture.loadFromFile("resource/texture/part" + std::to_string(i) + ".jpg")) {
            // std::cerr << "Error al cargar la textura del spritesheet, parte " << i << std::endl;
        }
        textures[i] = texture;
    }
    SpriteFondoLogo.setTexture(textures[currentTextureIndex]);
    frameRect = sf::IntRect(0, 0, 1280, 720);

    if (!FondoBuffer.loadFromFile("resource/sounds/IntroA.wav")) {
        // std::cerr << "Error al cargar el sonido A" << std::endl;
        return;
    }

    FondoSound.setBuffer(FondoBuffer);

    // Indicar que las texturas ya están cargadas
    texturesLoaded = true;
}

// Carga de recursos (texturas y sprites)
void Cinematic::Resource() {


    if (!textureLogoStudio.loadFromFile("resource/texture/imagelogopresa.png")) {
        // std::cerr << "Error al cargar la imagen del logotipo presa" << std::endl;
        return;
    }

    if (!textureLogoJuego.loadFromFile("resource/texture/logojuego14.png")) {
        // std::cerr << "Error al cargar la imagen del logotipo del juego" << std::endl;
        return;
    }

    spriteLogoStudio.setTexture(textureLogoStudio);
    spriteLogoStudio.setOrigin(500, 238.5f);
    spriteLogoStudio.setPosition(640, 360);

    spriteLogoJuego.setTexture(textureLogoJuego);
    spriteLogoJuego.setOrigin(256.5f, 209.4f);
    spriteLogoJuego.setPosition(640, 360);

    // Lanzar el hilo que cargará las texturas de la Animación #2
    textureLoaderThread = std::thread(&Cinematic::loadTexturesInBackground, this);
    soundOne = false;
}

// Actualización de la animación (desvanecimiento del logotipo y fondo animado)
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

        // Mostrar la Animación #1 (Logotipo)
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

        // Mostrar la Animación #2 (Fondo) solo si las texturas están completamente cargadas
        else if (clock.getElapsedTime().asSeconds() <= 12 && texturesLoaded) {
            if (soundOne != true) {

                FondoSound.play();
                soundOne = true;
            }
            updateFondo(deltaTimeFondo);
            window.draw(spriteLogoJuego);
        }else{
            // Detener el sonido al finalizar la cinemática, si es necesario
            FondoSound.stop();
            break;

        
        }

        window.display();
    }
}

// Actualiza el fondo para mostrar el frame correcto
void Cinematic::updateFondo(sf::Time deltaTime) {
    tiempoAcumuladoFondo += deltaTime.asSeconds();

    if (tiempoAcumuladoFondo >= frameTime) {
        tiempoAcumuladoFondo = 0.0f;
        currentFrame = (currentFrame + 1) % 12;  // Avanza al siguiente frame dentro de la textura actual

        if (currentFrame == 0) {  // Cambiar de textura después de 12 frames
            currentTextureIndex = (currentTextureIndex + 1) % 6;
            SpriteFondoLogo.setTexture(textures[currentTextureIndex]);
        }

        int frameX = (currentFrame % 3) * 1280;  // 3 columnas de frames
        int frameY = (currentFrame / 3) * 720;   // 4 filas de frames

        frameRect.left = frameX;
        frameRect.top = frameY;
        SpriteFondoLogo.setTextureRect(frameRect);
    }

    window.draw(SpriteFondoLogo);
}
