#ifndef PIECESELECTOFF_HPP
#define PIECESELECTOFF_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class PieceSelectOff {
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
    
    PieceSelectOff(sf::RenderWindow* windowRef);
    ~PieceSelectOff();
    void Resource();

    void displayPieces();

    
    void updateSelection();
    void updatePlayerPieceSelection(int newPieceIndex);
    
    sf::Sprite& getSelectedPiece();
};

#endif 
