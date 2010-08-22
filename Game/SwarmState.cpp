#include "SwarmState.h"
#include "GameManager.h"

SwarmState* SwarmState::_instance = NULL;

SwarmState* SwarmState::GetInst()
{
    if(!_instance)
        _instance = new SwarmState;
    return _instance;
}

SwarmState::SwarmState()
:
_player(0),
_level("maps/island2.map", "images/tiles.png"),
_manager(EntityManager::GetInst()),
_images(ImageManager::GetInst()),
_tree(2, _level.GetWidth(), _level.GetHeight() )
{
    _manager->Add(new Player(100, 100, "images/player.png"));
}
SwarmState::~SwarmState()
{
    if(_instance)
        delete _instance;
}
void SwarmState::Init()
{
}

void SwarmState::Cleanup()
{
}

void SwarmState::HandleEvents(GameManager* mgr)
{
    while(mgr->GetEvent(_event))
    {
        cell::UIState::GetInst()->Update(_event);
        if(_event.Type == sf::Event::Closed)
        {
            mgr->Close();
        }
    }
}

void SwarmState::Render(GameManager* mgr)
{
    _level.Render(*mgr);
    _manager->Render(*mgr);
}

void SwarmState::Update(GameManager* mgr)
{
    _manager->Update();
    _tree.Update(_manager);
    _tree.CheckCollisions();

}
