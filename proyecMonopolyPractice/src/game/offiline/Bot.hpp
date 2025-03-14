#ifndef BOT_HPP
#define BOT_HPP

#include <vector>
#include <string>

namespace CreatorB{
    std::vector<std::string> getRandomBotNames(int count);
    std::vector<int> getRandomBotPieces(int count);
    std::vector<int> getRandomBotAvatar(int count);
}

class Bot {
public:
    Bot(int id,int Dificultad);
    void playTurn();  // turno del bot
    

private:
    int id;
    int Dificultad;
    int score;  // atributos del bot
};

#endif
