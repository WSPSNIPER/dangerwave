#ifndef _TEST_STATE_H_
#define _TEST_STATE_H_

#include "State.h"
#include "GameManager.h"
#include "ImageManager.h"
#include "EntityManager.h"
#include "QuadTree.h"
#include "Player.h"
#include "QuadTree.h"

#include <fstream>
class TestState : public State
{
        TestState();
        static TestState* _instance;

    public:
        static TestState* GetInst();

        virtual ~TestState();
        void Render(GameManager*);
        void Update(GameManager*);
        void HandleEvents(GameManager*);
        void Init();
        void Cleanup();

    private:
        sf::Sprite _sprite;
        cell::ImageManager* _manager;
        EntityManager* _entityManager;
        cell::LuaManager* _luaManager;

        QuadTree t;
        std::ofstream file;
};

#endif
