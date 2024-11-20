#include "MovePieces.hpp"
#include "ResourceGlobal.hpp"

MovePieces::MovePieces(sf::RenderWindow& win) : window(&win), sprite(nullptr), casillas(nullptr), casillasRuleta(nullptr), caminoActual(0), casillaActual(0), enMovimiento(false), t(0.0f), casillasRestantes(0), rotacionActual(0.0f), rotacionMaxima(30.0f), velocidadRotacion(90.0f), girarIzquierda(true), tiempoCambio(0.5f), timer(0.0f), duracionMovimiento(0.0f), finalCamino(false) {};


void MovePieces::Inicializar(sf::Sprite* spriteC, std::vector<std::vector<sf::Vector2f>>* casillasC, std::vector<std::vector<sf::Vector2f>>* casillasImpuestoC) {
	this->sprite = spriteC;
	this->casillas = casillasC;
	this->casillasImpuesto = casillasImpuestoC;
}


void MovePieces::iniciarMovimiento(int numeroCasillas, float duracion) {
	casillasRestantes = numeroCasillas;


	if (caminoActual < casillas->size() && casillaActual < (*casillas)[caminoActual].size()) {

		posicionInicial = sprite->getPosition();
		posicionFinal = (*casillas)[caminoActual][casillaActual];
		this->duracionMovimiento = duracion;
		this->t = 0.0f;
		this->enMovimiento = true;
	}
}

int MovePieces::getCaminoActual() {
	return caminoActual;
}

int MovePieces::getcasillaActual() {
	return casillaActual;
}

void MovePieces::actualizarMovimiento(float deltaTime) {

	if (enMovimiento && !finalCamino) {
		t += deltaTime / duracionMovimiento;

		while (t > 1.0f && casillasRestantes > 0) {
			t -= 1.0f;

			sprite->setPosition(posicionFinal);


			casillaActual++;
			casillasRestantes--;


			std::cout << "\nCasi casi csio";
			if (casillaActual >= (*casillas)[caminoActual].size()) {
				casillaActual = 0;
				std::cout << "\nCasi caso";
				if (caminoActual + 1 >= (*casillas).size()) {

					finalCamino = true;

					updateCAmbioCasilla();
				}
				caminoActual++;



			}

			posicionInicial = sprite->getPosition();
			posicionFinal = (*casillas)[caminoActual][casillaActual];
		}

		if (enMovimiento && casillasRestantes > 0) {


			sf::Vector2f nuevaPosicion = posicionInicial + (posicionFinal - posicionInicial) * t;
			sprite->setPosition(nuevaPosicion);
		}
		else {
			enMovimiento = false;
			turn_Moviendo = false;
			giroRule = true;
		}

		animacionRebote(posicionFinal, deltaTime);

	}

}



