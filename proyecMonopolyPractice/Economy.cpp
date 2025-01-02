#include "Economy.hpp"
#include "MultiplayerGame.hpp"

Economy::Economy(int* _dinero, int *_impuesto,int *_salario) : dinero(_dinero), impuesto(_impuesto), salario(_salario){}

void Economy::sumardinero(int suma) {
   
    //if() 
    *dinero += suma;  // Modificamos el valor al que apunta 'dinero'
    client.moneyActu(*dinero);
}

void Economy::Sueldo() {
    *dinero += *salario;
    client.moneyActu(*dinero);
}

void Economy::restardinero(int resta) {
    *dinero -= resta;  // Modificamos el valor al que apunta 'dinero'
    client.moneyActu(*dinero);
}

void Economy::pagaImpuesto() {
    
    *dinero -= *impuesto;  // Restamos el impuesto del valor al que apunta 'dinero'
    client.moneyActu(*dinero);
}
