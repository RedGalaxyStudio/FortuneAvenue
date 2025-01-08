#include "menuP.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "SettingsManager.hpp"
#include "ResourceGlobal.hpp"
#include "ButtonG.hpp"
#include "GameModeSelector.hpp"
#include "PieceSelector.hpp"
#include "IniciaUser.hpp"
menuP::menuP() : window(nullptr), SesionValida(true){}
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

    if (!Textureflechainstder.loadFromFile("resource/texture/Button/flechapagder.png")) return;
    if (!Textureflechainstizq.loadFromFile("resource/texture/Button/flechapagizq.png")) return;
    if (!textureInstruccionesOn.loadFromFile("resource/texture/Button/instruccionesencendido.png")) return;
    if (!textureInstruccionesOff.loadFromFile("resource/texture/Button/instruccionesapagado.png")) return;
    if (!MenuMusicFondo.openFromFile("resource/sounds/MenuB.wav")) return;
    if (!Blur.loadFromFile("resource/Shaders/blur.frag", sf::Shader::Fragment)) return;
    if (!renderTexture.create(window->getSize().x, window->getSize().y)) return;
    if (!SelectingMusicFondo.openFromFile("resource/sounds/SelectingPieces.wav")) return;



    flechainstder.setTexture(Textureflechainstder);
    flechainstder.setPosition(1180,600);
    flechainstder.setOrigin(50,45);  

    flechainstizq.setTexture(Textureflechainstizq);
    flechainstizq.setPosition(100,600);
    flechainstizq.setOrigin(50,45);


    spriteInstrucciones.setTexture(textureInstruccionesOff);
    spriteInstrucciones.setPosition(400,500);
    spriteInstrucciones.setOrigin(103.5f, 36.5f);



    Blur.setUniform("resolution", sf::Glsl::Vec2(
        static_cast<float>(window->getSize().x),
        static_cast<float>(window->getSize().y)
    ));

    loadSounds();
    std::vector<sf::Sound*> effectPointers = { &HoverSound, &ClickSound,&girosSound,&DiceSound };
    std::vector<sf::Music*> MusicPointers =  { &MenuMusicFondo,&GameMusicFondo,&SelectingMusicFondo };

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

    musicSlider = new SettingsManager(200, 300, 200, 10,MusicPointers,*window);
    effectSlider = new SettingsManager(200, 400, 200, 10,effectPointers,*window); 
    loadCursors();

    window->setMouseCursor(normalCursor);

}
void menuP::MenuPrincipal() {
    window->setMouseCursorVisible(true);
    MenuMusicFondo.setLoop(true);
    MenuMusicFondo.play();

    Inicializar();

    selectedAvatarCopy.setPosition(84,74);
    selectedAvatarCopy.setScale(1,1);
   

    editorPerfil.setFillColor(sf::Color(0, 0, 0, 0));
    editorPerfil.setSize(sf::Vector2f( 380.0f,145.0f));
    editorPerfil.setPosition(16,0);
    editorPerfil.setOrigin(0, 0);
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
        window->draw(editorPerfil);
        window->display();
    }
}

void menuP::ValidarUser() {

    if (SesionValida) {

        Sesion.setString(input1);
        sf::FloatRect globalBounds = Sesion.getGlobalBounds();

        // Ajustar la posición centrando el texto
        Sesion.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
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
                MenuOpcion(true);
                SpriteBotonOpciones.setPosition(640, 560);
        
            }

           
            if (SpriteBotonSalir.getGlobalBounds().contains(mousePosFloat)) {
                playClickSound();
                MenuSalir(); 

            }
            if (spriteAcercaDe.getGlobalBounds().contains(mousePosFloat)) {
                playClickSound();
                MenuAcercaDe();
             
            } 
            
            if (editorPerfil.getGlobalBounds().contains(mousePosFloat)) {
                
                playClickSound();
                editPerfil();
                ValidarUser();
                
             
            }

        }
    }
}

void menuP::MenuJugar() {


    GameModeSelector GMSelector(*window);
    GMSelector.update();

   box.setPosition(273, 74);




};





void menuP::Inicializar() {
    IniciaUser iniciaUser(*window);
    

    
    iniciaUser.Resource();
    
    
    iniciaUser.Update();

    iniciaUser.~IniciaUser();

}

