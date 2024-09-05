#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Cinematic.hpp"
int main()
{
    sf::Clock clock;

    sf::RenderWindow window(sf::VideoMode(1500, 1000), "Ventana SFML");
    sf::Image icono;
    if (!icono.loadFromFile("resource/texture/256x256.png"))
    {
        std::cerr << "Error al cargar la imagen del ícono" << std::endl;
        return EXIT_FAILURE;
    }

    // Establecer el ícono de la ventana
    window.setIcon(icono.getSize().x, icono.getSize().y, icono.getPixelsPtr());

    Cinematic pantallaDeCarga(window);

    pantallaDeCarga.iniciarCarga();
    
    // Iniciar el ciclo del juego
    while (window.isOpen())
    {
        // Procesar eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Cerrar ventana: salir
            if (event.type == sf::Event::Closed)
                window.close();
        }

    
    }

    return EXIT_SUCCESS;
}
