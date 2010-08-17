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
    _collisionRect.x = x;
    _collisionRect.y = y;
}

void Entity::Move(float offset_x, float offset_y)
{
    _sprite.Move(offset_x, offset_y);
    _collisionRect.x += offset_x;
    _collisionRect.y += offset_y;
}


float Entity::GetX() const
{
    return _playerPos.x;
}

float Entity::GetY() const
{
    return _playerPos.y;
}

const sf::Vector2f Entity::GetPosition() const
{
    return _sprite.GetPosition();
}

const sf::Sprite& Entity::GetSprite()
{
    return _sprite;
}
