#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Trig.h"
#include "Entity.h"
#include "Animation.h"
#include <string>
#include "bullet.hpp"
#include "bulletmanager.hpp"
#include "slope.hpp"
#include "SFML/Audio.hpp"
#include "SoundManager.h"
/// @todo Create a Rect class to take care of Entity Collision
const float PLAYER_SPEED = 5.f;
class Player : public cell::Entity
{
    public:
        Player(float startX, float startY, sf::View* view, std::string image_name,  std::string script="");
        ~Player();

        void ChangeAnimation(std::string anim_name);
        virtual void Move(float off_x, float off_y);
        virtual void Update();
        virtual void HandleInput(const sf::Input &input);
        virtual void Render(sf::RenderWindow& window);
        void RotateToMouse();

        virtual void OnCollision(cell::Entity* e);
        void Shoot();

        void SetView(sf::View* view){ _view = view; }

        int  GetHp() const { return _hp; }
        void SetHp(int hp) { _hp = hp; }
        void ChangeHp(int c) { _hp += c; }

        int GetScore() { return _score; }
        void IncrementScore() {_score++;}
        void SetScore(int s) { _score = s;}

        int GetKills() { return _kills; }
        void AddKill() { _kills++; }
        void SetKills(int k) { _kills = k; }

        sf::Shape GetHealthBar() { return _healthBar; }

    private:
        int             _kills;
        int             _hp;
        cell::Animation _animation;
        std::string     _currentAnim;
        std::string     _script;
        float           _angle;
        Slope           _slope;
        sf::Clock       _shotTimer;
        int             _score;
        sf::Sound       _gunSound;
        cell::SoundManager* _sounds;
        sf::Clock          _hpTimer;
        sf::Shape           _healthBar;
        sf::View            *_view;



};

extern void ExportPlayer( Player* player );


#endif
