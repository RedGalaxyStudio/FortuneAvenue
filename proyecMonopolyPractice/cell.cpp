#include "cell.h"
#include <cmath>
#include <iostream>

// #define PERSPECTIVE

#define M_PI 3.14159265358979323846



Shape::Shape() {

    n = sf::Vector3f(0., 0., 0.); // normal vector components
    mc = sf::Vector3f(0., 0., 0.); // mass center coordinates

} // constructor

void Cell::get_projected_point(float &x, float &y, float &z) {

    float x_ = x;// - imageWidth;
    float y_ = y;// - imageHeight;
    float z_ = z;

    float Z0 = 512.;
    float Z = (Z0 + z_) / Z0;

    float x1 = x_ * Z;
    float y1 = y_ * Z;
    float z1 = z_;

//    x = x1 + imageWidth; y = y1 + imageHeight; z = z1;
    x = x1; y = y1; z = z1;

    return;
} // Cell::get_projected_point

Cell::Cell(const std::vector<sf::Vector3f> pt, sf::Color col,sf::Vector2f posicionInicial) : Shape(), initialPos{ posicionInicial.x, posicionInicial.y}, finAnimacion(false), conte(0){
int i;
   
        numCalls = 29;                // Número de veces que se llama a la función

      currentPos = initialPos;


    

    (*this).sizeP = (int)pt.size();

    // Fill in P vector
    for (i = 0; i < sizeP; i++) {
        sf::Vector3f Pt;
        Pt.x = pt.at(i).x;
        Pt.y = pt.at(i).y;
        Pt.z = pt.at(i).z;
        (*this).P.push_back(Pt);
    }//for_i

    (*this).cShape.setPointCount(sizeP);
    (*this).cShape.setFillColor(col);
    (*this).cShape.scale(0.04,0.04);
    //(*this).cShape.setOutlineColor(sf::Color::Black);
   // (*this).cShape.setOutlineThickness(-1);
    (*this).cShape.setOrigin(199.0, 350.0);
    (*this).cShape.setPosition(posicionInicial.x, posicionInicial.y);

    // Define corner points of the ConvexShape instance
    for (i = 0; i < sizeP; i++) {

        float x = P.at(i).x, y = P.at(i).y, z = P.at(i).z;
#if defined PERSPECTIVE
        (*this).get_projected_point(x, y, z);
#else
#endif // PERSPECTIVE
        (*this).cShape.setPoint(i, sf::Vector2f(x, y)); z = z; // avoid warning

    }//for_i

    // Compute normal vector components
    float p[3] = {0., 0., 0.}, q[3] = {0., 0., 0.}; // p[x,y,z], q[x,y,z]
    if (sizeP == 4) { // quadrangle

        p[0] = P[0].x - P[2].x;
        p[1] = P[0].y - P[2].y;
        p[2] = P[0].z - P[2].z;
        q[0] = P[1].x - P[3].x;
        q[1] = P[1].y - P[3].y;
        q[2] = P[1].z - P[3].z;

    }//if
    else if (sizeP == 3) { // triangle

        p[0] = P[0].x - P[1].x;
        p[1] = P[0].y - P[1].y;
        p[2] = P[0].z - P[1].z;

        q[0] = P[0].x - P[2].x;
        q[1] = P[0].y - P[2].y;
        q[2] = P[0].z - P[2].z;

    }//else_if
    else {}

    float Sx = 0.5 * (p[1] * q[2] - p[2] * q[1]);
    float Sy = 0.5 * (-p[0] * q[2] + p[2] * q[0]);
    float Sz = 0.5 * (p[0] * q[1] - p[1] * q[0]);
    float S = sqrt(Sx * Sx + Sy * Sy + Sz * Sz);
    float nx = Sx / S;
    float ny = Sy / S;
    float nz = Sz / S;

    (*this).setN(sf::Vector3f{nx, ny, nz});

    // Compute mass center coordinates
    float xc = 0., yc = 0., zc = 0.;

    i = 0;
    while (i < sizeP) {
        xc += P.at(i).x;
        yc += P.at(i).y;
        zc += P.at(i).z;
        i++;
    } // while_i
    xc /= (float)i; yc /= (float)i; zc /= (float)i;

    (*this).setMC(sf::Vector3f{xc, yc, zc});

} // constructor

