#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include <algorithm>




typedef struct line {
    sf::Vector2f p1;
    sf::Vector2f p2;


}Line;

float distance_squared(sf::Vector2f a, sf::Vector2f b)
{
    a = b - a;
    return a.x * a.x + a.y * a.y;
}
float distance(sf::Vector2f a, sf::Vector2f b)
{
    a = b - a;
    return sqrt(a.x * a.x + a.y * a.y);
}

float calculate_slope(sf::Vector2f p_1, sf::Vector2f p_2)
{
    if (p_1.x != p_2.x)
    {
        return ((p_2.y - p_1.y) / (p_2.x - p_1.x));
    }
    else
    {
        return 99999999999;
    }
}

sf::Vector2f check_intersection(Line line_1, Line line_2)
{
    float x1 = line_1.p1.x;
    float y1 = line_1.p1.y;
    float x2 = line_1.p2.x;
    float y2 = line_1.p2.y;
    float x3 = line_2.p1.x;
    float y3 = line_2.p1.y;
    float x4 = line_2.p2.x;
    float y4 = line_2.p2.y;

    float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

    float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

    if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {
        return sf::Vector2f(x1 + (uA * (x2 - x1)), y1 + (uA * (y2 - y1)));
    }
    else {
        return sf::Vector2f(-1000,-1000);
    }
    


}



int main()
{
    sf::Vector2f player = sf::Vector2f{ 100,100 };
    int n = 10000;
    int ray_length = 600;
    float offset = 0;
    std::vector<float> bars;






    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(800, 800), "Insert Text Here");
    sf::RenderWindow window_2(sf::VideoMode(800, 800), "Insert Text Here");
    window.setFramerateLimit(60);
    std::vector<sf::Vertex> walls;


    while (window.isOpen())
    {

        sf::Event event;
        std::srand(std::time(nullptr));
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
            {
                window.close();
                window_2.close();
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vertex dot;
                    dot.position = (sf::Vector2f)sf::Mouse::getPosition(window);
                    walls.push_back(dot);
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            offset -= 0.04;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            offset += 0.04;
        }

        player = (sf::Vector2f)sf::Mouse::getPosition(window);

        sf::VertexArray lines(sf::Lines, n * 2);
        for (int i = 0, j = 0; i < n; i++)
        {
            float dir_x = cos(3.14159 / (3 * n) * i * 2 + 0.000001 + offset);
            float dir_y = sin(3.14159 / (3 * n) * i * 2 + 0.000001 + offset);

            lines[j] = player;
            lines[j + 1] = sf::Vector2f{ dir_x * ray_length,dir_y * ray_length } + player;
            j += 2;

        }



        sf::CircleShape point_of_intersection;



        window.clear(sf::Color::Black);
        window_2.clear(sf::Color::Black);
        int n_walls = walls.size();


        for (int i = 0; i < n; i++)
        {
            Line l1 = { player , lines[1 + 2 * i].position };

            if (n_walls > 1)
            {
                std::vector<sf::Vector2f> intersect_points;

                for (int i = 0; i + 1 < n_walls; i += 2)
                {
                    Line line_buffer = Line{ walls[i].position,walls[i + 1].position };
                    intersect_points.push_back(check_intersection(l1, line_buffer));

                }
                std::sort(intersect_points.begin(), intersect_points.end(), [=](const auto& lhs, const auto& rhs) {
                    return distance_squared(player, lhs) < distance_squared(player, rhs);
                    });

                /*
                 point_of_intersection.setPosition(intersect_points[0]);
                 point_of_intersection.setFillColor(sf::Color::Red);
                 point_of_intersection.setRadius(4);
                 point_of_intersection.setOrigin(sf::Vector2f{ 4,4 });
                 window.draw(point_of_intersection);
             */
                bars.push_back(distance(player, intersect_points[0]));



                if (distance_squared(player, intersect_points[0]) < ray_length * ray_length)
                {
                    lines[1 + 2 * i].position = intersect_points[0];
                }



                intersect_points.clear();


            }
        }
        if (n_walls > 1)
        {
            window.draw(&walls[0], n_walls, sf::Lines);
        }

        window.draw(lines);


        int w = window_2.getSize().x;
        int h = window_2.getSize().y;
        float bar_width = w / (float)n;


        if (n_walls > 1)
        {
            for (int l = 0; l < n; l++)
            {
                if (bars[l] < ray_length)
                {
                    sf::RectangleShape barn;
                    float bar_height = (float)h / bars[l] * 100 ;
                    barn.setSize(sf::Vector2f(bar_width, bar_height));
                    barn.setPosition(bar_width * l, h/2);
                    barn.setOrigin(bar_width / 2, bar_height / 2 );
                    float shade = 100 - bars[l] / ray_length * 100;
                    barn.setFillColor(sf::Color(255 * shade / 100, 255 * shade / 100, 255 * shade / 100));
                    window_2.draw(barn);
                    
                }
            }
        }
        



        window.display();
        window_2.display();
        bars.clear();
    }




    //std::cout << check_intersection(first, second).x;
    return 0;
}
