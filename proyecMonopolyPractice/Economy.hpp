#pragma once

#include <iostream>

class Economy
{
public:
	
	Economy(int* _dinero);

	void sumardinero(int suma);
	void restardinero(int resta);

private:
	int* dinero;

};

