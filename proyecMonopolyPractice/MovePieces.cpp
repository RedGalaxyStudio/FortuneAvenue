#include "MovePieces.hpp"
#include "ResourceGlobal.hpp"

MovePieces::MovePieces(sf::RenderWindow& win): window(&win), sprite(nullptr), casillas(nullptr), caminoActual(0), casillaActual(0), enMovimiento(false), t(0.0f), casillasRestantes(0), rotacionActual(0.0f), rotacionMaxima(30.0f), velocidadRotacion(90.0f), girarIzquierda(true), tiempoCambio(0.5f), timer(0.0f){};


void MovePieces::Inicializar(sf::Sprite* spriteC, std::vector<std::vector<sf::Vector2f>>* casillasC) {
    this->sprite = spriteC;
    this->casillas = casillasC;
    
    //camino3 = { sf::Vector2f(473,661), sf::Vector2f(505, 632), sf::Vector2f(505 , 586), sf::Vector2f(519 , 544), sf::Vector2f(556 , 544), sf::Vector2f(568 ,586), sf::Vector2f(568 , 636), sf::Vector2f(580 , 678), sf::Vector2f(621 , 677), sf::Vector2f(632 , 637), sf::Vector2f(632 , 585), sf::Vector2f(642 , 542), sf::Vector2f(678,542), sf::Vector2f(694 ,582), sf::Vector2f(694 , 636), sf::Vector2f(725 , 668) };
}


void MovePieces::iniciarMovimiento(int numeroCasillas, float duracion) {
    casillasRestantes = numeroCasillas;  // Guardar cuántas casillas debe moverse

    // Avanzar a la siguiente casilla antes de iniciar el movimiento
    if (caminoActual < casillas->size() && casillaActual < (*casillas)[caminoActual].size()) {
      
        posicionInicial = sprite->getPosition();
        posicionFinal = (*casillas)[caminoActual][casillaActual];
        this->duracionMovimiento = duracion;
        this->t = 0.0f;
        this->enMovimiento = true;
    }
}


void MovePieces::actualizarMovimiento(float deltaTime) {

    if (enMovimiento && !finalCamino) {
        t += deltaTime / duracionMovimiento;

        while (t > 1.0f && casillasRestantes > 0) { // Bucle para moverse por varias casillas
            t -= 1.0f;  // Descontamos 1.0 para que no se pierdan los pasos         

            sprite->setPosition(posicionFinal);  // Asegura que está en la posición exacta


             casillaActual++;
            casillasRestantes--;

            if (casillaActual >= (*casillas)[caminoActual].size()) {
                casillaActual = 0;

                if (caminoActual+1 >= (*casillas).size()) {
                    
                    finalCamino = true;
                
                      updateCAmbioCasilla();
                }
                
                caminoActual++;
                if (caminoActual >= 7) {
                    caminoActual = 0;
                    casillas->resize(1);// Reiniciar caminos si es necesario
                }

            }

           


            // Establecer nuevas posiciones inicial y final
            posicionInicial = sprite->getPosition();
            posicionFinal = (*casillas)[caminoActual][casillaActual];
        }

        if (enMovimiento && casillasRestantes > 0) {
            // Interpolación lineal entre la posición inicial y final
            sf::Vector2f nuevaPosicion = posicionInicial + (posicionFinal - posicionInicial) * t;
            sprite->setPosition(nuevaPosicion);
        }
        else {
            enMovimiento = false;  // Terminar el movimiento si ya no hay casillas restantes
        }

        animacionRebote(posicionFinal, deltaTime);

    }

}



void MovePieces::updateCAmbioCasilla() {


    while (finalCamino == true) {

        sf::Event event;

        while (window->pollEvent(event)) {

            sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
            sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {

                renderTexture.clear();
                renderTexture.draw(spriteFondoGame);
                renderTexture.draw(spriteMapa);
                for (int i = 0; i < 4; i++)
                {
                    renderTexture.draw(NamePlayers[i]);
                    renderTexture.draw(boxPlayers[i]);
                    renderTexture.draw(MarcoPlayers[i]);
                    renderTexture.draw(AvatarPlayers[i]);
                }
                renderTexture.draw(spriteX);
                renderTexture.draw(overlay);
                renderTexture.display();
                Menup.MenuSalir();

                running = false; // Cambia el estado de ejecución
            }


            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // Verificar el click en "si" y cerrar la vetana

                if (SpriteArrowIzq.getGlobalBounds().contains(mousePosFloat)) {
                    playClickSound();
                    finalCamino = false;
                    seleccionarCaminoIzq();
                }

                if (SpriteArrowDer.getGlobalBounds().contains(mousePosFloat)) {
                    playClickSound();
                    finalCamino = false;
                    seleccionarCaminoDer();
                }


            }

        }

        currentCursor = &normalCursor;

        window->setMouseCursor(*currentCursor);

        float deltaTime = reloj.restart().asSeconds();
        animacionRastro( deltaTime);

        sf::Vector2f fichaPos = sprite->getPosition();
        float viewX = fichaPos.x;
        float viewY = fichaPos.y;

        if (viewY > 540) viewY = 540;
        if (viewX < 320) viewX = 320;
        if (viewY < 180) viewY = 180;
        view.setCenter(viewX, viewY); // Actualizar la vista centrada en la nueva posición

        view.setSize(1280 * 0.5, 720 * 0.5); // Actualizar el tamaño de la vista

        window->setView(view); // Establecer la vista antes de dibujar
        window->clear();

        window->draw(spriteFondoGame);
        window->draw(spriteMapa);
      //  for (const auto& s : rastro) {
       //     window->draw(s);
        //}
        window->draw(*sprite);
        window->setView(window->getDefaultView()); // Volver a la vista original


            window->draw(SpriteArrowIzq);
            window->draw(SpriteArrowDer);
        

        window->display();

    }

}


