#include "Economy.hpp"

Economy::Economy(int* _dinero) :dinero(_dinero) {}

void Economy::sumardinero(int suma) {
	dinero += suma;
}
void Economy::restardinero(int resta) {
	dinero -= resta;
}