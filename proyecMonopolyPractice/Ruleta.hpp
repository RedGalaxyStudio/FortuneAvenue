#ifndef RUELTA_HPP
#define RUELTA_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Particles.h"
#define M_PI 3.14159265358979323846

class Ruleta {
public:
    Ruleta(float width, float height, float centerX, float centerY);
    void draw(sf::RenderWindow& window, float deltaTime, bool Validar);
    void update(float deltaTime);

private:
    sf::Color fillColor;
    sf::RenderTexture renderTexture1; // Textura para shader1
    sf::RenderTexture renderTexture2; // Textura para shader2

    bool turno;

    sf::CircleShape textureCircule1;
    sf::CircleShape textureCircule2;

    float blinkTimer;
    float blinkDuration;
    bool giro;
    bool resultado;
    float currentRotation;
    bool isSpinning;
    float rotationSpeed;

    float width, height;
    float centerX, centerY;  // Posición central de la ruleta
    float radius;

    sf::Clock clock;
    sf::Clock lightClock;
    bool lightState = true;
   
    sf::Shader shader;
    sf::Shader noise;
    sf::Shader glowShader;
    sf::Shader shader_gradient;
    std::vector<sf::ConvexShape> segments;
    std::vector<sf::Texture> iconTextures;
    std::vector<sf::Sprite> icons;
    std::vector<sf::CircleShape> luces;
    sf::ConvexShape pointer;

    sf::CircleShape CentroCircule;
    sf::CircleShape borde;
    sf::CircleShape ruletaBase;

    static const int numSegments = 7; // Número de segmentos
    ParticleSystem particleSystem;

    sf::Color segmentColors[numSegments] = {
        sf::Color(255, 0, 0),
        sf::Color(0, 255, 0),
        sf::Color(0, 0, 255),
        sf::Color(255, 255, 0),
        sf::Color(0, 255, 255),
        sf::Color(255, 0, 255),
        sf::Color(255, 165, 0)/*
        sf::Color(239, 17, 17),//0
        sf::Color(94, 206, 64), //1
        sf::Color(175, 122, 197),//2
        sf::Color(241, 196, 15),//3
        sf::Color(23, 77, 205), //4
        sf::Color::Magenta, //5
        sf::Color(52, 73, 94)//6*/
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

#endif // RUELTA_HPP


