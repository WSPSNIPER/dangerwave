
#include"weapon.hpp"

void Weapon::Reload()
{
    if(reload_time_wait.GetElapsedTime() < _reloadSpeed && _reloading)//while reload time hasnt come..
    {
        // this gets the number of bullets in a mag and checks if its full or not
        if(_ammo / _mag == _clipSize) //if the current clip is full
        {
            _reloading = false; //dont reload
        }
        else
        {
            _reloading = true;
        }
    }
    else
    {
        //if pasted or equal to reload time and is till in realoading process...

        _reloading = false;//ends he reloading process

        _ammoleft -= _clipSize; // basically tells you how much ammo
        //in total are in all the mags left.

        _ammo = _ammomax; // sets ammo back to max
        _fireCount = 0;
    }
}

void Weapon::Shoot(sf::Vector2f player, sf::Vector2f Target)
{
    if(!_reloading) //if not reloading..
    {
        if(_ammo / _mag < 1) //if you have a dont have ammo
        {
            Reload(); // reload weapon
        }
        else
        {
            if(rate.GetElapsedTime() > _rateOfFire) // if you are ready to shoot
            {
                rate.Reset(); // reset counter
                _shooting = false; //set status as not shooting.
                _fireCount++; //increases the number of bullets fired.
            }
            else//if time hasnt come to shoot again...
            {
                _shooting = true; //shooting is till true..
            }
        }
    }
}

/*Weapon::Weapon(cell::Entity* owner)
{
    _owner = owner;
}*/

void Weapon::ConnectToEntity(cell::Entity*  NewOwner)
{
    _owner = NewOwner;

    /*for(int a; a < _mag; a++)
    {
        int i = 0;
        //BulletManager::KillBullet(bullet[a]);
    }*/
}

void Weapon::DisconnectFromEntity(cell::Entity* OldOwner)
{
    _owner = NULL;
}
void Weapon::Render(sf::RenderWindow &window)
{
    //_Slope(window.GetInput().GetMouseX(),window.GetInput().GetMouseY())
}
