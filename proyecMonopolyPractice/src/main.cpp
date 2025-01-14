#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <atomic>
#include <winsock2.h>
#include "Cinematic/Cinematic.hpp"
#include "core/ObjetosGlobal.hpp"
#include "core/ResourceGlobal.hpp"
#include "menu/IniciaUser.hpp"

std::atomic<bool> running(true); 
const unsigned short PORT = 53000; 
//int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Juego en Pantalla Completa", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

  
    sf::Image icono;
    if (!icono.loadFromFile("../assets/Icon/FortuneAvenue.png")) return EXIT_FAILURE;
    window.setMouseCursorVisible(false);
    window.setIcon(icono.getSize().x, icono.getSize().y, icono.getPixelsPtr());



   Cinematic cinematic(window);
   cinematic.Resource();
   cinematic.Update();

   //Cinematic cinematic(window);
   //cinematic.Resource();
   //cinematic.Update();

    loadTextures();
    cargue();
    Menup.setWindow(window);
    Menup.Resource();
    Menup.MenuPrincipal();

    CoUninitialize();
    return EXIT_SUCCESS;
}