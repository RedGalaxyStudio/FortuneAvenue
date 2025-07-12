#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <map>

class ResourceLoader {
public:
    ResourceLoader();

    ~ResourceLoader();

    // Carga todos los recursos al inicio
    void loadAllResources();

    // Métodos para obtener recursos
     sf::Texture &getTexture(const std::string &name);

     sf::Font &getFont(const std::string &name);

     sf::SoundBuffer &getSound(const std::string &name);

     sf::Shader &getShader(const std::string &name);

private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;
    std::map<std::string, sf::SoundBuffer> sounds;
    std::map<std::string, sf::Shader> shaders;

    // Métodos privados de carga
    void loadTexture(const std::string &name, const std::string &filepath);

    void loadFont(const std::string &name, const std::string &filepath);

    void loadSound(const std::string &name, const std::string &filepath);

    void loadShader(const std::string &name, const std::string &filepath);
};

#endif
