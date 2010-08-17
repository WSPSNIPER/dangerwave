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
_player(0, 0, "player.png")
{
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
}

void SwarmState::Render(GameManager* mgr)
{
}

void SwarmState::Update(GameManager* mgr)
{
}
