
#include "bulletmanager.hpp"
#include "bullet.hpp"

BulletManager* BulletManager::_instance = NULL;
BulletManager* BulletManager::GetInst()
{
    if(!_instance)
    {
        _instance = new BulletManager;
    }
    return _instance;
}


BulletManager::BulletManager()
{
    _bullet.clear();
}

BulletManager::~BulletManager()
{
    for(size_t i = 0; i < _bullet.size(); i++)
    {
        if(_bullet[i])
            delete _bullet[i];
    }
    _bullet.clear();
}

void BulletManager::Add(Bullet* bullet)
{
    _bullet.push_back(bullet);
}

void BulletManager::Render(sf::RenderWindow& window)
{
    for(size_t i = 0; i < _bullet.size(); i++)
    {
        _bullet[i]->Render(window);
    }
}

void BulletManager::Update()
{
    for(size_t i = 0; i < _bullet.size(); i++)
    {
        _bullet[i]->Update();
        if(_bullet[i]->Dead())
        {
            delete _bullet[i];
            _bullet.erase(_bullet.begin()+i);
            i--;
        }
    }
}
