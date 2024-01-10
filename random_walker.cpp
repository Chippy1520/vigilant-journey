#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <ctime>

int width = 800;
int height = 800;

void regulate(int *b)
{
    if (*b > 255)
    {
        *b = 255;
    }
    else if (*b < 0)
    {
        *b = 0;
    }
}

class Walker : public sf::CircleShape
{

public:
    int r;
    int g;
    int b;
    float x;
    float y;
    float radius = 1.0;
    sf::Vector2f position;

    Walker() : sf::CircleShape()
    {

        r = rand() % 255;
        g = rand() % 255;
        b = rand() % 255;
        x = rand() % 800 + 0;
        y = rand() % 800 + 0;

        position.x = x;
        position.y = y;

        setFillColor(sf::Color(r, g, b));
        setRadius(radius);
    }
    void UpdateValues()
    {

        x += (float)(rand() % 11 - 5) / 10;
        y += (float)(rand() % 11 - 5) / 10;
        b += rand() % 3 + -1;
        g += rand() % 3 + -1;
        r += rand() % 3 + -1;
        regulate(&b);
        regulate(&g);
        regulate(&r);
        if (x > width)
        {
            x = 0;
        }
        else if (x < 0)
        {
            x = width;
        }
        if (y > height)
        {
            y = 0;
        }
        else if (y < 0)
        {
            y = height;
        }
        setPosition(x, y);
        setFillColor(sf::Color(r, g, b));
    }
};

int main()
{

    int n = 1000;
    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(width, height), "Insert Text Here");
    //window.setFramerateLimit(60);
    sf::CircleShape walker;
    
    sf::RenderTexture texture;
    texture.create(width,height);
    Walker walkers[n];

    while (window.isOpen())
    {

        sf::Event event;
        // std::srand(std::time(nullptr));
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        for (int i = 0; i < n; i++)
        {
            walkers[i].UpdateValues();
            texture.draw(walkers[i]);
        }
        window.clear(sf::Color::White);
        texture.display();
        sf::Sprite sprite(texture.getTexture());
        window.draw(sprite);
        window.display();
    }
    return 0;
}
