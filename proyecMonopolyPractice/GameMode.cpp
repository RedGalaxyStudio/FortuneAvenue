#include "GameMode.hpp"
#include "ResourceGlobal.hpp"
#include "ObjetosGlobal.hpp"
#include "PieceSelector.hpp"
#include "ResourceGame.hpp"
<<<<<<< HEAD
#include "WindowClass.h"

GameMode::GameMode(sf::RenderWindow* windowRef): window(windowRef) {
=======
#include "Ruleta.hpp"
//#include <boost/asio.hpp>
//#include "Client.hpp"


GameMode::GameMode(sf::RenderWindow& win) : window(&win), Dado(window), ruleta(500.0f, 500.0f,640.0f, 360.0f), validar(false) , moverFicha1(win){
>>>>>>> f72d20990916be5037739544fb6b23cc6932def9
    loadResourceGame();
	resource();
}

void GameMode::resource() {
	if (!TextureMapa.loadFromFile("resource/texture/Game/mapa+S++.png")) return;
<<<<<<< HEAD
=======
	if (!SettingsOff.loadFromFile("resource/texture/Game/settingOff.png")) return;
	if (!SettingsOn.loadFromFile("resource/texture/Game/settingOn.png")) return;


    if (!TextureArrowIzq.loadFromFile("resource/texture/Game/Izq.png")) return;
    if (!TextureArrowDer.loadFromFile("resource/texture/Game/Der.png")) return;


    SpriteArrowIzq.setTexture(TextureArrowIzq);
    SpriteArrowIzq.setOrigin(200.0f,90.5f);
    SpriteArrowIzq.setPosition(300, 400);


    SpriteArrowDer.setTexture(TextureArrowDer);
    SpriteArrowDer.setOrigin(200.0f, 90.5f);
    SpriteArrowDer.setPosition(900, 400);





    Settings.setTexture(SettingsOff);
    Settings.setOrigin(25,25);
    Settings.setPosition(150,30 );

>>>>>>> f72d20990916be5037739544fb6b23cc6932def9
	spriteMapa.setTexture(TextureMapa);
	spriteMapa.setOrigin(360, 360);
	spriteMapa.setPosition(640, 360);


    if (!DiceBuffer.loadFromFile("resource/sounds/Dicerolling.wav")) return;

    DiceSound.setBuffer(DiceBuffer);

    // Vector para cada grupo de casillas (caminos)
    std::vector<sf::Vector2f> camino1 = { sf::Vector2f(375, 480) };
<<<<<<< HEAD
    std::vector<sf::Vector2f> camino2 = { sf::Vector2f(325,523), sf::Vector2f(325,576), sf::Vector2f(323,629), sf::Vector2f(351,676), sf::Vector2f(394,678), sf::Vector2f(425,655) };
    std::vector<sf::Vector2f> camino3 = { sf::Vector2f(473,661), sf::Vector2f(505, 632), sf::Vector2f(505 , 586), sf::Vector2f(519 , 544), sf::Vector2f(556 , 544), sf::Vector2f(568 ,586), sf::Vector2f(568 , 636), sf::Vector2f(580 , 678), sf::Vector2f(621 , 677), sf::Vector2f(632 , 637), sf::Vector2f(632 , 585), sf::Vector2f(642 , 542), sf::Vector2f(678,542), sf::Vector2f(694 ,582 ), sf::Vector2f(694 , 636), sf::Vector2f(725 , 668)};
    std::vector<sf::Vector2f> camino4 = { sf::Vector2f(280 , 300), sf::Vector2f(280 , 300), sf::Vector2f(280 , 300) };
=======
>>>>>>> f72d20990916be5037739544fb6b23cc6932def9

    // Agregar los caminos al vector principal
    for (int i = 0; i < 4; i++) {
        if(i==0){
            StringNamePlayers[i] = input; 
        }
        else{
        StringNamePlayers[i] = "bot" + std::to_string(i);
        }

        NamePlayers[i].setString(StringNamePlayers[i]);
        globalBounds = NamePlayers[i].getGlobalBounds();
        NamePlayers[i].setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
        MarcoPlayers[i].setOrigin(45.5f,45.5f);
    }
    casillas.push_back(camino1);
<<<<<<< HEAD
    casillas.push_back(camino2);
    casillas.push_back(camino3);
    casillas.push_back(camino4);
=======

    pieces.setPosition(330,439);
    view.setSize(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)); // Tamaño de la vista igual al de la ventana
    view.setCenter(pieces.getPosition()); // Centrar la vista en la ficha
>>>>>>> f72d20990916be5037739544fb6b23cc6932def9

    posicionActual = 0; // Posición actual del sprite en las casillas
}

