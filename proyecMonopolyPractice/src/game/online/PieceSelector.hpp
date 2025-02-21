#ifndef PIECESELECTOR_HPP
#define PIECESELECTOR_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../../network/Client.hpp"

class PieceSelector {
private:
 
    std::vector<sf::Sprite> shadow;  
    int selectedPiece;              
    sf::RenderWindow* window;       
    sf::Sprite* newSelection;  
    sf::Vector2i mousePosition;
    sf::Vector2f mousePosFloat;
    sf::FloatRect globalBounds;
    sf::Sprite fondopiece;
    sf::Texture Textufondopiece;
    sf::Texture Preguntasalir;
    Client* client;
    sf::Text CODE;
    float startX;
    float startY;


public:
    
    PieceSelector(sf::RenderWindow* windowRef);
    ~PieceSelector();
    void Resource();

    void displayPieces();

    
    void updateSelection();
    void updatePlayerPieceSelection(int newPieceIndex);
    
    sf::Sprite& getSelectedPiece();
};

#endif 
