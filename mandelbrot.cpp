#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <ctime>


int WIDTH = 1000;
int HEIGHT = 1000;

float magnitude(sf::Vector2f vec)
{
    float x = vec.x;
    float y = vec.y;

    return (sqrt(x * x + y * y));
}



int main()
{

    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Insert Text Here");
    window.setFramerateLimit(1);

    sf::RenderTexture texture;
    texture.create(WIDTH,HEIGHT);
    

    for(int x_cord = -500;x_cord < 500; x_cord++)
    {
        for(int y_cord = -500;y_cord < 500; y_cord++)
        {
            float a = x_cord / 500.0 * 2;
            float b = y_cord / 500.0 * 2;
            int n = 0;
            float x = a;
            float y = b;


            sf::Vector2f z = {0.f,0.f};

            while(magnitude(z) < 2 && n <= 255)
            {
                z = {x,y};
                float temp_x = x * x - y * y + a ;
                float temp_y = 2 * x * y + b;
                x = temp_x;
                y = temp_y;
                n++;
            }
            
            sf::RectangleShape pointer;
            pointer.setFillColor(sf::Color(n,n,n));
            pointer.setSize({1.f,1.f});
            pointer.setPosition((float)x_cord + WIDTH / 2.0 , (float)y_cord + HEIGHT / 2.0 );
            texture.draw(pointer);





        }
    }

    
    


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


        texture.display();
        sf::Sprite sprite(texture.getTexture());
        window.draw(sprite);

        window.display();
    }
    return 0;
}






