#ifndef RUELTA_HPP
#define RUELTA_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "../../ui/Particles.h"
#include <random>
#include <string>
#include "../../network/Client.hpp"

#define M_PI 3.14159265358979323846

class Ruleta {
public:
    Ruleta(float width, float height, float centerX, float centerY, Client* clienT);
    void draw(sf::RenderWindow& window, float deltaTime, bool Validar);
    void update(float deltaTime);
    void trurntrue();
    void enviarestado();
    int event;

private:
    sf::Color fillColor;
    Client* client;

    bool turno;
    float initialSpeed;
    float decelerationRate;
    bool decelerationStarted;
    bool isSpinning;
    float blinkTimer;
    float blinkDuration;
    bool giro;
    bool resultado;
    float currentRotation;
    
    bool sincro;

    float rotationSpeed;
  
    float width, height;
    float centerX, centerY;  
    float radius;

    int currentSegment;

    sf::Clock clock;
    sf::Clock lightClock;
    bool lightState = true;
   
    std::vector<sf::ConvexShape> segments;
    std::vector<sf::Texture> iconTextures;
    std::vector<sf::Sprite> icons;
    std::vector<sf::Sprite> iconsResul;
    std::vector<sf::CircleShape> luces;
    sf::ConvexShape pointer;

    sf::CircleShape CentroCircule;
    sf::CircleShape borde;
    sf::CircleShape ruletaBase;

    static const int numSegments = 7; 
    ParticleSystem particleSystem;

    sf::Color segmentColors[numSegments] = {
        sf::Color(243, 156, 18),
        sf::Color(241, 196, 14),
        sf::Color(171, 255, 46),
        sf::Color(0, 191, 255),
        sf::Color(255, 107, 181),
        sf::Color(231, 77, 60),
        sf::Color(145, 22, 254)
    };

    void createSegments();
    void loadIconTextures();
    void setupIcons();
    void setupLights();
    void drawLights(sf::RenderWindow& window, float deltaTime);
    void createPointer();
    void animatePointer();
    void setupBase();
};

#endif 


