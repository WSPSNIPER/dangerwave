#include "EntityManager.h"
#include "LuaManager.h"



//Singleton methods
EntityManager* EntityManager::_instance = NULL;
EntityManager* EntityManager::GetInst()
{
    if(!_instance)
    {
        _instance = new EntityManager;
    }
    return _instance;
}

EntityManager& EntityManager::GetRef()
{
    if(!_instance)
    {
        _instance = new EntityManager;
    }
    return *_instance;
}

//end singleton methods


EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
    for(unsigned int i = 0; i < _entity.size(); i++)
    {
        // kind  of iffy about this :0 hope i remember to put all the mem on the heap so i dont delete nothing
        if(_entity[i])
            delete _entity[i];
    }


    _entity.clear();

    if(_instance)
        delete _instance;
}

void EntityManager::Add(cell::Entity* entity)
{
    _entity.push_back(entity);/// arrg idk what to work on CODERS BLOCK!!!shi
}

void EntityManager::Add(cell::Entity& entity)
{
    _entity.push_back(new cell::Entity(entity)); // hope this works lol
}


void EntityManager::Render(sf::RenderWindow& window)
{
    for(unsigned int i = 0; i < _entity.size(); i++)
    {
        _entity[i]->Render(window);
    }
}

void EntityManager::Update()
{
    for(std::vector<cell::Entity*>::iterator it = _entity.begin();
        it != _entity.end();
        ++it )
    {
        (*it)->Update();
        if((*it)->Dead()){
            delete (*it);
            _entity.erase(it);
            --it;
        }
    }
}


