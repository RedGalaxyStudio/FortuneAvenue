#include "GameMode.hpp"
#include "ResourceGlobal.hpp"
// Inicializar el puntero estático
sf::Sprite* GameMode::lastHoveredButton = nullptr;

GameMode::GameMode(sf::RenderWindow& windowRef): window(windowRef) {
	resource();
}



void GameMode::resource() {

}

// Implementación del método update
void GameMode::update() {

}


