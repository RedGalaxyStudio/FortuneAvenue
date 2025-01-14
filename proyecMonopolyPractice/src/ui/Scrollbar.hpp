
#ifndef SCROLLBAR_HPP
#define SCROLLBAR_HPP

#include <SFML/Graphics.hpp>

class Scrollbar {
public:
    
    Scrollbar(float windowHeight, float scrollbarHeight, float width);

 
    void update(float deltaScroll);

   
    void draw(sf::RenderWindow& window);

    void Prinft();


    void setPosition(float xNew, float yNew);

    
    void setColors(const sf::Color& trackColor, const sf::Color& thumbColor, const sf::Color& borderColor);

   
    void setOutlineThickness(float thickness);

    
    float getScrollOffset() const;

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

private:
    
    sf::RectangleShape scrollbarTrack; 
    sf::RectangleShape scrollbarThumb;
    sf::CircleShape cornerTL, cornerTR, cornerBL, cornerBR; 
    float conerPs,x,y;
    float maxScrollOffset;
    
    bool dragging = false;         // Indica si el usuario está arrastrando el pulgar
    float dragOffset = 0.0f;


    float width;
    float windowHeight;      
    float scrollbarHeight;   
    float scrollOffset;    
   
};

#endif 