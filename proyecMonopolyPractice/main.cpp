#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <atomic>
#include <windows.h> // Necesario para HRESULT y COM
<<<<<<< HEAD

=======
>>>>>>> f72d20990916be5037739544fb6b23cc6932def9
#include "Client.hpp"
#include "Cinematic.hpp"
#include "ObjetosGlobal.hpp"
#include "ResourceGlobal.hpp"
#include "IniciaUser.hpp"
#include "Globals.hpp"

std::atomic<bool> running(true); // Definición aquí
const unsigned short PORT = 53000; // Definición aquí

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Juego en Pantalla Completa", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

<<<<<<< HEAD
   

=======
>>>>>>> f72d20990916be5037739544fb6b23cc6932def9
    // Configurar icono de la ventana
    sf::Image icono;
    if (!icono.loadFromFile("resource/texture/Icon/FortuneAvenue.png")) return EXIT_FAILURE;
    window.setMouseCursorVisible(false);
    window.setIcon(icono.getSize().x, icono.getSize().y, icono.getPixelsPtr());

    // Inicializar COM
    HRESULT hr = CoInitialize(nullptr);
    if (FAILED(hr)) {
        std::cerr << "Error al inicializar COM." << std::endl;
        return -1;
    }

    // Crear una instancia de la clase Cinematic
<<<<<<< HEAD
    Cinematic cinematic(window);
    cinematic.Resource();
    cinematic.Update();
=======
   // Cinematic cinematic(window);
   // cinematic.Resource();
   // cinematic.Update();
>>>>>>> f72d20990916be5037739544fb6b23cc6932def9
    loadTextures();
    cargue();
    Menup.setWindow(window);
    Menup.Resource();
    Menup.MenuPrincipal();

    // Esperar a que el hilo del cliente termine
  
    CoUninitialize();
    return EXIT_SUCCESS;
}