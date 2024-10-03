#include "menuP.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "SettingsManager.hpp"
#include "IniciaUser.hpp"
#include "ResourceGlobal.hpp"
#include "ButtonG.hpp"

// Constructor: inicializa la variable y la ventana
menuP::menuP() : window(nullptr), hwnd(nullptr), webviewManager(nullptr), isWebViewOpen(false) , SesionValida(true){}
void menuP::setWindow(sf::RenderWindow& win) {
    window = &win;
}

// Carga de recursos (texturas y sprites)
void menuP::Resource() {
    if (!TextureConfirmarSalir.loadFromFile("resource/texture/Button/boton2.png")) return;
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

    // Ajustar el tamaño del rectángulo según el tamaño actual de la ventana
    overlay.setSize(sf::Vector2f(static_cast<float>(window->getSize().x),static_cast<float>(window->getSize().y)));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
   
    Sesion.setFont(fontUser);
    Sesion.setCharacterSize(24);
    Sesion.setFillColor(sf::Color::White);
    Sesion.setOutlineThickness(2);
    Sesion.setOutlineColor(sf::Color(135, 135, 135));
    Sesion.setPosition(70, 70);

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

    box.setPosition(50, 50);
    // Crear los botones
    ButtonG botonJugar(SpriteBotonJugar, TextureBotonJugarOff, TextureBotonJugarOn);
    ButtonG botonOpciones(SpriteBotonOpciones, TextureBotonOpcionesOff, TextureBotonOpcionesOn);
    ButtonG botonSalir(SpriteBotonSalir, TextureBotonSalirOff, TextureBotonSalirOn);
    ButtonG botonAcercaDe(spriteAcercaDe, textureAcercaDeOff, textureAcercaDeOn);
    window->setMouseCursorVisible(true);
    Inicializar();
    // Configurar la posición de los botones
    SpriteBotonOpciones.setPosition(640, 560);
    ValidarUser();

    while (window->isOpen()) {


        // Manejar eventos del menú
        eventoMenuP();

        // Obtener la posición actual del ratón
        sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
        sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);
        window->setMouseCursorVisible(true);
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
        window->draw(box);
        window->draw(Sesion);
        window->draw(SpriteBotonJugar);
        window->draw(SpriteBotonOpciones);
        window->draw(SpriteBotonSalir);
        window->draw(spriteAcercaDe);
        window->display();
    }
}

void menuP::ValidarUser() {

    if (SesionValida) {
     //   GetUserEmail();

        Sesion.setString(input);
     /*   if (email.empty()) {
            Sesion.setString("Iniciar Sesion");
        }
        else
        {
            Sesion.setString(email);
        }
     SesionValida = false;*/
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
            renderTexture.draw(overlay);
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
        
            }

            // Verificar si el clic fue en el bot�n Salir
            if (SpriteBotonSalir.getGlobalBounds().contains(mousePosFloat)) {
                playClickSound();

                MenuSalir(); // Salir del juego
            }
            if (spriteAcercaDe.getGlobalBounds().contains(mousePosFloat)) {
                playClickSound();
      
                MenuAcercaDe();
             
            }
            if (box.getGlobalBounds().contains(mousePosFloat)) {
                playClickSound();
                 OpenWebView();
            }
        }
    }
}

void menuP::MenuJugar() {


};


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


void menuP::Inicializar() {

    IniciaUser iniciaUser(*window);

    // Cargar los recursos necesarios para la cinem�tica
    iniciaUser.Resource();

    //Iniciar la animaci�n
    iniciaUser.Update();

}
void menuP::MenuOpcion() {

    SpriteBotonOpciones.setTexture(TextureBotonOpcionesOn);
    SpriteBotonOpciones.setPosition(640, 100);

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
    overlay.setFillColor(sf::Color(0, 0, 0, 10));

   //Ubicacion del mensaje de confirmaci�n
    SpriteConfirmarSalir.setTexture(TextureConfirmarSalir);
    SpriteConfirmarSalir.setPosition(660, 370);
    SpriteConfirmarSalir.setOrigin(340, 240);

   //Ubicaciones de los botones si y no

    SpriteBotonSi.setPosition(480, 380);  

  
    SpriteBotonNo.setPosition(680, 380);  

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

LRESULT menuP::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        CloseWebView(false); // Cerrar WebView cuando la ventana se destruye
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


void menuP::OpenWebView() {
    try {
        if (!isWebViewOpen) { // Solo abrir si no está abierta
            // Crear la ventana de WebView2
            WNDCLASS wc = {};
            wc.lpfnWndProc = [](HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) -> LRESULT {
                return reinterpret_cast<menuP*>(GetWindowLongPtr(hwnd, GWLP_USERDATA))->WindowProc(hwnd, uMsg, wParam, lParam);
                };
            wc.hInstance = GetModuleHandle(nullptr);
            wc.lpszClassName = L"WebView2Example";

            RegisterClass(&wc);
            hwnd = CreateWindowEx(0, L"WebView2Example", L"WebView2 Demo",
                WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
                nullptr, nullptr, GetModuleHandle(nullptr), this); // Pasa `this` como puntero de datos

            if (!hwnd) {
                std::cerr << "Error al crear la ventana." << std::endl;
                return;
            }

            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this)); // Guarda el puntero

            // Inicializar WebViewManager
            webviewManager = new WebViewManager(hwnd);
            webviewManager->CreateWebView(); // Crear el WebView
            isWebViewOpen = true; // Marcar que la ventana está abierta
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Excepción: " << e.what() << std::endl;
    }
}


void menuP::CloseWebView(bool Vali) {

    SesionValida = Vali;

    if (isWebViewOpen) {
        DestroyWindow(hwnd); // Cerrar la ventana de WebView2
        hwnd = nullptr;      // Establecer hwnd a nullptr después de cerrarlo
        isWebViewOpen = false; // Marcar que la ventana está cerrada
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

    //crear ventana semitransparente


    // Oscurecer el fondo y hacer el rectángulo semitransparente
    overlay.setFillColor(sf::Color(0, 0, 0, 100));  // Aumentamos la opacidad para que sea más oscuro

    // Confgurar el texto "Acerca De"
    sf::Font Fuente;
    if (!Fuente.loadFromFile("resource/fonts/ARCADEPI.ttf")) {
        return;
    }

    sf::Text TextAcercaDe;
    TextAcercaDe.setFont(Fuente);

    TextAcercaDe.setString("Sonic The Fucking Hedgehog ");
    TextAcercaDe.setCharacterSize(30);  // Tamaño más grande para ser fácilmente legible
    TextAcercaDe.setFillColor(sf::Color::White);  // Color blanco para contrastar con el fondo oscuro
    TextAcercaDe.setPosition(50, 100);  // Posicionamos el texto dentro del rectángulo
    
 
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

        window->draw(TextAcercaDe);
        window->setMouseCursor(*currentCursor);
        window->display();
    }
}