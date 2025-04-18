#include "StealplayerO.hpp"
#include <iostream>
#include "../../core/ObjetosGlobal.hpp"
#include "../../ui/ResourceGeneral.hpp"
#include "ResourceGameO.hpp"
StealplayerO::StealplayerO(sf::RenderWindow* window, std::vector<int> UsuariosElec,std::vector<PlayerGameOff> PSteal) : window(window), UsuariosEleccion(UsuariosElec), PlayersSteal(PSteal) {

}

StealplayerO::~StealplayerO() {

}

void StealplayerO::resource() {
	SlectingPlayer.setCharacterSize(40);
	SlectingPlayer.setFont(fontUser);
	SlectingPlayer.setFillColor(sf::Color::White);
	SlectingPlayer.setOutlineThickness(2);
	SlectingPlayer.setOutlineColor(sf::Color(135, 135, 135));
	SlectingPlayer.setString("Selecciona un jugador a robar");
	SlectingPlayer.setPosition(640, 100);
	sf::FloatRect globalBounds = SlectingPlayer.getGlobalBounds();
	SlectingPlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
	SlectingPlayer.setPosition(640, 100);

    UsuariosEleccionC = UsuariosEleccion;
    if(!texturebottonRobar.loadFromFile("assets/image/Button/robar.png")) return;
    SpritebottonRobar.setTexture(texturebottonRobar);
    SpritebottonRobar.setOrigin(95, 38);


}
void StealplayerO::BotRobar() {

    int aux = static_cast<int>(playerGameInfo.size()) - 1;
    playerGameInfo[IndexTurn1].money += 100;
    playerGameOff[IndexTurn1].Money.setString(std::to_string(playerGameInfo[IndexTurn1].money));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, aux);

    int in;
    do {
        in = dist(gen); 
    } while (in == IndexTurn1); // Si es igual a IndexTurn1, genera otro
    
    playerGameInfo[in].money -= 100;
    playerGameOff[in].Money.setString(std::to_string(playerGameInfo[in].money));
}

