#include "menuP.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "SettingsManager.hpp"
#include "Game.hpp"
#include "ResourceGlobal.hpp"
#include "ButtonG.hpp"
// Constructor: inicializa la variable y la ventana
menuP::menuP() : window(nullptr) {}
void menuP::setWindow(sf::RenderWindow& win) {
    window = &win;
}

// Carga de recursos (texturas y sprites)
void menuP::Resource() {
    if (!TextureBotonSiOn.loadFromFile("resource/texture/Button/BotonSiOn.png")) return;
    if (!TextureBotonSiOff.loadFromFile("resource/texture/Button/BotonSiOff.png")) return;
    if (!TextureBotonNoOn.loadFromFile("resource/texture/Button/BotonNoOn.png")) return;
    if (!TextureBotonNoOff.loadFromFile("resource/texture/Button/BotonNoOff.png")) return;
    if (!textureLogoFortuneAvenue.loadFromFile("resource/texture/Logos/logojuego14.png")) return;
    if (!TextureBotonJugarOff.loadFromFile("resource/texture/Button/BotonJugarOff.png")) return;
    if (!TextureBotonJugarOn.loadFromFile("resource/texture/Button/BotonJugarOn.png")) return;
    if (!TextureBotonOpcionesOff.loadFromFile("resource/texture/Button/BotonOpcionesOff.png")) return;
    if (!TextureBotonOpcionesOn.loadFromFile("resource/texture/Button/BotonOpcionesOn.png")) return;
    if (!TextureBotonSalirOff.loadFromFile("resource/texture/Button/BotonSalirOff.png")) return;
    if (!TextureBotonSalirOn.loadFromFile("resource/texture/Button/BotonSalirOn.png")) return;
    if (!textureAcercaDeOn.loadFromFile("resource/texture/Button/AcercaDeOn.png")) return;
    if (!textureAcercaDeOff.loadFromFile("resource/texture/Button/AcercaDeOff.png")) return;
    if (!MenuMusicFondo.openFromFile("resource/sounds/MenuB.wav")) return;
    if (!Blur.loadFromFile("resource/Shaders/blur.frag", sf::Shader::Fragment)) return;
    if (!renderTexture.create(window->getSize().x, window->getSize().y)) return;
   
    Blur.setUniform("resolution", sf::Glsl::Vec2(
        static_cast<float>(window->getSize().x),
        static_cast<float>(window->getSize().y)
    ));

    loadSounds();
    std::vector<sf::Sound*> effectPointers = { &HoverSound, &ClickSound };

    // Configuraci�n del sprite del logotipo
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

    musicSlider = new SettingsManager(200, 300, 200, 10,&MenuMusicFondo,*window);  // Slider para la m�sica
    effectSlider = new SettingsManager(200, 400, 200, 10,effectPointers,*window);  // Slider para los efectos
    loadCursors();
    // Establecer el cursor inicial
    window->setMouseCursor(normalCursor);

}

// Actualizaci�n de la animaci�n (desvanecimiento del logotipo)
void menuP::MenuPrincipal() {
    MenuMusicFondo.setLoop(true);
    MenuMusicFondo.play();

    // Crear los botones
    ButtonG botonJugar(SpriteBotonJugar, TextureBotonJugarOff, TextureBotonJugarOn);
    ButtonG botonOpciones(SpriteBotonOpciones, TextureBotonOpcionesOff, TextureBotonOpcionesOn);
    ButtonG botonSalir(SpriteBotonSalir, TextureBotonSalirOff, TextureBotonSalirOn);
    ButtonG botonAcercaDe(spriteAcercaDe, textureAcercaDeOff, textureAcercaDeOn);

    // Configurar la posición de los botones
    SpriteBotonOpciones.setPosition(640, 560);

    window->setMouseCursorVisible(true);

    while (window->isOpen()) {
        // Manejar eventos del menú
        eventoMenuP();

        // Obtener la posición actual del ratón
        sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
        sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);
  
        // Establecer cursor por defecto antes de verificar los botones
        currentCursor = &normalCursor;
        

        // Actualizar el estado de los botones y el cursor
        botonJugar.update(mousePosFloat, currentCursor, linkCursor, normalCursor);
        botonOpciones.update(mousePosFloat, currentCursor, linkCursor, normalCursor);
        botonSalir.update(mousePosFloat, currentCursor, linkCursor, normalCursor);
        botonAcercaDe.update(mousePosFloat, currentCursor, linkCursor, normalCursor);
        window->setMouseCursor(*currentCursor);
  

        // Dibujar los elementos en la ventana
        window->clear();
        window->draw(SpriteFondoMenu);
        window->draw(spriteLogoFortuneAvenue);
        window->draw(SpriteBotonJugar);
        window->draw(SpriteBotonOpciones);
        window->draw(SpriteBotonSalir);
        window->draw(spriteAcercaDe);
        window->display();
    }
}


