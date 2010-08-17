//#include"headers.hpp"
#include"slope.hpp"

float Slope::Rise(float y1,float y2)
{
    return y2 - y1;
}

float Slope::Run(float x1,float x2)
{
    return x2 - x1;
}

sf::Vector2f Slope::RiseOverRun(sf::Vector2f First, sf::Vector2f Second)
{



    return sf::Vector2f(Second.y - First.y, Second.x - First.x);
}

