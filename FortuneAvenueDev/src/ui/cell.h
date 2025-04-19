#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>

#define ITER(cell, i) for(int i = 0; i < (int)cell.size(); i++)
#define imageWidth 1280
#define imageHeight 720

struct Position {
    float x;
    float y;
};

class Shape {

private:
    sf::Vector3f n; // normal vector components
    sf::Vector3f mc; // mass center coordinates

public:
    Shape();
    ~Shape();
    sf::Vector3f getN();
    sf::Vector3f getMC();
    void setN(sf::Vector3f n);
    void setMC(sf::Vector3f mc);

}; // Shape

class Cell : public Shape {

private:
    std::vector<sf::Vector3f> P{0};
    sf::ConvexShape cShape; // the shape itself
    int sizeP; // number of cell vertices
    
    Position initialPos;
    Position targetPos = { 640, 360 };
    int numCalls;
public:
    Cell(const std::vector<sf::Vector3f> pt, sf::Color col, sf::Vector2f posicionInicial);
    Cell(const std::vector<sf::Vector3f> pt, sf::Texture *texcar, sf::Vector2f posicionInicial);
    ~Cell();
    Position currentPos;
    sf::ConvexShape getCell();
    Position moveToTarget(Position currentPos, Position targetPos, int numCalls);
    void Rotate(sf::Vector3f O, sf::Vector3f W, float thetaY);
    void get_projected_point(float &x, float &y, float &z);
    bool finAnimacion;
   // float currentRotation;
    int conte;
}; // Cell

#endif // CELL_H
