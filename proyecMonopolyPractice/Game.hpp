#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <thread>
#include <vector>
#include "TextBox.hpp"
#include "ResourceGlobal.hpp"

class Game {
public:
    Game(sf::RenderWindow& windowRef);
    ~Game();

    void Resource();       // Carga de recursos (texturas, sonidos, etc.)
    void Update();         // Lógica principal del juego
private:
    sf::RenderWindow& window;

    // Texturas y sprites
    sf::Texture textureLogoJuego;
    sf::Sprite spriteLogoJuego;
    
    sf::Sprite SpriteFondoMenu;
    sf::Vector2i mousePosition;
    sf::Vector2f mousePosFloat;
    // Sonidos
    //sf::SoundBuffer FondoBuffer;
    //sf::Sound FondoSound;
    //bool soundOne;

    // Caja de texto (TextBox)
    TextBox textBox;  // Usar TextBox como miembro de Game
};

#endif // GAME_HPP
