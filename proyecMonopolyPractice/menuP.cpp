#include "menuP.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "SettingsManager.hpp"
#include "IniciaUser.hpp"
#include "ResourceGlobal.hpp"
#include "ButtonG.hpp"
#include "IniciarPartida.hpp"
#include "PieceSelector.hpp"

menuP::menuP() : window(nullptr), hwnd(nullptr), webviewManager(nullptr), isWebViewOpen(false) , SesionValida(true){}
void menuP::setWindow(sf::RenderWindow& win) {
    window = &win;
}


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

   
    overlay.setSize(sf::Vector2f(static_cast<float>(window->getSize().x),static_cast<float>(window->getSize().y)));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
   
    Sesion.setFont(fontUser);
    Sesion.setFillColor(sf::Color::White);
    Sesion.setOutlineThickness(2);
    Sesion.setOutlineColor(sf::Color(135, 135, 135));
  
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

    musicSlider = new SettingsManager(200, 300, 200, 10,&MenuMusicFondo,*window);  
    effectSlider = new SettingsManager(200, 400, 200, 10,effectPointers,*window); 
    loadCursors();

    window->setMouseCursor(normalCursor);

}

void menuP::MenuPrincipal() {
    window->setMouseCursorVisible(true);
    MenuMusicFondo.setLoop(true);
    //MenuMusicFondo.play();

    Inicializar();

    selectedAvatarCopy.setPosition(84,74);
    selectedAvatarCopy.setScale(1,1);

    recua.setPosition(84,74);
    recua.setScale(1,1);
    Sesion.setCharacterSize(24);
    Sesion.setPosition(273, 74 - 4);
    box.setPosition(273, 74);
    box.setScale(1,1);

    // Crear botones
    ButtonG botonJugar(SpriteBotonJugar, TextureBotonJugarOff, TextureBotonJugarOn);
    ButtonG botonOpciones(SpriteBotonOpciones, TextureBotonOpcionesOff, TextureBotonOpcionesOn);
    ButtonG botonSalir(SpriteBotonSalir, TextureBotonSalirOff, TextureBotonSalirOn);
    ButtonG botonAcercaDe(spriteAcercaDe, textureAcercaDeOff, textureAcercaDeOn);
    window->setMouseCursorVisible(true);
   
    SpriteBotonOpciones.setPosition(640, 560);
    ValidarUser();

    while (window->isOpen()) {


       
        eventoMenuP();

        
        sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
        sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);
        window->setMouseCursorVisible(true);
        

        currentCursor = &normalCursor;

        

        
        botonJugar.update(mousePosFloat, currentCursor, linkCursor, normalCursor);
        botonOpciones.update(mousePosFloat, currentCursor, linkCursor, normalCursor);
        botonSalir.update(mousePosFloat, currentCursor, linkCursor, normalCursor);
        botonAcercaDe.update(mousePosFloat, currentCursor, linkCursor, normalCursor);
        window->setMouseCursor(*currentCursor);
  


        window->clear();
        window->draw(SpriteFondoMenu);
        window->draw(spriteLogoFortuneAvenue);
        window->draw(box);
        window->draw(Sesion);
        window->draw(selectedAvatarCopy);
        window->draw(recua);
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

        Sesion.setString(input1);
        sf::FloatRect globalBounds = Sesion.getGlobalBounds();

        // Ajustar la posición centrando el texto
        Sesion.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
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
       
            renderTexture.clear(sf::Color::Transparent);  
            renderTexture.draw(SpriteFondoMenu);
            renderTexture.draw(spriteLogoFortuneAvenue);
            renderTexture.draw(box);
            renderTexture.draw(Sesion);
            renderTexture.draw(selectedAvatarCopy);
            renderTexture.draw(recua);
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

        
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);

            sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);
          
            
            if (SpriteBotonJugar.getGlobalBounds().contains(mousePosFloat)) {
                playClickSound();
                MenuJugar();
          
               
            }

            
            if (SpriteBotonOpciones.getGlobalBounds().contains(mousePosFloat)) {
                playClickSound();
                MenuOpcion();
        
            }

           
            if (SpriteBotonSalir.getGlobalBounds().contains(mousePosFloat)) {
                playClickSound();
                MenuSalir(); 

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


   IniciarPartida inicial(*window);
   inicial.update();

   box.setPosition(273, 74);




};


