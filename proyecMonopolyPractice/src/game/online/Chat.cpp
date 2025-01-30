#include "Chat.hpp"
#include "../../core/ObjetosGlobal.hpp"
#include "../../ui/ButtonG.hpp"
#include "../../ui/TextBox.hpp"
#include "../../ui/MensageBox.hpp"

Chat::Chat(sf::RenderWindow& win) : window(&win), pieceselector(window) {
	loadResourceGame();
	resource();
}


int calcularNumeroDeLineas(const sf::Text& text) {
	// Obtener el rect�ngulo delimitador (bounding box) del texto
	sf::FloatRect bounds = text.getGlobalBounds();

	// Dividir la altura del rect�ngulo entre la altura de la fuente
	// Esto nos da el n�mero de l�neas
	float alturaLinea = text.getCharacterSize();  // El tama�o de la fuente
	int numeroDeLineas = static_cast<int>(bounds.height / alturaLinea);

	return numeroDeLineas;
}

void Chat::resource() {

	TextureBotonEviar.loadFromFile("assets/image/envio2.png");

	if (!Fuentechat.loadFromFile("assets/fonts/Poppins-MediumItalic.ttf")) { std::cerr << "Error loading font/n";}
	if (!FuenteMensaje.loadFromFile("assets/fonts/Poppins-Light.ttf")) { std::cerr << "Error loading font/n"; }

	SpriteBotonEnviar.setTexture(TextureBotonEviar);
	SpriteBotonEnviar.setOrigin(20, 20);
	SpriteBotonEnviar.setPosition(1245, 675);

	spriteX.setPosition(1240, 35);

	enunciado.setCharacterSize(28);
	enunciado.setFont(fontUser);
	enunciado.setFillColor(sf::Color::White);
	enunciado.setOutlineThickness(2);
	enunciado.setOutlineColor(sf::Color(135, 135, 135));
	enunciado.setString("CHAT");
	enunciado.setPosition(1090, 30);
	sf::FloatRect globalBounds = enunciado.getGlobalBounds();
	enunciado.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);


	indicacion.setCharacterSize(20);
	indicacion.setFont(Fuentechat);
	indicacion.setFillColor(sf::Color::White);
	indicacion.setOutlineThickness(2);
	indicacion.setOutlineColor(sf::Color(135, 135, 135));
	indicacion.setString("Ingrese texto.");
	indicacion.setPosition(940, 668);
	globalBounds = indicacion.getGlobalBounds();
	indicacion.setOrigin(0, globalBounds.height / 2.0f);
	
	Fondo.setOrigin(0,0);
	Fondo.setSize( sf::Vector2f(380, 720));
	Fondo.setPosition(900, 0);
	Fondo.setFillColor(sf::Color(60,60,60));
	Fondo.setOutlineThickness(-10);
	Fondo.setOutlineColor(sf::Color(50,50,50));


	FondoChat.setSize(sf::Vector2f(380, 60));
	FondoChat.setPosition(900, 0);
	FondoChat.setFillColor(sf::Color(50, 50, 50));

	
	Caja.setSize(sf::Vector2f(260, 40));
	Caja.setPosition(940, 650);
	Caja.setFillColor(sf::Color (50, 50, 50));

	CajaI.setSize(sf::Vector2f(20,0));
	CajaI.setPosition(940, 670);
	CajaI.setFillColor(sf::Color(50, 50, 50));
	CajaI.setOrigin(20,0);

	CajaD.setSize(sf::Vector2f(20,0));
	CajaD.setPosition(1200, 670);
	CajaD.setFillColor(sf::Color(50, 50, 50));
	
	ArriDerecha.setOrigin(20, 20);
	ArriDerecha.setRadius(20);
	ArriDerecha.setFillColor(sf::Color (50,50,50));
	ArriDerecha.setPosition(1200, 670);

	ArriIzquierda.setOrigin(20, 20);
	ArriIzquierda.setRadius(20);
	ArriIzquierda.setFillColor(sf::Color (50, 50, 50));
	ArriIzquierda.setPosition(940, 670);

	AbajDerecha.setOrigin(20, 20);
	AbajDerecha.setRadius(20);
	AbajDerecha.setFillColor(sf::Color(50, 50, 50));
	AbajDerecha.setPosition(1200, 670);

	AbajIzquierda.setOrigin(20, 20);
	AbajIzquierda.setRadius(20);
	AbajIzquierda.setFillColor(sf::Color(50, 50, 50));
	AbajIzquierda.setPosition(940, 670);


	PlantillaMensajeE.SMSEnviado.setCharacterSize(15);
	PlantillaMensajeE.SMSEnviado.setFont(FuenteMensaje);
	PlantillaMensajeE.SMSEnviado.setFillColor(sf::Color::White);
	PlantillaMensajeE.SMSEnviado.setOutlineThickness(1);
	PlantillaMensajeE.SMSEnviado.setOutlineColor(sf::Color(117, 220, 255));
	PlantillaMensajeE.SMSEnviado.setString("MensajeEnviado");
	PlantillaMensajeE.SMSEnviado.setPosition(940, 618);
	globalBounds = PlantillaMensajeE.SMSEnviado.getGlobalBounds();
	PlantillaMensajeE.SMSEnviado.setOrigin(0, globalBounds.height / 2.0f);

	PlantillaMensajeE.ContenidoEnviado.setSize(sf::Vector2f(260, 40));
	PlantillaMensajeE.ContenidoEnviado.setPosition(940, 600);
	PlantillaMensajeE.ContenidoEnviado.setFillColor(sf::Color(0, 104, 167));



	PlantillaMensajeR.SMSRecibido.setCharacterSize(20);
	PlantillaMensajeR.SMSRecibido.setFont(FuenteMensaje);
	PlantillaMensajeR.SMSRecibido.setFillColor(sf::Color::White);
	PlantillaMensajeR.SMSRecibido.setOutlineThickness(1);
	PlantillaMensajeR.SMSRecibido.setOutlineColor(sf::Color(255, 168, 214));
	PlantillaMensajeR.SMSRecibido.setString("MensajeRecibido");
	PlantillaMensajeR.SMSRecibido.setPosition(940, 568);
	globalBounds = PlantillaMensajeR.SMSRecibido.getGlobalBounds();
	PlantillaMensajeR.SMSRecibido.setOrigin(0, globalBounds.height / 2.0f);

	PlantillaMensajeR.ContenidoRecibido.setSize(sf::Vector2f(260, 40));
	PlantillaMensajeR.ContenidoRecibido.setPosition(940, 550);
	PlantillaMensajeR.ContenidoRecibido.setFillColor(sf::Color(239, 39, 133));
}

