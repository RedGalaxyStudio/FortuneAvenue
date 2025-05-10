#include "ResourceGameO.hpp"
#include "../../core/ResourceGlobal.hpp"
#include "../../ui/ResourceGeneral.hpp"


 bool giroActivoO=false;

float initialSpeedActiO;
float decelerationRateActiO;
sf::Texture &textureBoxPerfilOff= textureBox;
sf::Texture textureBoxPerfilOn;
bool BotTurn=false;
std::vector<sf::Texture> TextureHouse; //texturecasa
sf::Texture TextureMoney1; //texturecash
sf::Texture TextureBuilding; //texturehome
sf::Font &fontUserProfile =fontUser ; //&fontUserPerfil
std::vector<sf::Texture> avatarTexturesOff; 
sf::Texture TextureFrame; //textureMarco
sf::Sprite spriteBackground;
int NumberPlayers;
std::string namePlayer; 
sf::View vision; // Declarar la vista //view
sf::Clock watch; //reloj
std::vector<sf::Sprite> trace;
sf::Sprite MapSprite;
std::vector<sf::Sprite> piecesOff;
//int previousSelectionIndex[4];
std::vector<sf::Texture> pieceShape;
sf::Texture CheckOn;
sf::Texture CheckOff; 
std::string Code1; //code

bool rouletteAnimation; //animacionRuleta

bool plataform; //server
bool rolldicePlayer;
std::string playerName; //username
std::vector<char> image1; //image Store image data directly.
 bool zero;
int countsalary;
bool SelectorPieces = false; // Inicialmente en seleccion de pieza
bool GamePlay = false;        // No en juego al principio
std::vector<PlayerInformation> playerGameInfo;
std::vector<PlayerGameOff> playerGameOff;
bool wait;
bool turnRule;
int CplayerIndex1 = -1;
int RoadOption;

bool userRulette;
bool userTax;
bool userHouse;


int customIndex = 0;
std::vector<int> ActiveUsers;

bool firstTurn;
bool secondTurn;
bool turn_dice;
bool turn_diceB;
bool turn_roulette;
bool turn_house;
bool turn_Tax;
bool turn_Move;
bool activeEvent;
bool isSpinningOff; 
int IndexTurn1;
bool draw_roulette;
bool draw_tax;
bool draw_house;

GameManager GM;

void loadResourceGameO() {

	if (!TextureFrame.loadFromFile("assets/image/Avatars/MarcoTexture.png")) return;

	fontUserProfile = fontUser;
	wait = false;
	
	if (!TextureBuilding.loadFromFile("assets/image/Game/casa.png")) return;
	if (!TextureMoney1.loadFromFile("assets/image/Game/cash.png")) return;
	if (!CheckOn.loadFromFile("assets/image/Game/check1on.png")) return;
	if (!CheckOff.loadFromFile("assets/image/Game/check1off.png")) return;

}



bool salirXoff(sf::Texture Pregunta, sf::RenderWindow* window) {
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
void resetGameResourcesO() {
    // Recursos gráficos
    TextureHouse.clear();
    pieceShape.clear();
    piecesOff.clear();
    trace.clear();

    // Texturas
    //TextureCash = sf::Texture();
    //TextureHome = sf::Texture();
    TextureFrame = sf::Texture();
    // CheckTexturesOn = sf::Texture();
    // CheckTexturesOff = sf::Texture();

     // Sprites
    MapSprite = sf::Sprite();
    // Font y texturas referenciadas (si están ligadas por referencia, no se pueden reiniciar directamente aquí)
    // fontUserPerfil;      <-- Referencia, cuidado con reiniciarla aquí
    // textureBoxPerfil;    <-- Referencia también

    // Variables de estado
 //   Resourceready = false;

    NumberPlayers = 0;
    userRulette = false;
    userTax = false;
    userHouse = false;
    countsalary = 0;
    zero = false;
   // rolldiceJugador = false;
   // ReturnMenu = false;
   // ReturnPieces = false;
   // chatOn = false;
   // ChatOn = false;
    SelectorPieces = false;
    GamePlay = false;
    rouletteAnimation = false;
    wait = false;
    turnRule = false;
    IndexTurn1 = 0;
    draw_roulette = false;
    draw_tax = false;
    draw_house = false;
    firstTurn = false;
    secondTurn = false;
    turn_dice = false;


    turn_roulette = false;
    turn_house = false;
    turn_Tax = false;
    turn_Move = false;
    activeEvent = false;
    RoadOption = 0;
    Code1.clear();
    //nameUser.clear();

    // Índices previos
    for (int& index : previousSelectionIndex) {
        index = -1;
    }

    // Usuarios activos
    ActiveUsers.clear();

    // Jugadores
    for (auto& info : playerGameInfo) {
        info.reset();
    }

    for (auto& gamePlayer : playerGameOff) {
        gamePlayer.reset();
    }

    playerGameInfo.clear();
    playerGameOff.clear();

    // Mensajes
   // Mensajes.clear();
    //PlantillaMensajeR = MensajeMSG();
}