#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "LuaManager.h"
#include <iostream>
#include "ImageManager.h"
#include "UIState.h"
#include "Trig.h"
#include "MyRect.h"
/**************************************************************************************************
 * @class Entity is a class that represents a base movable object, it is ment to be overriden
 * and used for polymorphism
 **************************************************************************************************/
// this class got bigger then i thought it was going to be lol
enum EntityType
{
    MAP_OBJECT = 0,
    BULLET,
    PLAYER,
    ENEMY,
    FOOD
};
namespace cell
{

     /// just a super basic entity class, you need to add to it for it to work, override the pure virtual functions exc.
    class Entity
    {
        public:
            Entity();
            Entity(float x, float y, float w, float h, std::string image_name);
            virtual ~Entity();

            virtual void Render(sf::RenderWindow& window);
            virtual void Update();

            virtual void OnCollision(){}
            virtual void OnCollision(int type){}// add to the enum if you want more or just make a define or somthing

            float GetX() const ;
            float GetY() const ;

            int GetType() { return _type; }
            void SetType(int t) { _type = t; }

            void SetAlive(bool a) { _alive = a; }

            bool Dead() { return !_alive; }
            bool Alive() { return _alive; }

            void Kill() { _alive = false; }

            void SetX(int x) { SetPosition(x, GetY());}
            void SetY(int y) { SetPosition(GetX(), y);}

            const sf::Vector2f GetPosition() const;

            const sf::Sprite& GetSprite();

            virtual void SetPosition(float x, float y);
            virtual void Move(float offset_x, float offset_y);

            MyRect& GetRect() { return _collisionRect; }

            inline bool Collision(cell::Entity* other)
            {
                return static_cast<bool>(_collisionRect.intersects(other->GetRect()));
            }
            inline bool Collision(MyRect& rect)
            {
                return static_cast<bool>(_collisionRect.intersects(rect));
            }

            virtual void SetImage(std::string filename);   // i had to make them all virtual because some entities use animations :)

        protected:
            void                    _turnToMouse();
            void                    _turnToPoint(sf::Vector2f& point);
            cell::UIState*          _state;
            cell::ImageManager&     _imgMgr;
            sf::Vector2f            _playerPos,
                                    _mousePos;
            sf::Sprite              _sprite;
            MyRect                  _collisionRect;
            bool                    _alive;
            int                     _type;
    };
}

#endif
