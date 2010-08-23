#include "Enemy.h"

Enemy::Enemy(int x, int y):
cell::Entity(x, y, 32,32, "images/enemy.png")
{
    _type = ENEMY;
    _rand.SetSeed(time(NULL));
}

Enemy::~Enemy()
{
}

void Enemy::OnCollision(int t)
{
    if(t == BULLET)
        Kill();

}

void Enemy::Update()
{

    Move(_rand.Random(-3.f, 3.f), _rand.Random(-3.f, 3.f));
    if(GetPosition().x > 640)
        SetX(640);
    else if(GetPosition().x < 0)
        SetX(0);
    if(GetPosition().y > 480)
        SetX(480);
    else if(GetPosition().y < 0)
        SetX(0);
}
