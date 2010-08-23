#include "Player.h"
#include <iostream>
#include "EntityManager.h"
#include "slope.hpp"
using namespace cell;

const float RATE_OF_FIRE = 0.5f;
Player::Player(float setX, float setY, sf::View* view, std::string setName, std::string script)
:
cell::Entity(setX, setY, 32, 32, setName),
_animation(_sprite, 80, 120/4, 4, VERTICAL),
_script(script),
_kills(0),
_sounds(cell::SoundManager::GetInst()),
_view(view)
{
    _alive = true;
    _type = PLAYER;
    _animation.AddAnimation("move");
    _animation.SetDelay(0.1f);
    _animation.GetSprite().SetCenter(40, (120/4)/2);
    _hp = 100;
    _angle = 0.f;
    _score = 0;
    _gunSound.SetBuffer(_sounds->GetBuffer("sounds/gun.wav"));
    _gunSound.SetVolume(20.f);
    _healthBar = sf::Shape::Rectangle(520, 20, 520+_hp, 40, sf::Color(20, 230, 60));
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
    _gunSound.Play();
}
void Player::HandleInput(const sf::Input &input)
{
    if(input.IsMouseButtonDown(sf::Mouse::Left))
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
    _view->Move(off_x, off_y);
}

void Player::OnCollision(cell::Entity* e)
{

    if(e->GetType() == ENEMY)
    {
        if(_hpTimer.GetElapsedTime() >= 0.07f){
            _hp--;
            _hpTimer.Reset();
        }
    }
    else if(e->GetType() == FOOD)
    {
        _hp += 10;
        if(_hp > 100)
            _hp = 100;
        std::cout << "score up" << std::endl;
    }
}

void Player::Update()
{
    _playerPos = _animation.GetSprite().GetPosition();



    if(_hp <= 0)
        Kill();


}


void Player::Render(sf::RenderWindow& window)
{
    _mousePos = window.ConvertCoords(_state->mouseX, _state->mouseY, _view);
    RotateToMouse();
   // sf::Vector2f p = window.ConvertCoords(520, 40, _view);
   // _healthBar.SetPosition(p.x, p.y);
    HandleInput(window.GetInput());
    _animation.PlayAnimation(window);

   // window.Draw(_healthBar);
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
