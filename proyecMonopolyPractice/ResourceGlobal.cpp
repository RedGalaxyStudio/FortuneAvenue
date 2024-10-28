#include "ResourceGlobal.hpp"
#include <fstream>
#include  "nlohmann/json.hpp"
// Definir las texturas y cursores

using json = nlohmann::json;

sf::Text Sesion;
sf::Texture TextureFondoMenu;
sf::Cursor normalCursor;
sf::Cursor linkCursor;
sf::Cursor textCursor;
sf::Cursor moveCursor;
sf::SoundBuffer HoverBuffer;
sf::SoundBuffer ClickBuffer;
std::string nombre;
std::string input;
sf::Sound HoverSound;  
sf::Sound ClickSound;  
sf::Cursor* currentCursor;
sf::Texture TextureMuted;
sf::Texture TextureMedium;
sf::Texture TextureHigh;
sf::RenderTexture renderTexture;
sf::Texture textureXOn;
sf::Texture textureXOff;
sf::Sprite spriteX;
std::vector<sf::CircleShape> avatars;


sf::CircleShape selectedAvatarCopy; // Copia del avatar seleccionado

sf::Texture textureBox;
sf::Sprite box;
sf::Font fontUser;
std::wstring Token;
std::string email;
std::string id;
std::string pictureUrl;
sf::RectangleShape overlay;
ButtonG* botonX = nullptr; // Definición de la variable
sf::Texture TextureAvatarSelec;
sf::Texture sharedTexture; // Textura compartida para los avatares
sf::Texture TextureBotonSiOn;
sf::Texture TextureBotonSiOff;
sf::Sprite SpriteBotonSi;

sf::Texture TextureBotonNoOn;
sf::Texture TextureBotonNoOff;
sf::Sprite SpriteBotonNo;
std::string TextureAvatarPath;
sf::Texture Texrecua;
sf::Sprite recua;




// Función para cargar la textura del fondo del menú
void loadTextures() {
    if (!TextureFondoMenu.loadFromFile("resource/texture/Fondos/fondomenu.png")) return;
    if (!textureXOn.loadFromFile("resource/texture/Button/XOn.png")) return;
    if (!textureXOff.loadFromFile("resource/texture/Button/XOff.png")) return;
    if (!TextureBotonSiOn.loadFromFile("resource/texture/Button/BotonSiOn.png")) return;
    if (!TextureBotonSiOff.loadFromFile("resource/texture/Button/BotonSiOff.png")) return;
    if (!TextureBotonNoOn.loadFromFile("resource/texture/Button/BotonNoOn.png")) return;
    if (!TextureBotonNoOff.loadFromFile("resource/texture/Button/BotonNoOff.png")) return;
    spriteX.setTexture(textureXOff);
    SpriteBotonNo.setTexture(TextureBotonNoOff);   
    SpriteBotonSi.setTexture(TextureBotonSiOff);
    // Ahora que las texturas están cargadas, se puede crear el botón
    botonX = new ButtonG(spriteX, textureXOff, textureXOn);
    if (!fontUser.loadFromFile("resource/fonts/ARCADEPI.ttf")) {
        std::cerr << "Error loading font\n";
    }
    if (!textureBox.loadFromFile("resource/texture/Button/rectanguloEncendido.png")) return;
    box.setTexture(textureBox);
    box.setOrigin(125,40);
    
}

void loadSounds(){

    if (!HoverBuffer.loadFromFile("resource/sounds/HoverBoton.wav")) return;
    if (!ClickBuffer.loadFromFile("resource/sounds/ClickBoton.wav")) return;

    HoverSound.setBuffer(HoverBuffer);
    ClickSound.setBuffer(ClickBuffer);

};

void loadVolumenIcon() {

    if (!TextureMuted.loadFromFile("resource/texture/Button/VolumeMuted.png")) return;
    if (!TextureMedium.loadFromFile("resource/texture/Button/VolumeMedium.png")) return;
    if (!TextureHigh.loadFromFile("resource/texture/Button/VolumeHigh.png")) return;
}


// Función para cargar los cursores desde una imagen o textura
void loadCursors() {
    sf::Image cursorNormal;
    if (!cursorNormal.loadFromFile("resource/texture/Cursor/normal-select-0.png")) return;

    sf::Image cursorLink;
    if (!cursorLink.loadFromFile("resource/texture/Cursor/link-select-0.png")) return;

    sf::Image cursorText;
    if (!cursorText.loadFromFile("resource/texture/Cursor/text-select-0.png")) return;

    sf::Image cursorMove;
    if (!cursorMove.loadFromFile("resource/texture/Cursor/move-0.png")) return;

    // Tamaño de cada cursor (por ejemplo 32x32)
    sf::Vector2u cursorSize(32, 32);

    // Crear cursores
    if (!normalCursor.loadFromPixels(cursorNormal.getPixelsPtr(), cursorSize, sf::Vector2u(0, 0))) return;

    if (!linkCursor.loadFromPixels(cursorLink.getPixelsPtr(), cursorSize, sf::Vector2u(0, 0))) return;

    if (!textCursor.loadFromPixels(cursorText.getPixelsPtr(), cursorSize, sf::Vector2u(0, 0))) return;

    if (!moveCursor.loadFromPixels(cursorMove.getPixelsPtr(), cursorSize, sf::Vector2u(0, 0))) return;
}
void playClickSound() {
    ClickSound.play();
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void GetUserEmail() {
    // Leer el token desde el archivo
    std::wifstream tokenFile("token.txt");
    std::wstring token;
    if (tokenFile.is_open()) {
        std::getline(tokenFile, token);
        tokenFile.close();
    }
    else {
        std::cerr << "Error al abrir el archivo para leer el token." << std::endl;
        return;  // Salir de la función si no se puede leer el token
    }

    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://www.googleapis.com/oauth2/v2/userinfo";
        std::string bearerToken = "Bearer ";
        for (wchar_t wc : token) {
            if (wc < 128) { // Solo convertir caracteres ASCII
                bearerToken += static_cast<char>(wc);
            }
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, ("Authorization: " + bearerToken).c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        else {
            // Parsear el JSON recibido
            try {
                json jsonData = json::parse(readBuffer);

                // Extraer el campo "email"
                email = jsonData["email"];
                std::cout << "Correo del usuario: " << email << std::endl;

                // Puedes extraer otros campos como:
                id = jsonData["id"];
                 pictureUrl = jsonData["picture"];
                bool isVerified = jsonData["verified_email"];

                std::cout << "ID del usuario: " << id << std::endl;
                std::cout << "Imagen del usuario: " << pictureUrl << std::endl;
                std::cout << "Correo verificado: " << (isVerified ? "Sí" : "No") << std::endl;
            }
            catch (const std::exception& e) {
                std::cerr << "Error al analizar el JSON: " << e.what() << std::endl;
            }
        }

        // Limpiar los encabezados
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}