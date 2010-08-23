#ifndef _ENTITY_MANAGER_H_
#define _ENTITY_MANAGER_H_

#include "Entity.h"
#include <vector>


class EntityManager
{
    private:
        EntityManager();
        static EntityManager* _instance;
    public:
        ~EntityManager();
        static EntityManager* GetInst();
        static EntityManager& GetRef();

        void Clear() {
            for(unsigned int i = 1; i < _entity.size(); i++)
            {
                if(_entity[i])
                    delete _entity[i];
                _entity.erase(_entity.begin()+1, _entity.end());
            }
        }

        void Render(sf::RenderWindow& window);
        void Update();

        void Kill(int i)
        {
            delete _entity[i];
            _entity.erase(_entity.begin()+i);
        }
        /// example use  Add(new Entity()) or Add(new Entity(player)) NOT NOT NOT! Add(&player) NOT THAT
        void Add(cell::Entity* entity); // always add entities like this, new Entity() if you have one do new Entity(entity)

        void Add(cell::Entity& entity); // incase you want to allocate an already made instance

        cell::Entity* GetEntity(int index) { return _entity[index]; }

        std::vector<cell::Entity*>& GetVector() { return _entity; }


    private:
        std::vector<cell::Entity*> _entity;
};

extern void ExportEntityManager();

#endif