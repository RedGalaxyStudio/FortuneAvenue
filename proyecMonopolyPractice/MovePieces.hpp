#ifndef MOVEPIECES_HPP
#define MOVEPIECES_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "ResourceGame.hpp"

class MovePieces {
public:
	MovePieces(sf::RenderWindow& win);

	void Inicializar(sf::Sprite* sprite, std::vector<std::vector<sf::Vector2f>>* casillasC, std::vector<std::vector<sf::Vector2f>>* casillasRuletaC, std::vector<std::vector<sf::Vector2f>>* casillaImpuestoC);

	// Iniciar el movimiento del sprite a lo largo de las casillas
	void iniciarMovimiento(int numeroCasillas, float duracion);

	// Actualizar la posición del sprite (llamado en cada frame)
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
	bool enMovimiento;  // Indica si el sprite está en movimiento

private:
	sf::Sprite* sprite;  // Guardamos la referencia al sprite
	std::vector<std::vector<sf::Vector2f>>* casillas;  // Lista de caminos/casillas
	std::vector<std::vector<sf::Vector2f>>* casillasRuleta;  // Lista de caminos/casillas
	std::vector<std::vector<sf::Vector2f>>* casillasImpuesto;  // Lista de caminos/casillas
	sf::RenderWindow* window;
	int caminoActual;  // El camino actual por el que está moviéndose el sprite
	int casillaActual;  // La casilla actual dentro del camino
	int casillasRestantes;  // Número de casillas que quedan por mover


	sf::Vector2f posicionInicial;  // Posición inicial para la interpolación
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

	std::vector<sf::Vector2f> caminoruleta3 = { 
		sf::Vector2f(425,654),
		sf::Vector2f(556 , 544),
		sf::Vector2f(632 , 585)
	};

	std::vector<sf::Vector2f> caminoimpuesto3 = { 
		sf::Vector2f(621 , 677),
		sf::Vector2f(694 ,582)
	};
	std::vector<sf::Vector2f> caminocasa3 = { 
		sf::Vector2f(505,586),
		sf::Vector2f(568,636),
		sf::Vector2f(694,636)
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

	std::vector<sf::Vector2f> caminoruleta5  { 
		sf::Vector2f(840, 476),
		sf::Vector2f(958, 372), 
		sf::Vector2f(930, 231), 
		sf::Vector2f(688, 137), 
		sf::Vector2f(675, 40), 
		sf::Vector2f(514, 141) 
	};
	std::vector<sf::Vector2f> caminoimpuesto5  { 
		sf::Vector2f(840, 476),
		sf::Vector2f(958, 372),
		sf::Vector2f(930, 231),
		sf::Vector2f(688, 137),
		sf::Vector2f(675, 40),
		sf::Vector2f(514, 141) 
	};

	std::vector<sf::Vector2f> caminocasa5  {
	sf::Vector2f(807, 416),
	sf::Vector2f(881, 312),
	sf::Vector2f(842, 238),
	sf::Vector2f(874, 132),
	sf::Vector2f(819, 188),
	sf::Vector2f(544, 175)
	};


	std::vector<sf::Vector2f> camino7{
		// sf::Vector2f(407, 98),
		 sf::Vector2f(402, 157),
		 sf::Vector2f(442, 209),
		 sf::Vector2f(413, 253),
		 sf::Vector2f(364, 283),
		 sf::Vector2f(368, 339)
	};

	std::vector<sf::Vector2f> caminoruleta7 = { sf::Vector2f(402, 157) };
	std::vector<sf::Vector2f> caminoimpuesto7 = { sf::Vector2f(413, 253) };
	std::vector<sf::Vector2f> caminocasa7 = { sf::Vector2f(368, 339) };
};

#endif // MOVEPIECES_HPP
