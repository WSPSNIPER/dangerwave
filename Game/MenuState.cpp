#include "MenuState.h"
#include "SwarmState.h"
#define OFFSET 9
MenuState* MenuState::_instance = NULL;
MenuState* MenuState::GetInst()
{
    if(!_instance)
        _instance = new MenuState;
    return _instance;
}

MenuState::MenuState():
_imgMgr(cell::ImageManager::GetInst())
{
    _menuImage.SetImage(_imgMgr->GetImage("images/menu.png"));
    _startImage.SetImage(_imgMgr->GetImage("images/start.png"));
    _quitImage.SetImage(_imgMgr->GetImage("images/quit.png"));
    _arrow.SetImage(_imgMgr->GetImage("images/arrow.png"));

    _startImage.SetPosition(300, 150);
    _quitImage.SetPosition(300, 300);
    _arrow.SetPosition(300 - 32, 150+OFFSET);
}

MenuState::~MenuState()
{
    if(_instance)
        delete _instance;
}



void MenuState::Init()
{

}

void MenuState::Cleanup()
{

}

void MenuState::Update(GameManager* mgr)
{

}

void MenuState::Render(GameManager* mgr)
{
    mgr->Draw(_menuImage);
    mgr->Draw(_startImage);
    mgr->Draw(_quitImage);
    mgr->Draw(_arrow);
}

void MenuState::HandleEvents(GameManager* mgr)
{
    const sf::Input& input = mgr->GetInput();
    sf::Event event;
    mgr->GetEvent(event);
    if(event.Type == sf::Event::Closed)
        mgr->Close();
    if(input.IsKeyDown(sf::Key::Return))
    {
        if(_arrow.GetPosition().y == _startImage.GetPosition().y + OFFSET)
        {
             mgr->PushState(SwarmState::GetInst());
        }
        else if(_arrow.GetPosition().y == _quitImage.GetPosition().y +OFFSET)
        {
            mgr->Close();
        }
    }
    else if(input.IsKeyDown(sf::Key::Down))
    {
        if(_arrow.GetPosition().y == _startImage.GetPosition().y +OFFSET)
        {
            _arrow.SetPosition(_quitImage.GetPosition().x - 32, _quitImage.GetPosition().y + OFFSET);
        }
        else
        {
            _arrow.SetPosition(_startImage.GetPosition().x - 32, _startImage.GetPosition().y + OFFSET);
        }
    }
    else if(input.IsKeyDown(sf::Key::Up))
    {
        if(_arrow.GetPosition().y == _startImage.GetPosition().y+OFFSET)
        {
            _arrow.SetPosition(_quitImage.GetPosition().x - 32, _quitImage.GetPosition().y+OFFSET);
        }
        else
        {
            _arrow.SetPosition(_startImage.GetPosition().x - 32, _startImage.GetPosition().y+OFFSET);
        }
    }
}
