#ifndef PIECESELECTOR_HPP
#define PIECESELECTOR_HPP

#include <SFML/Graphics.hpp>
#include <vector>

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
public:
    
    PieceSelector(sf::RenderWindow* windowRef);
    void Resource();

    void displayPieces();

    
    sf::Texture updateSelection();

    
    sf::Sprite& getSelectedPiece();
};

#endif 
