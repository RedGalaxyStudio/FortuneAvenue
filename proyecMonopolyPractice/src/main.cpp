#include <SFML/Graphics.hpp>
#include <iostream>
#include "Cinematic/Cinematic.hpp"
#include "core/ObjetosGlobal.hpp"
#include "core/ResourceGlobal.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include "Logger.hpp"

#define _CRTDBG_MAP_ALLOC

void terminator() {
	Logger::log("Error fatal: std::terminate fue llamado.");
	std::cerr << "El juego se cerró inesperadamente." << std::endl;
	std::abort();  
}


int main() {
	std::set_terminate(terminator);

	try {
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		sf::err().rdbuf(std::cout.rdbuf()); // Redirige los errores de SFML a la consola

		sf::ContextSettings settings;
		settings.attributeFlags = sf::ContextSettings::Debug;  // Activa depuración OpenGL

		std::unique_ptr<sf::RenderWindow> window = std::make_unique<sf::RenderWindow>(
			sf::VideoMode(1280, 720), "Fortune Avenue", sf::Style::Fullscreen, settings);

		window->setFramerateLimit(60);


		sf::Image icono;
		if (!icono.loadFromFile("assets/image/Icon/FortuneAvenue.png")) return EXIT_FAILURE;
		window->setMouseCursorVisible(false);
		window->setIcon(icono.getSize().x, icono.getSize().y, icono.getPixelsPtr());

		Cinematic cinematic(*window);
		cinematic.Resource();
		cinematic.Update();

		Menup.setWindow(*window);
		Menup.Resource();
		Menup.MenuPrincipal();


	}
	catch (const std::exception& e) {
		std::cerr << "Excepción atrapada: " << e.what() << std::endl;
		// Guarda en archivo log
		std::ofstream log("crash_log.txt", std::ios::app);
		log << "Excepción atrapada: " << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Excepción desconocida atrapada." << std::endl;
		std::ofstream log("crash_log.txt", std::ios::app);
		log << "Excepción desconocida atrapada." << std::endl;
	}
	return EXIT_SUCCESS;
}