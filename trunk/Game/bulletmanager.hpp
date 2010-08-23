#ifndef _BULLET_MGR_H_
#define _BULLET_MGR_H_

#include "Bullet.hpp"

class BulletManager
{
    static BulletManager* _instance;
    BulletManager();
public:
    static BulletManager* GetInst();
    ~BulletManager();

    void Add(Bullet* bullet);

    void Render(sf::RenderWindow& window);
    void Update();

    void Kill(int i)
    {
        delete _bullet[i];
        _bullet.erase(_bullet.begin()+i);
    }

    Bullet* GetBullet(int index) { return _bullet[index]; }
    std::vector<Bullet*>& GetVector() { return _bullet; }

private:
    std::vector<Bullet*> _bullet;
};

#endif
