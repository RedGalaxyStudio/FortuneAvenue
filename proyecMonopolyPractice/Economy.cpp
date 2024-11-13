#include "Economy.hpp"
#include "GameMode.hpp"

Economy::Economy(int* _dinero) : dinero(_dinero) {}

void Economy::sumardinero(int suma) {
   
    //if() playersGame[i].Money.setString(std::to_string(playerInfos[i].money));

    
    *dinero += suma;  // Modificamos el valor al que apunta 'dinero'
}

void Economy::restardinero(int resta) {
    *dinero -= resta;  // Modificamos el valor al que apunta 'dinero'
}

void Economy::impuesto(int sueldo) {
    int impuesto = static_cast<float>(sueldo * 0.20);  // Calculamos el 20% de 'sueldo'
    *dinero -= impuesto;  // Restamos el impuesto del valor al que apunta 'dinero'
}
