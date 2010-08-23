#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "EntityManager.h"
#include "QuadTree.h"
#include "State.h"
#include <string>

extern int score;
class GameManager : public sf::RenderWindow
{
    public:
        GameManager(int width, int height, int bpp, std::string title);
        ~GameManager();

        void Update();
        void Render();
        void HandleEvents();
        void Init();
        void Cleanup();

        void PushState(State*);
        void PopState();



    private:
        std::vector<State*> _states;

};

#endif