void menuP::eventoMenuO() {

    sf::Event event;

    while (window->pollEvent(event)) {
       
        if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            renderTexture.clear();  
            renderTexture.draw(SpriteFondoMenu);
            renderTexture.draw(SpriteBotonOpciones);
            renderTexture.draw(spriteX);
            musicSlider->Printf();
            effectSlider->Printf();
            renderTexture.display();
            MenuSalir();
        }

       

        musicSlider->handleEvent(event, *window);
        effectSlider->handleEvent(event, *window);

        
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

    
    iniciaUser.Resource();

    
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

    
    sf::RectangleShape overlay(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
    overlay.setFillColor(sf::Color(0, 0, 0, 10));

   
    SpriteConfirmarSalir.setTexture(TextureConfirmarSalir);
    SpriteConfirmarSalir.setPosition(660, 370);
    SpriteConfirmarSalir.setOrigin(340, 240);

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

                
                if (SpriteBotonSi.getGlobalBounds().contains(mousePosFloat)) {
                    playClickSound();

                    if (client.running && client.peer != nullptr) {
                        client.disconnect();
                    }

                    window->close();  
                }

                
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

            window->setMouseCursor(*currentCursor);

            renderedSprite.setTexture(renderTexture.getTexture());
       window->clear();
       window->draw(renderedSprite, &Blur); 
  

        window->draw(SpriteConfirmarSalir);  
        window->draw(SpriteBotonSi);        
        window->draw(SpriteBotonNo);       

       window->display();

        
    }
}

LRESULT menuP::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        CloseWebView(false); 
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


void menuP::OpenWebView() {
    try {
        if (!isWebViewOpen) { 

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
                nullptr, nullptr, GetModuleHandle(nullptr), this); 

            if (!hwnd) {
                std::cerr << "Error al crear la ventana." << std::endl;
                return;
            }

            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this)); 

            
            webviewManager = new WebViewManager(hwnd);
            webviewManager->CreateWebView();
            isWebViewOpen = true; 
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Excepción: " << e.what() << std::endl;
    }
}


void menuP::CloseWebView(bool Vali) {

    SesionValida = Vali;

    if (isWebViewOpen) {
        DestroyWindow(hwnd); 
        hwnd = nullptr;      
        isWebViewOpen = false; 
    }
}


void menuP::MenuAcercaDe() {

    
    sf::RectangleShape overlay(sf::Vector2f(
        static_cast<float>(window->getSize().x - 50),  
        static_cast<float>(window->getSize().y - 50)   
    ));


    
    overlay.setPosition(25.0f, 25.0f);

    overlay.setFillColor(sf::Color(0, 0, 0, 100));  

    sf::Font Fuente;
    if (!Fuente.loadFromFile("resource/fonts/ARCADEPI.ttf")) {
        return;
    }

    sf::Text TextAcercaDe;
    TextAcercaDe.setFont(Fuente);

    TextAcercaDe.setString(" Contribuciones ");
    TextAcercaDe.setCharacterSize(30);  
    TextAcercaDe.setFillColor(sf::Color::White);  
    TextAcercaDe.setPosition(50, 100);  
 
    window->setMouseCursorVisible(true);

    while (window->isOpen()) {
        currentCursor = &normalCursor;
        mousePosition = sf::Mouse::getPosition(*window);
        mousePosFloat = static_cast<sf::Vector2f>(mousePosition);
        botonX->update(mousePosFloat, currentCursor, linkCursor, normalCursor);
        eventoMenuO();
        renderedSprite.setTexture(renderTexture.getTexture());

        window->clear();

 
        window->draw(renderedSprite, &Blur);
        window->draw(spriteX);

        window->draw(overlay);


        window->draw(TextAcercaDe);

        window->draw(TextAcercaDe);
        window->setMouseCursor(*currentCursor);
        window->display();
    }
}