// Implementación del método update
void GameMode::update() {

<<<<<<< HEAD
    std::atomic<bool> running{ true }; // Inicializa a true
    const unsigned short PORT = 54000; // Define el puerto

    AvatarNetworkHandler avatarHandler("192.168.3.114", PORT); // Cambia la IP según tu configuración
    avatarHandler.iniciar(); // Inicia el hilo de recepción de mensajes


    PieceSelector pieceselector(window);
    pieceselector.Resource();
    piecesTextures = pieceselector.updateSelection();
=======
    PieceSelector pieceselector(window);
    pieceselector.Resource();


    piecesTextures = pieceselector.updateSelection();

    const float marginX = 100.0f; // Margen horizontal
    const float marginY = 100.0f; // Margen vertical

>>>>>>> f72d20990916be5037739544fb6b23cc6932def9
    pieces.setTexture(piecesTextures);
    globalBounds = pieces.getGlobalBounds();
    pieces.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
    sf::Clock clock;
    resultadoDado = 0;
    mousePosition = sf::Mouse::getPosition(*window);
    mousePosFloat = static_cast<sf::Vector2f>(mousePosition);
// Llamadas a setPlayerProfile para cada perfil

<<<<<<< HEAD
    NamePlayers[0].setPosition(188.65f, 52.5f);
    boxPlayers[0].setPosition(188.65f, 52.5f);
    boxPlayers[0].setScale(0.7f, 0.7f);
    MarcoPlayers[0].setPosition(52.5f, 52.5f);
=======
    NamePlayers[0].setPosition(188.65f, 62.5f);
    boxPlayers[0].setPosition(188.65f, 62.5f);
    boxPlayers[0].setScale(0.7f, 0.7f);
    MarcoPlayers[0].setPosition(52.5f, 62.5f);

>>>>>>> f72d20990916be5037739544fb6b23cc6932def9
    const sf::Texture* texture = selectedAvatarCopy.getTexture();
    if (texture != nullptr) {
        AvatarPlayers[0].setTexture(texture);
        AvatarPlayers[0].setRadius(static_cast<float>(texture->getSize().x / 2)); // Ajusta el tamaño del círculo
        AvatarPlayers[0].setOrigin(64, 64);
    }

<<<<<<< HEAD
    AvatarPlayers[0].setPosition(52.5f, 52.5f);
    AvatarPlayers[0].setScale(0.7f, 0.7f);

=======
    AvatarPlayers[0].setPosition(52.5f, 62.5f);
    AvatarPlayers[0].setScale(0.7f, 0.7f);

    
>>>>>>> f72d20990916be5037739544fb6b23cc6932def9
    //perfil 2
    NamePlayers[1].setPosition(1188.65f, 52.5f);
    boxPlayers[1].setPosition(1188.65f, 52.5f);
    boxPlayers[1].setScale(0.7f, 0.7f);
    MarcoPlayers[1].setPosition(52.5f, 652.5f);
    AvatarPlayers[1].setPosition(52.5f, 652.5f);
    AvatarPlayers[1].setScale(0.7f, 0.7f);

    //perfil 3
    NamePlayers[2].setPosition(188.65f, 652.5f);
    boxPlayers[2].setPosition(188.65f, 652.5f);
    boxPlayers[2].setScale(0.7f, 0.7f);
    MarcoPlayers[2].setPosition(1052.5f, 52.5f);
    AvatarPlayers[2].setPosition(1052.5f, 652.5f);
    AvatarPlayers[2].setScale(0.7f, 0.7f);

    //perfil 4
    NamePlayers[3].setPosition(1188.65f, 652.5f);
    boxPlayers[3].setPosition(1188.65f, 652.5f);
    boxPlayers[3].setScale(0.7f, 0.7f);
    MarcoPlayers[3].setPosition(1052.5f, 652.5f);

<<<<<<< HEAD
     
    AvatarPlayers[3].setPosition(1052.5f, 652.5f);
    AvatarPlayers[3].setScale(0.7f, 0.7f);
    Window Dado(window);

    Dado.start(1280, 720); // Cambia el tamaño y el título según sea necesario
    int DadoResul=0;
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {

            Dado.loop(event); // Cambia el tamaño y el título según sea necesario


            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                renderTexture.draw(spriteFondoGame);
                renderTexture.draw(spriteMapa);
                for (int i = 0; i < 4; i++)
                {
                    renderTexture.draw(NamePlayers[i]);
                    renderTexture.draw(boxPlayers[i]);
                    renderTexture.draw(MarcoPlayers[i]);
                    renderTexture.draw(AvatarPlayers[i]);
                }
                renderTexture.draw(spriteX);
                renderTexture.draw(overlay);
                Menup.MenuSalir();
                running = false; // Cambia el estado de ejecución
            }
            

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // Verificar el click en "si" y cerrar la vetana
     
                if (spriteMapa.getGlobalBounds().contains(mousePosFloat)) {
                    playClickSound();
                    resultadoDado = 1;
                    //cube.roll();  // Lanzar el dado
                        //saveSelectedAvatar();
                   // Menup.MenuPrincipal();
                   
                }
            }
          
        }
        resultadoDado = Dado.logica(); // Cambia el tamaño y el título según sea necesario
        if (resultadoDado != 0) {
            DadoResul = resultadoDado;
            std::cout << "\n" << DadoResul;
        }
