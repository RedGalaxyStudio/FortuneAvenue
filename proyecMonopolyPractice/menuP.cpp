#include "menuP.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "SettingsManager.hpp"

// Constructor: inicializa la variable y la ventana
menuP::menuP(sf::RenderWindow& windowRef) : window(windowRef),lastHoveredButton(nullptr){
    // Inicializaciones adicionales si es necesario
}

// Carga de recursos (texturas y sprites)
void menuP::Resource() {
    if (!textureLogoFortuneAvenue.loadFromFile("resource/texture/logojuego14.png")) return;
    if (!TextureBotonJugarOff.loadFromFile("resource/texture/BotonJugarOff.png")) return;
    if (!TextureBotonJugarOn.loadFromFile("resource/texture/BotonJugarOn.png")) return;
    if (!TextureBotonOpcionesOff.loadFromFile("resource/texture/BotonOpcionesOff.png")) return;
    if (!TextureBotonOpcionesOn.loadFromFile("resource/texture/BotonOpcionesOn.png")) return;
    if (!TextureBotonSalirOff.loadFromFile("resource/texture/BotonSalirOff.png")) return;
    if (!TextureBotonSalirOn.loadFromFile("resource/texture/BotonSalirOn.png")) return;
    if (!TextureFondoMenu.loadFromFile("resource/texture/fondomenu.png")) return;
    if (!textureAcercaDeOn.loadFromFile("resource/texture/AcercaDeOn.png")) return;
    if (!textureAcercaDeOff.loadFromFile("resource/texture/AcercaDeOff.png")) return;
    if (!textureXOn.loadFromFile("resource/texture/XOn.png")) return;
    if (!textureXOff.loadFromFile("resource/texture/XOff.png")) return;
    if (!HoverBuffer.loadFromFile("resource/sounds/deciB.wav")) return;
    if (!ClickBuffer.loadFromFile("resource/sounds/deciA.wav")) return;
    if (!MenuMusicFondo.openFromFile("resource/sounds/MenuB.wav")) return;
    if (!Blur.loadFromFile("resource/Shaders/wavePerso.frag", sf::Shader::Fragment)) return;
    if (!renderTexture.create(window.getSize().x, window.getSize().y)) return;
   
    //Blur.setUniform("resolution", sf::Glsl::Vec2(
    //    static_cast<float>(window.getSize().x),
    //    static_cast<float>(window.getSize().y)
    //));

    

    HoverSound.setBuffer(HoverBuffer);
    ClickSound.setBuffer(ClickBuffer);
    std::vector<sf::Sound*> effectPointers = { &HoverSound, &ClickSound};
    // Configuración del sprite del logotipo
    spriteLogoFortuneAvenue.setTexture(textureLogoFortuneAvenue);
    spriteLogoFortuneAvenue.setOrigin(256.5f, 209.4f);
    spriteLogoFortuneAvenue.setPosition(640, 260);

    SpriteBotonJugar.setTexture(TextureBotonJugarOff);
    SpriteBotonJugar.setOrigin(103.5f, 40);
    SpriteBotonJugar.setPosition(383, 560);

    SpriteBotonOpciones.setTexture(TextureBotonOpcionesOff);
    SpriteBotonOpciones.setOrigin(103.5f, 40);
    SpriteBotonOpciones.setPosition(640, 560);

    SpriteBotonSalir.setTexture(TextureBotonSalirOff);
    SpriteBotonSalir.setOrigin(103.5f, 40);
    SpriteBotonSalir.setPosition(895, 560);

    spriteX.setTexture(textureXOff);
    spriteX.setOrigin(20, 20);
    spriteX.setPosition(1200.5f, 50);

    spriteAcercaDe.setTexture(textureAcercaDeOff);
    spriteAcercaDe.setOrigin(64.5f, 25);
    spriteAcercaDe.setPosition(1200.5f, 680);
    SpriteFondoMenu.setTexture(TextureFondoMenu);

    musicSlider = new SettingsManager(200, 300, 200, 10,&MenuMusicFondo,window);  // Slider para la música
    effectSlider = new SettingsManager(200, 400, 200, 10,effectPointers,window);  // Slider para los efectos


}

