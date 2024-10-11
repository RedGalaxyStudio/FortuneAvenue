#include "GameMode.hpp"
#include "ResourceGlobal.hpp"
#include "ObjetosGlobal.hpp"
#include "PieceSelector.hpp"
#include "ResourceGame.hpp"
#include "WindowClass.h"

GameMode::GameMode(sf::RenderWindow* windowRef): window(windowRef) {
    loadResourceGame();
	resource();
}

void GameMode::resource() {
	if (!TextureMapa.loadFromFile("resource/texture/Game/mapa+S++.png")) return;
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
    casillas.push_back(camino2);
    casillas.push_back(camino3);
    casillas.push_back(camino4);

    posicionActual = 0; // Posición actual del sprite en las casillas
}

// Implementación del método update
void GameMode::update() {

    std::atomic<bool> running{ true }; // Inicializa a true
    const unsigned short PORT = 54000; // Define el puerto

    AvatarNetworkHandler avatarHandler("192.168.3.114", PORT); // Cambia la IP según tu configuración
    avatarHandler.iniciar(); // Inicia el hilo de recepción de mensajes


    PieceSelector pieceselector(window);
    pieceselector.Resource();
    piecesTextures = pieceselector.updateSelection();
    pieces.setTexture(piecesTextures);
    globalBounds = pieces.getGlobalBounds();
    pieces.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
    sf::Clock clock;
    resultadoDado = 0;
    mousePosition = sf::Mouse::getPosition(*window);
    mousePosFloat = static_cast<sf::Vector2f>(mousePosition);
// Llamadas a setPlayerProfile para cada perfil

    NamePlayers[0].setPosition(188.65f, 52.5f);
    boxPlayers[0].setPosition(188.65f, 52.5f);
    boxPlayers[0].setScale(0.7f, 0.7f);
    MarcoPlayers[0].setPosition(52.5f, 52.5f);
    const sf::Texture* texture = selectedAvatarCopy.getTexture();
    if (texture != nullptr) {
        AvatarPlayers[0].setTexture(texture);
        AvatarPlayers[0].setRadius(static_cast<float>(texture->getSize().x / 2)); // Ajusta el tamaño del círculo
        AvatarPlayers[0].setOrigin(64, 64);
    }

    AvatarPlayers[0].setPosition(52.5f, 52.5f);
    AvatarPlayers[0].setScale(0.7f, 0.7f);

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
        currentCursor = &normalCursor;

        window->setMouseCursor(*currentCursor);

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
}