=======
    moverFicha1.Inicializar(&pieces, &casillas);

    // Variables para controlar el tiempo

    float duracionMovimiento = 0.5f;  // Duración del movimiento entre casillas

     
    AvatarPlayers[3].setPosition(1052.5f, 652.5f);
    AvatarPlayers[3].setScale(0.7f, 0.7f);

    Dado.start(1280, 720); // Cambia el tamaño y el título según sea necesario
    int DadoResul=0;
    


    while (window->isOpen()) {
        
        Event();

        resultadoDado = Dado.logica(); // Cambia el tamaño y el título según sea necesario
        if (resultadoDado != 0) {
            DadoResul = resultadoDado;
            TempoAnimacion.restart();
        }

       
        // Actualizar el movimiento del sprite
        
>>>>>>> f72d20990916be5037739544fb6b23cc6932def9
        currentCursor = &normalCursor;

        window->setMouseCursor(*currentCursor);

<<<<<<< HEAD
        moverSprite(pieces, DadoResul);

        DadoResul = 0;

        window->clear();

        window->draw(spriteFondoGame);
        window->draw(spriteMapa);
        for (int i = 0; i < 4; i++)
        {
            window->draw(NamePlayers[i]);
            window->draw(boxPlayers[i]);
            window->draw(AvatarPlayers[i]);
            window->draw(MarcoPlayers[i]);
            
        }
        Dado.update();
        window->draw(pieces);

        window->display();
    }
    // Desconectar y unir el hilo cliente al final
    avatarHandler.desconectar();
}

void GameMode::moverSprite(sf::Sprite& sprite, int resultadoDado) {
    posicionActual += resultadoDado;

    // Mientras se supere el tamaño del vector actual, cambiar al siguiente vector
    while (posicionActual >= casillas[vectorActual].size()) {
        posicionActual -= static_cast<int>(casillas[vectorActual].size());  // Ajustar la posición
        vectorActual++;  // Ir al siguiente vector

        // Verificar si llegamos al final de los vectores
        if (vectorActual >= casillas.size()) {
            vectorActual = 0;  // Reiniciar al primer vector si se superan todos
        }
    }

    // Mueve el sprite a la posición de la casilla correspondiente en el vector actual
    sprite.setPosition(casillas[vectorActual][posicionActual]);
=======
        if (DadoResul != 0 && TempoAnimacion.getElapsedTime().asSeconds() >= 1.0f ) {
               
                moverFicha1.iniciarMovimiento(DadoResul, duracionMovimiento);
                DadoResul = 0;
        }
 

      float deltaTime = reloj.restart().asSeconds();
    // moverFicha1.animacionRastro(deltaTime);
     

        if (moverFicha1.enMovimiento == true) {
  
        moverFicha1.actualizarMovimiento(deltaTime);
  
        DrawPieceMoviendo(); 
            
        }
        else if (validar == true) { 
            DrawGameRuleta();  }
        else {

            DrawGame();
        }
        window->display();
   
    }

}

