#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Trig.h"
#include "EntityManager.h"
extern int amount;
class Enemy : public cell::Entity
{
    public:
        Enemy(int x, int y, float speed = 2.f);
        ~Enemy();
        virtual void OnCollision(cell::Entity* e);
        virtual void Update();
        virtual void Render(sf::RenderWindow& window);

        void RunAI();
    private:
    sf::Randomizer _rand;
    float _speed;
};
extern void ExportEnemy();
#endif // ENEMY_H
