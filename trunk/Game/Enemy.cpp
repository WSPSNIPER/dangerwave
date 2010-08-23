#include "Enemy.h"

Enemy::Enemy(int x, int y):
cell::Entity(x, y, 32,32, "images/enemy.png")
{

    _collisionRect.set(x,y,32,32);
    _type = ENEMY;
    _rand.SetSeed(time(NULL));
}

Enemy::~Enemy()
{
}

void Enemy::OnCollision(cell::Entity* e)
{
    if(e->GetType() == BULLET)
    {
        Kill();
        e->Kill();
    }

}

void Enemy::Update()
{
    int x = _rand.Random(-3.f, 3.f);
    int y = _rand.Random(-3.f, 3.f);
    Move(x,y);
    _collisionRect.x = x;
    _collisionRect.y = y;
    if(GetPosition().x > 640)
        SetX(640);
    else if(GetPosition().x < 0)
        SetX(0);
    if(GetPosition().y > 480)
        SetX(480);
    else if(GetPosition().y < 0)
        SetX(0);
}
