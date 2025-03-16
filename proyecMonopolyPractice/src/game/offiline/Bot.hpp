#ifndef BOT_HPP
#define BOT_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

namespace CreatorB{
    std::vector<std::string> getRandomBotNames(int count);
    std::vector<int> getRandomBotPieces(int count, int pieceP);
    std::vector<int> getRandomBotAvatar(int count);
}

class Bot {
public:
    Bot();
    bool roll();
    int eleccion();
    void resetT();
    void resetTCAM();
private:
    sf::Clock clock;
    float waitTime;



};

#endif
