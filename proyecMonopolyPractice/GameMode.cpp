#include "GameMode.hpp"
#include <String>
GameMode::GameMode(sf::RenderWindow& win) : window(&win), Dado(window), ruleta(500.0f, 500.0f,640.0f, 360.0f), validar(false) , moverFicha1(win){
    loadResourceGame();
	resource();
}

void GameMode::resource() {
	if (!TextureMapa.loadFromFile("resource/texture/Game/mapa+S++.png")) return;
	if (!SettingsOff.loadFromFile("resource/texture/Game/settingOff.png")) return;
	if (!SettingsOn.loadFromFile("resource/texture/Game/settingOn.png")) return;

    //Cargar Texturas de Flechas
    if (!TextureArrowIzq.loadFromFile("resource/texture/Game/Izq.png")) return;
    if (!TextureArrowDer.loadFromFile("resource/texture/Game/Der.png")) return;
    if (!TextureArrowArriba.loadFromFile("resource/texture/Game/Arriba.png")) return;

    //posicin y tamanio de flechas
    SpriteArrowIzq.setTexture(TextureArrowIzq);
    SpriteArrowIzq.setOrigin(200.0f,90.5f);
    SpriteArrowIzq.setPosition(300, 400);

    SpriteArrowDer.setTexture(TextureArrowDer);
    SpriteArrowDer.setOrigin(200.0f, 90.5f);
    SpriteArrowDer.setPosition(900, 400);

    SpriteArrowArriba.setTexture(TextureArrowArriba);
    SpriteArrowArriba.setOrigin(200.0f, 90.5f);
    SpriteArrowArriba.setPosition(900, 400);

    Settings.setTexture(SettingsOff);
    Settings.setOrigin(25,25);
    Settings.setPosition(150,30 );

	spriteMapa.setTexture(TextureMapa);
	spriteMapa.setOrigin(360, 360);
	spriteMapa.setPosition(640, 360);


    if (!DiceBuffer.loadFromFile("resource/sounds/Dicerolling.wav")) return;

    DiceSound.setBuffer(DiceBuffer);

    // Vector para cada grupo de casillas (caminos)
    std::vector<sf::Vector2f> camino1 = { sf::Vector2f(375, 480) };

    std::vector<sf::Vector2f> camino2 = { sf::Vector2f(325,523), sf::Vector2f(325,576), sf::Vector2f(323,629), sf::Vector2f(351,676), sf::Vector2f(394,678), sf::Vector2f(425,655) };
    std::vector<sf::Vector2f> camino3 = { sf::Vector2f(473,661), sf::Vector2f(505, 632), sf::Vector2f(505 , 586), sf::Vector2f(519 , 544), sf::Vector2f(556 , 544), sf::Vector2f(568 ,586), sf::Vector2f(568 , 636), sf::Vector2f(580 , 678), sf::Vector2f(621 , 677), sf::Vector2f(632 , 637), sf::Vector2f(632 , 585), sf::Vector2f(642 , 542), sf::Vector2f(678,542), sf::Vector2f(694 ,582 ), sf::Vector2f(694 , 636), sf::Vector2f(725 , 668)};
    std::vector<sf::Vector2f> camino4 = { sf::Vector2f(280 , 300), sf::Vector2f(280 , 300), sf::Vector2f(280 , 300) };
    std::vector<sf::Vector2f> camino5 = { sf::Vector2f(280 , 300), sf::Vector2f(280 , 300), sf::Vector2f(280 , 300) };


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


    pieces.setPosition(330,439);
    view.setSize(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)); 
    view.setCenter(pieces.getPosition()); // Centrar la vista en la ficha

    posicionActual = 0; 
}

