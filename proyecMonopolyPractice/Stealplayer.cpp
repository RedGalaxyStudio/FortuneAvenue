#include "Stealplayer.hpp"
#include <iostream>

// Constructor
Stealplayer::Stealplayer(sf::RenderWindow* window, std::vector<int> UsuariosElec) : window(window), UsuariosEleccion(UsuariosElec) {

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
    if (!UsuariosEleccion.empty()) { // Asegúrate de que el vector no esté vacío
        UsuariosEleccion.erase(UsuariosEleccion.begin()); // Elimina el primer elemento
    }
}
void Stealplayer::update() {



    // Configurar perfiles
    float perfilWidth = 200.0f; // Ancho estimado de cada perfil
    float separacion = 20.0f;   // Espaciado entre perfiles
    int totalPerfiles = UsuariosEleccion.size(); // Usar el número real de perfiles


    if (totalPerfiles > 0) {
        // Calcular ancho total ocupado por perfiles y separaciones
        float totalWidth = (totalPerfiles * perfilWidth) + ((totalPerfiles - 1) * separacion);

        // Calcular inicio X para centrar los perfiles horizontalmente
        float startX = (1280.0f - totalWidth) / 2.0f + (perfilWidth / 2.0f); // Desplaza para centrar el origen

        float startY = 360.0f; // Centrado verticalmente

        for (int i = 0; i < totalPerfiles; i++) {
            float xPos = startX + i * (perfilWidth + separacion); // Calcula la posición en X para cada perfil
            float yPos = startY;
            // Posicionar elementos
            playersGame[UsuariosEleccion[i]].NamePlayer.setPosition(xPos, startY + 70);
            playersGame[UsuariosEleccion[i]].boxPlayer.setPosition(xPos, startY + 70);
            playersGame[UsuariosEleccion[i]].AvatarPlayer.setPosition(xPos, startY);
            std::cout << "\n xPos" << xPos << "startY" << startY;
            playersGame[UsuariosEleccion[i]].MarcoPlayer.setPosition(xPos, startY);

            if (playersGame[UsuariosEleccion[i]].PieceSelect.getTexture() != nullptr) {
                playersGame[UsuariosEleccion[i]].PieceSelect.setScale(2.0f, 2.0f);
                sf::FloatRect pieceSelectBounds = playersGame[UsuariosEleccion[i]].PieceSelect.getGlobalBounds();
                playersGame[UsuariosEleccion[i]].PieceSelect.setOrigin(pieceSelectBounds.width / 2.0f, pieceSelectBounds.height / 2.0f);
                playersGame[UsuariosEleccion[i]].PieceSelect.setPosition(xPos + (pieceSelectBounds.width / 2.0f), startY + 240);
            }

            sf::FloatRect moneyBounds = playersGame[UsuariosEleccion[i]].Money.getGlobalBounds();
            playersGame[UsuariosEleccion[i]].Money.setOrigin(moneyBounds.width / 2.0f, moneyBounds.height / 2.0f);
            playersGame[UsuariosEleccion[i]].Money.setPosition(xPos, startY + 140);

           
        }
    }
    bool seleccionlista = false;


    while (window->isOpen()&& !seleccionlista) {
        sf::Event event;
        while (window->pollEvent(event)) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
            sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                renderTexture.clear();
                renderTexture.draw(spriteFondoGame);
                for (int i = 0; i < playersGame.size(); i++) {
                    renderTexture.draw(playersGame[UsuariosEleccion[i]].NamePlayer);
                    renderTexture.draw(playersGame[UsuariosEleccion[i]].boxPlayer);
                    renderTexture.draw(playersGame[UsuariosEleccion[i]].MarcoPlayer);
                    renderTexture.draw(playersGame[UsuariosEleccion[i]].AvatarPlayer);
                }
                renderTexture.draw(spriteX);
                renderTexture.draw(overlay);
                Menup.MenuSalir();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                
                for (int i = 0; i < UsuariosEleccion.size(); i++) {
        
                    if (playersGame[UsuariosEleccion[i]].boxPlayer.getGlobalBounds().contains(mousePosFloat)) {
                           playClickSound();
                           client.robarUser(UsuariosEleccion[i]);
                    }
                }
         
            }


            
        }

        window->clear();
        window->draw(spriteFondoGame);

        for (int i = 0; i < UsuariosEleccion.size(); i++) {
            window->draw(playersGame[UsuariosEleccion[i]].NamePlayer);
            window->draw(playersGame[UsuariosEleccion[i]].boxPlayer);
            window->draw(playersGame[UsuariosEleccion[i]].AvatarPlayer);
            window->draw(playersGame[UsuariosEleccion[i]].MarcoPlayer);
            window->draw(playersGame[UsuariosEleccion[i]].Money);
            window->draw(playersGame[UsuariosEleccion[i]].PieceSelect);
        }
        // Dibujar otros elementos
        window->draw(SlectingPlayer);
        window->display();
    }
}




