#include "ResourceGame.hpp"
#include "../../core/ResourceGlobal.hpp"
#include "../../ui/ResourceGeneral.hpp"


sf::Texture &textureBoxPerfil= textureBox;
std::vector <MensajeMSG> Mensajes;
bool Resourceready=false;
MensajeMSG PlantillaMensajeR;
std::vector<sf::Texture> TextureCasa;
sf::Texture TextureCash;
sf::Texture TextureHome;
sf::Font &fontUserPerfil=fontUser ;
std::vector<sf::Texture> avatarTextures;
sf::Texture TextureMarco;

int NumPlayers;

std::string nameUser;
sf::View view; 
sf::Clock reloj;
std::vector<sf::Sprite> rastro;
sf::Sprite spriteMapa;
std::vector<sf::Sprite> pieces;
int previousSelectionIndex[4];
std::vector<sf::Texture> piecesTextures;
sf::Texture CheckTexturesOn;
sf::Texture CheckTexturesOff;
std::string Code;
sf::Sprite SpriteArrowDer;
bool animacionRuleta;
sf::Sprite SpriteArrowArriba;
sf::Sprite SpriteArrowAbajo;
bool server;
bool rolldiceJugador;
std::string username;
std::vector<char> image;
bool chatOn = false;

 bool nular;
int conteosuel;
sf::Sprite SpriteArrowIzq;
bool SelectingPiece = false; 
bool Game = false;     
std::vector<PlayerInfo> playerInfos;
std::vector<PlayerGame> playersGame;
bool espera;
bool giroRule;
int CplayerIndex = -1;
int Opcioncami;

bool userRuleta;
bool userImpuesto;
bool userCasa;

std::vector<int> UsuariosActivos;

bool turn;
bool otherturn;
bool turn_dado;
bool turn_ruleta;
bool turn_casa;
bool turn_impuesto;
bool turn_Moviendo;
bool eventoActivo;
bool isSpinning;
int IndexTurn;
bool ruleta_draw;
bool impuesto_draw;
bool casa_draw;

bool ReturnMenu = false;
bool ReturnPieces = false;

bool ChatOn = false;

void loadResourceGame(){

	if (!TextureMarco.loadFromFile("assets/image/Avatars/MarcoTexture.png")) return;

	fontUserPerfil = fontUser;
	espera=false;
}
bool salirX(sf::Texture Pregunta, sf::RenderWindow* window, Client*cliente){
    sf::Sprite renderedSprite;

    sf::Sprite SpriteConfirmarSalir;
    sf::RectangleShape overlay(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
    overlay.setFillColor(sf::Color(0, 0, 0, 10));

    SpriteConfirmarSalir.setTexture(Pregunta);
    sf::Shader Blur;
    TextureBotonSiOn.loadFromFile("assets/image/Button/BotonSiOn.png");
    TextureBotonSiOff.loadFromFile("assets/image/Button/BotonSiOff.png");
    TextureBotonNoOn.loadFromFile("assets/image/Button/BotonNoOn.png");
    TextureBotonNoOff.loadFromFile("assets/image/Button/BotonNoOff.png");
    Blur.loadFromFile("assets/Shaders/blur.frag", sf::Shader::Fragment);
    Blur.setUniform("resolution", sf::Glsl::Vec2(
        static_cast<float>(window->getSize().x),
        static_cast<float>(window->getSize().y)
    ));

    SpriteConfirmarSalir.setPosition(660, 370);
    SpriteConfirmarSalir.setOrigin(340, 240);

    SpriteBotonSi.setPosition(480, 380);


    SpriteBotonNo.setPosition(680, 380);

    ButtonG BotonSi(SpriteBotonSi, TextureBotonSiOff, TextureBotonSiOn);
    ButtonG BotonNo(SpriteBotonNo, TextureBotonNoOff, TextureBotonNoOn);

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
                sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);


                if (SpriteBotonSi.getGlobalBounds().contains(mousePosFloat)) {
                    playClickSound();

                    if (cliente->clientData->running && cliente->peer != nullptr) {
                        cliente->disconnect();
                    }

                    return true;
                }


                if (SpriteBotonNo.getGlobalBounds().contains(mousePosFloat)) {
                    playClickSound();
                    return false;
                }
            }


        }

        currentCursor = &normalCursor;
        sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
        sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);
        BotonSi.update(mousePosFloat, currentCursor, linkCursor, normalCursor);
        BotonNo.update(mousePosFloat, currentCursor, linkCursor, normalCursor);

        window->setMouseCursor(*currentCursor);

        renderedSprite.setTexture(renderTexture.getTexture());
        window->clear();
        window->draw(renderedSprite, &Blur);

        window->draw(SpriteConfirmarSalir);
        window->draw(SpriteBotonSi);
        window->draw(SpriteBotonNo);

        window->display();


    }
    return true;
}