// Implementación del método update
void GameMode::update() {

    Dinero.resize(4);
    money[0] = 200;
    money[1] = 200;
    money[2] = 200;
    money[3] = 200;
    PieceSelector pieceselector(window);
    pieceselector.Resource();

    for (int i = 0; i < 4; i++)
    {
        Dinero[i].setString(std::to_string(money[i]));
        Dinero[i].setCharacterSize(17);
        Dinero[i].setFont(fontUser);
        Dinero[i].setFillColor(sf::Color::White);
        Dinero[i].setOutlineThickness(2);
        Dinero[i].setOutlineColor(sf::Color(135, 135, 135));
    }
    piecesTextures = pieceselector.updateSelection();

    pieces.setTexture(piecesTextures);
    globalBounds = pieces.getGlobalBounds();
    pieces.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
    sf::Clock clock;
    resultadoDado = 0;
    mousePosition = sf::Mouse::getPosition(*window);
    mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

    NamePlayers[0].setPosition(188.65f, 62.5f);
    boxPlayers[0].setPosition(188.65f, 62.5f);
    boxPlayers[0].setScale(0.7f, 0.7f);
    MarcoPlayers[0].setPosition(52.5f, 62.5f);
    Dinero[0].setPosition(170.65f, 95.5f);
    const sf::Texture* texture = selectedAvatarCopy.getTexture();
    if (texture != nullptr) {
        AvatarPlayers[0].setTexture(texture);
        AvatarPlayers[0].setRadius(static_cast<float>(texture->getSize().x / 2));
        AvatarPlayers[0].setOrigin(64, 64);
    }

    AvatarPlayers[0].setPosition(52.5f, 62.5f);
    AvatarPlayers[0].setScale(0.7f, 0.7f);

    
    //perfil 2
    NamePlayers[1].setPosition(188.65f, 552.5f);
    boxPlayers[1].setPosition(188.65f, 552.5f);
    boxPlayers[1].setScale(0.7f, 0.7f);
    MarcoPlayers[1].setPosition(1052.5f, 52.5f);
    AvatarPlayers[1].setPosition(1052.5f, 552.5f);
    AvatarPlayers[1].setScale(0.7f, 0.7f);
    Dinero[1].setPosition(170.65f, 585.5f);

    //perfil 3
    NamePlayers[2].setPosition(1188.65f, 52.5f);
    boxPlayers[2].setPosition(1188.65f, 52.5f);
    boxPlayers[2].setScale(0.7f, 0.7f);
    MarcoPlayers[2].setPosition(52.5f, 552.5f);
    AvatarPlayers[2].setPosition(52.5f, 552.5f);
    AvatarPlayers[2].setScale(0.7f, 0.7f);
    Dinero[2].setPosition(1170.65f, 85.5f);

    //perfil 4
    NamePlayers[3].setPosition(1188.65f, 552.5f);
    boxPlayers[3].setPosition(1188.65f, 552.5f);
    boxPlayers[3].setScale(0.7f, 0.7f);
    MarcoPlayers[3].setPosition(1052.5f, 552.5f);
    AvatarPlayers[3].setPosition(1052.5f, 652.5f);
    AvatarPlayers[3].setScale(0.7f, 0.7f);
    Dinero[3].setPosition(1170.65f, 585.5f);
  
    moverFicha1.Inicializar(&pieces, &casillas);

    float duracionMovimiento = 0.5f;  

     
 

    Dado.start(1280, 720); 
    int DadoResul=0;
    


    while (window->isOpen()) {
        
        Event();

        resultadoDado = Dado.logica(); 
        if (resultadoDado != 0) {
            DadoResul = resultadoDado;
            TempoAnimacion.restart();
        }

        currentCursor = &normalCursor;

        window->setMouseCursor(*currentCursor);

        if (DadoResul != 0 && TempoAnimacion.getElapsedTime().asSeconds() >= 1.0f ) {
               
                moverFicha1.iniciarMovimiento(DadoResul, duracionMovimiento);
                DadoResul = 0;
        }
 

      float deltaTime = reloj.restart().asSeconds();

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
  //  client.disconnect();
}

void  GameMode::Event(){

    sf::Event event;

    while (window->pollEvent(event)) {

        Dado.loop(event); 

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
          //  running = false;
        }


        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

            if (Settings.getGlobalBounds().contains(mousePosFloat)) {
                playClickSound();

                Menup.MenuOpcion();

            }
            validar = true;

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


    view.setCenter(viewX, viewY);

    view.setSize(1280 * 0.5, 720 * 0.5); 
    window->setView(view); 
    window->clear();

    window->draw(spriteFondoGame);
    window->draw(spriteMapa);
    //for (const auto& s : rastro) {
     //   window->draw(s);
    ///}
    window->draw(pieces);
    window->setView(window->getDefaultView());

    if (moverFicha1.finalCamino){
    window->draw(SpriteArrowIzq);
    window->draw(SpriteArrowDer);
    }

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
    window->setView(window->getDefaultView()); 
    
    window->clear();

    window->draw(spriteFondoGame);
    window->draw(spriteMapa);
    //window->setView(window->getDefaultView()); 
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
        window->draw(Dinero[i]);
    }

   window->draw(Settings);
}