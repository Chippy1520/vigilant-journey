#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <ctime>

const int num = 400;
const int width = 800;
const int height = 800;
bool grid[num][num];
bool temp_grid[num][num];
void regulate(int *b)
{
    if ((*b + 5) > num)
    {
        *b = num -5;
    }
    else if ((*b - 5) < 0)
    {
        *b = 5;
    }
}
int check(int x, int y)
{
    if (y < (num-1))
    {

        if (!grid[x][y + 1])
        {

            return 1;
        }
        else if (!grid[x - 1][y + 1] & x > 0 & !grid[x + 1][y + 1] & x < (num -1))
        {
            return std::rand() % 2 + 3;
        }
        else if (!grid[x - 1][y + 1] & x > 0)
        {
            return 3;
        }
        else if (!grid[x + 1][y + 1] & x < (num -1))
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
    sf::Vector2i cord;
    float x;
    float y;
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
    sf::RenderWindow window(sf::VideoMode(width,height), "My window");
    window.setFramerateLimit(120);

    
    sf::Vector2f grain_size(width / (float)num, width / (float)num);

    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        std::srand(std::time(nullptr));
        while (window.pollEvent(event))
        {



            sf::Vector2f init_pos =  (sf::Vector2f) sf::Mouse::getPosition(window);


                cord.x = (int)floor(init_pos.x / grain_size.x);
                cord.y = (int)floor(init_pos.y / grain_size.y);


                regulate(&cord.x);
                regulate(&cord.y);
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
                

                
                for(int i = -4; i < 5;i++)
                {
                    for(int j = -4; j < 5;j++)
                    {
                        grid[cord.x + i][cord.y + j] = true;
                    }
                }
                
                
            }
            else if(event.type == sf::Event::MouseButtonReleased)
            {
                for(int i = -4; i < 5;i++)
                {
                    for(int j = -4; j < 5;j++)
                    {
                        grid[cord.x + i][cord.y + j] = false;
                    }
                }

            }
        }

        // shape.setOutlineThickness(10.f);
        // shape.setOutlineColor(sf::Color(250, 150, 100));

        // clear the window with black color
        window.clear(sf::Color::Black);
        for (int i = 0; i < num; i++)
        {
            for (int j = 0; j < num; j++)
            {

                
                if (grid[i][j])

                {
                    switch (check(i, j))
                {
                case 0:

                    break;
                case 1:
                    temp_grid[i][j] = false;
                    temp_grid[i][j + 1] = true;
                    
                    break;

                case 3:
                    temp_grid[i][j] = false;
                    temp_grid[i - 1][j + 1] = true;
                    
                    break;
                case 4:
                    temp_grid[i][j] = false;
                    temp_grid[i + 1][j + 1] = true;
                    
                    break;
                
            
                }

                sf::RectangleShape grain;
                grain.setSize(grain_size);
                grain.setFillColor(sf::Color::Yellow);
                x = (float)i * grain_size.x;
                y = (float)j * grain_size.y;
                grain.setPosition(x,y);
                window.draw(grain);
                }
            }
        }
        for (int i = 0; i < num; i++)
        {
            for (int j = 0; j < num; j++)
            {
                grid[i][j] = temp_grid[i][j];
            }

        }

        // draw everything here...
        // window.draw(...);

        // window.draw();
        

                
        // end the current frame
        window.display();
    }
    return 0;
}