#ifndef _BULLET_MGR_H_
#define _BULLET_MGR_H_

#include "Bullet.hpp"

class BulletManager

{

   public:

   void Register(Bullet &bullet, float angle, Slope &slope, sf::Vector2f StartPosition);



   bool Collison(sf::Vector2f &coords);



   void KillBullet(Bullet &bullet);



   void KillBullet(sf::Vector2f &coord, Bullet &bullet); //change for collision



   void Move(Bullet &bullet,sf::Vector2f &slope);



   std::string GetShooter(Bullet &bullet);



   int GetType(Bullet &bullet);



};

#endif
