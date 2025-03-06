#ifndef BOT_HPP
#define BOT_HPP

class Bot {
public:
    Bot(int id);
    void playTurn();  // turno del bot
  

private:
    int id;
    int score;  // atributos del bot
};

#endif
