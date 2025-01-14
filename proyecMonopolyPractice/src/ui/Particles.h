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
        shape.setFillColor(Susana); 
        this->velocity = velocity;
        this->lifetime = lifetime;
    }

    void update(float dt) {
        lifetime -= dt;
        shape.move(velocity * dt);
        float alpha = (lifetime > 0) ? 255 * (lifetime / 3.0f) : 0; 

        sf::Color currentColor = shape.getFillColor();
        shape.setFillColor(sf::Color(currentColor.r, currentColor.g, currentColor.b, static_cast<sf::Uint8>(alpha)));
      
    }

    bool isDead() const {
        return lifetime <= 0;
    }
};


class ParticleSystem {
public:
    std::vector<Particle> particles;

    void addParticle(const sf::Vector2f& position, sf::Color color, float startRadius) {
        for (int i = 0; i < 50; ++i) {
            // Generar un ángulo aleatorio entre 0 y 2*PI
            float angle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2 * 3.14159f;

            // Generar una velocidad aleatoria
            float speed = static_cast<float>(rand() % 100 + 50);

            // Calcular la posición inicial en un radio alrededor del punto central
            sf::Vector2f offset(cos(angle) * startRadius, sin(angle) * startRadius);
            sf::Vector2f initialPosition = position + offset;

            // Calcular la velocidad en la dirección del ángulo
            sf::Vector2f velocity(cos(angle) * speed, sin(angle) * speed);

            particles.emplace_back(initialPosition, velocity, 5.0f, 3.0f, color);
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

    void reset() {
        particles.clear(); 
    }

};
