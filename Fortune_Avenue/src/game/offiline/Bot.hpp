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
    void houseBuy(int costo, int money);
    void resetTRuleta();
    void resetTCAMRuleta();

private:
    sf::Clock clock;
    float waitTime;



};

#endif
