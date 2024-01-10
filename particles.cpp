#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <ctime>


class particle
{
public:
    sf::Vector2f pos;
    sf::Vector2f velocity = {0.f, 0.f};
    

    particle()
    {
        pos = {(float)(std::rand() % 800 + 0), (float)(std::rand() % 800 + 0)};
        velocity = {(float)(std::rand() % 3 -1)/10, (float)(std::rand() % 3 -1)/10};
        
    }
};


void update(particle *a,sf::Vector2i b)
{
    float limit =10.f;
    sf::Vector2f uni = (sf::Vector2f)b - a->pos;
    float d =  abs(sqrt(pow(uni.x,2.0) + pow(uni.y,2.0)));
    uni.x = uni.x / d;
    uni.y = uni.y / d;
    float acc = 100000 / pow(d,2.0) ;
    if(d > 10.0){
    a->velocity.x += uni.x * acc;
    a->velocity.y += uni.y * acc;
    }
    else{
    a->velocity.x += uni.x * (-10);
    a->velocity.y += uni.y * (-10);
    }
    if(a->velocity.x > limit)
    {
        a->velocity.x = limit;
    }
    if(a->velocity.y > limit)
    {
        a->velocity.y = limit;
    }
    if(a->velocity.x < limit * (-1))
    {
        a->velocity.x = limit * (-1);
    }
    if(a->velocity.y < limit * (-1))
    {
        a->velocity.y = limit * (-1);
    }
}









int main()
{

    sf::Clock clock;
    std::srand(std::time(nullptr));
    sf::RenderWindow window(sf::VideoMode(800, 800), "Insert Text Here");
    window.setFramerateLimit(60);
    

    const int n = 20000;
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
        sf::Vector2i grav_hole = sf::Mouse::getPosition(window);

        window.clear(sf::Color::Black);
        for(int i = 0; i < n; i++)
        {

            sf::CircleShape point(1.f);
            point.setPosition(particles[i].pos);
            window.draw(point);
            update(&particles[i],grav_hole);
            particles[i].pos += particles[i].velocity;
            
            
        }
        

        window.display();
    }
    return 0;
}