void menuP::editPerfil() {
    IniciaUser iniciaUserEdit(*window);



    iniciaUserEdit.Resource();


    iniciaUserEdit.UpdateEdit();


    iniciaUserEdit.~IniciaUser();

    selectedAvatarCopy.setPosition(84, 74);
    selectedAvatarCopy.setScale(1, 1);
    recua.setPosition(84, 74);
    recua.setScale(1, 1);
    Sesion.setCharacterSize(24);
    Sesion.setPosition(273, 74 - 4);
    box.setPosition(273, 74);
    box.setScale(1, 1);

}
void menuP::MenuOpcion(bool fon) {

    SpriteBotonOpciones.setTexture(TextureBotonOpcionesOn);
    SpriteBotonOpciones.setPosition(640, 100);

    while (window->isOpen()) {
        currentCursor = &normalCursor;
        mousePosition = sf::Mouse::getPosition(*window);
        mousePosFloat = static_cast<sf::Vector2f>(mousePosition);
        botonX->update(mousePosFloat, currentCursor, linkCursor, normalCursor);


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
                    musicSlider->saveSettings();
                    effectSlider->saveSettings();
                    playClickSound();

                    return;

                }
                if (spriteInstrucciones.getGlobalBounds().contains(mousePosFloat)) {
                    playClickSound();
                    instruccionesGame();

                }
            }
        }
        
       
        window->clear();
        if(fon){
        window->draw(SpriteFondoMenu);
        }
        else {
            window->draw(spriteFondoGame);
        }
        window->draw(spriteX);
        window->draw(SpriteBotonOpciones);
        window->draw(spriteInstrucciones);
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

