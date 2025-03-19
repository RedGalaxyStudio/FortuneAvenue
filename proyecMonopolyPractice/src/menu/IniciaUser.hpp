#ifndef INICIAUSER_HPP
#define INICIAUSER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <thread>
#include <vector>
#include "../ui/TextBox.hpp"
#include "../core/ResourceGlobal.hpp"

class IniciaUser {
public:
    IniciaUser(sf::RenderWindow &windowRef);
    ~IniciaUser();

    void Resource();       
    void Update();       
    void UpdateEdit();
    void IniciAcion();
    void saveSelectedAvatar();
    void loadSelectedAvatar();
    void loadAvatars();
    void fun();
private:
    sf::RenderWindow *window;
    sf::Image originalImage;
    std::vector<sf::CircleShape> avatars;
    std::vector<sf::Texture> avatarTextures;
    std::vector<std::string> textureAvatarsFilePath;
    // Texturas y sprites
    sf::Texture ckeck;
    int selectedIndex = -1;
    sf::Sprite spriteCkeck;
    std::string imagePath;
    std::string projectPath=""; // Guarda la ruta original

    sf::CircleShape* selectedAvatar = nullptr; 
    sf::Sprite SpriteFondoMenu;
    sf::Sprite SpriteFondoMenuAvar;
    sf::Texture TextureFondoMenuAvar;
    sf::Vector2i mousePosition;
    sf::Vector2f mousePosFloat;

    int currentIndex;  

    TextBox textBox; 
};

#endif

