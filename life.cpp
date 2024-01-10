#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <ctime>

sf::Color colors[5] = {sf::Color::White, sf::Color::Blue, sf::Color::Red, sf::Color::Yellow, sf::Color::Green};

class particle
{
public:
    sf::Vector2f pos;
    sf::Vector2f velocity = {0.f, 0.f};
    int color;

    particle()
    {
        pos = {(float)(std::rand() % 800 + 0), (float)(std::rand() % 800 + 0)};
        // velocity = {(float)(std::rand() % 3 -1)/10, (float)(std::rand() % 3 -1)/10};
        color = std::rand() % 5 + 0;
    }
};

void process(particle *a, particle b)
{
    sf::Vector2f r_vec = b.pos - a->pos;
    float r = sqrt(pow(r_vec.x, 2) + pow(r_vec.y, 2));
    r_vec.x = r_vec.x / r;
    r_vec.y = r_vec.y / r;
    int repel = 2;
    int attract = 1;

    if (r <= 10)
    {
        a->velocity.x += (r_vec.x * (-10 + (-1 * repel) * r / 10)) / 10;
        a->velocity.y += (r_vec.y * (-10 + (-1 * repel) * r / 10)) / 10;
    }
    else if (r <= 20)
    {
        a->velocity.x += ((repel * (r - 10) / 10) - repel -1) * r_vec.x / 10;
        a->velocity.y += ((repel * (r - 10) / 10) - repel -1) * r_vec.y / 10;
    }
    else if (r <= 30)
    {
        a->velocity.x += (r_vec.x * (attract) * (r - 20) / 10) / 10;
        a->velocity.y += (r_vec.y * (attract) * (r - 20) / 10) / 10;
    }
    else if (r <= 100)
    {
        a->velocity.x += (attract - ((attract) * (r - 30) / 70)) * r_vec.x / 100;
        a->velocity.y += (attract - ((attract) * (r - 30) / 70)) * r_vec.y / 100;
    }
}

int main()
{

    sf::Clock clock;
    std::srand(std::time(nullptr));
    sf::RenderWindow window(sf::VideoMode(800, 800), "Insert Text Here");
    window.setFramerateLimit(60);

    const int n = 500;

    particle particles[n];

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

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i != j)
                {
                    process(&particles[i], particles[j]);
                }
            }
            sf::CircleShape point(3);
            point.setFillColor(colors[particles[i].color]);
            particles[i].pos += particles[i].velocity;
            particles[i].velocity = {0.f, 0.f};
            point.setPosition(particles[i].pos);

            window.draw(point);
        }

        window.display();
    }
    return 0;
}