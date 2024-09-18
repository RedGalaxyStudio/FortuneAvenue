
#include <SFML/Graphics.hpp>
#include "Cinematic.hpp"
#include "ResourceGlobal.hpp"
#include "menuP.hpp"
#include "Game.hpp"





int main() {
    // Obtener la lista de modos de video soportados
      // El primer modo suele ser el m�s grande

    // Crear la ventana en pantalla completa
    sf::RenderWindow window(sf::VideoMode(1280,720), "Juego en Pantalla Completa", sf::Style::Fullscreen);

    // Configuraci�n del frame rate (opcional)
    window.setFramerateLimit(60);

    sf::Image icono;
    if (!icono.loadFromFile("resource/texture/Icon/FortuneAvenue.png")) return EXIT_FAILURE;

    window.setMouseCursorVisible(false);
    // Establecer el �cono de la ventana
   window.setIcon(icono.getSize().x, icono.getSize().y, icono.getPixelsPtr());
    
    // Crear una instancia de la clase Cinematic y pasarle la ventana por referencia
    Cinematic cinematic(window);

    // Cargar los recursos necesarios para la cinem�tica
    cinematic.Resource();

    //Iniciar la animaci�n
    cinematic.Update();
    loadTextures();
    Menup.setWindow(window);
    // Cargar los recursos necesarios para la cinem�tica
    Menup.Resource();

    // Iniciar la animaci�n
   Menup.MenuPrincipal();

   
    return EXIT_SUCCESS;
}

