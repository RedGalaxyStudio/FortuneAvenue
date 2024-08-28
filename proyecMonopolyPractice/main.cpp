#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::Clock clock;

    sf::RenderWindow window(sf::VideoMode(1500, 1000), "Ventana SFML");

    sf::Image icono;
    if (!icono.loadFromFile("resource/texture/256x256.png"))
    {
        std::cerr << "Error al cargar la imagen del ícono" << std::endl;
        return EXIT_FAILURE;
    }
    pipippii
    // Establecer el ícono de la ventana
    window.setIcon(icono.getSize().x, icono.getSize().y, icono.getPixelsPtr());

    sf::Texture texture;
    if (!texture.loadFromFile("resource/texture/imagelogopresa.png"))
    {
        return EXIT_FAILURE;
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setOrigin(500, 238.5); // Ajusta según el tamaño del sprite
    sprite.setPosition(750, 500); // Posición del sprite

    sf::Clock fadeClock;
    float alpha = 0.0f;
    bool fadingIn = true;

    // Iniciar el ciclo del juego
    while (window.isOpen())
    {
        // Procesar eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Cerrar ventana: salir
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Obtener el tiempo transcurrido desde que se creó el reloj
        sf::Time deltaTime = fadeClock.restart();

        if (fadingIn)
        {
            alpha += 255.0f * deltaTime.asSeconds(); // Incrementa la opacidad
            if (alpha >= 255.0f)
            {
                alpha = 255.0f;
                fadingIn = false;
            }
        }
        else
        {
            alpha -= 255.0f * deltaTime.asSeconds(); // Decrementa la opacidad
            if (alpha <= 0.0f)
            {
                alpha = 0.0f;
                fadingIn = true;
            }
        }

        sprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));

        // Limpiar la pantalla
        window.clear();

        if (clock.getElapsedTime().asSeconds() <= 5)
        {
            // Dibujar el sprite
            window.draw(sprite);
        }

        // Actualizar la ventana
        window.display();
    }

    return EXIT_SUCCESS;
}
