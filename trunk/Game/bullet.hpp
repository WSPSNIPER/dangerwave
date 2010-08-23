#ifndef _BULLET_H_
#define _BULLET_H_

#include "Entity.h"
#include "slope.hpp"
#include <string>
using namespace std;
class Bullet : public cell::Entity

{
public:
   float Angle, Type;

   sf::Vector2f _Speed;

   sf::Vector2f Position;

   string Shooter;

   bool done;

   bool Shot;

   Bullet(float angle,float type,sf::Vector2f slope,sf::Vector2f position, string owner);

   void Move(float x, float y);

   void OnCollision(cell::Entity*);

   void Update();

   void Render(sf::RenderWindow& window);

   void SetRotation(float Rot);

   void SetSpeed(sf::Vector2f _slope);

   void SetPosition(sf::Vector2f );

   Slope _Slope;

};

#endif
