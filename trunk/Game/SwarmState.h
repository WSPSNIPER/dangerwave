#ifndef _SWARM_STATE_H_
#define _SWARM_STATE_H_

#include "State.h"
#include "Player.h"
#include "EntityManager.h"
#include "ImageManager.h"
#include "QuadTree.h"
#include "Level.h"
#include "Trig.h"
#include "Food.h"
#include "Enemy.h"
#include <time.h>
#include "bulletmanager.hpp"
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
#define MAX_LEVELS 100
#define TIME_LIMIT 10000 // no time limit
#define IN_ROUND 1
#define OUT_OF_ROUND 2
#define PASS 1
#define FAIL 2 /// should have used an enum lol

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

        void SpawnWave(int amount);
        void SpawnFood(int amount);
        void UpdateMsg();

        void StartRound(int level);
        bool KilledAll();

        void UpdateText();

    private:
        int             _scoreGoal;
        sf::String      _pressText;
        sf::String      _timerText2;
        sf::String      _scoreText2;
        sf::String      _levelText2;
        sf::String      _timerText;
        sf::String      _scoreText;
        sf::String      _levelText;
        int             _score;
        int             _currentLevel;
        sf::Clock       _timer;
        Player*         _player;
        Level           _level;
        EntityManager*  _manager;
        ImageManager*   _images;
        QuadTree        _tree;
        int             _enemyCount;
        sf::Music       _music;
        sf::Randomizer  _rand;
        sf::View        _view;
        sf::Clock       _spawnTimer;
        sf::Shape       _health;
        sf::Clock       _scoreTimer;
        sf::String      _message;
        /// @TODO finish this state


};

#endif