#include "Stealplayer.hpp"
#include <iostream>

// Constructor
Stealplayer::Stealplayer(sf::RenderWindow* window, std::vector<int> UsuariosElec,std::vector<PlayerGame> PSteal) : window(window), UsuariosEleccion(UsuariosElec), PlayersSteal(PSteal) {

}

// Destructor
Stealplayer::~Stealplayer() {}

 
void Stealplayer::resource() {
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
   //std::cout << "\n3";
    if (!UsuariosEleccion.empty()) { // Asegúrate de que el vector no esté vacío
        UsuariosEleccion.erase(UsuariosEleccion.begin()); // Elimina el primer elemento
    }
    isMouseOver.resize(UsuariosEleccion.size());
    PosIsMouseOver.resize(UsuariosEleccion.size());
   //std::cout << "\n4";
    for (auto& MouseOver : isMouseOver) {

        MouseOver.setFillColor(sf::Color(0, 0, 0, 0));
        MouseOver.setSize(sf::Vector2f(200.0f, 380.0f));
        MouseOver.setOrigin(100, 64);
    }
   //std::cout << "\n7";


    if(!texturebottonRobar.loadFromFile("../assets/Button/robar.png")) return;
    SpritebottonRobar.setTexture(texturebottonRobar);
    SpritebottonRobar.setOrigin(95, 38);


}
void Stealplayer::update() {


    return;
    // Configurar perfiles
    float perfilWidth = 200.0f; // Ancho estimado de cada perfil
    float separacion = 20.0f;   // Espaciado entre perfiles
    int totalPerfiles = static_cast<int>(UsuariosEleccion.size()); // Usar el número real de perfiles


    if (totalPerfiles > 0) {
        // Calcular ancho total ocupado por perfiles y separaciones
        float totalWidth = (totalPerfiles * perfilWidth) + ((totalPerfiles - 1) * separacion);

        // Calcular inicio X para centrar los perfiles horizontalmente
        float startX = (1280.0f - totalWidth) / 2.0f + (perfilWidth / 2.0f); // Desplaza para centrar el origen

        float startY = 300.0f; // Centrado verticalmente

        for (int i = 0; i < totalPerfiles; i++) {
            float xPos = startX + i * (perfilWidth + separacion); // Calcula la posición en X para cada perfil
            float yPos = startY;

            PosIsMouseOver[i] = sf::Vector2f(startX, startY +270);
            // Posicionar elementos
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
   //std::cout << "\n77";
    int indexMouseOver=-1;
    while (window->isOpen()&& !seleccionlista) {
        sf::Event event;
        while (window->pollEvent(event)) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
            sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                renderTexture.clear();
                renderTexture.draw(spriteFondoGame);
                for (int i = 0; i < UsuariosEleccion.size(); i++) {
                    renderTexture.draw(PlayersSteal[UsuariosEleccion[i]].NamePlayer);
                    renderTexture.draw(PlayersSteal[UsuariosEleccion[i]].boxPlayer);
                    renderTexture.draw(PlayersSteal[UsuariosEleccion[i]].MarcoPlayer);
                    renderTexture.draw(PlayersSteal[UsuariosEleccion[i]].AvatarPlayer);
                }
                renderTexture.draw(spriteX);
                renderTexture.draw(overlay);
                Menup.MenuSalir();
            }
            indexMouseOver = -1;
            for (int i = 0; i < UsuariosEleccion.size(); i++) {

                if (isMouseOver[i].getGlobalBounds().contains(mousePosFloat)) {
                    
                    indexMouseOver = i;
                    SpritebottonRobar.setPosition(PosIsMouseOver[i]);
                    
                }
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (SpritebottonRobar.getGlobalBounds().contains(mousePosFloat)) {

                    playClickSound();
                    client.networkMessage.stealPlayer(UsuariosEleccion[indexMouseOver]);
                    seleccionlista = true;

                }
               

            }

            
        }

        window->clear();
        window->draw(spriteFondoGame);

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
       //std::cout << "\n6";
        // Dibujar otros elementos
        window->draw(SlectingPlayer);
   
        window->display();
    }
}