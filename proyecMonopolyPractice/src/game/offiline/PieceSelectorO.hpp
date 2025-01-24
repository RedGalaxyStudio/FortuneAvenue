#ifndef PIECESELECTOR1_HPP
#define PIECESELECTOR1_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class PieceSelector1 {
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
    
    sf::Text CODE;
    float startX;
    float startY;


public:
    
    PieceSelector1(sf::RenderWindow* windowRef);
    ~PieceSelector1();
    void Resource();

    void displayPieces();

    
    void updateSelection();
    void updatePlayerPieceSelection(int newPieceIndex);
    
    sf::Sprite& getSelectedPiece();
};

#endif 
