#include "Player.h"
#include <iostream>
#include "EntityManager.h"
#include "slope.hpp"
using namespace cell;

const float RATE_OF_FIRE = 0.5f;
Player::Player(float setX, float setY, std::string setName, std::string script)
:
cell::Entity(setX, setY, 80, 120/4, setName),
_animation(_sprite, 80, 120/4, 4, VERTICAL),
_script(script)
{
    _alive = true;
    _type = PLAYER;
    _animation.AddAnimation("move");
    _animation.SetDelay(0.1f);
    _animation.GetSprite().SetCenter(40, (120/4)/2);
    _hp = 100;
    _angle = 0.f;
    _score = 0;
}

void Player::RotateToMouse()
{
    _animation.GetSprite().SetRotation(VectorMath::GetRotationAngle(_playerPos, _mousePos));
}
Player::~Player()
{
}

void Player::ChangeAnimation(std::string name)
{
    _animation.SetCurrentAnimation(name);
}

void Player::Shoot()
{
    /// @todo fix the bullet dir
    EntityManager::GetInst()->Add(new Bullet(_angle, 0, Vect::GetBulletPath(_playerPos, _mousePos),
                                             _playerPos, "player"));
}
void Player::HandleInput(const sf::Input &input)
{
    if(input.IsKeyDown(sf::Key::Space))
    {
        if(_shotTimer.GetElapsedTime() >= RATE_OF_FIRE)
        {
            _shotTimer.Reset();
            Shoot();
        }
    }
    if(input.IsKeyDown(sf::Key::W))
    {
        Move(0.f, -PLAYER_SPEED);
    }
    else if(input.IsKeyDown(sf::Key::S))
    {
        Move(0.f, PLAYER_SPEED);
    }
    else if(input.IsKeyDown(sf::Key::D))
    {
        Move(PLAYER_SPEED, 0.f);
    }
    else if(input.IsKeyDown(sf::Key::A))
    {
        Move(-PLAYER_SPEED, 0.f);
    }
}


void Player::Move(float off_x, float off_y)
{
    _animation.GetSprite().Move(off_x, off_y);
    Entity::Move(off_x, off_y);
}

void Player::OnCollision(int t)
{
    if(t == ENEMY)
    {
        _hp -= 10;
    }
    else if(t == FOOD)
    {
        _score += 1;
    }
}

void Player::Update()
{
    _mousePos.x = _state->mouseX;
    _mousePos.y = _state->mouseY;
    _playerPos = _animation.GetSprite().GetPosition();

    if(_hp <= 0)
        Kill();

    RotateToMouse();
}


void Player::Render(sf::RenderWindow& window)
{
    HandleInput(window.GetInput());
    _animation.PlayAnimation(window);
}

void ExportPlayer(Player* player)
{
    cell::LuaManager *manager = cell::LuaManager::GetInst();
    luabind::module(manager->GetState())
    [
        luabind::class_<Player>("Player")
        .def("SetHp", &Player::SetHp)
        .def("GetHp", &Player::GetHp)
        .def("GetX", &Player::GetX)
        .def("GetY", &Player::GetY)
        .def("SetPosition", &Player::SetPosition)
        .def("Move", &Player::Move)
        .def("GetType", &Player::GetType)
        .def("Dead", &Player::Dead)
        .def("Kill", &Player::Kill)
    ];
    manager->SetGlobal("player", player);
}
