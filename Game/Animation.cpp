#include "Animation.h"
#include <iostream>

/// i rock at art lol ... the code is messy but ya
/// it had to be done :)
using namespace cell;

Animation::Animation(std::string name, uint16_t frame_width, uint16_t frame_height, uint16_t num_frames, anim_type type)
    :
    _frameWidth(frame_width),
    _frameHeight(frame_height),
    _delay(0.5f),
    _type(type),
    _imgMgr(ImageManager::GetRef()),
    _row(0),
    _frame(0)
{
    _maxFrame =num_frames -1;
    _sprite.SetImage(_imgMgr.GetImage(name));
}

Animation::Animation(sf::Image& image, uint16_t frame_width, uint16_t frame_height, uint16_t num_frames, anim_type type)
    :
    _frameWidth(frame_width),
    _frameHeight(frame_height),
    _delay(0.5f),
    _type(type),
    _imgMgr(ImageManager::GetRef()),
    _row(0),
    _frame(0)
{
    _maxFrame = num_frames -1;
    _sprite.SetImage(image);
}

Animation::Animation(sf::Sprite& sprite, uint16_t frame_width, uint16_t frame_height, uint16_t num_frames, anim_type type)
    :
    _frameWidth(frame_width),
    _frameHeight(frame_height),
    _delay(0.5f),
    _type(type),
    _imgMgr(ImageManager::GetRef()),
    _row(0),
    _frame(0)
{
    _maxFrame = num_frames -1;
    _sprite = sprite;
}

Animation::~Animation()
{
}

int Animation::GetRow(std::string name)
{
    for(size_t i = 0; i < _animList.size(); i++)
    {
        if(_animList[i].GetString() == name)
        {
            return i;
        }
    }
    //std::cout << "error animation dose not exist, using first row animation!" << std::endl;
    return 0;
}

void Animation::IncrementFrame(bool ocillate)
{
    _frame++;
    if(_frame > _maxFrame)
    {
        _frame = 0; // lol no ocillation :) it is easy to implement and ill do it when im not tired
    }
}
void Animation::PlayAnimation(std::string name, sf::RenderWindow& window, int times) // times not used yet
{
    if(_clock.GetElapsedTime() >= _delay)
    {
        IncrementFrame();
        _clock.Reset();
    }
    int x, y;
    if(_type == HORIZONTAL)
    {
        y = GetRow(name) * _frameHeight;
        x = _frame * _frameWidth;
    }
    else
    {
        y = _frame * _frameHeight;
        x = GetRow(name) * _frameWidth;
    }
    _sprite.SetSubRect(sf::IntRect(x, y, x + _frameWidth, y + _frameHeight));
    window.Draw(_sprite);
}



void Animation::PlayAnimation(sf::RenderWindow& window, int times)
{
    if(_clock.GetElapsedTime() >= _delay)
    {
        IncrementFrame();
        _clock.Reset();
    }
    int x, y;
    if(_type == HORIZONTAL)
    {
        y = GetRow(_animName) * _frameHeight;
        x = _frame * _frameWidth;
    }
    else
    {
        y = _frame * _frameHeight;
        x = GetRow(_animName) * _frameWidth;
    }
    _sprite.SetSubRect(sf::IntRect(x, y, x + _frameWidth, y + _frameHeight));
    window.Draw(_sprite);
}

void Animation::AddAnimation(std::string name)
{
    _animList.push_back(NumString(name, _row));
    _row += 1;
}
