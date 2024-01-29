#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <unordered_map>
#include <algorithm> 

typedef struct {
    int x;
    int y;
    int g_cost;
    int h_cost;
    int f_cost;


}Node;

Node seeker;
Node target;

int target_hash;
int start_hash;

int calculate_h_cost(int cell_x, int cell_y, Node target)
{
    //calculates h_cost of a node
    int x = abs(cell_x - target.x);
    int y = abs(cell_y - target.y);

    if (y >= x)
    {
        return (y - x) * 10 + x * 14;

    }
    else
    {
        return (x - y) * 10 + y * 14;
    }
}
int calculate_h_cost_0(int cell_x, int cell_y, int cell_2_x,int cell_2_y)
{
    //calculates h_cost of a node
    int x = abs(cell_x - cell_2_x);
    int y = abs(cell_y - cell_2_y);

    if (y >= x)
    {
        return (y - x) * 10 + x * 14;

    }
    else
    {
        return (x - y) * 10 + y * 14;
    }
}
const int grid_size = 80;
const int columns = grid_size;
const int rows = grid_size;
bool grid[columns][rows];
std::unordered_map<int, Node> node_map;

std::vector<int> explored_hashes;
std::vector<int> adjacent_hashes;
std::vector<int> path_back;

int calculate_hash(int x, int y)
{
    return y * grid_size + x;

}
bool compareNodes(int hash_1, int hash_2)
{
    if (node_map[hash_1].f_cost != node_map[hash_2].f_cost)
    {
        return node_map[hash_1].f_cost < node_map[hash_2].f_cost;
    }
    else
    {
        return node_map[hash_1].h_cost < node_map[hash_2].h_cost;
    }
}
bool compareNodes_back(int hash_1, int hash_2)
{
    if (node_map[hash_1].f_cost != node_map[hash_2].f_cost)
    {
        return node_map[hash_1].f_cost < node_map[hash_2].f_cost;
    }
    else
    {
        return node_map[hash_1].g_cost < node_map[hash_2].g_cost;
    }
}
void calculate_next_node(std::vector<int>* Adjacent_hashes)
{
    //returns the hash of the next node to search from a sorted list/vector of adjacent node hashes
    std::sort(Adjacent_hashes->begin(), Adjacent_hashes->end(), compareNodes);

}

int find_the_best_node_back(Node Seeker, std::vector<int> Explored_hashes, std::vector<int> Path_back)
{
    std::vector<int> buffer_cells;
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if (!(i == 0 && j == 0))
            {
                int x = Seeker.x + j;
                int y = Seeker.y + i;
                if (y >= 0 && y < grid_size && x >= 0 && x < grid_size) {
                    int hash = calculate_hash(x, y);
                    if (std::find(Path_back.begin(), Path_back.end(), hash) == Path_back.end())
                    {
                        if (std::find(Explored_hashes.begin(), Explored_hashes.end(), hash) != Explored_hashes.end())
                        {
                            buffer_cells.push_back(hash);
                        }
                    }
                }

            }
        }
    }

    std::sort(buffer_cells.begin(), buffer_cells.end(), compareNodes_back);
    return buffer_cells.front();
}


//update function where seeker update/create nodes for adjacent cells
//only update the g_cost if the current g_cost of the node is higher than the new one
//new g_cost = g_cost of the seeker node + distance value to that cell (14 if diagonal else 10)

