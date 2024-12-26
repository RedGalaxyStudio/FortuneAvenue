#include <SFML/Graphics.hpp>
#include "IniciaUser.hpp"
#include "TextBox.hpp"
#include <SFML/Audio.hpp>
#include "Scrollbar.hpp"
#include <string>
#include "ResourceGlobal.hpp"
#include "menuP.hpp"
#include "ObjetosGlobal.hpp"
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;


IniciaUser::IniciaUser(sf::RenderWindow& windowRef)
    : window(windowRef), currentIndex(0) {  
    Resource();
    loadAvatars();
}
IniciaUser::~IniciaUser() {
}
void IniciaUser::Resource() {
    SpriteFondoMenu.setTexture(TextureFondoMenu);

    conteosuel = 0;
}
void IniciaUser::Update() {

    if (!std::filesystem::exists("perfil.json")) {
        if (!ckeck.loadFromFile("resource/texture/Avatars/cheeke2.png")) return;
        spriteCkeck.setTexture(ckeck);
        if (!TextureFondoMenuAvar.loadFromFile("resource/texture/Fondos/fondomenuAvar.png")) return;
        SpriteFondoMenuAvar.setTexture(TextureFondoMenuAvar);
        loadAvatars();
        IniciAcion();
    }else{
        loadSelectedAvatar();
    }
    
}
void IniciaUser::IniciAcion(){
    spriteCkeck.setPosition(850, 70);

    
    float baseXPos = 92.0f;
    float baseYPos = 472.0f;
    
    

    float deltaScroll = 0.0f;
    float scrollStep = 10.0f; // Para el desplazamiento con las teclas
    const float avatarWidth = 128.0f;
    const float avatarHeight = 128.0f;
    const float avatarSeparation = 28.0f;
    const float visibleAreaHeight = 248.0f;
    const float maxScrollOffset = 156.0f;  

    float widthSeparation = avatarWidth + avatarSeparation;
    float heightSeparation = avatarHeight + avatarSeparation;

    recua.setPosition(400, 112);
    TextBox textBox(496, 50, "Ingresa tu nombre: ");  
    textBox.setPosition(496, 50);
    
    const float totalContentHeight = 440.0f; 
    const float scrollbarHeight = 340.0f;

    
    float proportion = visibleAreaHeight / totalContentHeight;
    float thumbHeight = scrollbarHeight * proportion;

    
    const float minThumbHeight = 14.0f; 
    thumbHeight = std::max(thumbHeight, minThumbHeight);

    
    Scrollbar scrollbar(340, thumbHeight, 14);  

    scrollbar.setPosition(1260, 340);  

   
 
    selectedAvatarCopy.setPosition(400, 112);  
    for (int i = 0; i < avatars.size(); i++) {
        sf::Vector2f pos = avatars[i].getPosition();
     
    }
    float avatarYOffset = 0.0f; 

    while (window.isOpen()) {
        mousePosition = sf::Mouse::getPosition(window);
        mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                renderTexture.clear(sf::Color::Transparent);
                renderTexture.draw(SpriteFondoMenu);
                for (int i = 0; i < avatars.size(); ++i) {
                    renderTexture.draw(avatars[i]);
                }
                renderTexture.draw(SpriteFondoMenuAvar);
                if (selectedAvatar != nullptr) {
                    renderTexture.draw(selectedAvatarCopy);  
                }
                textBox.Prinf();  

                scrollbar.Prinft();
                renderTexture.draw(recua);
                renderTexture.draw(spriteCkeck);
                renderTexture.draw(overlay);
                renderTexture.display();
                Menup.MenuSalir();
            }

            scrollbar.handleEvent(event, window);
            avatarYOffset = scrollbar.getScrollOffset();
           // scrollbar.evento(event);
            if (event.type == sf::Event::MouseWheelScrolled) {
                
                scrollbar.update(event.mouseWheelScroll.delta);  
                avatarYOffset = scrollbar.getScrollOffset();

            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Down) {
                    deltaScroll = 1.0f; // Desplazamiento hacia abajo
                    scrollbar.update(deltaScroll);
                    avatarYOffset = scrollbar.getScrollOffset();
                }
                else if (event.key.code == sf::Keyboard::Up) {
                    deltaScroll = -1.0f; // Desplazamiento hacia arriba
                    scrollbar.update(deltaScroll);
                    avatarYOffset = scrollbar.getScrollOffset();
                }
            }


            if (avatarYOffset > maxScrollOffset) {
                avatarYOffset = maxScrollOffset;  
            }
            else if (avatarYOffset < 0) {
                avatarYOffset = 0;  
            }

            if (avatarYOffset != 0) {
                std::vector<sf::FloatRect> avatarBounds(avatars.size());
                for (int i = 0; i < avatars.size(); ++i) {
                    int column = i % 8;  
                    int row = i / 8;     

                    float xPos = baseXPos + column * widthSeparation;

                    float yPos = (baseYPos + row * heightSeparation) - avatarYOffset;

                    avatarBounds[i] = sf::FloatRect(xPos, yPos, avatars[i].getGlobalBounds().width, avatars[i].getGlobalBounds().height);

                    avatars[i].setPosition(xPos, yPos);

                }
            }
                
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                
                if (spriteCkeck.getGlobalBounds().contains(mousePosFloat)) {
                    playClickSound();
                    saveSelectedAvatar();
                    Menup.MenuPrincipal();
                }


                sf::CircleShape* newSelection = nullptr;


                

                for (int i = 0; i < avatars.size(); ++i) {

                    if (avatars[i].getGlobalBounds().contains(mousePosFloat)) {
                        newSelection = &avatars[i];
                        break;
                    }
                }

                
                if (spriteX.getGlobalBounds().contains(mousePosFloat)) {
                    playClickSound();
                    Menup.MenuPrincipal();
                }
                if (newSelection != nullptr) {  
                    if (newSelection != selectedAvatar) {
                        if (selectedAvatar) {
                            selectedAvatar->setOutlineColor(sf::Color::Transparent);  
                            selectedAvatar->setOutlineThickness(0);
                        }
                        if (newSelection) {
                            newSelection->setOutlineColor(sf::Color::Black);  
                            newSelection->setOutlineThickness(4);
                         
                            selectedAvatarCopy.setTexture(newSelection->getTexture());  
                        }
                        selectedAvatar = newSelection;
                    }
                }
            }
                    
                    input1=textBox.handleInput(event,11);
        }
        window.clear();
        window.draw(SpriteFondoMenu);
      
        for (int i = 0; i < avatars.size(); ++i) {

                    sf::Vector2f pos = avatars[i].getPosition();

                    window.draw(avatars[i]);
        }

               
               
                window.draw(SpriteFondoMenuAvar);
                
                if (selectedAvatar != nullptr) {
                    window.draw(selectedAvatarCopy);  
                }  
                textBox.draw(window);  

                scrollbar.draw(window);
                window.draw(recua);
                window.draw(spriteCkeck);
                window.display();
    }
}
void IniciaUser::saveSelectedAvatar(){
    if (selectedAvatar != nullptr) {

        int selectedIndex = -1;
        for (int i = 0; i < avatars.size(); ++i) {
            if (&avatars[i] == selectedAvatar) {
                selectedIndex = i;
                break;
            }
        }


        if (selectedIndex != -1) {
       
            json avatarData;
            avatarData["selected_avatar_path"] = textureAvatarsFilePath[selectedIndex];
            
           //std::cout << "\ninput1:" << input1;
            avatarData["username"] = input1;  

         
            std::ofstream outFile("perfil.json");


            if (outFile.is_open()) {
                outFile << avatarData.dump(4);  
                outFile.close();
            }
        }
    }
}
void IniciaUser::loadSelectedAvatar() {


    std::ifstream inFile("perfil.json");
    if (inFile.is_open()) {
        json avatarData;
        inFile >> avatarData;
        inFile.close();

        TextureAvatarPath = avatarData["selected_avatar_path"];
        input1 = avatarData["username"];  

        
        if (!TextureAvatarSelec.loadFromFile(TextureAvatarPath)) loadAvatars();

        selectedAvatarCopy.setTexture(&TextureAvatarSelec);  
    }
}

