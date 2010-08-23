#include "FailState.h"

FailState* FailState::_instance;
FailState* FailState::GetInst()
{
    if(!_instance)
    {
        _instance = new FailState;
    }
    return _instance;
}

FailState::FailState()
{
    _failImage.SetImage(cell::ImageManager::GetInst()->GetImage("images/fail.png"));
}

FailState::~FailState()
{
    if(_instance)
        delete _instance;
}


void FailState::HandleEvents(GameManager* mgr)
{
    const sf::Input& input = mgr->GetInput();
    sf::Event _event;
    while(mgr->GetEvent(_event))
    {
        cell::UIState::GetInst()->Update(_event);
        if(_event.Type == sf::Event::Closed)
        {
            mgr->Close();
        }
        if(input.IsKeyDown(sf::Key::Escape))
        {
            mgr->Close();
        }
    }
}

void FailState::Update(GameManager*)
{
    // do nothing but laugh
}
void FailState::Render(GameManager* mgr)
{
    mgr->Draw(_failImage);
}
