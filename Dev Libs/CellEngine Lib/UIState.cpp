#include "UIState.h"

using namespace cell;

UIState *UIState::_instance = NULL;
UIState *UIState::GetInst()
{
    if(!_instance)
    {
        _instance = new UIState;
    }
    return _instance;
}

UIState::UIState()
:
mouseDown(false),
mouseX(0),
mouseY(0),
itemHot(0),
itemActive(0)
{

}


void UIState::Update(sf::Event &event)
{
    if(event.Type == sf::Event::MouseMoved)
    {
        mouseX = event.MouseMove.X;
        mouseY = event.MouseMove.Y;
    }
    else if(event.Type == sf::Event::MouseButtonPressed)
    {
        mouseDown = true;
        itemActive = 1;
    }
    else if(event.Type == sf::Event::MouseButtonReleased)
    {
        mouseDown = false;
        itemActive = 0;
    }

}

UIState::~UIState()
{

}

