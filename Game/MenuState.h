#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"
#include "ImageManager.h"
#include "EntityManager.h"
#include "GameManager.h"

class MenuState : public State
{
    MenuState();
    static MenuState *_instance;
    public:
        static MenuState *GetInst();
        virtual ~MenuState();
    protected:
        void Init();
        void Cleanup();
        void Update(GameManager*);
        void Render(GameManager*);
        void HandleEvents(GameManager*);
    private:
        // eeek arrg. not enough time lol
        cell::ImageManager *_imgMgr;
        sf::Sprite _menuImage;
        sf::Sprite _quitImage;
        sf::Sprite _startImage;
        sf::Sprite _arrow;
        sf::Clock  _timer;


};

#endif // MENUSTATE_H
