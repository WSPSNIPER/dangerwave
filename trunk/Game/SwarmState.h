#ifndef _SWARM_STATE_H_
#define _SWARM_STATE_H_

#include "State.h"
#include "Player.h"
#include "EntityManager.h"
#include "ImageManager.h"
#include "QuadTree.h"
#include "Level.h"
#include "Trig.h"

using namespace cell;


/// @SWARMSTATE
/// @Inherits State ( State.h )
/// @Singleton
/// @ImplementedIn GameManager ( GameManager.cpp ) as a state in the list

/** ***********************************************************************************************
*** the swarm state is a game mode in where you have to survive a swarm of enemies
*** there are ( x ) amount of waves where the number of enemies increases by ( n )
*** each wave and may get stronger
**************************************************************************************************/

class SwarmState : public State
{
    SwarmState();
    static SwarmState* _instance;
    public:
        ~SwarmState();
        static SwarmState* GetInst();

        void Init();
        void Cleanup();
        void Update(GameManager*);
        void HandleEvents(GameManager*);
        void Render(GameManager*);

    private:
        Player*         _player;
        Level           _level;
        EntityManager*  _manager;
        ImageManager*   _images;
        QuadTree        _tree;
        /// @TODO finish this state


};

#endif