void Chat::insertarSaltoDeLinea() {
	if (input.empty()) return;
	std::string aux = input;
	// Crear un texto temporal para medir cada segmento
	sf::Text tempText;
	tempText.setFont(Fuentechat);
	tempText.setCharacterSize(indicacion.getCharacterSize());
	tempText.setStyle(indicacion.getStyle());

	// Iterar sobre el texto y ajustar
	size_t posicionUltimoEspacio = 0;
	for (size_t i = 0; i < input.size(); ++i) {
		tempText.setString(input.substr(0, i + 1));
		if (tempText.getGlobalBounds().width > 260) {
			if (posicionUltimoEspacio > 0) {
				input[posicionUltimoEspacio] = '\n'; // Reemplazar el espacio con un salto de l�nea
				posicionUltimoEspacio = 0;          // Reiniciar el �ltimo espacio
			}
			else {
				aux.pop_back();
				tempText.setString(aux);

				if (tempText.getGlobalBounds().width > 260) {
					input.insert(i-1, "\n"); // Insertar un salto de l�nea si no hay espacio disponible

				}
				else {

			    input.insert(i, "\n"); // Insertar un salto de l�nea si no hay espacio disponible

				}

	
			}
			break;
		}
		if (input[i] == ' ') {
			posicionUltimoEspacio = i;
		}
	}
}

