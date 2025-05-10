#include "Bot.hpp"
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <random>

namespace CreatorB {
	std::vector<std::string> getRandomBotNames(int count) {
		std::ifstream file("assets/DATE/NBOTS.txt");
		if (!file.is_open()) {
			std::cerr << "Error al abrir el archivo." << std::endl;
			return {};
		}

		std::vector<std::string>botNames;
		std::string line;

		while (std::getline(file, line)) {
			botNames.push_back(line);
		}
		file.close();

		if (botNames.size() < count) {
			std::cerr << "No hay suficientes nombres en el archivo." << std::endl;
			return {};
		}

		std::random_device rd;
		std::mt19937 gen(rd());
		std::unordered_set<size_t> usedIndices;
		std::vector<std::string> selectedNames;


		while (selectedNames.size() < count) {
			std::uniform_int_distribution<size_t> dist(0, botNames.size() - 1);
			size_t randomIndex = dist(gen);

			if (usedIndices.find(randomIndex) == usedIndices.end()) {
				usedIndices.insert(randomIndex);
				selectedNames.push_back(botNames[randomIndex]);
			}
		}

		return selectedNames;
	}
	std::vector<int> getRandomBotPieces(int count,int pieceP) {


		if (count > 20) {
			count = 20; 
		}

		std::vector<int> pieces;
		std::unordered_set<int> usedNumbers;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(0, 18);

		while (pieces.size() < count) {
			int num = dist(gen);
			if (usedNumbers.insert(num).second && (num != pieceP)) { 
				pieces.push_back(num);
			}
		}

		return pieces;

	}
	std::vector<int> getRandomBotAvatar(int count) {


		if (count > 20) {
			count = 20; 
		}

		std::vector<int> avatarss;
		std::unordered_set<int> usedNumbers;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(1, 20);

		while (avatarss.size() < count) {
			int num = dist(gen);
			if (usedNumbers.insert(num).second) { 
				avatarss.push_back(num);
			}
		}

		return avatarss;

	}
}

Bot::Bot() {}
bool Bot::roll() {
	if ( clock.getElapsedTime().asSeconds() >=waitTime) {
		return true;
	}
	return false;
}
int Bot::eleccion() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, 1);

	int cam = dist(gen);
	return cam;
}

void Bot::resetT() {
	waitTime = 2.0f + std::rand() % 3;
	clock.restart();
}
void Bot::resetTCAM() {
	waitTime = 2.0f + std::rand() % 4; 
	clock.restart();
}
void Bot::resetTCAMRuleta() {
	waitTime = 2.0f + std::rand() % 4;
	clock.restart();
}