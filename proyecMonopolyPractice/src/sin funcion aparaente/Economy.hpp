#pragma once

#include <iostream>

class Economy
{
public:
	
	Economy(int* _dinero, int* _impuesto, int* _salario);

	void sumardinero(int suma);
	void Sueldo();
	void restardinero(int resta);
	void pagaImpuesto();
	int* dinero;
	int* impuesto;
	int* salario;
private:
	

};

