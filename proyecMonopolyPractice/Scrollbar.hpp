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

private:
    
    sf::RectangleShape scrollbarTrack; 
    sf::RectangleShape scrollbarThumb;
    sf::CircleShape cornerTL, cornerTR, cornerBL, cornerBR; 
    float conerPs,x,y;
    float maxScrollOffset;
    
    float width;
    float windowHeight;      
    float scrollbarHeight;   
    float scrollOffset;    
   
};

#endif 