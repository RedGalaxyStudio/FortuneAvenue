#include <SFML/Graphics.hpp>
#include "Cinematic.hpp"
#include "ObjetosGlobal.hpp"
#include "ResourceGlobal.hpp"
#include "IniciaUser.hpp"

int main() {
    // Crear la ventana en pantalla completa
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Juego en Pantalla Completa", sf::Style::Fullscreen);

    // Configuraci n del frame rate (opcional)
    window.setFramerateLimit(60);

    sf::Image icono;
    if (!icono.loadFromFile("resource/texture/Icon/FortuneAvenue.png")) return EXIT_FAILURE;

    window.setMouseCursorVisible(false);
    // Establecer el  cono de la ventana
    window.setIcon(icono.getSize().x, icono.getSize().y, icono.getPixelsPtr());

    // Inicializar COM
    HRESULT hr = CoInitialize(nullptr);
    if (FAILED(hr)) {
        std::cerr << "Error al inicializar COM." << std::endl;
        return -1;
    }
    /*
    // Crear una instancia de la clase Cinematic y pasarle la ventana por referencia
    Cinematic cinematic(window);

    // Cargar los recursos necesarios para la cinem tica
    cinematic.Resource();

    //Iniciar la animaci n
    cinematic.Update();*/
    loadTextures();
    cargue();
    Menup.setWindow(window);
    // Cargar los recursos necesarios para la cinem tica
    Menup.Resource();

    // Iniciar la animaci n
    Menup.MenuPrincipal();

    CoUninitialize();

    return EXIT_SUCCESS;
}