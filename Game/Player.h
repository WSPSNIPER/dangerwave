#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Entity.h"
#include "Animation.h"
#include <string>

/// @todo Create a Rect class to take care of Entity Collision

class Player : public cell::Entity
{
    public:
        Player(float startX, float startY, std::string image_name);
        ~Player();

        void ChangeAnimation(std::string anim_name);
        virtual void Move(float off_x, float off_y);
        virtual void Update();
        virtual void HandleInput(const sf::Input &input);
        virtual void Render(sf::RenderWindow& window);
        void RotateToMouse();

        virtual void OnCollision();

        int  GetHp() const { return _hp; }
        void SetHp(int hp) { _hp = hp; }

        void Die() { std::cout << "player dead " << std::endl; }

    private:
        int             _hp;
        cell::Animation _animation;
        std::string     _currentAnim;

};

extern void ExportPlayer( Player* player );


#endif
