#include "SoundManager.h"

using namespace cell;

SoundManager *SoundManager::_instance = NULL;
SoundManager *SoundManager::GetInst()
{
    if(!_instance)
    {
        _instance = new SoundManager;
    }
    return _instance;
}

SoundManager &SoundManager::GetRef()
{
    if(!_instance)
    {
        _instance = new SoundManager;
    }
    return *_instance;
}

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
    _buffers.clear();

    if(_instance)
    {
        delete _instance;
    }
}


sf::SoundBuffer& SoundManager::GetBuffer(std::string name)
{
    _iterator = _buffers.find(name);

    if(_iterator == _buffers.end())
    {
        return _addSound(name);
    }
    return _iterator->second;
}



sf::SoundBuffer& SoundManager::_addSound(std::string name)
{
    sf::SoundBuffer temp;
    temp.LoadFromFile(name);
    _buffers.insert(std::make_pair<std::string, sf::SoundBuffer>(name, temp));

    _iterator = _buffers.find(name);
    return _iterator->second;
}

