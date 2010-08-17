#include "GameManager.h"


GameManager::GameManager(int width, int height, int bpp, std::string title)
:
sf::RenderWindow(sf::VideoMode(width, height, bpp), title)
{
    _states.clear();
}

GameManager::~GameManager()
{
    _states.clear();
}

void GameManager::HandleEvents()
{

    _states.back()->HandleEvents(this);

}

void GameManager::Init()
{

}

void GameManager::Cleanup()
{

}

void GameManager::Update()
{

    _states.back()->Update(this);
}

void GameManager::Render()
{
    Clear();

    _states.back()->Render(this);

    Display();
}

void GameManager::PushState(State* state)
{
    _states.push_back(state);
    _states.back()->Init();
}

void GameManager::PopState()
{
    _states.back()->Cleanup();
    _states.pop_back();
}
