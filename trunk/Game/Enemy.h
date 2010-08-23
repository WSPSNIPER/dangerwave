#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "EntityManager.h"
#include <random>

class Enemy : public cell::Entity
{
    public:
        Enemy(int x, int y);
        virtual ~Enemy();

        void OnCollision(int t = 0);
        void Update();
    private:
    sf::Randomizer _rand;
};

#endif // ENEMY_H
