#include <SFML/Graphics.hpp>
#include <iostream>
#include "cinematic/Cinematic.hpp"
#include "core/ObjetosGlobal.hpp"
#include "core/ResourceGlobal.hpp"
#include <fstream>
#include <SFML/System.hpp>
#include <exception>
#include "Logger.hpp"
#include <filesystem>


void terminator() {
	Logger::log("Error fatal: std::terminate fue llamado.");
	std::cerr << "El juego se cerro inesperadamente." << std::endl;
	std::abort();  
}



int runGame() {
	std::set_terminate(terminator);
	std::cout<<"\nuy";
	try {
		sf::err().rdbuf(std::cout.rdbuf());
		std::unique_ptr<sf::RenderWindow> window = std::make_unique<sf::RenderWindow>(
			sf::VideoMode(1280, 720), "Fortune Avenue", sf::Style::Fullscreen);
		window->setFramerateLimit(60);
		sf::Image icono;
		if (!icono.loadFromFile("assets/image/Icon/FortuneAvenue.png")) return EXIT_FAILURE;
		window->setMouseCursorVisible(false);
		window->setIcon(icono.getSize().x, icono.getSize().y, icono.getPixelsPtr());
		if (!window->setActive(true)) return -1;
		//Cinematic cinematic(*window);
		//cinematic.Resource();
		//cinematic.Update();
		Menup.setWindow(*window);
		Menup.Resource();
		Menup.MenuPrincipal();

	}
	catch (const std::exception& e) {
		std::cerr << "Excepcion atrapada: " << e.what() << std::endl;
		std::ofstream log("crash_log.txt", std::ios::app);
		log << "Excepcion atrapada: " << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Excepcion desconocida atrapada." << std::endl;
		std::ofstream log("crash_log.txt", std::ios::app);
		log << "Excepcion desconocida atrapada." << std::endl;
	}
	return EXIT_SUCCESS;
	
}

//#ifdef _WIN32
//#include <windows.h>
//int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
//	return runGame();
//}
//#else
int main() {
	return runGame();
}
//#endif
