#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "ImageManager.h"
#include "UIState.h"
#include "Trig.h"
/**************************************************************************************************
 * @class Entity is a class that represents a base movable object, it is ment to be overriden
 * and used for polymorphism
 **************************************************************************************************/

enum EntityType
{
    MAP_OBJECT = 0,
    BULLET,
    PLAYER // add more when you need to
};
namespace cell
{

     /// just a super basic entity class, you need to add to it for it to work, override the pure virtual functions exc.
    class Entity
    {
        public:
            Entity();
            Entity(float x, float y, std::string image_name);
            virtual ~Entity();

            virtual void Render(sf::RenderWindow& window);
            virtual void Update();

            virtual void OnCollision(){}
            virtual void OnCollision(int type){}// add to the enum if you want more or just make a define or somthing

            virtual float GetX() const;
            virtual float GetY() const;

            virtual sf::Vector2f GetPosition() const;

            virtual sf::Sprite& GetSprite();

            virtual void SetPosition(float x, float y);
            virtual void Move(float offset_x, float offset_y);

            sf::FloatRect& GetRect() { return _collisionRect; }

            inline bool Collision(cell::Entity* other)
            {
                return (other->GetRect().Intersects(_collisionRect));
            }
            inline bool Collision(sf::FloatRect rect)
            {
                return (rect.Intersects(_collisionRect));
            }

            virtual void SetImage(std::string filename);   // i had to make them all virtual because some entities use animations :)

        protected:
            void            _turnToMouse();
            void            _turnToPoint(sf::Vector2f& point);
            cell::UIState*        _state;
            cell::ImageManager&   _imgMgr;
            sf::Vector2f    _playerPos,
                            _mousePos;
            sf::Sprite      _sprite;
            sf::FloatRect   _collisionRect;
    };
}

#endif
