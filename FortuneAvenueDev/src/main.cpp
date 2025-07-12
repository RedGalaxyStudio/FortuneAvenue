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
#include "../libs/nlohmann/json.hpp"
#include <shlobj.h>
using json = nlohmann::json;
void terminator() {
	Logger::log("Error fatal: std::terminate fue llamado.");
	std::cerr << "El juego se cerro inesperadamente." << std::endl;
	std::abort();  
}



int runGame() {
	std::set_terminate(terminator);
	try {
		sf::err().rdbuf(std::cout.rdbuf());
		sf::RenderWindow* window = new sf::RenderWindow();
		char appDataPath[MAX_PATH];
		if (SHGetFolderPathA(nullptr, CSIDL_APPDATA, nullptr, 0, appDataPath) != S_OK) {
			std::cerr << "No se pudo obtener la ruta de AppData." << std::endl;
			return 0;
		}

		std::string rutaFinalC = std::string(appDataPath) + "\\Fortune Avenue\\";
		std::string documente = rutaFinalC + "settings.json";

		if (std::filesystem::exists(documente)) {

			std::ifstream inFile(documente);
			if (inFile.is_open()) {
				json settingData;

				inFile >> settingData;
				inFile.close();

				bool isFullscreen = settingData.value("fullscreen", true);
				createtheWindow(window, isFullscreen);

			}
		}

		window->setMouseCursorVisible(false);


		if (!window->setActive(true)) return -1;
		//Cinematic cinematic(*window);
		//cinematic.Resource();
		//cinematic.Update();
		Menup.setWindow(*window);
		Menup.Resource();
		Menup.MenuPrincipal();
		delete window;
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
