#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <ctime>

int main()
{

    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(800, 800), "Insert Text Here");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {

        sf::Event event;
        std::srand(std::time(nullptr));
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        window.draw();

        window.display();
    }
    return 0;
}