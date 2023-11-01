#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <ctime>

double distance(sf::Vector2f first_object_pos, sf::Vector2f second_object_pos)
{

    return sqrt((first_object_pos.x - second_object_pos.x) * (first_object_pos.x - second_object_pos.x) + (first_object_pos.y - second_object_pos.y) * (first_object_pos.y - second_object_pos.y));
}

sf::Vector2f Velocity_after_collision(sf::Vector2f v1, sf::Vector2f v2, int m1, int m2)
{
    float v3x, v3y, v4x, v4y;
    v3x = ((m1 - m2) * v1.x / (m1 + m2)) + 2 * m2 * v2.x / (m1 + m2);
    v4x = (m1 / m2) * (v1.x - v3x) + v2.x;
    v1.x = v3x;
    v2.x = v4x;

    v3y = ((m1 - m2) * v1.y / (m1 + m2)) + 2 * m2 * v2.y / (m1 + m2);
    v4y = (m1 / m2) * (v1.y - v3y) + v2.y;
    v1.y = v3y;
    v2.y = v4y;

    return v1, v2;
}

class Astroid : public sf::CircleShape
{

public:
    int mass;
    float radius;

    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    // sf::RenderWindow window;

    Astroid(float x = std::rand() % 600 + 100, float y = std::rand() % 600 + 100, float Vx = 0, float Vy = 0, float Ax = 0, float Ay = 0, float Radius = 5) : sf::CircleShape(Radius)
    {

        mass = 100;
        position.x = x;
        position.y = y;
        velocity.x = Vx;
        velocity.y = Vy;
        acceleration.x = Ax;
        acceleration.y = Ay;
        radius = Radius;
        // window = Window;
        setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
    }

    void UpdateValues()
    {
        velocity.x += acceleration.x;
        velocity.y += acceleration.y;
        acceleration.x = 0;
        acceleration.y = 0;
        int terminal_velocity = 2;
       if (velocity.x > terminal_velocity){
            velocity.x = terminal_velocity;
        }
        if (velocity.x < -terminal_velocity){
            velocity.x = -terminal_velocity;
        }
        if (velocity.y > terminal_velocity){
            velocity.y = terminal_velocity;
        }
        if (velocity.y < -terminal_velocity){
            velocity.y = -terminal_velocity;
        }
        
        position += velocity;

        
        setPosition(position);

        /*
                if ((getGlobalBounds().top + getGlobalBounds().height) >= 600)
                {

                    velocity.y = (velocity.y ) * (-1);
                }
                if ((getGlobalBounds().left + getGlobalBounds().width) >= 800)
                {

                    velocity.x = (velocity.x) * (-1);
                }
                if ((getGlobalBounds().top) <= 0)
                {

                    velocity.y = (velocity.y) * (-1);
                }
                if ((getGlobalBounds().left) <= 0)
                {

                    velocity.x = (velocity.x) * (-1);
                }
                */
    }
};
bool Check_asteroid_collision(Astroid first, Astroid second)
{

    return (distance(first.position, second.position) <= (first.radius + second.radius));
}
float Calculate_Gravitational_Acceleration_x(Astroid first, Astroid second)
{
    float G_cons = 0.1;
    float g;
    float gx;
    float d = distance(first.position, second.position);
    
    g = second.mass * G_cons / (d * d);
    gx = g * (second.position.x - first.position.x)/d;
    if (d <= first.radius + second.radius){
        if(gx > 0){gx = -1 * 0.1  ;}
        else{gx = 1 * 0.1 ;}
        
    }
    

    return gx;
    

}
float Calculate_Gravitational_Acceleration_y(Astroid first, Astroid second)
{
    float G_cons = 0.1;
    float g;
    float gy;
    float d = distance(first.position, second.position);
    
    g = second.mass * G_cons / (d * d);
    gy = g * (second.position.y - first.position.y)/d;
    if (d <= first.radius + second.radius){
        if(gy > 0){gy = -1 * 0.1  ;}
        else{gy = 1 * 0.1  ;}
    }
    

    
    return gy;
    

}
int main()
{
    std::srand(std::time(nullptr));
    int num = 100;
    sf::RenderWindow window(sf::VideoMode(800, 800), "My window");
    // Astroid a0001(400.f, 300.f, 10.f, 10.f, 0.f, 0.f, 10, 20.0f);
    Astroid as[num];
    

    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // shape.setOutlineThickness(10.f);
        // shape.setOutlineColor(sf::Color(250, 150, 100));

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);

        for (int i = 0; i < num; i++)
        {
            for (int j = 0; j < num; j++)
            {
                if (i != j)
                {
                    as[i].acceleration.x += Calculate_Gravitational_Acceleration_x(as[i], as[j]);
                    as[i].acceleration.y += Calculate_Gravitational_Acceleration_y(as[i], as[j]);
                    
                }

                // if(i != j && Check_asteroid_collision(as[i],as[j])){

                // as[i].velocity,as[j].velocity = Velocity_after_collision(as[i].velocity,as[j].velocity,as[i].mass,as[j].mass);

                // }
            }
            as[i].UpdateValues();
            window.draw(as[i]);
        }

        // end the current frame
        window.display();
    }
    return 0;
}