// Actualización de la animación (desvanecimiento del logotipo)
void menuP::MenuPrincipal() {
    MenuMusicFondo.setLoop(true);
    MenuMusicFondo.play();

    SpriteBotonOpciones.setPosition(640, 560);

    window.setMouseCursorVisible(true);
    while (window.isOpen()) {
       // Blur.setUniform("time", clock.getElapsedTime().asSeconds());

        eventoMenuP();

        // Actualizar estado de los botones según la posición del mouse
        mousePosition = sf::Mouse::getPosition(window);
        mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

        sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos = window.mapPixelToCoords(mousePixelPos);



        sf::Vector2f mouseNormPos = sf::Vector2f(mousePos.x / window.getSize().x, mousePos.y / window.getSize().y);

        // Pasamos la posición del mouse y el tiempo al shader
        Blur.setUniform("mousePos", mouseNormPos);
        Blur.setUniform("time", clock.getElapsedTime().asSeconds());
        Blur.setUniform("resolution", sf::Glsl::Vec2(
            static_cast<float>(window.getSize().x),
            static_cast<float>(window.getSize().y)
        ));


        // Verificar si el ratón está sobre el botón Jugar
        if (SpriteBotonJugar.getGlobalBounds().contains(mousePosFloat)) {
            SpriteBotonJugar.setTexture(TextureBotonJugarOn);
            handleHover(&SpriteBotonJugar);
        }
        else {
            SpriteBotonJugar.setTexture(TextureBotonJugarOff);
            resetLastHoveredButton(&SpriteBotonJugar);
        }

        // Verificar si el ratón está sobre el botón Opciones
        if (SpriteBotonOpciones.getGlobalBounds().contains(mousePosFloat)) {
            SpriteBotonOpciones.setTexture(TextureBotonOpcionesOn);
            handleHover(&SpriteBotonOpciones);
        }
        else {
            SpriteBotonOpciones.setTexture(TextureBotonOpcionesOff);
            resetLastHoveredButton(&SpriteBotonOpciones);
        }

        // Verificar si el ratón está sobre el botón Salir
        if (SpriteBotonSalir.getGlobalBounds().contains(mousePosFloat)) {
            SpriteBotonSalir.setTexture(TextureBotonSalirOn);
            handleHover(&SpriteBotonSalir);
        }
        else {
            SpriteBotonSalir.setTexture(TextureBotonSalirOff);
            resetLastHoveredButton(&SpriteBotonSalir);
        }

        if (spriteAcercaDe.getGlobalBounds().contains(mousePosFloat)) {
            spriteAcercaDe.setTexture(textureAcercaDeOn);
            handleHover(&spriteAcercaDe);
        }
        else {
            spriteAcercaDe.setTexture(textureAcercaDeOff);
            resetLastHoveredButton(&spriteAcercaDe);
        }

 /*       
        // Dibujar elementos en la ventana
        window.clear();
        window.draw(SpriteFondoMenu);
        window.draw(spriteLogoFortuneAvenue);
        window.draw(SpriteBotonJugar);
        window.draw(SpriteBotonOpciones);
        window.draw(SpriteBotonSalir);
        window.draw(spriteAcercaDe);
        
        window.display();
*/
        // Dibujar todo el contenido en el render texture
        renderTexture.clear(sf::Color::Transparent);  // O cualquier otro color
        renderTexture.draw(SpriteFondoMenu);
        renderTexture.draw(spriteLogoFortuneAvenue);
        renderTexture.draw(SpriteBotonJugar);
        renderTexture.draw(SpriteBotonOpciones);
        renderTexture.draw(SpriteBotonSalir);
        renderTexture.draw(spriteAcercaDe);
        renderTexture.draw(spriteX);  // Asegúrate de dibujar todos los elementos
        renderTexture.display();

        // Aplicar el shader a la textura renderizada
        sf::Sprite renderedSprite(renderTexture.getTexture());
        window.clear();
        window.draw(renderedSprite, &Blur);
        window.display();

    }
}

void menuP::eventoMenuP() {

    sf::Event event;
    
    while (window.pollEvent(event)) {
        // Cerrar la ventana con Escape o al cerrar
        if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            window.close();
        }

        // Manejar clic del mouse
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

            // Verificar si el clic fue en el botón Jugar
            if (SpriteBotonJugar.getGlobalBounds().contains(mousePosFloat)) {
                playClickSound();
               // std::cout << "Jugar presionado" << std::endl;
                // Aquí puedes cambiar la escena o empezar el juego
            }

            // Verificar si el clic fue en el botón Opciones
            if (SpriteBotonOpciones.getGlobalBounds().contains(mousePosFloat)) {
                playClickSound();
                MenuOpcion();
                //std::cout << "Opciones presionado" << std::endl;
                // Aquí puedes abrir el menú de opciones
            }

            // Verificar si el clic fue en el botón Salir
            if (SpriteBotonSalir.getGlobalBounds().contains(mousePosFloat)) {
                playClickSound();
                //std::cout << "Salir presionado" << std::endl;
                window.close(); // Salir del juego
            }
        }
    }
}

void menuP::eventoMenuO() {

    sf::Event event;

    while (window.pollEvent(event)) {
        // Cerrar la ventana con Escape o al cerrar
        if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            window.close();
        }

        // Manejar eventos del slider de música y efectos
        musicSlider->handleEvent(event, window);
        effectSlider->handleEvent(event, window);

        // Manejar clic del mouse
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

            if (spriteX.getGlobalBounds().contains(mousePosFloat)) {
                playClickSound();
                MenuPrincipal();

            }
        }
    }
}

void menuP::handleHover(sf::Sprite* currentButton) {
    if (lastHoveredButton != currentButton) {
        playHoverSound();
        lastHoveredButton = currentButton;
    }
}

void menuP::resetLastHoveredButton(sf::Sprite* currentButton) {
    if (lastHoveredButton == currentButton) {
        lastHoveredButton = nullptr;
    }
}

void menuP::playHoverSound() {
    if (HoverSound.getStatus() != sf::Sound::Playing) {
        HoverSound.play();
    }
}

void menuP::playClickSound() {
    ClickSound.play();
}

void menuP::MenuJugar(){}

void menuP::MenuOpcion() {
    
    
    
    SpriteBotonOpciones.setTexture(TextureBotonOpcionesOn);
    SpriteBotonOpciones.setPosition(640, 100);

    window.setMouseCursorVisible(true);
    while (window.isOpen()) {

        mousePosition = sf::Mouse::getPosition(window);
        mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

        eventoMenuO();

        if (spriteX.getGlobalBounds().contains(mousePosFloat)) {
            spriteX.setTexture(textureXOn);
            handleHover(&spriteX);
        }
        else {
            spriteX.setTexture(textureXOff);
            resetLastHoveredButton(&spriteX);
        }


    
  
        // Dibujar elementos en la ventana
        window.clear();
        window.draw(SpriteFondoMenu);
        window.draw(spriteX);
        window.draw(SpriteBotonOpciones);
        musicSlider->draw(window);
        effectSlider->draw(window);
        window.display();
    }

}

void menuP::MenuSalir() {}

void menuP::MenuAcercaDe() {}