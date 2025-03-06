#include "MovePiecesO.hpp"
#include "../../core/ResourceGlobal.hpp"
#include "../../core/ObjetosGlobal.hpp"
#include "../../ui/ResourceGeneral.hpp"

MovePiecesO::MovePiecesO(sf::RenderWindow& win) : window(&win), sprite(nullptr), casillas(nullptr), caminoActual(0), casillaActual(0), enMovimiento(false), t(0.0f), casillasRestantes(0), rotacionActual(0.0f), rotacionMaxima(30.0f), velocidadRotacion(90.0f), girarIzquierda(true), tiempoCambio(0.5f), timer(0.0f), duracionMovimiento(0.0f), finalCamino(false) {};
void MovePiecesO::Inicializar(sf::Sprite* spriteC, std::vector<std::vector<sf::Vector2f>>* casillasC, int* vuel, sf::Vector2f fin, bool* CsFin, bool PiecUser) {
	this->sprite = spriteC;
	this->casillas = casillasC;
	this->vuelta = vuel;
	this->final = fin;
	this->CsFinal = CsFin;
	PieceUser = PiecUser;
	*vuelta = 2;
}
void MovePiecesO::iniciarMovimiento(int numeroCasillas, float duracion) {
	casillasRestantes = numeroCasillas;

	if (caminoActual + 1 > (*casillas).size() ) {

		finalCamino = true;
		//std::cout << " caminoActual + 1" << caminoActual + 1 << "(*casillas).size()" << (*casillas).size();
		updateCAmbioCasilla();
		posicionFinal = (*casillas)[caminoActual][casillaActual];
		this->duracionMovimiento = duracion;
		this->t = 0.0f;
		this->enMovimiento = true;
	}else if (caminoActual < casillas->size() && casillaActual < (*casillas)[caminoActual].size()) {

		posicionInicial = sprite->getPosition();
		posicionFinal = (*casillas)[caminoActual][casillaActual];
		this->duracionMovimiento = duracion;
		this->t = 0.0f;
		this->enMovimiento = true;
	}
}
int MovePiecesO::getCaminoActual() {
	return caminoActual;
}
int MovePiecesO::getcasillaActual() {
	return casillaActual;
}
void MovePiecesO::actualizarMovimiento(float deltaTime) {
	std::cout << "\n Peinci" ;
	if (enMovimiento && !finalCamino) {
		t += deltaTime / duracionMovimiento;
		std::cout <<"\n"<< *CsFinal;
		while (t > 1.0f && casillasRestantes > 0 && !*CsFinal) {
			t -= 1.0f;

			sprite->setPosition(posicionFinal);


			casillaActual++;
			casillasRestantes--;


			if (*vuelta < 3) {
			if (casillaActual >= (*casillas)[caminoActual].size()) {
				casillaActual = 0;

				//std::cout << "\nCasi caso";
				if (caminoActual + 1 == 7 && casillasRestantes != 0) {
					*vuelta += 1;

					if (*vuelta > 3) {
						*vuelta = 3;
					}

					if (*vuelta == 3) {


						posicionFinal = final;
						casillasRestantes = 1;


					}
					else {
						(*casillas).resize(1);
						caminoActual = -1;


					}


				}
				else
					if (caminoActual + 1 >= (*casillas).size() && casillasRestantes != 0) {

						finalCamino = true;

						updateCAmbioCasilla();
					}
				caminoActual++;



			}
		}
		
			if(casillasRestantes!=0){
			posicionInicial = sprite->getPosition();
			if (*vuelta != 3) {
			posicionFinal = (*casillas)[caminoActual][casillaActual];}
			}
		}

		if (enMovimiento && casillasRestantes > 0 && !*CsFinal) {

			 
			sf::Vector2f nuevaPosicion = posicionInicial + (posicionFinal - posicionInicial) * t;
			sprite->setPosition(nuevaPosicion);

			if (*vuelta == 3&& sprite->getPosition()== final){

				*CsFinal = true;
				casillasRestantes = 0;

				enMovimiento = false;
				turn_Move = false;
				turnRule = true;


				if (PieceUser) {

					//client.llegadaFinal();
					
				}
			}
		}
		else {		
			
			enMovimiento = false;
			turn_Move = false;
			turnRule = true;
			if (*vuelta == 3) {

				*CsFinal = true;
			


				if (PieceUser) {

					//client.llegadaFinal();

				}
			}


		}
		if (casillasRestantes != 0) {
			animacionRebote(posicionFinal, deltaTime);
		}



	}
	//std::cout << "\n Peinci11111111111";
}
void MovePiecesO::updateCAmbioCasilla() {

	int tan = static_cast<int>((*casillas).size());
//	std::cout << "\nturn:" << turn;

	if (tan == 3) {
		SpriteUpArrow.setPosition(370, 400);

		RightArrow.setPosition(900, 400);

	}
	else if (tan == 5) {
		SpriteUpArrow.setPosition(900, 400);

		LeftArrow.setPosition(370, 400);
	}
	else if (tan == 1) {
		LeftArrow.setPosition(370, 400);

		RightArrow.setPosition(900, 400);
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

			if (firstTurn) {
				if (event.type == sf::Event::Closed ||
					(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {

					renderTexture.clear();
					renderTexture.draw(spriteBackgroundG);
					renderTexture.draw(MapSprite);
					for (int i = 0; i < 4; i++)
					{
						renderTexture.draw(playerGameOff[i].NamePlayer);
						renderTexture.draw(playerGameOff[i].boxPlayer);
						renderTexture.draw(playerGameOff[i].MarcoPlayer);
						renderTexture.draw(playerGameOff[i].AvatarPlayer);
					}
					renderTexture.draw(spriteX);
					renderTexture.draw(overlay);
					renderTexture.display();
					Menup.MenuSalir(nullptr);

				}



				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

					if (tan == 3) {
						if (SpriteUpArrow.getGlobalBounds().contains(mousePosFloat)) {
							playClickSound();
							finalCamino = false;
						//	client.networkMessage.sendPathOption(0);
							seleccionarCaminoIzq();
							
						}

						if (RightArrow.getGlobalBounds().contains(mousePosFloat)) {
							playClickSound();
							finalCamino = false;
						//	client.networkMessage.sendPathOption(1);
							seleccionarCaminoDer();
						}

					}
					else if (tan == 5) {
						if (SpriteUpArrow.getGlobalBounds().contains(mousePosFloat)) {
							playClickSound();
							finalCamino = false;
							//client.networkMessage.sendPathOption(0);
							seleccionarCaminoDer();
							
						}

						if (LeftArrow.getGlobalBounds().contains(mousePosFloat)) {
							playClickSound();
							finalCamino = false;
							//client.networkMessage.sendPathOption(1);
							seleccionarCaminoIzq();
						}
					}
					else if (tan == 1) {
						if (LeftArrow.getGlobalBounds().contains(mousePosFloat)) {
							playClickSound();
							finalCamino = false;
							//client.networkMessage.sendPathOption(0);
							seleccionarCaminoIzq();
						}

						if (RightArrow.getGlobalBounds().contains(mousePosFloat)) {
							playClickSound();
							finalCamino = false;
						//	client.networkMessage.sendPathOption(1);
							seleccionarCaminoDer();
						}
					}


				}

			}
		}




		if (!firstTurn) {

		//	std::cout << "\nRoadOption:" << RoadOption;
			if (tan == 3) {
				if (RoadOption == 0) {
					playClickSound();
					finalCamino = false;
					seleccionarCaminoIzq();
					RoadOption = -1;
				}

				if (RoadOption == 1) {
					playClickSound();
					finalCamino = false;
					seleccionarCaminoDer();
					RoadOption = -1;
				}

			}
			else if (tan == 5) {
				if (RoadOption == 0) {
					playClickSound();
					finalCamino = false;
					seleccionarCaminoDer();
					RoadOption = -1;
				}

				if (RoadOption == 1) {
					playClickSound();
					finalCamino = false;
					seleccionarCaminoIzq();
					RoadOption = -1;
				}
			}
			else if (tan == 1) {
				if (RoadOption == 0) {
					playClickSound();
					finalCamino = false;
					seleccionarCaminoIzq();
					RoadOption = -1;
				}

				if (RoadOption == 1) {
					playClickSound();
					finalCamino = false;
					seleccionarCaminoDer();
					RoadOption = -1;
				}
			}
		}
		currentCursor = &normalCursor;

		window->setMouseCursor(*currentCursor);

		float deltaTime = watch.restart().asSeconds();
		animacionRastro(deltaTime);

		sf::Vector2f fichaPos = sprite->getPosition();
		float viewX = fichaPos.x;
		float viewY = fichaPos.y;

		if (viewY > 540) viewY = 540;
		if (viewX < 320) viewX = 320;
		if (viewY < 180) viewY = 180;
		vision.setCenter(viewX, viewY);

		vision.setSize(1280 * 0.5, 720 * 0.5);

		window->setView(vision);
		window->clear();

		window->draw(spriteBackgroundG);
		window->draw(MapSprite);
		window->draw(*sprite);
		window->setView(window->getDefaultView());




		if (tan == 3) {
			window->draw(SpriteUpArrow);


			window->draw(RightArrow);

		}
		else if (tan == 5) {
			window->draw(SpriteUpArrow);

			window->draw(LeftArrow);
		}
		else if (tan == 1) {
			window->draw(LeftArrow);

			window->draw(RightArrow);
		}



		window->display();

	}
}
void MovePiecesO::seleccionarCaminoIzq() {

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
void MovePiecesO::seleccionarCaminoDer() {

	if ((*casillas).size() == 1) {
		std::vector<sf::Vector2f> camino2_2{
	 sf::Vector2f(428, 517),
	 sf::Vector2f(429, 566),
	 sf::Vector2f(429, 612),
	 sf::Vector2f(425, 654)
		};

	
		std::vector<sf::Vector2f> caminoimpuesto2_2 = {  };
		std::vector<sf::Vector2f> caminocasa2_2 = {  };

		

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



		casillas->push_back(camino6_2);
		casillas->push_back(camino7);

	}

}
void MovePiecesO::animacionRastro(float deltaTime) {
	static float tiempoAcumulado = 0.0f;
	float intervalo = 0.1f;

	tiempoAcumulado += deltaTime;


	if (tiempoAcumulado >= intervalo) {
		sf::Sprite copia = *sprite;
		copia.setColor(sf::Color(255, 255, 255, 50));
		trace.push_back(copia);
		tiempoAcumulado = 0.0f;
	}

	
	for (auto& s : trace) {
		sf::Color color = s.getColor();
		if (color.a > 0) {
			color.a -= static_cast<sf::Uint8>(30 * deltaTime);
			s.setColor(color);
		}
	}

	trace.erase(std::remove_if(trace.begin(), trace.end(), [](const sf::Sprite& s) {
		return s.getColor().a <= 0;
		}), trace.end());
}
void MovePiecesO::animacionRebote(sf::Vector2f posicionFinal, float deltaTime) {

	float distancia = static_cast<float>(std::sqrt(std::pow(posicionFinal.x - sprite->getPosition().x, 2) + std::pow(posicionFinal.y - sprite->getPosition().y, 2)));
	if (distancia < 5.0f) {
		float rebote = std::sin(deltaTime * 10) * 5;
		sprite->move(0, 4);
	}
}
void MovePiecesO::animacionRotacion(float deltaTime) {
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
void MovePiecesO::animacionEscala(float deltaTime) {
	float escalaMaxima = 1.1f;
	float escalaMinima = 1.0f;
	float velocidadEscala = 2.0f;

	float factorEscala = escalaMinima + (escalaMaxima - escalaMinima) * std::sin(velocidadEscala * deltaTime);
	sprite->setScale(factorEscala, factorEscala);
}
