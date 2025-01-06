#ifndef PIECESELECTOR_HPP
#define PIECESELECTOR_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class PieceSelector {
private:
    std::vector<sf::Sprite> pieces; 
    std::vector<sf::Sprite> shadow;  
    std::vector<sf::Sprite> Check; 
    std::vector<sf::Texture> piecesTextures;
    std::vector<sf::Texture> CheckTexturesOn;
    std::vector<sf::Texture> CheckTexturesOff;
    int selectedPiece;              
    sf::RenderWindow* window;       
    sf::Sprite* newSelection;  
    sf::Vector2i mousePosition;
    sf::Vector2f mousePosFloat;
    sf::FloatRect globalBounds;
    sf::Sprite fondopiece;
    sf::Texture Textufondopiece;
    int previousSelectionIndex[4];
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