void update(std::vector<int>* Adjacent_hashes, std::vector<int> Explored_hashes, Node Seeker, std::unordered_map<int, Node>& Node_map, bool Grid[][grid_size])
{

    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if (!(i == 0 && j == 0))
            {
                int x = Seeker.x + j;
                int y = Seeker.y + i;
                if (!Grid[y][x]) {
                    if (y >= 0 && y < grid_size && x >= 0 && x < grid_size)
                    {
                        int hash = calculate_hash(x, y);

                        if (std::find(Explored_hashes.begin(), Explored_hashes.end(), hash) == Explored_hashes.end())
                        {
                            int G_cost = Seeker.g_cost + calculate_h_cost(x, y, Seeker);
                            if (std::find(Adjacent_hashes->begin(), Adjacent_hashes->end(), hash) == Adjacent_hashes->end())
                            {
                                Adjacent_hashes->push_back(hash);
                                int H_cost = calculate_h_cost(x, y, target);
                                Node_map[hash];
                                Node_map[hash].x = x;
                                Node_map[hash].y = y;
                                Node_map[hash].g_cost = G_cost;
                                Node_map[hash].h_cost = H_cost;
                                Node_map[hash].f_cost = G_cost + H_cost;
                            }
                            else
                            {
                                if (Node_map[hash].g_cost < G_cost)
                                {
                                    Node_map[hash].g_cost = G_cost;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

class Seeker_c
{
public:
    sf::Vector2i pos;
    Seeker_c(sf::Vector2i Pos = {0,0})
    {
        pos = Pos;
    }   

};

class target_c
{
public:
    sf::Vector2i pos;
    target_c(sf::Vector2i Pos);
    



};

target_c::target_c(sf::Vector2i Pos)
{
    pos = Pos;
}





std::vector<int> find_path()
{
    do
    {
        static int count = 1;

        update(&adjacent_hashes, explored_hashes, seeker, node_map, grid);
        calculate_next_node(&adjacent_hashes);
        int seeker_hash = adjacent_hashes.front();
        explored_hashes.push_back(seeker_hash);
        seeker = node_map[seeker_hash];
        adjacent_hashes.erase(adjacent_hashes.begin());
        //std::cout << "Finding way to the target... iteration " << count << " Current Seeker Pos : " << seeker.x << " , " << seeker.y << "\n";

        count++;
    } while (calculate_hash(seeker.x, seeker.y) != target_hash);
    //std::cout << "target found\n";



    Node seeker_2 = target;
    path_back.push_back(target_hash);
    do
    {
        int temp = find_the_best_node_back(seeker_2, explored_hashes, path_back);
        path_back.push_back(temp);
        seeker_2 = node_map[temp];



    } while (calculate_hash(seeker_2.x, seeker_2.y) != start_hash);

    //std::cout << "The shortest path\n";
    std::reverse(path_back.begin(), path_back.end());
    return path_back;

}










int main()
{   
    
   

    float cell_height = 10;
    float cell_width = 10;
   

    
    
    Seeker_c seeker1_c({0,0});
    target_c target1_c({columns / 2 - 1,rows / 2 - 1 });

    
    


    
    for (size_t i = 0; i < columns; i++)
    {
        for (size_t j = 0; j < rows; j++)
        {
            grid[i][j] = false;
        }
    }

    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(800, 800), "Grid System");
    sf::RenderTexture texture;
    texture.create(800, 800);
    //window.setFramerateLimit(60);


    sf::RectangleShape seekerShape;
    seekerShape.setSize({ cell_width, cell_height });
    seekerShape.setFillColor(sf::Color::Blue);

    sf::RectangleShape targetShape;
    targetShape.setSize({ cell_width, cell_height });
    targetShape.setFillColor(sf::Color::Red);
    targetShape.setPosition({ target1_c.pos.x * cell_width,target1_c.pos.y * cell_height });


    

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
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            int x = floor(pos.x / cell_width);
            int y = floor(pos.y / cell_height);
            if (x >= 0 && x < columns && y >= 0 && y < rows)
            {
                grid[y][x] = true;
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            int xd = floor(pos.x / cell_width);
            int yd = floor(pos.y / cell_height);
            if (xd >= 0 && xd < columns && yd >= 0 && yd < rows)
            {
                grid[yd][xd] = false;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            sf::Vector2i pos_s = sf::Mouse::getPosition(window);
            int xs = floor(pos_s.x / cell_width);
            int ys = floor(pos_s.y / cell_height);
            if (xs >= 0 && xs < columns && ys >= 0 && ys < rows)
            {
                seeker1_c.pos = { xs,ys };
                seekerShape.setPosition({ seeker1_c.pos.x * cell_width,seeker1_c.pos.y * cell_height });
                    
                
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            sf::Vector2i pos_t = sf::Mouse::getPosition(window);
            int xt = floor(pos_t.x / cell_width);
            int yt = floor(pos_t.y / cell_height);
            if (xt >= 0 && xt < columns && yt >= 0 && yt < rows)
            {
                target1_c.pos = { xt,yt };
                targetShape.setPosition({ target1_c.pos.x * cell_width,target1_c.pos.y * cell_height });


            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {

            texture.clear(sf::Color::Black);
            int start_x = seeker1_c.pos.x;
            int start_y = seeker1_c.pos.y;
            int target_x = target1_c.pos.x;
            int target_y = target1_c.pos.y;

            int temp_cost = calculate_h_cost_0(start_x, start_y, target_x, target_y);

            Node start = { start_x,start_y,0,temp_cost,temp_cost};
            target = { target_x,target_y,temp_cost,0,temp_cost };
            seeker = start;
            target_hash = calculate_hash(target_x, target_y);
            start_hash = calculate_hash(start_x, start_y);
            node_map[start_hash] = start;
            explored_hashes.push_back(start_hash);
            std::vector<int> path_blocks = find_path();
            explored_hashes.clear();
            adjacent_hashes.clear();
            path_back.clear();

            for (int k : path_blocks)
            {
                int x = node_map[k].x;
                int y = node_map[k].y;

                sf::RectangleShape cell;
                cell.setPosition((float)(cell_width* x), (float)(cell_height* y));
                cell.setSize({ cell_width, cell_height });
                cell.setFillColor(sf::Color::Green);
                texture.draw(cell);
            }








            node_map.clear();




        }
        

        window.clear(sf::Color::Black);


        texture.display();
        sf::Sprite sprite(texture.getTexture());
        window.draw(sprite);


        for (int i = 0; i < columns; i++)
        {
            for (int j = 0;  j < rows;  j++)
            {
                if (grid[i][j]) 
                {
                    sf::RectangleShape cell;
                    cell.setPosition((float)(cell_width * j), (float)(cell_height * i));
                    cell.setSize({ cell_width, cell_height });
                    cell.setFillColor(sf::Color::White);
                    window.draw(cell);         


                }
            }
        }
        
        
            
            
            
            window.draw(seekerShape);
            window.draw(targetShape);

        
        

        window.display();
    }
    return 0;
}
