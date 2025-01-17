#ifndef MOVEPIECES_HPP
#define MOVEPIECES_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "ResourceGameO.hpp"

class MovePieces {
public:
	MovePieces(sf::RenderWindow& win);

	void Inicializar(sf::Sprite* sprite, std::vector<std::vector<sf::Vector2f>>* casillasC, int* vuel, sf::Vector2f fin, bool* CsFin, bool PiecUser);

	
	void iniciarMovimiento(int numeroCasillas, float duracion);

	
	void actualizarMovimiento(float deltaTime);
	bool finalCamino;
	void seleccionarCaminoIzq();
	void seleccionarCaminoDer();
	void updateCAmbioCasilla();
	int getCaminoActual();
	int getcasillaActual();
	void animacionRastro(float deltaTime);
	void animacionRebote(sf::Vector2f posicionFinal, float deltaTime);
	void animacionRotacion(float deltaTime);
	void animacionEscala(float deltaTime);
	bool enMovimiento; 

private:
	sf::Sprite* sprite;  
	std::vector<std::vector<sf::Vector2f>>* casillas;  
	sf::RenderWindow* window;
	int caminoActual;  
	int casillaActual;  
	int casillasRestantes;  
	sf::Vector2f final;
	int *vuelta;
	bool* CsFinal;

	bool PieceUser;
	sf::Vector2f posicionInicial;  
	sf::Vector2f posicionFinal;  // Posición final hacia la que se mueve el sprite
	float duracionMovimiento;  // Duración de la transición entre casillas
	float t;  // Valor de interpolación entre 0 y 1


	float rotacionActual; // Rotación actual en grados
	float rotacionMaxima; // Máximo en grados a girar a la izquierda o derecha
	float velocidadRotacion; // Grados por segundo
	bool girarIzquierda; // Estado de dirección de rotación
	float tiempoCambio; // Tiempo para cambiar de dirección
	float timer; // Timer para rastrear el tiempo


	std::vector<sf::Vector2f> camino3 = {
		
		sf::Vector2f(473,661),
		sf::Vector2f(505,632),
		sf::Vector2f(505,586),
		sf::Vector2f(519,544),
		sf::Vector2f(556,544),
		sf::Vector2f(568,586),
		sf::Vector2f(568,636),
		sf::Vector2f(580,678),
		sf::Vector2f(621,677),
		sf::Vector2f(632,637),
		sf::Vector2f(632,585),
		sf::Vector2f(642,542),
		sf::Vector2f(678,542),
		sf::Vector2f(694,582),
		sf::Vector2f(694,636),
		sf::Vector2f(725,668),
		sf::Vector2f(772,666)
	};






	std::vector<sf::Vector2f> camino5{
	 sf::Vector2f(881, 495),
	 sf::Vector2f(840, 476),
	 sf::Vector2f(805, 450),
	 sf::Vector2f(807, 416),
	 sf::Vector2f(838, 398),
	 sf::Vector2f(881, 399),
	 sf::Vector2f(925, 396),
	 sf::Vector2f(958, 372),
	 sf::Vector2f(953, 335),
	 sf::Vector2f(920, 312),
	 sf::Vector2f(881, 312),
	 sf::Vector2f(838, 311),
	 sf::Vector2f(806, 292),
	 sf::Vector2f(808, 257),
	 sf::Vector2f(842, 238),
	 sf::Vector2f(882, 238),
	 sf::Vector2f(930, 231),
	 sf::Vector2f(956, 190),
	 sf::Vector2f(956, 141),
	 sf::Vector2f(917, 124),
	 sf::Vector2f(874, 132),
	 sf::Vector2f(861, 178),
	 sf::Vector2f(819, 188),
	 sf::Vector2f(773, 190),
	 sf::Vector2f(722, 183),
	 sf::Vector2f(688, 137),
	 sf::Vector2f(688, 81),
	 sf::Vector2f(675, 40),
	 sf::Vector2f(635, 37),
	 sf::Vector2f(619, 81),
	 sf::Vector2f(620, 131),
	 sf::Vector2f(595, 175),
	 sf::Vector2f(544, 175),
	 sf::Vector2f(514, 141),
	 sf::Vector2f(503, 98),
	 sf::Vector2f(460, 79)
	};

	


	std::vector<sf::Vector2f> caminocasa5  {
	sf::Vector2f(807, 416),
	sf::Vector2f(881, 312),
	sf::Vector2f(842, 238),
	sf::Vector2f(874, 132),
	sf::Vector2f(819, 188),
	sf::Vector2f(595, 175),
	sf::Vector2f(505,586),
	sf::Vector2f(568,636),
	sf::Vector2f(694,636),
	sf::Vector2f(368, 339), 
	sf::Vector2f(407, 98),
	sf::Vector2f(764, 577),
	sf::Vector2f(429, 566),
	sf::Vector2f(955, 609),
	sf::Vector2f(355, 40),
	sf::Vector2f(323,629),
	sf::Vector2f(394,678)
	
	};


	std::vector<sf::Vector2f> camino7{
		// sf::Vector2f(407, 98),
		 sf::Vector2f(402, 157),
		 sf::Vector2f(442, 209),
		 sf::Vector2f(413, 253),
		 sf::Vector2f(364, 283),
		 sf::Vector2f(368, 339)
	};

};

#endif
