#include "Player.h"
#include <iostream>

using namespace cell;

Player::Player(float setX, float setY, std::string setName)
:
cell::Entity(setX, setY, 80, 120/4, setName),
_animation(_sprite, 80, 120/4, 4, VERTICAL)
{
    _animation.AddAnimation("move");
    _animation.SetDelay(0.1f);
    _animation.GetSprite().SetCenter(40, (120/4)/2);
    _hp = 0;
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

void Player::HandleInput(const sf::Input &input)
{
    if(input.IsKeyDown(sf::Key::W))
    {
        Move(0.f, -5.f);
    }
    else if(input.IsKeyDown(sf::Key::S))
    {
        Move(0.f, 5.f);
    }
    else if(input.IsKeyDown(sf::Key::D))
    {
        Move(5.f, 0.f);
    }
    else if(input.IsKeyDown(sf::Key::A))
    {
        Move(-5.f, 0.f);
    }
}


void Player::Move(float off_x, float off_y)
{
    _animation.GetSprite().Move(off_x, off_y);
    Entity::Move(off_x, off_y);
}

void Player::OnCollision()
{
    std::cout << "collision " << std::endl;
}

void Player::Update()
{
    _mousePos.x = _state->mouseX;
    _mousePos.y = _state->mouseY;
    _playerPos = _animation.GetSprite().GetPosition();

    RotateToMouse();
}


void Player::Render(sf::RenderWindow& window)
{
    HandleInput(window.GetInput());
    _animation.PlayAnimation(window);
}

void ExportPlayer(Player* player)
{
    /*cell::LuaManager *manager = cell::LuaManager::GetInst();
    luabind::module(manager->GetState())
    [
        luabind::class_<Player>("Player")
        .def("SetHp", &Player::SetHp)
        .def("GetHp", &Player::GetHp)
        .def("GetX", &Player::GetX)
        .def("GetY", &Player::GetY)
        .def("SetPosition", &Player::SetPosition)
        .def("Move", &Player::Move)
        .def("Die", &Player::Die)
    ];
    manager->SetGlobal("player", player);*/
}
