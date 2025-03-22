#include <SFML/Graphics.hpp>
#include <iostream>
#include "Cinematic/Cinematic.hpp"
#include "core/ObjetosGlobal.hpp"
#include "core/ResourceGlobal.hpp"
#define _CRTDBG_MAP_ALLOC  

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    sf::err().rdbuf(std::cout.rdbuf()); // Redirige los errores de SFML a la consola

    sf::ContextSettings settings;
    settings.attributeFlags = sf::ContextSettings::Debug;  // Activa depuración OpenGL

    std::unique_ptr<sf::RenderWindow> window = std::make_unique<sf::RenderWindow>(
        sf::VideoMode(1280, 720), "Juego en Pantalla Completa", sf::Style::Fullscreen, settings);

    window->setFramerateLimit(60);

  
    sf::Image icono;
    if (!icono.loadFromFile("assets/image/Icon/FortuneAvenue.png")) return EXIT_FAILURE;
    window->setMouseCursorVisible(false);
    window->setIcon(icono.getSize().x, icono.getSize().y, icono.getPixelsPtr());
  /* 
  Cinematic cinematic(*window);
   cinematic.Resource();
   cinematic.Update();
   */

    printMemoryUsage();
    Sleep(1000); // Mide cada 1 segundo
    Menup.setWindow(*window);  
    Menup.Resource();   
    Menup.MenuPrincipal();
    return EXIT_SUCCESS;
}