#ifndef FOOD_H
#define FOOD_H
#include "Entity.h"
#include "EntityManager.h"
#include "ImageManager.h"

class Food : public cell::Entity
{
    public:
        Food(int x, int y, int heal, std::string name);
        virtual ~Food();

        void Render(sf::RenderWindow& window);

        void OnCollision(cell::Entity* e);

        int Heal() { return _healAmnt; }
        void SetHeal(int amnt) { _healAmnt = amnt; }
    protected:
        int _healAmnt;
};

#endif // FOOD_H
