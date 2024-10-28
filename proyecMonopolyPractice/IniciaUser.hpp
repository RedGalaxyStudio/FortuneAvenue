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
    void loadAvatars();
private:
    sf::RenderWindow& window;

    std::vector<sf::Texture> avatarTextures;
    std::vector<std::string> textureAvatarsFilePath;
    // Texturas y sprites
    sf::Texture ckeck;
    sf::Sprite spriteCkeck;
    sf::CircleShape* selectedAvatar = nullptr; // Avatar seleccionado
    sf::Sprite SpriteFondoMenu;
    sf::Sprite SpriteFondoMenuAvar;
    sf::Texture TextureFondoMenuAvar;
    sf::Vector2i mousePosition;
    sf::Vector2f mousePosFloat;

    int currentIndex;  // Índice de avatares visibles

    TextBox textBox;  // Usar TextBox como miembro de IniciaUser
};

#endif // IniciaUser_HPP