void menuP::eventoMenuP() {

    sf::Event event;

    while (window->pollEvent(event)) {
        // Cerrar la ventana con Escape o al cerrar   
        // 
        //  renderTexture.clear(sf::Color::Transparent);  // O cualquier otro color
            renderTexture.draw(SpriteFondoMenu);
            renderTexture.draw(spriteLogoFortuneAvenue);
            renderTexture.draw(SpriteBotonJugar);
            renderTexture.draw(SpriteBotonOpciones);
            renderTexture.draw(SpriteBotonSalir);
            renderTexture.draw(spriteAcercaDe);
            renderTexture.display();
        if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {

            MenuSalir();
        }

        // Manejar clic del mouse
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);

            sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);
          
            // Verificar si el clic fue en el bot�n Jugar
            if (SpriteBotonJugar.getGlobalBounds().contains(mousePosFloat)) {
                playClickSound();

                MenuJugar();
                // std::cout << "Jugar presionado" << std::endl;
                 // Aqu� puedes cambiar la escena o empezar el juego
            }

            // Verificar si el clic fue en el bot�n Opciones
            if (SpriteBotonOpciones.getGlobalBounds().contains(mousePosFloat)) {
                playClickSound();
                MenuOpcion();
                //std::cout << "Opciones presionado" << std::endl;
                // Aqu� puedes abrir el men� de opciones
            }

            // Verificar si el clic fue en el bot�n Salir
            if (SpriteBotonSalir.getGlobalBounds().contains(mousePosFloat)) {
                playClickSound();
                //std::cout << "Salir presionado" << std::endl;
                MenuSalir(); // Salir del juego
            }
            if (spriteAcercaDe.getGlobalBounds().contains(mousePosFloat)) {
                playClickSound();
                //std::cout<<"Acerca De presionado" << std::endl;
                //Aqui puedes leer Acerca De este juego
                MenuAcercaDe();

            }
        }
    }
}

void menuP::eventoMenuO() {

    sf::Event event;

    while (window->pollEvent(event)) {
        // Cerrar la ventana con Escape o al cerrar
        if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            renderTexture.clear();  // O cualquier otro color
            renderTexture.draw(SpriteFondoMenu);
            renderTexture.draw(SpriteBotonOpciones);
            renderTexture.draw(spriteX);
            musicSlider->Printf();
            effectSlider->Printf();
            renderTexture.display();
            MenuSalir();
        }

        // Manejar eventos del slider de m�sica y efectos
        musicSlider->handleEvent(event, *window);
        effectSlider->handleEvent(event, *window);

        // Manejar clic del mouse
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
            sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

            if (spriteX.getGlobalBounds().contains(mousePosFloat)) {
                playClickSound();
                MenuPrincipal();

            }
        }
    }
}


void menuP::MenuJugar() {

    Game Game(*window);

    // Cargar los recursos necesarios para la cinem�tica
    Game.Resource();

    //Iniciar la animaci�n
    Game.Update();

}
void menuP::MenuOpcion() {

    SpriteBotonOpciones.setTexture(TextureBotonOpcionesOn);
    SpriteBotonOpciones.setPosition(640, 100);

    window->setMouseCursorVisible(true);
    while (window->isOpen()) {
        currentCursor = &normalCursor;
        mousePosition = sf::Mouse::getPosition(*window);
        mousePosFloat = static_cast<sf::Vector2f>(mousePosition);
        botonX->update(mousePosFloat, currentCursor, linkCursor, normalCursor);


        eventoMenuO();
        

        // Dibujar elementos en la ventana
        window->clear();
        window->draw(SpriteFondoMenu);
        window->draw(spriteX);
        window->draw(SpriteBotonOpciones);
        musicSlider->draw(*window);
        effectSlider->draw(*window);
        window->setMouseCursor(*currentCursor);
        window->display();
    }

}