void  GameMode::Event(){

    sf::Event event;

    while (window->pollEvent(event)) {

        Dado.loop(event); // Cambia el tamaño y el título según sea necesario

        sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
        sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

        if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            renderTexture.draw(spriteFondoGame);
            renderTexture.draw(spriteMapa);
            for (int i = 0; i < 4; i++)
            {
                renderTexture.draw(NamePlayers[i]);
                renderTexture.draw(boxPlayers[i]);
                renderTexture.draw(MarcoPlayers[i]);
                renderTexture.draw(AvatarPlayers[i]);
            }
            renderTexture.draw(spriteX);
            renderTexture.draw(overlay);
            Menup.MenuSalir();
            running = false; // Cambia el estado de ejecución
        }

        if (moverFicha1.finalCamino) {

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // Verificar el click en "si" y cerrar la vetana


            }


        }


        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

            if (Settings.getGlobalBounds().contains(mousePosFloat)) {
                playClickSound();

                Menup.MenuOpcion();

            }
            // validar = true;

        }

    }



}


void GameMode::DrawPieceMoviendo(){

    sf::Vector2f fichaPos = pieces.getPosition();
    float viewX = fichaPos.x;
    float viewY = fichaPos.y;

    if (viewY > 540) viewY = 540;
    if (viewX < 320) viewX = 320;

    if (viewY < 180) viewY = 180;


    view.setCenter(viewX, viewY); // Actualizar la vista centrada en la nueva posición

    view.setSize(1280 * 0.5, 720 * 0.5); // Actualizar el tamaño de la vista

    window->setView(view); // Establecer la vista antes de dibujar
    window->clear();

    window->draw(spriteFondoGame);
    window->draw(spriteMapa);
    //for (const auto& s : rastro) {
     //   window->draw(s);
    ///}
    window->draw(pieces);
    window->setView(window->getDefaultView()); // Volver a la vista original

    if (moverFicha1.finalCamino){
    window->draw(SpriteArrowIzq);
    window->draw(SpriteArrowDer);
    }



  //Dado.update();

}
void GameMode::DrawGameRuleta() {

    float deltaTime = clock.restart().asSeconds();

    window->clear();

    renderTexture.clear();

    renderTexture.draw(spriteFondoGame);
    renderTexture.draw(spriteMapa);
    for (int i = 0; i < 4; i++)
    {
        renderTexture.draw(NamePlayers[i]);
        renderTexture.draw(boxPlayers[i]);
        renderTexture.draw(MarcoPlayers[i]);
        renderTexture.draw(AvatarPlayers[i]);
    }
    renderTexture.draw(overlay);

    renderTexture.display();

    renderedSprite.setTexture(renderTexture.getTexture());

    window->draw(renderedSprite);
    ruleta.draw(*window, deltaTime, validar);
}

void GameMode::DrawGame() {
    window->setView(window->getDefaultView()); // Volver a la vista original
    
    window->clear();

    window->draw(spriteFondoGame);
    window->draw(spriteMapa);
    //window->setView(window->getDefaultView()); // Volver a la vista original
   // for (const auto& s : rastro) {
    //    window->draw(s);
    //}
    window->draw(pieces);
    Dado.update();
    float deltaTime = clock.restart().asSeconds();

    //ruleta.draw(*window, deltaTime, validar);
    for (int i = 0; i < 4; i++)
    {
        window->draw(NamePlayers[i]);
        window->draw(boxPlayers[i]);
        window->draw(AvatarPlayers[i]);
        window->draw(MarcoPlayers[i]);

    }

   window->draw(Settings);
>>>>>>> f72d20990916be5037739544fb6b23cc6932def9
}