void IniciaUser::loadAvatars(){
    
    int avatarCount = 20;  
    avatars.resize(avatarCount);
    avatarTextures.resize(avatarCount);
    textureAvatarsFilePath.resize(avatarCount);



    for (int i = 0; i < avatarCount; i++) {

        textureAvatarsFilePath[i] = "resource/texture/Avatars/avatar" + std::to_string(i) + ".png";

        if (!avatarTextures[i].loadFromFile(textureAvatarsFilePath[i]))
            return;

        float radio = avatarTextures[i].getSize().x / 2.0f;
        avatars[i].setRadius(radio);
        avatars[i].setTexture(&avatarTextures[i]);
        avatars[i].setOrigin(radio, radio);


    }

    for (int i = 0; i < avatars.size(); i++) {
        int row = i / 8;  
        int col = i % 8;  

        float x = 92.0f + col * 156.0f;  
        float y = 472.0f + row * 156.0f;  
      
        avatars[i].setPosition(x, y);
    }
    if (!sharedTexture.loadFromFile("resource/texture/Avatars/Vacio.jpg")) return;

    selectedAvatarCopy.setRadius(64);  
    selectedAvatarCopy.setTexture(&sharedTexture);  
    selectedAvatarCopy.setOrigin(64, 64);  

    Texrecua.loadFromFile("resource/texture/Avatars/recua.png");
    recua.setTexture(Texrecua);
    recua.setOrigin(65, 65);
}