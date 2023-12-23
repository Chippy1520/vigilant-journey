#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <ctime>

bool grid[80][80];

int check(int x, int y)
{
    if (y < 79)
    {

        if (!grid[x][y + 1])
        {

            return 1;
        }
        else if (!grid[x - 1][y + 1] & x > 0 & !grid[x + 1][y + 1] & x < 79)
        {
            return std::rand() % 2 + 3;
        }
        else if (!grid[x - 1][y + 1] & x > 0)
        {
            return 3;
        }
        else if (!grid[x + 1][y + 1] & x < 79)
        {
            return 4;
        }
        else
        {
            return 404;
        }
    }
    else
    {
        return 0;
    }
}

int main()
{
    float r = 125;
    float g = 125;
    float b = 125;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            grid[i][j] = false;
        }
    }
    int count = 0;
    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(800, 800), "My window");
    window.setFramerateLimit(60);

    sf::RectangleShape grain[10000];
    sf::Vector2f grain_size(10.f, 10.f);

    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        std::srand(std::time(nullptr));
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                r += (float)(rand() % 4 - 2)/10;
                g += (float)(rand() % 4 - 2)/10;
                b += (float)(rand() % 4 - 2)/10;
                if(r>255){
                    r = 250;
                }
                else if (r < 0){
                    r = 10;
                }
                 if(g>255){
                    g = 250;
                }
                else if (g < 0){
                    g = 10;
                }
                 if(b>255){
                    b = 250;
                }
                else if (b < 0){
                    b = 10;
                }
                sf::Vector2f init_pos =  (sf::Vector2f) sf::Mouse::getPosition(window);
                if (!grid[(int)floor(init_pos.x / grain_size.x)][(int)floor(init_pos.y / grain_size.y)])
                {
                grain[count].setFillColor(sf::Color(r,g,b));
                grain[count].setSize(grain_size);

                grain[count].setPosition((float)floor(init_pos.x / grain_size.x) * grain_size.x, (float)floor(init_pos.y / grain_size.y) * grain_size.y);

                count++;
                }
            }
        }

        // shape.setOutlineThickness(10.f);
        // shape.setOutlineColor(sf::Color(250, 150, 100));

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);

        // window.draw();
        if (count > 0)
        {
            for (int i = 0; i <= count; i++)
            {

                window.draw(grain[i]);
                sf::Vector2f temp_pos = grain[i].getPosition();
                int x = floor(temp_pos.x / grain_size.x);
                int y = floor(temp_pos.y / grain_size.y);

                switch (check(x, y))
                {
                case 0:

                    break;
                case 1:
                    grid[x][y] = false;
                    grid[x][y + 1] = true;
                    grain[i].move(0.f, grain_size.y);
                    break;

                case 3:
                    grid[x][y] = false;
                    grid[x - 1][y + 1] = true;
                    grain[i].move(grain_size.x * (-1), grain_size.y);
                    break;
                case 4:
                    grid[x][y] = false;
                    grid[x + 1][y + 1] = true;
                    grain[i].move(grain_size.x, grain_size.y);
                    break;
                }
            }
        }
        // end the current frame
        window.display();
    }
    return 0;
}