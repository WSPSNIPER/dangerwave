#ifndef _WEAPON_H_

#define _WEAPON_H_



#include "Entity.h"



#include "ImageManager.h"



#include "LuaManager.h"


#include "SFML/Graphics.hpp"


#include "slope.hpp"

//#include "bullet.hpp"

#include <string>
using namespace std;

class Weapon : public cell::Entity

{



public:



   // eek! i hate coders block!!!



   Weapon(cell::Entity* owner); // the owner of the weapon



   Weapon();



   Slope _Slope;



   virtual void Update();



   virtual void Render(sf::RenderWindow& window);



   virtual void Reload();

   virtual void Shoot(sf::Vector2f player, sf::Vector2f Target);



   void ConnectToEntity(cell::Entity* newOwner); // so they can pick it up off the ground

   void DisconnectFromEntity(cell::Entity* OldOwner);

   //so the play can switch weapons or drop





   float GetAccuracy()     const

   {

       return _accuracy;

   }



   float GetReloadSpeed()  const

   {

       return _reloadSpeed;

   }



   float GetDamage()       const

   {

       return _damage;

   }



   int GetClipSize()       const

   {

       return _clipSize;

   }



   int GetRateOfFire()     const

   {

       return _rateOfFire;

   }



protected:



   virtual bool LoadLuaScript(string filename);



   float           _accuracy;



   float           _reloadSpeed;



   int             _clipSize;



   int             _rateOfFire;



   float           _damage;



   float           _rotation;



   int             _fireCount;



   int             _mag;



   int             _ammo, _ammoleft, _ammomax;



   bool            _reloading, _shooting;



   cell::Entity*   _owner;



   sf::Clock reload_time_wait;

   sf::Clock rate;



   sf::Sprite      _sprite;



};



#endif // _WEAPON_H_