Cell::Cell(const std::vector<sf::Vector3f> pt, sf::Texture *texcar, sf::Vector2f posicionInicial) : Shape(), initialPos{ posicionInicial.x, posicionInicial.y },finAnimacion(false), conte(0) {
int i;

    (*this).sizeP = (int)pt.size();

    numCalls = 29;
    currentPos = initialPos;
    // Fill in P vector
    for (i = 0; i < sizeP; i++) {
        sf::Vector3f Pt;
        Pt.x = pt.at(i).x;
        Pt.y = pt.at(i).y;
        Pt.z = pt.at(i).z;
        (*this).P.push_back(Pt);
    }//for_i

    (*this).cShape.setPointCount(sizeP);
    (*this).cShape.setTexture(texcar);
    (*this).cShape.scale(0.04,0.04);
    //(*this).cShape.setOutlineColor(sf::Color::Black);
    //(*this).cShape.setOutlineThickness(-1);
    (*this).cShape.setOrigin(199.0, 350.0);
    (*this).cShape.setPosition(640, 360);;

    // Define corner points of the ConvexShape instance
    for (i = 0; i < sizeP; i++) {

        float x = P.at(i).x, y = P.at(i).y, z = P.at(i).z;
#if defined PERSPECTIVE
        (*this).get_projected_point(x, y, z);
#else
#endif // PERSPECTIVE
        (*this).cShape.setPoint(i, sf::Vector2f(x, y)); z = z; // avoid warning

    }//for_i

    // Compute normal vector components
    float p[3] = {0., 0., 0.}, q[3] = {0., 0., 0.}; // p[x,y,z], q[x,y,z]
    if (sizeP == 4) { // quadrangle

        p[0] = P[0].x - P[2].x;
        p[1] = P[0].y - P[2].y;
        p[2] = P[0].z - P[2].z;
        q[0] = P[1].x - P[3].x;
        q[1] = P[1].y - P[3].y;
        q[2] = P[1].z - P[3].z;

    }//if
    else if (sizeP == 3) { // triangle

        p[0] = P[0].x - P[1].x;
        p[1] = P[0].y - P[1].y;
        p[2] = P[0].z - P[1].z;

        q[0] = P[0].x - P[2].x;
        q[1] = P[0].y - P[2].y;
        q[2] = P[0].z - P[2].z;

    }//else_if
    else {}

    float Sx = 0.5 * (p[1] * q[2] - p[2] * q[1]);
    float Sy = 0.5 * (-p[0] * q[2] + p[2] * q[0]);
    float Sz = 0.5 * (p[0] * q[1] - p[1] * q[0]);
    float S = sqrt(Sx * Sx + Sy * Sy + Sz * Sz);
    float nx = Sx / S;
    float ny = Sy / S;
    float nz = Sz / S;

    (*this).setN(sf::Vector3f{nx, ny, nz});

    // Compute mass center coordinates
    float xc = 0., yc = 0., zc = 0.;

    i = 0;
    while (i < sizeP) {
        xc += P.at(i).x;
        yc += P.at(i).y;
        zc += P.at(i).z;
        i++;
    } // while_i
    xc /= (float)i; yc /= (float)i; zc /= (float)i;

    (*this).setMC(sf::Vector3f{xc, yc, zc});

} // constructor

Cell::~Cell() {

    (*this).P.clear();

} // destructor

Shape::~Shape() {

} // destructor

sf::ConvexShape Cell::getCell() {

    return (*this).cShape;

} // Cell::getCell

sf::Vector3f Shape::getN() {

    return (*this).n;

} // Shape::getN

sf::Vector3f Shape::getMC() {

    return (*this).mc;

} // Shape::getMC

void Shape::setN(sf::Vector3f n) {

    (*this).n = n;

} // Shape::setN

void Shape::setMC(sf::Vector3f mc) {

    (*this).mc = mc;

} // Shape :: setMC


Position Cell::moveToTarget(Position currentPos, Position targetPos, int numCalls) {
    // Calculamos el cambio en X e Y por cada llamada
    float deltaX = (targetPos.x - currentPos.x) / numCalls;
    float deltaY = (targetPos.y - currentPos.y) / numCalls;

    // Actualizamos la posición
    currentPos.x += deltaX;
    currentPos.y += deltaY;

    return currentPos;
}