void Chat::update() {
	Valida = false;

	bool valida2 = false;
	while (window->isOpen() && !valida2) {
		sf::Event event;
		mousePosition = sf::Mouse::getPosition(*window);
		mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

		while (window->pollEvent(event)) {

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				if (SpriteBotonEnviar.getGlobalBounds().contains(mousePosFloat) && !input.empty()) {
					playClickSound();
					PlantillaMensajeE.SMSEnviado.setString(input);
					PlantillaMensajeE.ContenidoEnviado.setSize(sf::Vector2f(PlantillaMensajeE.SMSEnviado.getGlobalBounds().width + 20,
					PlantillaMensajeE.SMSEnviado.getGlobalBounds().height + 10));

					input = "";
					indicacion.setString(input);


					for (int i = 0; i < Mensajes.size(); i++) {

						Mensajes[i].ContenidoEnviado.setPosition(Mensajes[i].positionContenidoEnviado);
						Mensajes[i].SMSEnviado.setPosition(Mensajes[i].positionSMSEnviado);
					}

					Aumento = 0;
					float aux = PlantillaMensajeE.ContenidoEnviado.getGlobalBounds().height;


					int In = calcularNumeroDeLineas(PlantillaMensajeE.SMSEnviado) + 1;
					///	int Ca = Caja.getGlobalBounds().height / 40;
					///	if (Ca > In && Ca) {
					if (In == 1) {
						sf::FloatRect altura = PlantillaMensajeE.SMSEnviado.getGlobalBounds();

						PlantillaMensajeE.ContenidoEnviado.setSize(sf::Vector2f(altura.width + 20, 40));
						PlantillaMensajeE.ContenidoEnviado.setPosition(1280 - (PlantillaMensajeE.ContenidoEnviado.getGlobalBounds().width + 20), 600);
						PlantillaMensajeE.SMSEnviado.setPosition(1280 - (PlantillaMensajeE.ContenidoEnviado.getGlobalBounds().width + 10), 618);
						PlantillaMensajeE.positionContenidoEnviado = PlantillaMensajeE.ContenidoEnviado.getPosition();;
						PlantillaMensajeE.positionSMSEnviado = PlantillaMensajeE.SMSEnviado.getPosition();

						PlantillaMensajeR.ContenidoRecibido.setSize(sf::Vector2f(altura.width + 20, 40));
						PlantillaMensajeR.ContenidoRecibido.setPosition(1280 - (PlantillaMensajeR.ContenidoRecibido.getGlobalBounds().width + 20), 600);
						PlantillaMensajeR.SMSRecibido.setPosition(1280 - (PlantillaMensajeR.ContenidoRecibido.getGlobalBounds().width + 10), 618);
						PlantillaMensajeR.positionContenidoRecibido = PlantillaMensajeR.ContenidoRecibido.getPosition();;
						PlantillaMensajeR.positionSMSRecibido = PlantillaMensajeR.SMSRecibido.getPosition();
					}

					else if (In > 1) {
						indicacion.setPosition(940, 668);
						Caja.setSize(sf::Vector2f(260, 40));
						Caja.setPosition(940, 650);
						CajaI.setSize(sf::Vector2f(20, 0));
						CajaI.setPosition(940, 670);
						CajaD.setSize(sf::Vector2f(20, 0));
						CajaD.setPosition(1200, 670);
						ArriDerecha.setPosition(1200, 670);
						ArriIzquierda.setPosition(940, 670);
						AbajDerecha.setPosition(1200, 670);
						AbajIzquierda.setPosition(940, 670);


						sf::FloatRect altura = PlantillaMensajeE.SMSEnviado.getGlobalBounds();
		
						PlantillaMensajeE.ContenidoEnviado.setSize(sf::Vector2f(altura.width + 20, altura.height + 22));
						PlantillaMensajeE.ContenidoEnviado.setPosition(sf::Vector2f(1280 - (PlantillaMensajeE.ContenidoEnviado.getGlobalBounds().width + 20), 640 - PlantillaMensajeE.ContenidoEnviado.getGlobalBounds().height));
						PlantillaMensajeE.SMSEnviado.setPosition(sf::Vector2f(1280 - (PlantillaMensajeE.ContenidoEnviado.getGlobalBounds().width + 10), PlantillaMensajeE.ContenidoEnviado.getPosition().y + 18));
						PlantillaMensajeE.positionContenidoEnviado = PlantillaMensajeE.ContenidoEnviado.getPosition();
						PlantillaMensajeE.positionSMSEnviado = PlantillaMensajeE.SMSEnviado.getPosition();


						PlantillaMensajeR.ContenidoRecibido.setSize(sf::Vector2f(altura.width + 20, altura.height + 22));
						PlantillaMensajeR.ContenidoRecibido.setPosition(sf::Vector2f(1280 - (PlantillaMensajeR.ContenidoRecibido.getGlobalBounds().width + 20), 640 - PlantillaMensajeR.ContenidoRecibido.getGlobalBounds().height));
						PlantillaMensajeR.SMSRecibido.setPosition(sf::Vector2f(1280 - (PlantillaMensajeR.ContenidoRecibido.getGlobalBounds().width + 10), PlantillaMensajeR.ContenidoRecibido.getPosition().y + 18));
						PlantillaMensajeR.positionContenidoRecibido = PlantillaMensajeR.ContenidoRecibido.getPosition();
						PlantillaMensajeR.positionSMSRecibido = PlantillaMensajeR.SMSRecibido.getPosition();
					}

					aux += 20;
					Mensajes.push_back(PlantillaMensajeE);
					for (int i = 0; i < Mensajes.size()-1; i++)
					{
						Mensajes[i].ContenidoEnviado.setPosition(Mensajes[i].ContenidoEnviado.getPosition().x, Mensajes[i].ContenidoEnviado.getPosition().y - aux );
						Mensajes[i].SMSEnviado.setPosition(Mensajes[i].ContenidoEnviado.getPosition().x, Mensajes[i].ContenidoEnviado.getPosition().y +20);
						Mensajes[i].positionContenidoEnviado = Mensajes[i].ContenidoEnviado.getPosition();
						Mensajes[i].positionSMSEnviado = Mensajes[i].SMSEnviado.getPosition();

						Mensajes[i].c.setPosition(Mensajes[i].ContenidoEnviado.getPosition().x, Mensajes[i].ContenidoEnviado.getPosition().y - aux );
						Mensajes[i].SMSEnviado.setPosition(Mensajes[i].ContenidoEnviado.getPosition().x, Mensajes[i].ContenidoEnviado.getPosition().y +20);
						Mensajes[i].positionContenidoEnviado = Mensajes[i].ContenidoEnviado.getPosition();
						Mensajes[i].positionSMSEnviado = Mensajes[i].SMSEnviado.getPosition();

					}
					

				}
			}


			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
				renderTexture.clear();
				renderTexture.draw(spriteFondoGame);
				renderTexture.draw(SpriteCrearPartida);
				renderTexture.draw(SpriteUnirsePartida);
				renderTexture.draw(enunciado);
				renderTexture.draw(indicacion);



				renderTexture.draw(spriteX);
				renderTexture.draw(overlay);
				Menup.MenuSalir();
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {


				if (spriteX.getGlobalBounds().contains(mousePosFloat) && Valida == true) {
					playClickSound();
					valida2 = true;

				}
			}

			if (event.type == sf::Event::TextEntered ) {

				if (event.text.unicode < 128) {
					if (event.text.unicode == '\b' && !input.empty()) {
						input.pop_back();
						indicacion.setString(input);

						int In = calcularNumeroDeLineas(indicacion) + 1;
						if (In == 1) {
							Caja.setSize(sf::Vector2f(260, 40));

							Caja.setPosition(940, 650);

							ArriDerecha.setPosition(sf::Vector2f(1200, 670));
							ArriIzquierda.setPosition(sf::Vector2f(940, 670));

							AbajDerecha.setPosition(1200, 670);
							AbajIzquierda.setPosition(940, 670);


							CajaD.setSize(sf::Vector2f(20, 0));
							CajaD.setPosition(sf::Vector2f(1200, 670));

							CajaI.setSize(sf::Vector2f(20, 0));
							CajaI.setPosition(sf::Vector2f(940, 670));

							for (int i = 0; i < Mensajes.size(); i++) {

								Mensajes[i].ContenidoEnviado.setPosition(Mensajes[i].positionContenidoEnviado.x, Mensajes[i].positionContenidoEnviado.y - Aumento);
								Mensajes[i].SMSEnviado.setPosition(Mensajes[i].positionSMSEnviado.x, Mensajes[i].positionSMSEnviado.y - Aumento);
							}

							Aumento = 0;
							indicacion.setPosition(940, 668);
						}
						else if (In > 1) {

							sf::FloatRect altura = indicacion.getGlobalBounds();



							Caja.setSize(sf::Vector2f(260, altura.height + 22));

							Caja.setPosition(sf::Vector2f(940, 690 - Caja.getGlobalBounds().height));
							ArriDerecha.setPosition(sf::Vector2f(1200, 710 - Caja.getGlobalBounds().height));
							ArriIzquierda.setPosition(sf::Vector2f(940, 710 - Caja.getGlobalBounds().height));

							AbajDerecha.setPosition(1200, 670);
							AbajIzquierda.setPosition(940, 670);

							CajaD.setSize(sf::Vector2f(20, AbajDerecha.getPosition().y - ArriDerecha.getPosition().y));
							CajaD.setPosition(sf::Vector2f(1200, 710 - Caja.getGlobalBounds().height));


							CajaI.setSize(sf::Vector2f(20, AbajIzquierda.getPosition().y - ArriIzquierda.getPosition().y));
							CajaI.setPosition(sf::Vector2f(940, 710 - Caja.getGlobalBounds().height));
							Aumento = altura.height - 8;


							for (int i = 0; i < Mensajes.size(); i++) {

								Mensajes[i].ContenidoEnviado.setPosition(Mensajes[i].positionContenidoEnviado.x, Mensajes[i].positionContenidoEnviado.y - Aumento);
								Mensajes[i].SMSEnviado.setPosition(Mensajes[i].positionSMSEnviado.x, Mensajes[i].positionSMSEnviado.y - Aumento);
							}

							indicacion.setPosition(sf::Vector2f(940, Caja.getPosition().y + 18));
						}

					}

					else if (event.text.unicode != '\b' && input.size() < maxLength) {
					
						char enteredChar = static_cast<char>(event.text.unicode);
							input += enteredChar; 

							indicacion.setString(input);

							if (indicacion.getGlobalBounds().width > 260) {
									insertarSaltoDeLinea();
									indicacion.setString(input);
                              	std::cout << "Holamundo:" << indicacion.getGlobalBounds().width << std::endl;
									int In = calcularNumeroDeLineas(indicacion) + 1;
								///	int Ca = Caja.getGlobalBounds().height / 40;
								///	if (Ca > In && Ca) {
										if (In == 1) {
											Caja.setSize(sf::Vector2f(260, 40));

											Caja.setPosition(940, 650);

											ArriDerecha.setPosition(sf::Vector2f(1200, 670));
											ArriIzquierda.setPosition(sf::Vector2f(940, 670));

											AbajDerecha.setPosition(1200, 670);
											AbajIzquierda.setPosition(940, 670);


											CajaD.setSize(sf::Vector2f(20, 0));
											CajaD.setPosition(sf::Vector2f(1200, 670));

											CajaI.setSize(sf::Vector2f(20, 0));
											CajaI.setPosition(sf::Vector2f(940, 670));
											for (int i = 0; i < Mensajes.size(); i++) {

												Mensajes[i].ContenidoEnviado.setPosition(Mensajes[i].positionContenidoEnviado);
												Mensajes[i].SMSEnviado.setPosition(Mensajes[i].positionSMSEnviado);
											}
											Aumento = 0;


											indicacion.setPosition(940, 668);
										}
										else if (In > 1) {

											sf::FloatRect altura = indicacion.getGlobalBounds();



											Caja.setSize(sf::Vector2f(260, altura.height + 22));

											Caja.setPosition(sf::Vector2f(940, 690 - Caja.getGlobalBounds().height));
											ArriDerecha.setPosition(sf::Vector2f(1200, 710 - Caja.getGlobalBounds().height));
											ArriIzquierda.setPosition(sf::Vector2f(940, 710 - Caja.getGlobalBounds().height));

											AbajDerecha.setPosition(1200, 670);
											AbajIzquierda.setPosition(940, 670);

											CajaD.setSize(sf::Vector2f(20, AbajDerecha.getPosition().y - ArriDerecha.getPosition().y));
											CajaD.setPosition(sf::Vector2f(1200, 710 - Caja.getGlobalBounds().height));


											CajaI.setSize(sf::Vector2f(20, AbajIzquierda.getPosition().y - ArriIzquierda.getPosition().y));
											CajaI.setPosition(sf::Vector2f(940, 710 - Caja.getGlobalBounds().height));

											Aumento = altura.height - 8;


											for (int i = 0; i < Mensajes.size(); i++){

												Mensajes[i].ContenidoEnviado.setPosition(Mensajes[i].positionContenidoEnviado.x, Mensajes[i].positionContenidoEnviado.y - Aumento);
												Mensajes[i].SMSEnviado.setPosition(Mensajes[i].positionSMSEnviado.x, Mensajes[i].positionSMSEnviado.y - Aumento);
											}

											indicacion.setPosition(sf::Vector2f(940, Caja.getPosition().y + 18));
										}



		
							}
					}
					
					
				

					
					std::cout << "Input Text: " << input << std::endl;
				}
			}
		}



		///sf::FloatRect textBounds = indicacion.getGlobalBounds();
		///float newHeight = textBounds.height + 10; // Margen adicional de 10 px (5 arriba, 5 abajo)
	///	Caja.setSize(sf::Vector2f(270, newHeight)); // Ancho fijo de 260 + 10 px de margen lateral

		/// Ajustar la posici�n de la caja y el texto
		///Caja.setPosition(sf::Vector2f(940, Caja.getPosition().y));
		///indicacion.setPosition(sf::Vector2f(945, Caja.getPosition().y + 5));

		Valida = true;

		currentCursor = &normalCursor;

		botonX->update(mousePosFloat, currentCursor, linkCursor, normalCursor);

		window->setMouseCursor(*currentCursor);



		renderTexture.clear();

		renderTexture.draw(spriteFondoGame);
		renderTexture.draw(spriteMapa);
		for (int i = 0; i < UsuariosActivos.size(); i++)
		{
			renderTexture.draw(playersGame[UsuariosActivos[i]].NamePlayer);
			renderTexture.draw(playersGame[UsuariosActivos[i]].boxPlayer);
			renderTexture.draw(playersGame[UsuariosActivos[i]].AvatarPlayer);
			renderTexture.draw(playersGame[UsuariosActivos[i]].MarcoPlayer);
		}
		renderTexture.draw(overlay);

		renderTexture.display();

		renderedSprite.setTexture(renderTexture.getTexture());

		window->clear();
		window->draw(renderedSprite);
		window->draw(Fondo);
		window->draw(Caja);
		window->draw(FondoChat);
		window->draw(SpriteBotonEnviar);
		window->draw(ArriDerecha);
		window->draw(ArriIzquierda);
		window->draw(AbajDerecha);
		window->draw(AbajIzquierda);
		window->draw(CajaI);
		window->draw(CajaD);
		window->draw(enunciado);
		window->draw(indicacion);
		window->draw(spriteX);
		//window->draw(PlantillaMensajeE.ContenidoEnviado);
		//window->draw(PlantillaMensajeE.SMSEnviado);
		//window->draw(PlantillaMensajeR.ContenidoRecibido);
		//window->draw(PlantillaMensajeR.SMSRecibido);

		for (int i = 0; i < Mensajes.size(); i++)
		{
			window->draw(Mensajes[i].ContenidoEnviado);
			window->draw(Mensajes[i].SMSEnviado);
		}
		window->display();

	}
}

