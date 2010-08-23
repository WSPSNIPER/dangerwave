#ifndef FAILSTATE_H
#define FAILSTATE_H

#include "GameManager.h"
#include "State.h"
#include "ImageManager.h"

using namespace cell;

class FailState :public State
{
        FailState();
        static FailState* _instance;
    public:
        static FailState* GetInst();
        ~FailState();

        void Init(){}
        void Cleanup(){}
        void Update(GameManager*);
        void Render(GameManager*);
        void HandleEvents(GameManager*);
    private:
        sf::Sprite _failImage;
};

#endif // FAILSTATE_H
