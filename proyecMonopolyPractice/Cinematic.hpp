#ifndef CINEMATIC_HPP
#define CINEMATIC_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <thread>
#include <vector>

class Cinematic {
public:
    Cinematic(sf::RenderWindow& window);
    ~Cinematic();

    // Función para iniciar la pantalla de carga
    void iniciarCarga();

    // Función para cargar los recursos
    void cargarRecursos();

    // Función para dibujar la pantalla de carga
    void dibujar();

    // Verifica si la carga ha terminado
    bool cargaCompleta() const;

private:
    sf::RenderWindow& window;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Clock clock;
    sf::Clock fadeClock;
    std::vector<sf::Texture> texturas;
    sf::SoundBuffer buffer;
    std::thread hiloCarga;
    bool cargaTerminada;
};

#endif // CINEMATIC_HPP
