
#include "bulletmanager.hpp"
#include "bullet.hpp"

void BulletManager::Register(Bullet &bullet, float angle, Slope &slope, sf::Vector2f StartPosition)
{
    bullet.Shot = false;
    bullet.Angle = angle;
//    bullet.SetPosition(StartPosition);
    bullet._Slope = slope;
}

void BulletManager::KillBullet(Bullet &bullet)
{
    bullet.Shot = false;
}

void  BulletManager::Move(Bullet &bullet,sf::Vector2f &slope)
{
    bullet.Move(slope.x,slope.y);
}
//not done yet. still need to work on little indiviual stuff and make the bullet class as easy as it can be.
