#ifndef PIECESELECTOR_HPP
#define PIECESELECTOR_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class PieceSelector {
private:
    std::vector<sf::Sprite> pieces;  // List of pieces to select
    std::vector<sf::Sprite> shadow;  // List of pieces to select
    std::vector<sf::Sprite> Check;  // List of pieces to select
    std::vector<sf::Texture> piecesTextures;
    std::vector<sf::Texture> CheckTexturesOn;
    std::vector<sf::Texture> CheckTexturesOff;
    int selectedPiece;               // Index of the selected piece
    sf::RenderWindow* window;        // Reference to the window
    sf::Sprite* newSelection;  // Puntero para la nueva selección
    sf::Vector2i mousePosition;
    sf::Vector2f mousePosFloat;
    sf::FloatRect globalBounds;
public:
    // Constructor
    PieceSelector(sf::RenderWindow* windowRef);
    void Resource();
    // Display pieces for selection
    void displayPieces();

    // Update the selection based on user input
    sf::Texture updateSelection();

    // Get the selected piece
    sf::Sprite& getSelectedPiece();
};

#endif // PIECESELECTOR_HPP
