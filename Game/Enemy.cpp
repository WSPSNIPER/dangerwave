#include "Enemy.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Trig.h"
void ExportEntity()
{

}

int amount = 0;

Enemy::Enemy(int x, int y, float speed):
cell::Entity(x, y, 32,32, "images/enemy.png")
{
    SetPosition(x, y);
    _collisionRect.set(x,y,30,30);
    _type = ENEMY;
    _alive = true;
    _speed = speed;


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
        amount--;
        //EntityManager::GetInst()->Add(new Enemy((int)rand() % 40*32, (int)rand() % 40*32));
    }

}

void Enemy::Render(sf::RenderWindow& window)
{
    window.Draw(_sprite);
}

void Enemy::Update()
{
    _playerPos = _sprite.GetPosition();
    RunAI();
    cell::Entity::Update();
    _collisionRect.x = _playerPos.x;
    _collisionRect.y = _playerPos.y;
}

void Enemy::RunAI()
{
    Entity* player = EntityManager::GetInst()->GetEntity(0);
    sf::Vector2f other(player->GetX(), player->GetY());
    sf::Vector2f vel = cell::Vect::GetPlayerPath(other, _playerPos, _speed);

    Move(-vel.x, -vel.y);

}