void menuP::instruccionesGame() {

    int pag = 0;
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

    sf::Text TextInstruccion1;
    sf::Text TextInstruccion2;
    sf::Text TextInstruccion3;
    TextInstruccion1.setFont(Fuente);
    TextInstruccion2.setFont(Fuente);
    TextInstruccion3.setFont(Fuente);

    TextInstruccion1.setString("Instrucciones de Fortuna Avenue\n\nObjetivo del juego :\nEl objetivo de Fortuna Avenue es ser el jugador con mas dinero al final de la partida, despues de \ncompletar 3 vueltas alrededor del tablero.Los jugadores deben administrar sus recursos, hacer \ninversiones y aprovechar tanto la suerte como la estrategia para ganar.\n\nComponentes del juego :\n    - Tablero : Un tablero con 4 tipos de casillas :\n    - Casillas :\n    -  Casillas de Casas : 17 casillas donde los jugadores pueden comprar casas.\n    - Casillas de Impuestos : 14 casillas donde los jugadores deben pagar impuestos.\n    - Casillas de Ruleta : 14 casillas con diferentes efectos aleatorios.\n    - Casillas Vacias : 43 casillas donde no ocurre ningun evento especial.    \n    - Dados : Un dado de 6 caras que dicta la cantidad de casillas que se movera el jugador.    \n    - Dinero : Cada jugador comienza con 200 billetes y recibe 60 billetes cada 2 turnos como sueldo \nbase y de ahi en adelante, al sueldo base se le ira sumando el sueldo de las casas que adquiera.\n\nPreparacion del juego :\n    1. Cada jugador selecciona una ficha que al iniciar el juego, se colocara automaticamente en la \ncasilla de ''Start''.\n    2. Los jugadores reciben 200 billetes como su primer sueldo.\n    3. El orden de turnos se elegira a partir de quienes ingresen primero a la sala, es decir, el \n    primer turno sera del creador de la sala y a partir de ahi, se elegira por orden de entrada, \n    que se mantendra durante toda la partida.\n    4. En el juego, se dan 3 vueltas por el tablero.Despues de la tercera vuelta de todos los \n    jugadores, el jugador con mas dinero gana.");
    TextInstruccion2.setString(
        "Como jugar:\n\n"
        "1. Turnos:\n"
        "    Los jugadores se turnan para tirar el dado. En cada turno, un jugador debe:\n"
        "    - Lanzar el dado para determinar cuantas casillas avanzara su ficha.\n"
        "    - Mover su ficha el numero de casillas indicado por el dado.\n"
        "    - Realizar una accion segun la casilla en la que caiga.\n\n"
        "2. Tipos de Casillas:\n"
        "    Existen 3 tipos principales de casillas con acciones especificas:\n"
        "    - Casillas de Impuestos:\n"
        "        - El jugador paga una cantidad de dinero.\n"
        "        - El monto base es 50 billetes, pero aumenta segun las casas del jugador.\n"
        "    - Casillas de Casas:\n"
        "        - El jugador puede comprar una casa entre 400 y 750 billetes.\n"
        "        - Las casas incrementan el sueldo en un rango de 60 a 113 billetes.\n"
        "        - Tambien aumentan los impuestos entre 50 y 94 billetes, segun la casa.\n"
        "    - Casillas de Ruleta:\n"
        "        - Al caer aqui, el jugador gira la ruleta, que tiene 7 posibles resultados:\n"
        "          1. Paga impuestos: Debe pagar dinero al banco.\n"
        "          2. Gana 150 billetes.\n"
        "          3. Pierde el siguiente turno.\n"
        "          4. Todos los demas jugadores le pagan 30 billetes.\n"
        "          5. Compra de casa: Puede adquirir una casa.\n"
        "          6. Inversión segura: Invierte 100 billetes y recibe 200 en dos turnos.\n"
        "          7. Robo a un jugador: Roba 100 billetes a un jugador al azar.\n\n"
        "       - Casillas Vacias:\n"
        "           - No ocurre ningun evento especial."
    );
    TextInstruccion3.setString(
        "Final del juego:\n\n"
        "El juego finaliza cuando todos los jugadores hayan dado 3 vueltas alrededor del tablero. Al finalizar, \n"
        "se cuentan los billetes de cada jugador, y el jugador con la mayor cantidad de billetes es el ganador.\n\n"
        "Ejemplo de turno:\n"
        "1. Jugador 1 lanza el dado y obtiene un 4. Elige el camino de la izquierda, mueve su ficha 4 casillas \ny cae en una casilla de casa.\n"
        "    - El jugador decide comprar una casa por 400 billetes. Su sueldo aumenta en 60 billetes por \n    encima del sueldo base \n"
        "      (es decir, 60$ + 60$ = 120$ -> nuevo sueldo). Sin embargo, sus impuestos tambien suben 70 \n    billetes por encima del impuesto base \n"
        "      (es decir, 50$ + 50$ = 100$ -> nuevo impuesto).\n"
        "2. Jugador 2 lanza el dado y obtiene un 2. Mueve su ficha 2 casillas a la derecha y cae en una\n casilla de impuestos. \n"
        "    - El jugador paga 50 billetes (si no ha comprado casas aún).\n"
        "3. El turno pasa al siguiente jugador.\n\n"
        "Consejos:\n"
        "- Administra bien tu dinero: Comprar casas aumenta tu sueldo, pero tambien tus impuestos. Tomate \ntu tiempo para decidir \n"
        "  si invertir es lo mejor en cada momento.\n"
        "- Observa a tus oponentes: Las decisiones de otros jugadores pueden afectar tu estrategia. Presta \natencion a sus movimientos \n"
        "  y gestiona tu dinero para contrarrestar sus ventajas.\n"
        "- Aprovecha las ruletas: Las casillas de ruleta son impredecibles, pero algunas pueden darte grandes \n      beneficios. \n"
        "         Aprovecha las oportunidades cuando las encuentres.\n\n"
        "           ¡Diviertete jugando a Fortuna Avenue!"
    );


    TextInstruccion1.setCharacterSize(static_cast <unsigned int>(17.5f));
    TextInstruccion2.setCharacterSize(static_cast <unsigned int>(17.5f));
    TextInstruccion3.setCharacterSize(static_cast <unsigned int>(17.5f));
    TextInstruccion1.setFillColor(sf::Color::White);
    TextInstruccion2.setFillColor(sf::Color::White);
    TextInstruccion3.setFillColor(sf::Color::White);
    TextInstruccion1.setPosition(50, 100);
    TextInstruccion2.setPosition(50, 100);
    TextInstruccion3.setPosition(50, 100);

    bool cierre = false;
    window->setMouseCursorVisible(true);

    while (window->isOpen() && !cierre) {
        currentCursor = &normalCursor;
        mousePosition = sf::Mouse::getPosition(*window);
        mousePosFloat = static_cast<sf::Vector2f>(mousePosition);
        
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


            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
                sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

                if (spriteX.getGlobalBounds().contains(mousePosFloat)) {
                    playClickSound();
                    cierre = true;

                }

                if (flechainstizq.getGlobalBounds().contains(mousePosFloat)) {
                    
                    if (pag > 0) {
                    playClickSound();
                    pag--;
                    }
                }
                if (flechainstder.getGlobalBounds().contains(mousePosFloat)) {
                    
                    if (pag < 2) {
                        playClickSound();
                        pag++;
                    }
                }
            }
        }

        botonX->update(mousePosFloat, currentCursor, linkCursor, normalCursor);

        renderedSprite.setTexture(renderTexture.getTexture());
         window->setMouseCursor(*currentCursor);
        window->clear();


        window->draw(renderedSprite, &Blur);
        window->draw(spriteX);

        window->draw(overlay);


        if (pag == 0) {
            window->draw(TextInstruccion1);
            window->draw(flechainstder);
        }
        else if (pag == 1) {
            window->draw(TextInstruccion2);
            window->draw(flechainstizq);
            window->draw(flechainstder);
        }
        else if (pag == 2) {

            window->draw(TextInstruccion3);
            window->draw(flechainstizq);
        }

   


        window->display();
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

    TextAcercaDe.setString(
        "Fortune Avenue\n"
        "version 1.0.0\n\n"
        "Fortune Avenue esta basado en los clasicos juegos de mesa donde el objetivo principal es obtener \nla mayor cantidad de dinero al finalizar la partida, tomando decisiones sobre la compra de viviendas \ny el pago de impuestos, todo mientras el azar juega un papel importante al final de cada partida.\n\n"
        "Este proyecto fue desarrollado por Red Galaxy Studio, un equipo de 4 estudiantes apasionados por el \ndesarrollo de videojuegos. Nuestra mision es crear experiencias unicas e interactivas que entretengan \ny desafien a los jugadores.\n\n"
        "Integrantes del equipo:\n\n"
        "Daniel Fernandez\n"
        "Lider del Proyecto | Programador | Especialista en Redes\n\n"
        "Jose Garcia\n"
        "Especialista en Testing y Calidad | Disenador de Mecanicas | Encargado de Documentacion\n\n"
        "Susana Rendon\n"
        "Artista Grafico | Disenadora de Interfaz de Usuario (UI/UX) | Encargada de Implementacion de Sonidos\n\n"
        "Marcos Rondon\n"
        "Encargado de Marketing | Disenador de Mecanicas | Responsable de Economia del Juego\n\n"
        "Nota: Aunque cada miembro asumio roles especificos, el proyecto fue un esfuerzo colaborativo en el \nque todos contribuyeron activamente en diversas areas del desarrollo.\n\n"
        "Ubicacion: Proyecto academico, Universidad de los Andes.\n"
        "Tecnologias utilizadas: SFML, ENet, C++.\n"
        "Contacto: redgalaxy.studio24@gmail.com"
    );

    TextAcercaDe.setCharacterSize(static_cast <unsigned int>(17.5f));
    TextAcercaDe.setFillColor(sf::Color::White);  
    TextAcercaDe.setPosition(50, 100);  
 
    window->setMouseCursorVisible(true);

    while (window->isOpen()) {
        currentCursor = &normalCursor;
        mousePosition = sf::Mouse::getPosition(*window);
        mousePosFloat = static_cast<sf::Vector2f>(mousePosition);



        sf::Event event;

        while (window->pollEvent(event)) {

            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                renderTexture.clear();

                renderTexture.draw(renderedSprite, &Blur);
                renderTexture.draw(spriteX);

                renderTexture.draw(overlay);


                renderTexture.draw(TextAcercaDe);
                renderTexture.draw(spriteX);
                renderTexture.display();
                MenuSalir();
            }



            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
                sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

                if (spriteX.getGlobalBounds().contains(mousePosFloat)) {

                    playClickSound();

                    return;

                }

            }
        }
        botonX->update(mousePosFloat, currentCursor, linkCursor, normalCursor);
        
        renderedSprite.setTexture(renderTexture.getTexture());

        window->clear();

 
        window->draw(renderedSprite, &Blur);
        window->draw(spriteX);

        window->draw(overlay);


        window->draw(TextAcercaDe);

        window->setMouseCursor(*currentCursor);
        window->display();
    }
}