#ifndef FAILSTATE_H
#define FAILSTATE_H

#include "GameManager.h"
#include "State.h"
#include "ImageManager.h"
#include "GameManager.h"
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
        sf::String _scoreString;
        sf::String _message;
        sf::Randomizer _rand;
        sf::Clock       _flicker;
};

#endif // FAILSTATE_H
