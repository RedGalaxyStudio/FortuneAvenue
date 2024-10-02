#ifndef INICIAUSER_HPP
#define INICIAUSER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <thread>
#include <vector>
#include "TextBox.hpp"
#include "ResourceGlobal.hpp"

class IniciaUser {
public:
    IniciaUser(sf::RenderWindow& windowRef);
    ~IniciaUser();

    void Resource();       // Carga de recursos (texturas, sonidos, etc.)
    void Update();         // Lógica principal del juego
    void IniciAcion();
    void saveSelectedAvatar();
    void loadSelectedAvatar();
private:
    sf::RenderWindow& window;

    // Texturas y sprites
    sf::Texture textureLogoJuego;
    sf::Sprite spriteLogoJuego;
    sf::CircleShape* selectedAvatar = nullptr; // Avatar seleccionado
    sf::Sprite SpriteFondoMenu;
    sf::Vector2i mousePosition;
    sf::Vector2f mousePosFloat;

    int currentIndex;  // Índice de avatares visibles

    // Sonidos
    //sf::SoundBuffer FondoBuffer;
    //sf::Sound FondoSound;
    //bool soundOne;
    sf::Texture sharedTexture; // Textura compartida para los avatares
    // Caja de texto (TextBox)
    TextBox textBox;  // Usar TextBox como miembro de IniciaUser
};

#endif // IniciaUser_HPP