void menuP::MenuSalir() {


    
    //crear ventana semitransparente
    sf::RectangleShape overlay(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));

   //Ubicacion del mensaje de confirmaci�n
    SpriteConfirmarSalir.setTexture(TextureConfirmarSalir);
    SpriteConfirmarSalir.setPosition(580, 150); 

   //Ubicaciones de los botones si y no
    SpriteBotonSi.setTexture(TextureBotonSiOff);
    SpriteBotonSi.setPosition(335, 200);  

    SpriteBotonNo.setTexture(TextureBotonNoOff);
    SpriteBotonNo.setPosition(735, 200);  

    window->setMouseCursorVisible(true);
    ButtonG BotonSi(SpriteBotonSi, TextureBotonSiOff, TextureBotonSiOn);
    ButtonG BotonNo(SpriteBotonNo, TextureBotonNoOff, TextureBotonNoOn);

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
                sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

                // Verificar el click en "si" y cerrar la vetana
                if (SpriteBotonSi.getGlobalBounds().contains(mousePosFloat)) {
                    playClickSound();
                    window->close();  
                }

                // Verificar el click en "no" y volver al menu principal
                if (SpriteBotonNo.getGlobalBounds().contains(mousePosFloat)) {
                    playClickSound();
                    return;  
                }
            }

 
        }
        
            currentCursor = &normalCursor;
            sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
            sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);
            BotonSi.update(mousePosFloat, currentCursor, linkCursor, normalCursor);
            BotonNo.update(mousePosFloat, currentCursor, linkCursor, normalCursor);
            // Manejo de hover en el bot�n "S�
            window->setMouseCursor(*currentCursor);


        
       // Dibujar todo el contenido en el render texture


       // Aplicar el shader a la textura renderizada
            renderedSprite.setTexture(renderTexture.getTexture());
       window->clear();
       window->draw(renderedSprite, &Blur); 
       // Dibujar los elementos de confirmaci�n de salida sobre el overlay
        window->draw(SpriteConfirmarSalir);  // Texto de confirmaci�n
        window->draw(SpriteBotonSi);         // Bot�n "S�"
        window->draw(SpriteBotonNo);         // Bot�n "No"

       window->display();

        //window->draw(overlay);  // Oscurece el fondo
    }
}

void menuP::MenuAcercaDe() {
    // Crear un rectángulo más pequeño que la ventana y centrarlo
    sf::RectangleShape overlay(sf::Vector2f(
        static_cast<float>(window->getSize().x - 50),  // 50 píxeles más pequeño en ancho
        static_cast<float>(window->getSize().y - 50)   // 50 píxeles más pequeño en alto
    ));

    // Posicionar el rectángulo en el centro, con un margen de 25 píxeles
    overlay.setPosition(25.0f, 25.0f);

    // Oscurecer el fondo y hacer el rectángulo semitransparente
    overlay.setFillColor(sf::Color(0, 0, 0, 100));  // Aumentamos la opacidad para que sea más oscuro

    // Confgurar el texto "Acerca De"
    sf::Font Fuente;
    if (!Fuente.loadFromFile("resource/fonts/ARCADEPI.ttf")) {
        return;
    }

    sf::Text TextAcercaDe;
    TextAcercaDe.setFont(Fuente);
    TextAcercaDe.setString("Acerca De este juego");
    TextAcercaDe.setCharacterSize(40);  // Tamaño más grande para ser fácilmente legible
    TextAcercaDe.setFillColor(sf::Color::White);  // Color blanco para contrastar con el fondo oscuro
    TextAcercaDe.setPosition(360, 100);  // Posicionamos el texto dentro del rectángulo
    

    
    window->setMouseCursorVisible(true);

    while (window->isOpen()) {
        currentCursor = &normalCursor;
        mousePosition = sf::Mouse::getPosition(*window);
        mousePosFloat = static_cast<sf::Vector2f>(mousePosition);
        botonX->update(mousePosFloat, currentCursor, linkCursor, normalCursor);
        eventoMenuO();
        renderedSprite.setTexture(renderTexture.getTexture());
        // Dibujar los elementos en la ventana
        window->clear();

        // Dibujar el fondo del menú y otros elementos
        window->draw(renderedSprite, &Blur);
        window->draw(spriteX);
        // Dibujar el rectángulo oscuro centrado
        window->draw(overlay);

        // Dibujar el texto "Acerca De"
        window->draw(TextAcercaDe);

        window->display();
    }
}
