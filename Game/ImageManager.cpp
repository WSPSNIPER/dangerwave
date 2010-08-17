#include "ImageManager.h"


using namespace cell;

// i documented this too well lol

/**************************************************************************************************
 * singleton methods
 **************************************************************************************************/
ImageManager* ImageManager::_instance = NULL;
ImageManager* ImageManager::GetInst()
{
    if(!_instance)
    {
        _instance = new ImageManager();
    }
    return _instance;
}

ImageManager& ImageManager::GetRef()
{
    if(!_instance)
    {
        _instance = new ImageManager();
    }
    return *_instance;
}
///************************************************************************************************




/// constructor
ImageManager::ImageManager()
{
}

/// destructor
ImageManager::~ImageManager()
{
    _images.clear();
    if(_instance)
    {
        delete _instance;
    }
}


/// gets an image from the list if it exists or creates one if it dosent
sf::Image& ImageManager::GetImage(std::string image_name)
{
    _iterator = _images.find(image_name);
    if(_iterator == _images.end())
    {
        return _addImage(image_name);
    }
    return _iterator->second;
}


/// adds an image to the list
sf::Image& ImageManager::_addImage(std::string image_name)
{
    sf::Image temp;
    temp.LoadFromFile(image_name);
    temp.CreateMaskFromColor(sf::Color(255,0,255));
    _images.insert(std::make_pair<std::string, sf::Image>(image_name, temp)); // i dont think i need the template brackets but its fine

    _iterator = _images.find(image_name);
    return _iterator->second;
}


