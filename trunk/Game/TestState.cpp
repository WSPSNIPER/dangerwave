#include "TestState.h"

TestState *TestState::_instance = NULL;
TestState *TestState::GetInst()
{
    if(!_instance)
    {
        _instance = new TestState;
    }
    return _instance;
}

TestState::TestState()
:
_manager(cell::ImageManager::GetInst()),
_entityManager(EntityManager::GetInst()),
_luaManager(cell::LuaManager::GetInst()),
t(2)
{

    _entityManager->Add(new Player(100, 100, "player.png"));
    _entityManager->Add(new cell::Entity(110, 110, "player.png"));
    _entityManager->Add(new cell::Entity(300, 100, "player.png"));
    //ExportPlayer(&_player); // export the player to lua
}

TestState::~TestState()
{
    file.close();
    if(_instance)
        delete _instance;
}

void TestState::Init()
{

    file.open("debug.txt", std::ios::out);
}

void TestState::Cleanup()
{

}

void TestState::Update(GameManager* game)
{

    //cell::LuaManager::GetInst()->DoFile("player.lua");
    _entityManager->Update();

    file <<  " about to check collisions \n";
    file.flush();

    t.Update(_entityManager);
    t.CheckCollisions();
    //_tree.Update(_entityManager);

    file << " done checking collisions \n";
    file.flush();

}

void TestState::Render(GameManager* game)
{
    _entityManager->Render(*game);
}

void TestState::HandleEvents(GameManager* game)
{
    while(game->GetEvent(_event))
    {
        cell::UIState::GetInst()->Update(_event);
        if(_event.Type == sf::Event::Closed)
        {
            game->Close();
        }
    }
}

