// Globals.hpp
#ifndef GLOBALS_HPP
#define GLOBALS_HPP
#include <SFML/Graphics.hpp>
#include <atomic>


extern std::atomic<bool> running; // Declaración externa
extern const unsigned short PORT;  // Declaración externa
extern std::vector<sf::Texture> avatarTextures; // Vector para almacenar las texturas de los avatares

#endif // GLOBALS_HPP