void MovePieces::seleccionarCaminoIzq() {



    if((*casillas).size() == 1){
    std::vector<sf::Vector2f> camino2_1 = { sf::Vector2f(325,523), sf::Vector2f(325,576), sf::Vector2f(323,629), sf::Vector2f(351,676), sf::Vector2f(394,678), sf::Vector2f(425,654) };
    casillas->push_back(camino2_1);
    casillas->push_back(camino3);
    }else if ((*casillas).size() == 3){
        std::vector<sf::Vector2f> camino4_1{
sf::Vector2f(765, 623),
sf::Vector2f(764, 577),
sf::Vector2f(790, 539),
sf::Vector2f(835, 540),
sf::Vector2f(881, 540)

    };

        casillas->push_back(camino4_1);
        casillas->push_back(camino5);
    }else if ((*casillas).size() == 5) {


        std::vector<sf::Vector2f> camino6_1{
sf::Vector2f(407, 98),
//sf::Vector2f(402, 157)
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
    casillas->push_back(camino4_2);
    casillas->push_back(camino5);
    }else if((*casillas).size() == 5){


     std::vector<sf::Vector2f> camino6_2{
    sf::Vector2f(444, 42),
    sf::Vector2f(398, 41),
    sf::Vector2f(355, 40),
    sf::Vector2f(322, 73),
    sf::Vector2f(320, 118),
    sf::Vector2f(328, 161),
    sf::Vector2f(365, 168)
        };


        casillas->push_back(camino6_2);
        casillas->push_back(camino7);

    }

}

            //Animaciones

void MovePieces::animacionRastro(float deltaTime) {
    static float tiempoAcumulado = 0.0f;  // Acumular el tiempo para generar menos copias
    float intervalo = 0.1f;  // Generar una nueva copia cada 0.1 segundos (ajusta a tus necesidades)

    tiempoAcumulado += deltaTime;

    // Generar una copia solo cada cierto intervalo de tiempo
    if (tiempoAcumulado >= intervalo) {
        sf::Sprite copia = *sprite;  // Crear una copia del sprite
        copia.setColor(sf::Color(255, 255, 255, 50));  // Hacer la copia más transparente (a=50)
        rastro.push_back(copia);  // Añadirla al rastro
        tiempoAcumulado = 0.0f;  // Reiniciar el contador de tiempo
    }

    // Desvanecer el rastro
    for (auto& s : rastro) {
        sf::Color color = s.getColor();
        if (color.a > 0) {
            color.a -= static_cast<sf::Uint8>(30 * deltaTime);  // Reducir la opacidad más lentamente para un desvanecimiento más suave
            s.setColor(color);
        }
    }

    // Eliminar rastros completamente invisibles
    rastro.erase(std::remove_if(rastro.begin(), rastro.end(), [](const sf::Sprite& s) {
        return s.getColor().a <= 0;
        }), rastro.end());
}



void MovePieces::animacionRebote(sf::Vector2f posicionFinal, float deltaTime) {
    // Movimiento elástico usando una función de rebote
    float distancia = static_cast<float>(std::sqrt(std::pow(posicionFinal.x - sprite->getPosition().x, 2) + std::pow(posicionFinal.y - sprite->getPosition().y, 2)));
    if (distancia < 5.0f) {  // Si está lo suficientemente cerca de la casilla
        float rebote = std::sin(deltaTime * 10) * 5;  // Pequeño rebote
        sprite->move(0, 4);  // Mover solo en eje Y para simular rebote
    }
}

void MovePieces::animacionRotacion(float deltaTime) {
    timer += deltaTime; // Aumentar el timer

    // Definimos los ángulos de rotación
    const float rotacionDerecha = 20.0f;  // Rotar 20 grados a la derecha
    const float rotacionIzquierda = 40.0f; // Rotar 40 grados a la izquierda

    // Cambiar la dirección de la rotación basado en el tiempo
    if (timer >= tiempoCambio) {
        if (girarIzquierda) {
            // Girar 20 grados a la derecha
            sprite->rotate(rotacionDerecha);
            rotacionActual += rotacionDerecha; // Actualizar la rotación actual
        }
        else {
            // Girar 40 grados a la izquierda
            sprite->rotate(-rotacionIzquierda);
            rotacionActual -= rotacionIzquierda; // Actualizar la rotación actual
        }

        // Cambiar la dirección para el siguiente ciclo
        girarIzquierda = !girarIzquierda; // Cambiar la dirección
        timer = 0.0f; // Reiniciar el timer
    }

    // Volver a la rotación original después de las rotaciones
    if (std::abs(rotacionActual) >= rotacionIzquierda) {
        // Restablecer a la posición original
        sprite->setRotation(0.0f); // Restablecer la rotación del sprite
        rotacionActual = 0.0f; // Reiniciar la rotación actual
    }
}




void MovePieces::animacionEscala(float deltaTime) {
    float escalaMaxima = 1.1f; // Tamaño máximo de escala
    float escalaMinima = 1.0f; // Tamaño normal
    float velocidadEscala = 2.0f; // Velocidad de la animación de escalado

    // Escala hacia arriba y hacia abajo en un ciclo continuo
    float factorEscala = escalaMinima + (escalaMaxima - escalaMinima) * std::sin(velocidadEscala * deltaTime);
    sprite->setScale(factorEscala, factorEscala);
}
