#ifndef _STATE_H_
#define _STATE_H_

#include "SFML/Graphics.hpp"

class GameManager;

/// Must over ride this class with the new state
class State
{
    protected:
        State(){}
    public:
        virtual ~State(){}
        virtual void Update(GameManager*) = 0;
        virtual void Render(GameManager*) = 0;
        virtual void HandleEvents(GameManager*) = 0;
        virtual void Init() = 0;
        virtual void Cleanup() = 0;

        void PushState(State* state, GameManager*){}
        void PopState(GameManager*){}

    protected:
        sf::Event _event;
};

#endif
