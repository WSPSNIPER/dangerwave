#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Trig.h"
#include "Entity.h"
#include "Animation.h"
#include <string>
#include "bullet.hpp"
#include "slope.hpp"
/// @todo Create a Rect class to take care of Entity Collision
const float PLAYER_SPEED = 3.f;
class Player : public cell::Entity
{
    public:
        Player(float startX, float startY, std::string image_name, std::string script="");
        ~Player();

        void ChangeAnimation(std::string anim_name);
        virtual void Move(float off_x, float off_y);
        virtual void Update();
        virtual void HandleInput(const sf::Input &input);
        virtual void Render(sf::RenderWindow& window);
        void RotateToMouse();

        virtual void OnCollision(int t = 0);

        void Shoot();

        int  GetHp() const { return _hp; }
        void SetHp(int hp) { _hp = hp; }
        void ChangeHp(int c) { _hp += c; }

    private:

        int             _hp;
        cell::Animation _animation;
        std::string     _currentAnim;
        std::string     _script;
        float _angle;
        Slope _slope;
        sf::Clock _shotTimer;

};

extern void ExportPlayer( Player* player );


#endif