void MovePieces::updateCAmbioCasilla() {

	int tan = static_cast<int>((*casillas).size());
//	std::cout << "\nturn:" << turn;

	if (tan == 3) {
		SpriteArrowArriba.setPosition(370, 400);

		SpriteArrowDer.setPosition(900, 400);

	}
	else if (tan == 5) {
		SpriteArrowArriba.setPosition(900, 400);

		SpriteArrowIzq.setPosition(370, 400);
	}
	else if (tan == 1) {
		SpriteArrowIzq.setPosition(370, 400);

		SpriteArrowDer.setPosition(900, 400);
	}

	if (caminoActual >= 6) {
		caminoActual = 0;
		casillas->resize(1);
		finalCamino = false;
		caminoActual--;
	
	}

	while (finalCamino == true) {
	
		sf::Event event;
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
		sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

		while (window->pollEvent(event)) {

			if (turn) {
				if (event.type == sf::Event::Closed ||
					(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {

					renderTexture.clear();
					renderTexture.draw(spriteFondoGame);
					renderTexture.draw(spriteMapa);
					for (int i = 0; i < 4; i++)
					{
						renderTexture.draw(playersGame[i].NamePlayer);
						renderTexture.draw(playersGame[i].boxPlayer);
						renderTexture.draw(playersGame[i].MarcoPlayer);
						renderTexture.draw(playersGame[i].AvatarPlayer);
					}
					renderTexture.draw(spriteX);
					renderTexture.draw(overlay);
					renderTexture.display();
					Menup.MenuSalir();

					running = false;
				}



				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

					if (tan == 3) {
						if (SpriteArrowArriba.getGlobalBounds().contains(mousePosFloat)) {
							playClickSound();
							finalCamino = false;
							client.opcionCaminoenvio(0);
							seleccionarCaminoIzq();
							
						}

						if (SpriteArrowDer.getGlobalBounds().contains(mousePosFloat)) {
							playClickSound();
							finalCamino = false;
							client.opcionCaminoenvio(1);
							seleccionarCaminoDer();
						}

					}
					else if (tan == 5) {
						if (SpriteArrowArriba.getGlobalBounds().contains(mousePosFloat)) {
							playClickSound();
							finalCamino = false;
							client.opcionCaminoenvio(0);
							seleccionarCaminoDer();
							
						}

						if (SpriteArrowIzq.getGlobalBounds().contains(mousePosFloat)) {
							playClickSound();
							finalCamino = false;
							client.opcionCaminoenvio(1);
							seleccionarCaminoIzq();
						}
					}
					else if (tan == 1) {
						if (SpriteArrowIzq.getGlobalBounds().contains(mousePosFloat)) {
							playClickSound();
							finalCamino = false;
							client.opcionCaminoenvio(0);
							seleccionarCaminoIzq();
						}

						if (SpriteArrowDer.getGlobalBounds().contains(mousePosFloat)) {
							playClickSound();
							finalCamino = false;
							client.opcionCaminoenvio(1);
							seleccionarCaminoDer();
						}
					}


				}

			}
		}




		if (!turn) {

		//	std::cout << "\nOpcioncami:" << Opcioncami;
			if (tan == 3) {
				if (Opcioncami == 0) {
					playClickSound();
					finalCamino = false;
					seleccionarCaminoIzq();
					Opcioncami = -1;
				}

				if (Opcioncami == 1) {
					playClickSound();
					finalCamino = false;
					seleccionarCaminoDer();
					Opcioncami = -1;
				}

			}
			else if (tan == 5) {
				if (Opcioncami == 0) {
					playClickSound();
					finalCamino = false;
					seleccionarCaminoDer();
					Opcioncami = -1;
				}

				if (Opcioncami == 1) {
					playClickSound();
					finalCamino = false;
					seleccionarCaminoIzq();
					Opcioncami = -1;
				}
			}
			else if (tan == 1) {
				if (Opcioncami == 0) {
					playClickSound();
					finalCamino = false;
					seleccionarCaminoIzq();
					Opcioncami = -1;
				}

				if (Opcioncami == 1) {
					playClickSound();
					finalCamino = false;
					seleccionarCaminoDer();
					Opcioncami = -1;
				}
			}
		}
		currentCursor = &normalCursor;

		window->setMouseCursor(*currentCursor);

		float deltaTime = reloj.restart().asSeconds();
		animacionRastro(deltaTime);

		sf::Vector2f fichaPos = sprite->getPosition();
		float viewX = fichaPos.x;
		float viewY = fichaPos.y;

		if (viewY > 540) viewY = 540;
		if (viewX < 320) viewX = 320;
		if (viewY < 180) viewY = 180;
		view.setCenter(viewX, viewY);

		view.setSize(1280 * 0.5, 720 * 0.5);

		window->setView(view);
		window->clear();

		window->draw(spriteFondoGame);
		window->draw(spriteMapa);
		window->draw(*sprite);
		window->setView(window->getDefaultView());




		if (tan == 3) {
			window->draw(SpriteArrowArriba);


			window->draw(SpriteArrowDer);

		}
		else if (tan == 5) {
			window->draw(SpriteArrowArriba);

			window->draw(SpriteArrowIzq);
		}
		else if (tan == 1) {
			window->draw(SpriteArrowIzq);

			window->draw(SpriteArrowDer);
		}



		window->display();

	}
}


void MovePieces::seleccionarCaminoIzq() {

	if ((*casillas).size() == 1) {

		std::vector<sf::Vector2f> camino2_1 = {
			sf::Vector2f(325,523),
			sf::Vector2f(325,576),
			sf::Vector2f(323,629),
			sf::Vector2f(351,676),
			sf::Vector2f(394,678),
			sf::Vector2f(425,654)
		};



		std::vector<sf::Vector2f> caminocasa2_1 = {  };

		casillas->push_back(camino2_1);
		casillas->push_back(camino3);
	}
	else if ((*casillas).size() == 3) {
		std::vector<sf::Vector2f> camino4_1{
		sf::Vector2f(765, 623),
		sf::Vector2f(764, 577),
		sf::Vector2f(790, 539),
		sf::Vector2f(835, 540),
		sf::Vector2f(881, 540)
		};


		std::vector<sf::Vector2f> caminoimpuesto4_1 = {  };
		std::vector<sf::Vector2f> caminocasa4_1 = { sf::Vector2f(323,629), sf::Vector2f(394,678),sf::Vector2f(765, 623) };

		casillasImpuesto->push_back(caminoimpuesto4_1);
	

		casillas->push_back(camino4_1);
		casillas->push_back(camino5);
	}
	else if ((*casillas).size() == 5) {


		std::vector<sf::Vector2f> camino6_1{
			sf::Vector2f(407, 98),
		};


		casillas->push_back(camino6_1);
		casillas->push_back(camino7);

	}

}


void MovePieces::seleccionarCaminoDer() {

	if ((*casillas).size() == 1) {
		std::vector<sf::Vector2f> camino2_2{
	 sf::Vector2f(428, 517),
	 sf::Vector2f(429, 566),
	 sf::Vector2f(429, 612),
	 sf::Vector2f(425, 654)
		};

	
		std::vector<sf::Vector2f> caminoimpuesto2_2 = {  };
		std::vector<sf::Vector2f> caminocasa2_2 = {  };

		casillasImpuesto->push_back(caminoimpuesto2_2);
		

		casillas->push_back(camino2_2);
		casillas->push_back(camino3);
	}
	else if ((*casillas).size() == 3) {
		std::vector<sf::Vector2f> camino4_2{
		sf::Vector2f(817, 679),
		sf::Vector2f(869, 679),
		sf::Vector2f(923, 679),
		sf::Vector2f(955, 648),
		sf::Vector2f(955, 609),
		sf::Vector2f(955, 568),
		sf::Vector2f(926, 541),
		sf::Vector2f(881, 541)
		};

	
		std::vector<sf::Vector2f> caminoimpuesto4_2 = {  };
		std::vector<sf::Vector2f> caminocasa4_2 = {  };

		casillasImpuesto->push_back(caminoimpuesto4_2);



		casillas->push_back(camino4_2);
		casillas->push_back(camino5);
	}
	else if ((*casillas).size() == 5) {


		std::vector<sf::Vector2f> camino6_2{
	   sf::Vector2f(444, 42),
	   sf::Vector2f(398, 41),
	   sf::Vector2f(355, 40),
	   sf::Vector2f(322, 73),
	   sf::Vector2f(320, 118),
	   sf::Vector2f(328, 161),
	   sf::Vector2f(365, 168)
		};

	
		std::vector<sf::Vector2f> caminoimpuesto6_2 = { sf::Vector2f(790, 539),sf::Vector2f(444, 42), sf::Vector2f(320, 118),sf::Vector2f(869, 679),sf::Vector2f(428, 517) };
		std::vector<sf::Vector2f> caminocasa6_2 = {  };

		casillasImpuesto->push_back(caminoimpuesto6_2);
		casillasImpuesto->push_back(caminoimpuesto7);


		casillas->push_back(camino6_2);
		casillas->push_back(camino7);

	}

}

void MovePieces::animacionRastro(float deltaTime) {
	static float tiempoAcumulado = 0.0f;
	float intervalo = 0.1f;

	tiempoAcumulado += deltaTime;


	if (tiempoAcumulado >= intervalo) {
		sf::Sprite copia = *sprite;
		copia.setColor(sf::Color(255, 255, 255, 50));
		rastro.push_back(copia);
		tiempoAcumulado = 0.0f;
	}

	
	for (auto& s : rastro) {
		sf::Color color = s.getColor();
		if (color.a > 0) {
			color.a -= static_cast<sf::Uint8>(30 * deltaTime);
			s.setColor(color);
		}
	}

	rastro.erase(std::remove_if(rastro.begin(), rastro.end(), [](const sf::Sprite& s) {
		return s.getColor().a <= 0;
		}), rastro.end());
}



void MovePieces::animacionRebote(sf::Vector2f posicionFinal, float deltaTime) {

	float distancia = static_cast<float>(std::sqrt(std::pow(posicionFinal.x - sprite->getPosition().x, 2) + std::pow(posicionFinal.y - sprite->getPosition().y, 2)));
	if (distancia < 5.0f) {
		float rebote = std::sin(deltaTime * 10) * 5;
		sprite->move(0, 4);
	}
}

void MovePieces::animacionRotacion(float deltaTime) {
	timer += deltaTime;

	const float rotacionDerecha = 20.0f;
	const float rotacionIzquierda = 40.0f;

	if (timer >= tiempoCambio) {
		if (girarIzquierda) {

			sprite->rotate(rotacionDerecha);
			rotacionActual += rotacionDerecha;
		}
		else {

			sprite->rotate(-rotacionIzquierda);
			rotacionActual -= rotacionIzquierda;
		}


		girarIzquierda = !girarIzquierda;
		timer = 0.0f;
	}


	if (std::abs(rotacionActual) >= rotacionIzquierda) {

		sprite->setRotation(0.0f);
		rotacionActual = 0.0f;
	}
}




void MovePieces::animacionEscala(float deltaTime) {
	float escalaMaxima = 1.1f;
	float escalaMinima = 1.0f;
	float velocidadEscala = 2.0f;

	float factorEscala = escalaMinima + (escalaMaxima - escalaMinima) * std::sin(velocidadEscala * deltaTime);
	sprite->setScale(factorEscala, factorEscala);
}
