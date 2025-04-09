#include "MovePiecesO.hpp"
#include "../../core/ResourceGlobal.hpp"
#include "../../core/ObjetosGlobal.hpp"
#include "../../ui/ResourceGeneral.hpp"


sf::Texture MovePiecesO::TextureArrowIzq;
sf::Texture MovePiecesO::TextureArrowDer;
sf::Texture MovePiecesO::TextureArrowArriba;
sf::Texture MovePiecesO::TextureArrowAbajo;


MovePiecesO::MovePiecesO(sf::RenderWindow& win, int mapauso) : window(&win), sprite(nullptr), mapaActual(mapauso), casillas(nullptr), caminoActual(0), casillaActual(0), enMovimiento(false), t(0.0f), casillasRestantes(0), rotacionActual(0.0f), rotacionMaxima(30.0f), velocidadRotacion(90.0f), girarIzquierda(true), tiempoCambio(0.5f), timer(0.0f), duracionMovimiento(0.0f), finalCamino(false) {

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

	if (mapaActual == 3) {
		posSelecCAm = { sf::Vector2f(858.500f, 332.500f),	sf::Vector2f(855.000f, 427.500f),sf::Vector2f(506.833f, 516.500f),sf::Vector2f(330.167f, 459.833f), sf::Vector2f(470.167f, 268.500f),sf::Vector2f(828.167f, 157.500f) };
	}
	else if (mapaActual == 2) {


		posSelecCAm = { sf::Vector2f(641.833f, 688.500f),sf::Vector2f(641.750f, 550.250f),sf::Vector2f(642.167f, 448.833f),sf::Vector2f(386.833f, 153.500f), sf::Vector2f(641.750f, 170.000f) };

	}

};
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

	if (caminoActual + 1 > (*casillas).size()) {

		finalCamino = true;
		updateCAmbioCasilla();
		posicionInicial = sprite->getPosition();
		posicionFinal = (*casillas)[caminoActual][casillaActual];
		this->duracionMovimiento = duracion;
		this->t = 0.0f;
		this->enMovimiento = true;
	}
	else if (caminoActual < casillas->size() && casillaActual < (*casillas)[caminoActual].size()) {

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

			if (casillasRestantes != 0) {
				posicionInicial = sprite->getPosition();
				if (*vuelta != 3) {
					posicionFinal = (*casillas)[caminoActual][casillaActual];
				}
			}
		}

		if (enMovimiento && casillasRestantes > 0 && !*CsFinal) {


			sf::Vector2f nuevaPosicion = posicionInicial + (posicionFinal - posicionInicial) * t;
			sprite->setPosition(nuevaPosicion);

			if (*vuelta == 3 && sprite->getPosition() == final) {

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
}
void MovePiecesO::updateCAmbioCasilla() {



	switch (mapaActual) {
	case 1: // Configuración para el mapa 1

		tan = static_cast<int>((*casillas).size());
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

		break;

	case 2:
		for (int i = 0; i < posSelecCAm.size(); i++)
		{
			if (posSelecCAm[i] == sprite->getPosition()) {
				tan = i + 1;
			}
		}

		std::cout << "hola\n\n" << tan;
		if (tan == 3) {

			DownArrow.setPosition(370, 400);

			SpriteUpArrow.setPosition(900, 400);

		}
		else if (tan == 4) {

			SpriteUpArrow.setPosition(370, 400);

			RightArrow.setPosition(900, 400);

		}

		else if (tan == 2) {
			LeftArrow.setPosition(370, 400);

			SpriteUpArrow.setPosition(900, 400);
		}
		else if (tan == 1) {
			LeftArrow.setPosition(370, 400);

			SpriteUpArrow.setPosition(900, 400);
		}
		else if (tan == 5) {
			RightArrow.setPosition(900, 400);

			SpriteUpArrow.setPosition(370, 400);
		}


		if (tan == 6) {
			caminoActual = 0;
			casillas->resize(1);
			finalCamino = false;
			caminoActual--;

		}

		break;

	case 3: // Configuración para el mapa 3

		for (int i = 0; i < posSelecCAm.size(); i++)
		{
			if (posSelecCAm[i] == sprite->getPosition()) {
				tan = i + 1;
			}
		}

		std::cout << "hola\n\n" << tan;
		if (tan == 3) {

			DownArrow.setPosition(370, 400);

			SpriteUpArrow.setPosition(900, 400);

		}
		else if (tan == 2 || tan == 4) {
			RightArrow.setPosition(900, 400);

			LeftArrow.setPosition(370, 400);
		}
		else if (tan == 1) {
			LeftArrow.setPosition(370, 400);

			DownArrow.setPosition(900, 400);
		}
		else if (tan == 5) {
			LeftArrow.setPosition(370, 400);

			RightArrow.setPosition(900, 400);
		}


		if (tan == 6) {
			caminoActual = 0;
			casillas->resize(1);
			finalCamino = false;
			caminoActual--;

		}

		break;
	}



	if (secondTurn) {

		GM.bot.resetTCAM();
	}

	while (finalCamino == true) {

		sf::Event event;
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
		sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

		while (window->pollEvent(event)) {
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
			if (firstTurn) {


				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
					switch (mapaActual) {
					case 1: // Configuración para el mapa 1
						if (tan == 3) {
							if (SpriteUpArrow.getGlobalBounds().contains(mousePosFloat)) {
								playClickSound();
								finalCamino = false;
								//	client.networkMessage.sendPathOption(0);
								selCamIzq1();

							}

							if (RightArrow.getGlobalBounds().contains(mousePosFloat)) {
								playClickSound();
								finalCamino = false;
								//	client.networkMessage.sendPathOption(1);
								selCamDer1();
							}

						}
						else if (tan == 5) {
							if (SpriteUpArrow.getGlobalBounds().contains(mousePosFloat)) {
								playClickSound();
								finalCamino = false;
								//client.networkMessage.sendPathOption(0);
								selCamDer1();

							}

							if (LeftArrow.getGlobalBounds().contains(mousePosFloat)) {
								playClickSound();
								finalCamino = false;
								//client.networkMessage.sendPathOption(1);
								selCamIzq1();
							}
						}
						else if (tan == 1) {
							if (LeftArrow.getGlobalBounds().contains(mousePosFloat)) {
								playClickSound();
								finalCamino = false;
								//client.networkMessage.sendPathOption(0);
								selCamIzq1();
							}

							if (RightArrow.getGlobalBounds().contains(mousePosFloat)) {
								playClickSound();
								finalCamino = false;
								//	client.networkMessage.sendPathOption(1);
								selCamDer1();
							}
						}
						break;

					case 2:
						if (tan == 3) {
							if (LeftArrow.getGlobalBounds().contains(mousePosFloat)) {
								playClickSound();
								finalCamino = false;
								selCamIzq2();

							}

							if (RightArrow.getGlobalBounds().contains(mousePosFloat)) {
								playClickSound();
								finalCamino = false;
								selCamDer2();
							}

						}
						else if (tan == 4 || tan == 5) {
							if (RightArrow.getGlobalBounds().contains(mousePosFloat)) {
								playClickSound();
								finalCamino = false;
								//client.networkMessage.sendPathOption(0);
								selCamDer2();

							}

							if (SpriteUpArrow.getGlobalBounds().contains(mousePosFloat)) {
								playClickSound();
								finalCamino = false;
								//client.networkMessage.sendPathOption(1);
								selCamIzq2();
							}
						}
						else if (tan == 1 || tan == 2) {
							if (LeftArrow.getGlobalBounds().contains(mousePosFloat)) {
								playClickSound();
								finalCamino = false;
								selCamIzq2();
							}

							if (SpriteUpArrow.getGlobalBounds().contains(mousePosFloat)) {
								playClickSound();
								finalCamino = false;
								selCamDer2();
							}
						}



						break;

					case 3: // Configuración para el mapa 3
						if (tan == 3) {
							if (DownArrow.getGlobalBounds().contains(mousePosFloat)) {
								playClickSound();
								finalCamino = false;
								selCamIzq3();

							}

							if (SpriteUpArrow.getGlobalBounds().contains(mousePosFloat)) {
								playClickSound();
								finalCamino = false;
								selCamDer3();
							}

						}
						else if (tan == 4 || tan == 2) {
							if (RightArrow.getGlobalBounds().contains(mousePosFloat)) {
								playClickSound();
								finalCamino = false;
								//client.networkMessage.sendPathOption(0);
								selCamDer3();

							}

							if (LeftArrow.getGlobalBounds().contains(mousePosFloat)) {
								playClickSound();
								finalCamino = false;
								//client.networkMessage.sendPathOption(1);
								selCamIzq3();
							}
						}
						else if (tan == 1) {
							if (LeftArrow.getGlobalBounds().contains(mousePosFloat)) {
								playClickSound();
								finalCamino = false;
								selCamIzq3();
							}

							if (DownArrow.getGlobalBounds().contains(mousePosFloat)) {
								playClickSound();
								finalCamino = false;
								selCamDer3();
							}
						}
						else if (tan == 5) {
							if (LeftArrow.getGlobalBounds().contains(mousePosFloat)) {
								playClickSound();
								finalCamino = false;
								selCamIzq3();
							}

							if (RightArrow.getGlobalBounds().contains(mousePosFloat)) {
								playClickSound();
								finalCamino = false;
								selCamDer3();
							}
						}
						break;
					}



				}

			}
		}

		if (secondTurn) {

			if (GM.bot.roll()) {

				RoadOption = GM.bot.eleccion();

			}
		}


		if (!firstTurn) {
			switch (mapaActual) {
			case 1: // Configuración para el mapa 1
				if (tan == 3) {
					if (RoadOption == 0) {
						playClickSound();
						finalCamino = false;
						selCamIzq1();
						RoadOption = -1;
					}

					if (RoadOption == 1) {
						playClickSound();
						finalCamino = false;
						selCamDer1();
						RoadOption = -1;
					}

				}
				else if (tan == 5) {
					if (RoadOption == 0) {
						playClickSound();
						finalCamino = false;
						selCamDer1();
						RoadOption = -1;
					}

					if (RoadOption == 1) {
						playClickSound();
						finalCamino = false;
						selCamIzq1();
						RoadOption = -1;
					}
				}
				else if (tan == 1) {
					if (RoadOption == 0) {
						playClickSound();
						finalCamino = false;
						selCamIzq1();
						RoadOption = -1;
					}

					if (RoadOption == 1) {
						playClickSound();
						finalCamino = false;
						selCamDer1();
						RoadOption = -1;
					}
				}
				break;

			case 2:
				if (tan == 3) {
					if (RoadOption == 0) {
						playClickSound();
						finalCamino = false;
						selCamIzq2();
						RoadOption = -1;
					}

					if (RoadOption == 1) {
						playClickSound();
						finalCamino = false;
						selCamDer2();
						RoadOption = -1;
					}

				}
				else if (tan == 4 || tan == 5) {
					if (RoadOption == 0) {
						playClickSound();
						finalCamino = false;
						selCamIzq2();
						RoadOption = -1;
					}

					if (RoadOption == 1) {
						playClickSound();
						finalCamino = false;
						selCamDer2();
						RoadOption = -1;
					}

				}
				else if (tan == 1 || tan == 2) {
					if (RoadOption == 0) {
						playClickSound();
						finalCamino = false;
						selCamDer2();
						RoadOption = -1;
					}

					if (RoadOption == 1) {
						playClickSound();
						finalCamino = false;
						selCamIzq2();
						RoadOption = -1;
					}
				}

				break;

			case 3: // Configuración para el mapa 3
				if (tan == 3) {
					if (RoadOption == 0) {
						playClickSound();
						finalCamino = false;
						selCamIzq3();
						RoadOption = -1;
					}

					if (RoadOption == 1) {
						playClickSound();
						finalCamino = false;
						selCamDer3();
						RoadOption = -1;
					}

				}
				else if (tan == 4 || tan == 2) {
					if (RoadOption == 0) {
						playClickSound();
						finalCamino = false;
						selCamIzq3();
						RoadOption = -1;
					}

					if (RoadOption == 1) {
						playClickSound();
						finalCamino = false;
						selCamDer3();
						RoadOption = -1;
					}

				}
				else if (tan == 5) {
					if (RoadOption == 0) {
						playClickSound();
						finalCamino = false;
						selCamDer3();
						RoadOption = -1;
					}

					if (RoadOption == 1) {
						playClickSound();
						finalCamino = false;
						selCamIzq3();
						RoadOption = -1;
					}
				}
				else if (tan == 1) {
					if (RoadOption == 0) {
						playClickSound();
						finalCamino = false;
						selCamIzq3();
						RoadOption = -1;
					}

					if (RoadOption == 1) {
						playClickSound();
						finalCamino = false;
						selCamDer3();
						RoadOption = -1;
					}
				}
				break;
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


		switch (mapaActual) {
		case 1: // Configuración para el mapa 1
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
			break;

		case 2:
			if (tan == 3) {
				window->draw(LeftArrow);

				//std::cout << "HOla";
				window->draw(RightArrow);

			}
			else if (tan == 4 || tan == 5) {
				window->draw(RightArrow);

				window->draw(SpriteUpArrow);
			}
			else if (tan == 1 || tan == 2) {
				window->draw(LeftArrow);

				window->draw(SpriteUpArrow);
			}

			break;

		case 3: // Configuración para el mapa 3
			if (tan == 3) {
				window->draw(DownArrow);

				std::cout << "HOla";
				window->draw(SpriteUpArrow);

			}
			else if (tan == 2 || tan == 4) {
				window->draw(RightArrow);

				window->draw(LeftArrow);
			}
			else if (tan == 1) {
				window->draw(LeftArrow);

				window->draw(DownArrow);
			}
			else if (tan == 5) {
				window->draw(LeftArrow);

				window->draw(RightArrow);
			}
			break;
		}





		window->display();

	}
}


void MovePiecesO::selCamIzq1() {

	if ((*casillas).size() == 1) {

		std::vector<sf::Vector2f> camino2_1 = {
			sf::Vector2f(325,523),
			sf::Vector2f(325,576),
			sf::Vector2f(323,629),
			sf::Vector2f(351,676),
			sf::Vector2f(394,678),
			sf::Vector2f(425,654)
		};
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





		casillas->push_back(camino4_1);
		casillas->push_back(camino5);
	}
	else if ((*casillas).size() == 5) {


		std::vector<sf::Vector2f> camino6_1{
			sf::Vector2f(407, 98),
		};
		std::vector<sf::Vector2f> camino7{
			// sf::Vector2f(407, 98),
			 sf::Vector2f(402, 157),
			 sf::Vector2f(442, 209),
			 sf::Vector2f(413, 253),
			 sf::Vector2f(364, 283),
			 sf::Vector2f(368, 339)
		};

		casillas->push_back(camino6_1);
		casillas->push_back(camino7);

	}

}
void MovePiecesO::selCamDer1() {

	if ((*casillas).size() == 1) {
		std::vector<sf::Vector2f> camino2_2{
	 sf::Vector2f(428, 517),
	 sf::Vector2f(429, 566),
	 sf::Vector2f(429, 612),
	 sf::Vector2f(425, 654)
		};

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


		std::vector<sf::Vector2f> camino7{
			// sf::Vector2f(407, 98),
			 sf::Vector2f(402, 157),
			 sf::Vector2f(442, 209),
			 sf::Vector2f(413, 253),
			 sf::Vector2f(364, 283),
			 sf::Vector2f(368, 339)
		};

		casillas->push_back(camino6_2);
		casillas->push_back(camino7);

	}

}

void MovePiecesO::selCamIzq2() {

	if (tan == 1) {

		std::vector<sf::Vector2f> camino2 = {
			sf::Vector2f(574.167f, 684.833f),
			sf::Vector2f(502.167f, 656.833f),
			sf::Vector2f(436.000f, 617.500f),
			sf::Vector2f(386.500f, 564.750f)
		};

		std::vector<sf::Vector2f> camino3 = {
			sf::Vector2f(348.625f, 504.062f),
			sf::Vector2f(322.500f, 437.167f),
			sf::Vector2f(312.500f, 364.833f),
			sf::Vector2f(320.167f, 288.500f),
			sf::Vector2f(345.500f, 220.167f),
			sf::Vector2f(386.833f, 153.500f)
		};

		casillas->push_back(camino2);
		casillas->push_back(camino3);
	}
	else if (tan == 2) {

		std::vector<sf::Vector2f> camino3 = {
	sf::Vector2f(588.000f, 551.000f),
	sf::Vector2f(538.250f, 551.750f),
	sf::Vector2f(485.500f, 524.833f),
	sf::Vector2f(412.833f, 498.167f)
		};

		std::vector<sf::Vector2f> camino4 = {
			sf::Vector2f(348.625f, 504.062f),
			sf::Vector2f(322.500f, 437.167f),
			sf::Vector2f(312.500f, 364.833f),
			sf::Vector2f(320.167f, 288.500f),
			sf::Vector2f(345.500f, 220.167f),
			sf::Vector2f(386.833f, 153.500f)
		};

		casillas->push_back(camino3);
		casillas->push_back(camino4);





	}
	else if (tan == 3) {

		std::vector<sf::Vector2f> camino22 = {
	sf::Vector2f(584.000f, 450.000f),
	sf::Vector2f(558.833f, 407.500f),
	sf::Vector2f(552.167f, 360.167f),
	sf::Vector2f(559.500f, 310.167f),
	sf::Vector2f(584.167f, 274.167f)
		};



		std::vector<sf::Vector2f> camino25 = {
			sf::Vector2f(640.250f, 269.000f),
			sf::Vector2f(641.500f, 222.500f),
			sf::Vector2f(641.750f, 170.000f)
		};

		casillas->push_back(camino22);
		casillas->push_back(camino25);


	}
	else if (tan == 4) {
		std::vector<sf::Vector2f> camino27 = {
	sf::Vector2f(441.500f, 99.000f),
	sf::Vector2f(502.500f, 63.500f),
	sf::Vector2f(568.500f, 40.750f)
		};


		std::vector<sf::Vector2f> camino28 = {
			sf::Vector2f(642.500f, 31.250f),
			sf::Vector2f(714.250f, 36.750f),
			sf::Vector2f(779.500f, 64.000f),
			sf::Vector2f(844.500f, 101.500f),
			sf::Vector2f(896.500f, 155.000f),
			sf::Vector2f(933.000f, 212.000f),
			sf::Vector2f(955.500f, 261.000f),
			sf::Vector2f(967.000f, 309.000f),
			sf::Vector2f(971.500f, 360.500f),
			sf::Vector2f(965.500f, 417.500f),
			sf::Vector2f(952.500f, 470.500f),
			sf::Vector2f(931.000f, 515.500f)
		};

		casillas->push_back(camino27);
		casillas->push_back(camino28);
	}
	else if (tan == 5) {

		std::vector<sf::Vector2f> camino29 = {
	sf::Vector2f(641.167f, 120.500f),
	sf::Vector2f(641.500f, 78.500f)
		};

		std::vector<sf::Vector2f> camino28 = {
			sf::Vector2f(642.500f, 31.250f),
			sf::Vector2f(714.250f, 36.750f),
			sf::Vector2f(779.500f, 64.000f),
			sf::Vector2f(844.500f, 101.500f),
			sf::Vector2f(896.500f, 155.000f),
			sf::Vector2f(933.000f, 212.000f),
			sf::Vector2f(955.500f, 261.000f),
			sf::Vector2f(967.000f, 309.000f),
			sf::Vector2f(971.500f, 360.500f),
			sf::Vector2f(965.500f, 417.500f),
			sf::Vector2f(952.500f, 470.500f),
			sf::Vector2f(931.000f, 515.500f)
		};
		casillas->push_back(camino29);
		casillas->push_back(camino28);


	}

}
void MovePiecesO::selCamDer2() {


	if (tan == 1) {


		std::vector<sf::Vector2f> camino2 = {
			sf::Vector2f(640.750f, 638.750f),
			sf::Vector2f(641.250f, 602.750f),
			sf::Vector2f(641.750f, 550.250f)
		};
		casillas->push_back(camino2);
	}
	else if (tan == 2) {


		std::vector<sf::Vector2f> camino21 = {
			sf::Vector2f(642.000f, 500.000f),
			sf::Vector2f(642.167f, 448.833f)
		};
		casillas->push_back(camino21);



	}
	else if (tan == 3) {



		std::vector<sf::Vector2f> camino23 = {
			sf::Vector2f(698.000f, 450.000f),
			sf::Vector2f(726.833f, 408.833f),
			sf::Vector2f(732.167f, 358.500f),
			sf::Vector2f(727.500f, 310.500f),
			sf::Vector2f(701.167f, 272.833f)
		};

		std::vector<sf::Vector2f> camino25 = {
			sf::Vector2f(640.250f, 269.000f),
			sf::Vector2f(641.500f, 222.500f),
			sf::Vector2f(641.750f, 170.000f)
		};
		casillas->push_back(camino23);
		casillas->push_back(camino25);


	}
	else if (tan == 4) {
		std::vector<sf::Vector2f> camino26 = {
	sf::Vector2f(441.250f, 168.000f),
	sf::Vector2f(508.500f, 166.750f),
	sf::Vector2f(576.500f, 167.750f),
	sf::Vector2f(641.750f, 170.000f)
		};

		casillas->push_back(camino26);

	}
	else if (tan == 5) {

		std::vector<sf::Vector2f> camino30 = {
	sf::Vector2f(700.500f, 168.833f),
	sf::Vector2f(766.000f, 168.500f),
	sf::Vector2f(834.500f, 170.000f)
		};


		std::vector<sf::Vector2f> camino28 = {
			sf::Vector2f(896.500f, 155.000f),
			sf::Vector2f(933.000f, 212.000f),
			sf::Vector2f(955.500f, 261.000f),
			sf::Vector2f(967.000f, 309.000f),
			sf::Vector2f(971.500f, 360.500f),
			sf::Vector2f(965.500f, 417.500f),
			sf::Vector2f(952.500f, 470.500f),
			sf::Vector2f(931.000f, 515.500f)
		};

		casillas->push_back(camino30);
		casillas->push_back(camino28);

	}

}

void MovePiecesO::selCamIzq3() {

	if (tan == 1) {

		std::vector<sf::Vector2f> camino2_1 = {
		sf::Vector2f(800.500f, 333.000f),
	sf::Vector2f(758.500f, 333.000f),
	sf::Vector2f(715.000f, 335.000f),
	sf::Vector2f(661.500f, 335.000f),
	sf::Vector2f(660.500f, 397.000f),
	sf::Vector2f(660.000f, 463.500f)
		};

		std::vector<sf::Vector2f> camino3 = {
			sf::Vector2f(660.833f, 532.500f),
			sf::Vector2f(602.833f, 532.500f),
			sf::Vector2f(556.167f, 530.500f),
			sf::Vector2f(506.833f, 516.500f)
		};


		casillas->push_back(camino2_1);
		casillas->push_back(camino3);
	}
	else if (tan == 2) {

		std::vector<sf::Vector2f> camino3 = {
				sf::Vector2f(803.000f, 436.500f),
				sf::Vector2f(759.000f, 476.000f),
				//	sf::Vector2f(761.500f, 584.000f),
					sf::Vector2f(746.500f, 534.000f),
					sf::Vector2f(660.833f, 532.500f),
					sf::Vector2f(602.833f, 532.500f),
					sf::Vector2f(556.167f, 530.500f),
					sf::Vector2f(506.833f, 516.500f)
		};
		casillas->push_back(camino3);
	}
	else if (tan == 3) {


		std::vector<sf::Vector2f> camino9 = {
		sf::Vector2f(483.000f, 570.000f),
		sf::Vector2f(438.833f, 597.833f),
		sf::Vector2f(385.500f, 597.167f),
		sf::Vector2f(341.500f, 570.500f),
		sf::Vector2f(320.167f, 513.833f),
		sf::Vector2f(330.167f, 459.833f)
		};





		//casillas->push_back(camino5_1);
		casillas->push_back(camino9);
	}
	else if (tan == 4) {
		std::vector<sf::Vector2f> camino11 = {
	sf::Vector2f(288.000f, 416.000f),
	sf::Vector2f(254.167f, 362.167f),
	sf::Vector2f(248.833f, 302.833f),
	sf::Vector2f(280.833f, 254.833f),
	sf::Vector2f(308.167f, 207.500f)
		};
		std::vector<sf::Vector2f> camino12 = {
	sf::Vector2f(348.000f, 160.000f),
	sf::Vector2f(400.167f, 126.833f),
	sf::Vector2f(453.500f, 128.167f)
		};

		std::vector<sf::Vector2f> camino13 = {
	sf::Vector2f(506.000f, 150.000f),
	sf::Vector2f(556.833f, 127.500f),
	sf::Vector2f(604.833f, 128.167f),
	sf::Vector2f(661.500f, 128.833f),
	sf::Vector2f(722.833f, 127.500f),
	sf::Vector2f(778.167f, 130.833f),
	sf::Vector2f(828.167f, 157.500f)
		};


		casillas->push_back(camino11);
		casillas->push_back(camino12);
		casillas->push_back(camino13);

	}
	else if (tan == 5) {


		std::vector<sf::Vector2f> camino11 = {
	sf::Vector2f(419.500f, 261.500f),
	sf::Vector2f(380.833f, 218.167f)
		};

		std::vector<sf::Vector2f> camino12 = {
	sf::Vector2f(348.000f, 160.000f),
	sf::Vector2f(400.167f, 126.833f),
	sf::Vector2f(453.500f, 128.167f)
		};

		std::vector<sf::Vector2f> camino13 = {
	sf::Vector2f(506.000f, 150.000f),
	sf::Vector2f(556.833f, 127.500f),
	sf::Vector2f(604.833f, 128.167f),
	sf::Vector2f(661.500f, 128.833f),
	sf::Vector2f(722.833f, 127.500f),
	sf::Vector2f(778.167f, 130.833f),
	sf::Vector2f(828.167f, 157.500f)
		};


		casillas->push_back(camino11);
		casillas->push_back(camino12);
		casillas->push_back(camino13);

	}

}
void MovePiecesO::selCamDer3() {

	if (tan == 1) {
		std::vector<sf::Vector2f> camino2_2 = {
	sf::Vector2f(855.000f, 427.500f)

		};



		casillas->push_back(camino2_2);

	}
	else if (tan == 2) {


		std::vector<sf::Vector2f> camino3 = {
				sf::Vector2f(916.000f, 449.000f),
				sf::Vector2f(950.500f, 510.500f),
				sf::Vector2f(944.500f, 580.500f),
				sf::Vector2f(893.500f, 621.500f),
				sf::Vector2f(842.500f, 631.000f),
				sf::Vector2f(792.000f, 619.000f),
				sf::Vector2f(761.500f, 584.000f),
				sf::Vector2f(746.500f, 534.000f),
				sf::Vector2f(660.833f, 532.500f),
				sf::Vector2f(602.833f, 532.500f),
				sf::Vector2f(556.167f, 530.500f),
				sf::Vector2f(506.833f, 516.500f)
		};
		casillas->push_back(camino3);
	}
	else if (tan == 3) {
		std::vector<sf::Vector2f> camino5_1 = {
			sf::Vector2f(496.500f, 462.833f),
			sf::Vector2f(458.500f, 425.500f),
			sf::Vector2f(470.833f, 379.833f),
			sf::Vector2f(470.167f, 331.833f),
			sf::Vector2f(470.167f, 268.500f)
		};




		casillas->push_back(camino5_1);
		//	casillas->push_back(camino5);
	}
	else if (tan == 4) {

		std::vector<sf::Vector2f> camino10 = {
			sf::Vector2f(366.883f, 429.070f),
			sf::Vector2f(411.743f, 413.369f),
			sf::Vector2f(458.500f, 425.500f),
			sf::Vector2f(470.833f, 379.833f),
			sf::Vector2f(470.167f, 331.833f),
			sf::Vector2f(470.167f, 268.500f)
		};


		casillas->push_back(camino10);

	}
	else if (tan == 5) {

		std::vector<sf::Vector2f> camino10 = {
	sf::Vector2f(474.000f, 207.000f)
		};
		std::vector<sf::Vector2f> camino13 = {
sf::Vector2f(506.000f, 150.000f),
sf::Vector2f(556.833f, 127.500f),
sf::Vector2f(604.833f, 128.167f),
sf::Vector2f(661.500f, 128.833f),
sf::Vector2f(722.833f, 127.500f),
sf::Vector2f(778.167f, 130.833f),
sf::Vector2f(828.167f, 157.500f)
		};

		casillas->push_back(camino10);
		casillas->push_back(camino13);



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