#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Cinematic.hpp"

int main() {
    // Crear la ventana en main
    sf::RenderWindow window(sf::VideoMode(1500, 1000), "Ventana SFML");

    // Crear una instancia de la clase Cinematic y pasarle la ventana por referencia
    Cinematic cinematic(window);

    // Cargar los recursos necesarios para la cinem�tica
    cinematic.Resource();

    // Iniciar la animaci�n
    cinematic.Update();

    return EXIT_SUCCESS;
}