void StealplayerO::update() {

    

    UsuariosEleccion = UsuariosEleccionC;


    auto it = std::find(UsuariosEleccion.begin(), UsuariosEleccion.end(),IndexTurn1);
    if (it != UsuariosEleccion.end()) {
        UsuariosEleccion.erase(it);
    }
    isMouseOver.resize(UsuariosEleccion.size());
    PosIsMouseOver.resize(UsuariosEleccion.size());

    for (auto& MouseOver : isMouseOver) {

        MouseOver.setFillColor(sf::Color(0, 0, 0, 0));
        MouseOver.setSize(sf::Vector2f(200.0f, 380.0f));
        MouseOver.setOrigin(100, 64);
    }

    float perfilWidth = 200.0f; 
    float separacion = 20.0f;  
    int totalPerfiles = static_cast<int>(UsuariosEleccion.size());

    GM.bot.resetTCAM();
    if (totalPerfiles > 0) {
      
        float totalWidth = (totalPerfiles * perfilWidth) + ((totalPerfiles - 1) * separacion);
        float startX = (1280.0f - totalWidth) / 2.0f + (perfilWidth / 2.0f); 
        float startY = 300.0f; 

        for (int i = 0; i < totalPerfiles; i++) {
            float xPos = startX + i * (perfilWidth + separacion);
            float yPos = startY;

            PosIsMouseOver[i] = sf::Vector2f(xPos, startY +270);
            
            PlayersSteal[UsuariosEleccion[i]].NamePlayer.setPosition(xPos, startY + 70);
            PlayersSteal[UsuariosEleccion[i]].boxPlayer.setPosition(xPos, startY + 70);
            PlayersSteal[UsuariosEleccion[i]].AvatarPlayer.setPosition(xPos, startY);
            PlayersSteal[UsuariosEleccion[i]].MarcoPlayer.setPosition(xPos, startY);
            isMouseOver[i].setPosition(xPos, startY);
            if (PlayersSteal[UsuariosEleccion[i]].PieceSelect.getTexture() != nullptr) {
                PlayersSteal[UsuariosEleccion[i]].PieceSelect.setScale(2.0f, 2.0f);
                sf::FloatRect pieceSelectBounds = PlayersSteal[UsuariosEleccion[i]].PieceSelect.getGlobalBounds();
                PlayersSteal[UsuariosEleccion[i]].PieceSelect.setOrigin(pieceSelectBounds.width / 2.0f, pieceSelectBounds.height / 2.0f);
                PlayersSteal[UsuariosEleccion[i]].PieceSelect.setPosition(xPos + (pieceSelectBounds.width / 2.0f), startY + 220);
            }

            sf::FloatRect moneyBounds = PlayersSteal[UsuariosEleccion[i]].Money.getGlobalBounds();
            PlayersSteal[UsuariosEleccion[i]].Money.setOrigin(moneyBounds.width / 2.0f, moneyBounds.height / 2.0f);
            PlayersSteal[UsuariosEleccion[i]].Money.setPosition(xPos, startY + 120);

           
        }
    }
    bool seleccionlista = false;

    int indexMouseOver=-1;
    while (window->isOpen()&& !seleccionlista) {
        sf::Event event;
        while (window->pollEvent(event)) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
            sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                renderTexture.clear();
                renderTexture.draw(spriteBackgroundG);
                for (int i = 0; i < UsuariosEleccion.size(); i++) {
                    renderTexture.draw(PlayersSteal[UsuariosEleccion[i]].NamePlayer);
                    renderTexture.draw(PlayersSteal[UsuariosEleccion[i]].boxPlayer);
                    renderTexture.draw(PlayersSteal[UsuariosEleccion[i]].MarcoPlayer);
                    renderTexture.draw(PlayersSteal[UsuariosEleccion[i]].AvatarPlayer);
                }
                renderTexture.draw(spriteX);
                renderTexture.draw(overlay);
                Menup.MenuSalir(nullptr);
            }
            if(!secondTurn){indexMouseOver = -1;
            for (int i = 0; i < UsuariosEleccion.size(); i++) {

                if (isMouseOver[i].getGlobalBounds().contains(mousePosFloat)) {

                    indexMouseOver = i;
                    SpritebottonRobar.setPosition(PosIsMouseOver[i]);

                }
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (SpritebottonRobar.getGlobalBounds().contains(mousePosFloat)) {

                    playClickSound();
                    playerGameInfo[IndexTurn1].money += 100;
                    playerGameOff[IndexTurn1].Money.setString(std::to_string(playerGameInfo[IndexTurn1].money));
                    playerGameInfo[UsuariosEleccion[indexMouseOver]].money -= 100;
                    playerGameOff[UsuariosEleccion[indexMouseOver]].Money.setString(std::to_string(playerGameInfo[UsuariosEleccion[indexMouseOver]].money));
                    seleccionlista = true;                 

                }
            }
        }
        }
        if (secondTurn) {

            if (GM.bot.roll()) {


                BotRobar();
                seleccionlista = true;
            }
        }
        window->clear();
        window->draw(spriteBackgroundG);

        for (int i = 0; i < UsuariosEleccion.size(); i++) {
            window->draw(PlayersSteal[UsuariosEleccion[i]].NamePlayer);
            window->draw(PlayersSteal[UsuariosEleccion[i]].boxPlayer);
            window->draw(PlayersSteal[UsuariosEleccion[i]].AvatarPlayer);
            window->draw(PlayersSteal[UsuariosEleccion[i]].MarcoPlayer);
            window->draw(PlayersSteal[UsuariosEleccion[i]].Money);
            window->draw(PlayersSteal[UsuariosEleccion[i]].PieceSelect);
            if (indexMouseOver != -1){
                window->draw(isMouseOver[indexMouseOver]);
                window->draw(SpritebottonRobar);
            }

        }
        window->draw(SlectingPlayer);
        window->display();
    }
}