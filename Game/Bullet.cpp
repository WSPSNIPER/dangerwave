#include"Entity.h"
#include"SFML/System.hpp"
#include"string"
using namespace std;
#include"bullet.hpp"

void Bullet::Move(float x, float y)
{
    _sprite.SetPosition(Position.x + x,Position.y + y);
}



Bullet::Bullet(float angle,float type,sf::Vector2f Speed,sf::Vector2f position, string owner)
{
    Angle = angle; Type = type; _Speed = Speed; Position = position; Shooter = owner;
}

