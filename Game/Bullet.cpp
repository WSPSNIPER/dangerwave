#include"Entity.h"
#include"SFML/System.hpp"
#include"string"
using namespace std;
#include"bullet.hpp"

void Bullet::Move(float x, float y)
{
    _sprite.Move(x , y);
    _collisionRect.x += x;
    _collisionRect.y += y;
}

void Bullet::Update()
{
    Move(_Speed.x, _Speed.y);

    if(_sprite.GetPosition().x > 10000 || _sprite.GetPosition().y > 10000)
        Kill();
}

void Bullet::OnCollision(int t)
{
    if(t != PLAYER)
        Kill();

}

void Bullet::Render(sf::RenderWindow& window)
{
    window.Draw(_sprite);
}


Bullet::Bullet(float angle,float type,sf::Vector2f Speed,sf::Vector2f position, string owner)
:cell::Entity(position.x, position.y, 10, 10, "images/bullet.png")
{

    _collisionRect.set(position.x, position.y, 5, 5);
    Angle = angle; Type = type; _Speed = Speed; Position = position; Shooter = owner;
    _alive = true;
    _type = BULLET;
    _sprite.SetPosition(position);
}

