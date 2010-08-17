#include "Entity.h"

using namespace cell;

Entity::Entity()
:
_state(cell::UIState::GetInst()),
_imgMgr(ImageManager::GetRef())
{
}

Entity::Entity(float x, float y, std::string image_name)
:
_state(cell::UIState::GetInst()),
_imgMgr(ImageManager::GetRef())
{
    _sprite.SetImage(_imgMgr.GetImage(image_name));
    _sprite.SetPosition(x, y);
}

Entity::~Entity()
{
}


void Entity::Update()
{
    _playerPos = _sprite.GetPosition();
}

void Entity::Render(sf::RenderWindow& window)
{
    window.Draw(_sprite);
}

void Entity::_turnToMouse()
{
    _sprite.SetRotation(VectorMath::GetRotationAngle(_playerPos, _mousePos));
}

void Entity::_turnToPoint(sf::Vector2f& point)
{
    _sprite.SetRotation(VectorMath::GetRotationAngle(_playerPos, point));
}


void Entity::SetImage(std::string filename)
{
    _sprite.SetImage(_imgMgr.GetImage(filename));
}

void Entity::SetPosition(float x, float y)
{
    _sprite.SetPosition(x,y);
}

void Entity::Move(float offset_x, float offset_y)
{
    _sprite.Move(offset_x, offset_y);
}


float Entity::GetX() const
{
    return _sprite.GetPosition().x;
}

float Entity::GetY() const
{
    return _sprite.GetPosition().y;
}

sf::Vector2f Entity::GetPosition() const
{
    return _sprite.GetPosition();
}

sf::Sprite& Entity::GetSprite()
{
    return _sprite;
}
