#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Particle {
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float lifetime;

    Particle(const sf::Vector2f& position, const sf::Vector2f& velocity, float lifetime, float size,sf::Color Susana) {
        shape.setPosition(position);
        shape.setRadius(size);
        shape.setFillColor(Susana); // Color de la partícula (puedes cambiarlo)
        this->velocity = velocity;
        this->lifetime = lifetime;
    }

    void update(float dt) {
        lifetime -= dt;
        shape.move(velocity * dt);
        float alpha = (lifetime > 0) ? 255 * (lifetime / 3.0f) : 0; // Gradual desaparición

        sf::Color currentColor = shape.getFillColor();
        shape.setFillColor(sf::Color(currentColor.r, currentColor.g, currentColor.b, static_cast<sf::Uint8>(alpha)));
       // shape.setFillColor(sf::Color(255, 255, 0, static_cast<sf::Uint8>(alpha))); // Ajusta la opacidad
    }

    bool isDead() const {
        return lifetime <= 0;
    }
};


class ParticleSystem {
public:
    std::vector<Particle> particles;

    void addParticle(const sf::Vector2f& position,sf::Color Jose) {
        // Añadir varias partículas al sistema con diferentes velocidades y duraciones
        for (int i = 0; i < 50; ++i) { // Ajusta la cantidad de partículas
           // sf::Vector2f velocity(static_cast<float>(rand() % 200 - 100), static_cast<float>(rand() % 200 - 100)); // Velocidad aleatoria
            float angle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2 * 3.14159f;

            // Genera una velocidad aleatoria, opcionalmente dentro de un rango
            float speed = static_cast<float>(rand() % 100 + 50);

            // Calcula las componentes X e Y de la velocidad usando coseno y seno
            sf::Vector2f velocity(cos(angle) * speed, sin(angle) * speed);

            particles.emplace_back(position, velocity, 5.0f, 3.0f, Jose); // Lifetime de 2 segundos y tamaño de 3px
        }
    }

    void update(float dt) {
        for (auto& particle : particles) {
            particle.update(dt);
        }
        // Eliminar partículas que hayan "muerto"
        particles.erase(std::remove_if(particles.begin(), particles.end(),
            [](const Particle& p) { return p.isDead(); }), particles.end());
    }

    void draw(sf::RenderWindow& window) {
        for (const auto& particle : particles) {
            window.draw(particle.shape);
        }
    }
};
