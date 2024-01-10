#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <ctime>

bool calculate(bool a,bool b,bool c,int hash)
{
    int check = a * 4 + b *2 + c;
    switch(check)
    {
        case 0:
            return hash % 2;
        case 1:
            return (hash/2) % 2;
        case 2:
            return ((hash/2)/2) % 2;
        case 3:
            return (((hash/2)/2)/2) % 2;
        case 4:
            return ((((hash/2)/2)/2)/2) % 2;
        case 5:
            return (((((hash/2)/2)/2)/2)/2) % 2;
        case 6:
            return ((((((hash/2)/2)/2)/2)/2)/2) % 2;
        case 7:
            return (((((((hash/2)/2)/2)/2)/2)/2)/2);


    }
}



int main()
{   int width = 1000;
    int height = 1000;
    int y = 0;
    const int num = 999;
    int cell_size = width / num;
    bool cells[num];
    bool cells_inter[num];

    for (int i = 0;i < num; i++)
    {
        cells[i] = 0;
        cells_inter[i] = 0;
    }
    cells[num/2 + 1] = 1;
    int hash_f;
    std::cout << "Enter a number between [0-255] : ";
    std::cin >> hash_f;

    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(width, height), "Insert Text Here");
    window.setFramerateLimit(60);
    sf::RenderTexture texture;
    texture.create(width,height);

    

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

        for (int i = 1; i<num -1; i++)
        {
            if (! cells[i])
            {
                sf::RectangleShape pixel({(float)cell_size,(float)cell_size});
                pixel.setPosition((float)cell_size * i,(float)cell_size * y);
                texture.draw(pixel);

            }
            cells_inter[i] = calculate(cells[i-1],cells[i],cells[i+1],hash_f);
        }
        
        y++;
        for (int i = 0;i < num; i++)
        {
            cells[i] = cells_inter[i];
            
        }
        texture.display();
        sf::Sprite sprite(texture.getTexture());
        window.draw(sprite);
        window.display();
    }
    return 0;
}