void Cell::Rotate(sf::Vector3f O, sf::Vector3f W, float thetaY) {

    sf::Vector2f scale = (*this).cShape.getScale();
    if (scale.y < 1.){
        int i;
        
        float thetaX = 0;
        // Convertir los ángulos a radianes
        thetaX *= M_PI / 180.0f;
        thetaY *= M_PI / 180.0f;

        // Crear matrices de rotación individuales para X e Y
        float RX[3][3] = {
            {1, 0, 0},
            {0, cos(thetaX), -sin(thetaX)},
            {0, sin(thetaX), cos(thetaX)}
        };

        float RY[3][3] = {
            {cos(thetaY), 0, sin(thetaY)},
            {0, 1, 0},
            {-sin(thetaY), 0, cos(thetaY)}
        };

        // Combinar las rotaciones RX y RY
        float R[3][3];
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                R[row][col] = RX[row][0] * RY[0][col] +
                    RX[row][1] * RY[1][col] +
                    RX[row][2] * RY[2][col];
            }
        }

        std::vector<sf::Vector3f> Psh;
        // Desplazar los puntos al origen
        for (i = 0; i < (*this).sizeP; i++) {
            Psh.push_back(P.at(i) - O);
        }

        std::vector<sf::Vector3f> Prot;
        // Rotar los puntos
        for (i = 0; i < (*this).sizeP; i++) {
            sf::Vector3f x0 = Psh.at(i);
            sf::Vector3f x1;

            x1.x = R[0][0] * x0.x + R[0][1] * x0.y + R[0][2] * x0.z;
            x1.y = R[1][0] * x0.x + R[1][1] * x0.y + R[1][2] * x0.z;
            x1.z = R[2][0] * x0.x + R[2][1] * x0.y + R[2][2] * x0.z;

            Prot.push_back(x1 + O);
        }

        Psh.clear();
        P = Prot;
        Prot.clear();

        // Actualizar los puntos de la forma convexa
        for (i = 0; i < sizeP; i++) {
            float x = P.at(i).x, y = P.at(i).y, z = P.at(i).z;
#if defined PERSPECTIVE
            (*this).get_projected_point(x, y, z);
#else
#endif // PERSPECTIVE
            (*this).cShape.setPoint(i, sf::Vector2f(x, y));


            
                // Obtener la escala de la forma
              
              

                   
        }
        
        (*this).cShape.scale(1.02814f, 1.02814f);
         currentPos = moveToTarget(currentPos, targetPos, numCalls);
         (*this).cShape.setPosition(currentPos.x, currentPos.y);
  sf::Vector2f posicionactu = (*this).cShape.getScale();
                std::cout << "\nScale:" << posicionactu.x << " x:y " << posicionactu.y;

        // Actualizar el vector normal
        sf::Vector3f n0 = (*this).getN();
        sf::Vector3f n1;

        n1.x = R[0][0] * n0.x + R[0][1] * n0.y + R[0][2] * n0.z;
        n1.y = R[1][0] * n0.x + R[1][1] * n0.y + R[1][2] * n0.z;
        n1.z = R[2][0] * n0.x + R[2][1] * n0.y + R[2][2] * n0.z;

        (*this).setN(n1);

        // Actualizar el centro de masa
        sf::Vector3f xc0 = getMC();
        xc0 -= O;
        sf::Vector3f xc1;

        xc1.x = R[0][0] * xc0.x + R[0][1] * xc0.y + R[0][2] * xc0.z;
        xc1.y = R[1][0] * xc0.x + R[1][1] * xc0.y + R[1][2] * xc0.z;
        xc1.z = R[2][0] * xc0.x + R[2][1] * xc0.y + R[2][2] * xc0.z;

        (*this).setMC(xc1 + O);
        conte += 1;
       // std::cout << "\nConte.x:" << conte; std::cout << "\ncurrentPos.x:" << currentPos.x << " currentPos.y" << currentPos.y;
    }
    else {


        finAnimacion = true;

    }
    
   

    }

