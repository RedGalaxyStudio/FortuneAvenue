#include "ResourceLoader.h"
#include <iostream>

ResourceLoader::ResourceLoader() {
    // Constructor, si necesitas inicializar algo
}

ResourceLoader::~ResourceLoader() {
    // Destructor
}

void ResourceLoader::loadAllResources() {
  // Fondo y logo
    loadTexture("menuBackgroundTexture", "assets/image/Fondos/fondomenu.png"); // TextureFondoMenu
    loadTexture("logoFortuneAvenueTexture", "assets/image/Logos/logojuego14.png"); // textureLogoFortuneAvenue

// Botones principales del menú
loadTexture("playButtonOffTexture", "assets/image/Button/BotonJugarOff.png"); // TextureBotonJugarOff
loadTexture("playButtonOnTexture", "assets/image/Button/BotonJugarOn.png");   // TextureBotonJugarOn
loadTexture("optionsButtonOffTexture", "assets/image/Button/BotonOpcionesOff.png"); // TextureBotonOpcionesOff
loadTexture("optionsButtonOnTexture", "assets/image/Button/BotonOpcionesOn.png");   // TextureBotonOpcionesOn
loadTexture("exitButtonOffTexture", "assets/image/Button/BotonSalirOff.png"); // TextureBotonSalirOff
loadTexture("exitButtonOnTexture", "assets/image/Button/BotonSalirOn.png");   // TextureBotonSalirOn
loadTexture("aboutButtonOnTexture", "assets/image/Button/AcercaDeOn.png");    // textureAcercaDeOn
loadTexture("aboutButtonOffTexture", "assets/image/Button/AcercaDeOff.png");  // textureAcercaDeOff
loadTexture("instructionsButtonOnTexture", "assets/image/Button/instruccionesencendido.png"); // textureInstruccionesOn
loadTexture("instructionsButtonOffTexture", "assets/image/Button/instruccionesapagado.png");  // textureInstruccionesOff

// Botones Sí / No
loadTexture("yesButtonOnTexture", "assets/image/Button/BotonSiOn.png");   // TextureBotonSiOn
loadTexture("yesButtonOffTexture", "assets/image/Button/BotonSiOff.png"); // TextureBotonSiOff
loadTexture("noButtonOnTexture", "assets/image/Button/BotonNoOn.png");    // TextureBotonNoOn
loadTexture("noButtonOffTexture", "assets/image/Button/BotonNoOff.png");  // TextureBotonNoOff

// Botón de cerrar (X)
loadTexture("closeButtonOnTexture", "assets/image/Button/XOn.png");   // textureXOn
loadTexture("closeButtonOffTexture", "assets/image/Button/XOff.png"); // textureXOff

// Flechas para instrucciones
loadTexture("instructionArrowRightTexture", "assets/image/Button/flechapagder.png"); // Textureflechainstder
loadTexture("instructionArrowLeftTexture", "assets/image/Button/flechapagizq.png");  // Textureflechainstizq

// Confirmaciones
loadTexture("confirmExitTexture", "assets/image/Button/boton2.png");        // TextureConfirmarSalir
loadTexture("confirmExitRoomTexture", "assets/image/Button/ExitSala.png");  // TextureConfirmarSalirSala
loadTexture("confirmExitGameTexture", "assets/image/Button/boton2.png");    // TextureConfirmarSalirPartida

// Caja de opciones/configuración
loadTexture("settingsBoxTexture", "assets/image/Button/rectanguloEncendido.png"); // textureBox
// Botón de edición
loadTexture("editButtonTexture", "assets/image/Nueva carpeta/edit22.png"); // TextureEditButton
//
// Fuentes
loadFont("userFont", "assets/fonts/ARCADEPI.ttf");//Fuente
    loadFont("fontMenu", "assets/fonts/Pix.ttf");

// Sonidos
//loadSound("menuMusic", "assets/sounds/MenuB.wav"); // MenuMusicFondo
//loadSound("selectionMusic", "assets/sounds/SelectingPieces.wav"); // SelectingMusicFondo

}

void ResourceLoader::loadTexture(const std::string& name, const std::string& filepath) {
    sf::Texture texture;
    if (!texture.loadFromFile(filepath)) {
        std::cerr << "Error al cargar textura: " << filepath << std::endl;
    } else {
        textures[name] = texture;  // Copia el objeto texture
    }
}

void ResourceLoader::loadFont(const std::string& name, const std::string& filepath) {
    sf::Font font;
    if (!font.loadFromFile(filepath)) {
        std::cerr << "Error al cargar fuente: " << filepath << std::endl;
    } else {
        fonts[name] = font;
    }
}

void ResourceLoader::loadSound(const std::string& name, const std::string& filepath) {
    sf::SoundBuffer soundBuffer;
    if (!soundBuffer.loadFromFile(filepath)) {
        std::cerr << "Error al cargar sonido: " << filepath << std::endl;
    } else {
        sounds[name] = soundBuffer;
    }
}

void ResourceLoader::loadShader(const std::string& name, const std::string& filepath) {
    sf::Shader shader;

}

sf::Texture& ResourceLoader::getTexture(const std::string& name) {
    return textures.at(name);
}

 sf::Font& ResourceLoader::getFont(const std::string& name) {
    return fonts.at(name);
}

 sf::SoundBuffer& ResourceLoader::getSound(const std::string& name) {
    return sounds.at(name);
}

 sf::Shader& ResourceLoader::getShader(const std::string &name) {
    return shaders.at(name);
}