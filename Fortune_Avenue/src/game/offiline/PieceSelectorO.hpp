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
    sf::Sprite CircleSpri;
    sf::Texture Textufondopiece;
    sf::Texture Textucicle;
    
    sf::Text CODE;
    float startX;
    float startY;
    int nUserBot;
    int Nmap;
public:
    
    PieceSelectOff(sf::RenderWindow* windowRef,int UsersN,int Map);
    ~PieceSelectOff();
    void Resource();

    void displayPieces();

    
    void updateSelection();
    void updatePlayerPieceSelection(int newPieceIndex);
    
    sf::Sprite& getSelectedPiece();
};

#endif 
