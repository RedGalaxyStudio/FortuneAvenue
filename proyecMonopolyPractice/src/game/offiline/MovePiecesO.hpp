#ifndef MOVEPIECESO_HPP
#define MOVEPIECESO_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "ResourceGameO.hpp"

class MovePiecesO {
public:
	MovePiecesO(sf::RenderWindow& win,int mapauso);

	void Inicializar(sf::Sprite* sprite, std::vector<std::vector<sf::Vector2f>>* casillasC, int* vuel, sf::Vector2f fin, bool* CsFin, bool PiecUser);

	
	void iniciarMovimiento(int numeroCasillas, float duracion);

	
	void actualizarMovimiento(float deltaTime);
	bool finalCamino;

	void updateCAmbioCasilla();
	int getCaminoActual();
	int getcasillaActual();
	void animacionRastro(float deltaTime);
	void animacionRebote(sf::Vector2f posicionFinal, float deltaTime);
	void animacionRotacion(float deltaTime);
	void animacionEscala(float deltaTime);
	bool enMovimiento; 

private:

	void selCamIzq1();
	void selCamDer1();

	void selCamIzq2();
	void selCamDer2();

	void selCamIzq3();
	void selCamDer3();
	std::vector<sf::Vector2f> posSelecCAm;
	int tan;

	sf::Sprite* sprite;  
	std::vector<std::vector<sf::Vector2f>>* casillas;  
	sf::RenderWindow* window;
	int caminoActual;  
	int casillaActual;  
	int casillasRestantes;  
	sf::Vector2f final;
	int *vuelta;
	bool* CsFinal;
	int mapaActual;
	bool PieceUser;
	sf::Vector2f posicionInicial;  
	sf::Vector2f posicionFinal; 
	float duracionMovimiento; 
	float t; 
	float rotacionActual;
	float rotacionMaxima; 
	float velocidadRotacion; 
	bool girarIzquierda; 
	float tiempoCambio; 
	float timer;

};

#endif
