#include "MovePieces.hpp"
#include "../../core/ResourceGlobal.hpp"
#include "../../core/ObjetosGlobal.hpp"
#include "../../ui/ResourceGeneral.hpp"

sf::Texture MovePieces::TextureArrowIzq;
sf::Texture MovePieces::TextureArrowDer;
sf::Texture MovePieces::TextureArrowArriba;
sf::Texture MovePieces::TextureArrowAbajo;

MovePieces::MovePieces(sf::RenderWindow& win, Client* clienT) : window(&win),client(clienT), sprite(nullptr), casillas(nullptr), caminoActual(0), casillaActual(0), enMovimiento(false), t(0.0f), casillasRestantes(0), rotacionActual(0.0f), rotacionMaxima(30.0f), velocidadRotacion(90.0f), girarIzquierda(true), tiempoCambio(0.5f), timer(0.0f), duracionMovimiento(0.0f), finalCamino(false) {
	static bool texturesLoaded = false;
	if (!texturesLoaded) {
		TextureArrowIzq.loadFromFile("assets/image/Game/izq.png");
		TextureArrowDer.loadFromFile("assets/image/Game/der.png");
		TextureArrowArriba.loadFromFile("assets/image/Game/arriba.png");
		TextureArrowAbajo.loadFromFile("assets/image/Game/abajo.png");
		texturesLoaded = true;
	}
	LeftArrow.setTexture(TextureArrowIzq);
	LeftArrow.setOrigin(65, 42);
	//	LeftArrow.setPosition(370, 400);

	RightArrow.setTexture(TextureArrowDer);
	RightArrow.setOrigin(65, 42);
	//	RightArrow.setPosition(900, 400);

	DownArrow.setTexture(TextureArrowAbajo);
	DownArrow.setOrigin(42, 65);
	//	DownArrow.setPosition(900, 400);


	SpriteUpArrow.setTexture(TextureArrowArriba);
	SpriteUpArrow.setOrigin(42, 65);
	//SpriteUpArrow.setPosition(370, 400);

};
void MovePieces::Inicializar(sf::Sprite* spriteC, std::vector<std::vector<sf::Vector2f>>* casillasC, int* vuel, sf::Vector2f fin, bool* CsFin, bool PiecUser) {
	this->sprite = spriteC;
	this->casillas = casillasC;
	this->vuelta = vuel;
	this->final = fin;
	this->CsFinal = CsFin;
	PieceUser = PiecUser;
	*vuelta = 1;
}
void MovePieces::iniciarMovimiento(int numeroCasillas, float duracion) {
	casillasRestantes = numeroCasillas;

	if (caminoActual + 1 > (*casillas).size() ) {

		finalCamino = true;
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
int MovePieces::getCaminoActual() {
	return caminoActual;
}
int MovePieces::getcasillaActual() {
	return casillaActual;
}
void MovePieces::actualizarMovimiento(float deltaTime) {
	if (enMovimiento && !finalCamino) {
		t += deltaTime / duracionMovimiento;
		while (t > 1.0f && casillasRestantes > 0 && !*CsFinal) {
			t -= 1.0f;
			sprite->setPosition(posicionFinal);

			casillaActual++;
			casillasRestantes--;
			
			if (*vuelta < 3) {
			if (casillaActual >= (*casillas)[caminoActual].size()) {
				casillaActual = 0;
				
				if (caminoActual + 1 == 7 && casillasRestantes != 0) {
					*vuelta += 1;
				
					if (*vuelta > 2) {
						*vuelta = 2;
						
					}
				
					if (*vuelta == 2) {


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
		
			if (*vuelta != 2) {
			
			posicionFinal = (*casillas)[caminoActual][casillaActual];}
			}
		}

		if (enMovimiento && casillasRestantes > 0 && !*CsFinal) {
	
			sf::Vector2f nuevaPosicion = posicionInicial + (posicionFinal - posicionInicial) * t;
			sprite->setPosition(nuevaPosicion);
			
			if (*vuelta == 2&& sprite->getPosition()== final){
				casillasRestantes = 0;
			
				enMovimiento = false;
				turn_Moviendo = false;
				giroRule = true;

				if (PieceUser) {

					client->networkMessage.llegadaFinal();
					
				}		
			}
		}
		else {		
		
			enMovimiento = false;
			turn_Moviendo = false;
			giroRule = true;
			if (*vuelta == 2) {
				
				*CsFinal = true;
			
				if (PieceUser) {

					client->networkMessage.llegadaFinal();

				}
				
			}


		}
		if (casillasRestantes != 0) {
			
			animacionRebote(posicionFinal, deltaTime);
			
		}
	}
}
void MovePieces::updateCAmbioCasilla() {

	int tan = static_cast<int>((*casillas).size());

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

			if (turn) {
				if (event.type == sf::Event::Closed ||
					(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {

					renderTexture.clear();
					renderTexture.draw(spriteBackgroundG);
					renderTexture.draw(spriteMapa);
					for (int i = 0; i < UsuariosActivos.size(); i++)
					{
						renderTexture.draw(playersGame[i].NamePlayer);
						renderTexture.draw(playersGame[i].boxPlayer);
						renderTexture.draw(playersGame[i].MarcoPlayer);
						renderTexture.draw(playersGame[i].AvatarPlayer);
					}
					renderTexture.draw(spriteX);
					renderTexture.draw(overlay);
					renderTexture.display();
					Menup.MenuSalir(client);

				}



				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

					if (tan == 3) {
						if (SpriteUpArrow.getGlobalBounds().contains(mousePosFloat)) {
							playClickSound();
							finalCamino = false;
							client->networkMessage.sendPathOption(0);
							seleccionarCaminoIzq();
							
						}

						if (RightArrow.getGlobalBounds().contains(mousePosFloat)) {
							playClickSound();
							finalCamino = false;
							client->networkMessage.sendPathOption(1);
							seleccionarCaminoDer();
						}

					}
					else if (tan == 5) {
						if (SpriteUpArrow.getGlobalBounds().contains(mousePosFloat)) {
							playClickSound();
							finalCamino = false;
							client->networkMessage.sendPathOption(0);
							seleccionarCaminoDer();
							
						}

						if (LeftArrow.getGlobalBounds().contains(mousePosFloat)) {
							playClickSound();
							finalCamino = false;
							client->networkMessage.sendPathOption(1);
							seleccionarCaminoIzq();
						}
					}
					else if (tan == 1) {
						if (LeftArrow.getGlobalBounds().contains(mousePosFloat)) {
							playClickSound();
							finalCamino = false;
							client->networkMessage.sendPathOption(0);
							seleccionarCaminoIzq();
						}

						if (RightArrow.getGlobalBounds().contains(mousePosFloat)) {
							playClickSound();
							finalCamino = false;
							client->networkMessage.sendPathOption(1);
							seleccionarCaminoDer();
						}
					}


				}

			}
		}




		if (!turn) {

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

		window->draw(spriteBackgroundG);
		window->draw(spriteMapa);
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
