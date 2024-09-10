#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Cinematic.hpp"
#include "FadeEffect.hpp"
#include "menuP.hpp"

int main() {
    // Obtener la lista de modos de video soportados
      // El primer modo suele ser el m�s grande

    // Crear la ventana en pantalla completa
    sf::RenderWindow window(sf::VideoMode(1280,720), "Juego en Pantalla Completa",sf::Style::Fullscreen);

    // Configuraci�n del frame rate (opcional)
    window.setFramerateLimit(60);

    // Crear la ventana en main
    //sf::RenderWindow window(sf::VideoMode(1280,720), "Ventana SFML");
    
    sf::Image icono;
    if (!icono.loadFromFile("resource/texture/fortunepocho23.png"))
    {
        std::cerr << "Error al cargar la imagen del �cono" << std::endl;
        return EXIT_FAILURE;
    }

    // Establecer el �cono de la ventana
    window.setIcon(icono.getSize().x, icono.getSize().y, icono.getPixelsPtr());


    // Crear una instancia de la clase Cinematic y pasarle la ventana por referencia
    Cinematic cinematic(window);

    // Cargar los recursos necesarios para la cinem�tica
    cinematic.Resource();

    //Iniciar la animaci�n
    cinematic.Update();

    menuP Menup(window);

    // Cargar los recursos necesarios para la cinem�tica
    Menup.Resource();

    // Iniciar la animaci�n
    Menup.Update();


    return EXIT_SUCCESS;
}

