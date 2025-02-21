#ifndef BOT_HPP
#define BOT_HPP

class Bot {
public:
    Bot(int id);
    void playTurn();  // L�gica del turno del bot
    // Otros m�todos seg�n se necesiten, como calcular estrategias, etc.

private:
    int id;
    int score;  // Ejemplo de un atributo del bot
};

#endif
