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
//#include <TGUI/TGUI.hpp>
//#include <boost/asio.hpp>

#define _CRTDBG_MAP_ALLOC

void terminator() {
	Logger::log("Error fatal: std::terminate fue llamado.");
	std::cerr << "El juego se cerró inesperadamente." << std::endl;
	std::abort();  // Cierra el juego de forma segura
}


int main() {
	//std::cout << "SFML Version: " << SFML_VERSION_MAJOR << "." << SFML_VERSION_MINOR << "." << SFML_VERSION_PATCH << std::endl;
	std::set_terminate(terminator);

  //  boost::asio::io_context io;
	try {
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		sf::err().rdbuf(std::cout.rdbuf()); // Redirige los errores de SFML a la consola

		sf::ContextSettings settings;
		settings.attributeFlags = sf::ContextSettings::Debug;  // Activa depuración OpenGL

		std::unique_ptr<sf::RenderWindow> window = std::make_unique<sf::RenderWindow>(
			sf::VideoMode(1280, 720), "Juego en Pantalla Completa", sf::Style::Fullscreen, settings);
		//tgui::;

	   // tgui::Button::Ptr button = tgui::Button::create("Click me!");
		//button->setPosition(350, 250);
		//gui.add(button);
		window->setFramerateLimit(60);


		sf::Image icono;
		if (!icono.loadFromFile("assets/image/Icon/FortuneAvenue.png")) return EXIT_FAILURE;
		window->setMouseCursorVisible(false);
		window->setIcon(icono.getSize().x, icono.getSize().y, icono.getPixelsPtr());

		// Cinematic cinematic(*window);
		 // cinematic.Resource();
		  //cinematic.Update();

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