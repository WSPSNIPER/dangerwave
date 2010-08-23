#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "EntityManager.h"
extern int amount;
class Enemy : public cell::Entity
{
    public:
        Enemy(int x, int y, std::string image = "images/enemy.png");
        ~Enemy();
        virtual void OnCollision(cell::Entity* e);
        virtual void Update();
        virtual void Render(sf::RenderWindow& window);

        void RunAI();
    private:
    sf::Randomizer _rand;
};
extern void ExportEnemy();
#endif // ENEMY_H
