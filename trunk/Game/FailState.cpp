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
    _rand.SetSeed((unsigned)time(NULL));
    char buffer[33];
    _failImage.SetImage(cell::ImageManager::GetInst()->GetImage("images/fail.png"));
    std::string s = "YOU SCORED ";
    std::string a = itoa(score, buffer, 10);
    std::string txt = s+a;

    _scoreString.SetText(txt);

    if(score == 0)
    {
        _message.SetText("YOUR A SUPER NOOB");
    }
    if(score >= 1)
    {
        _message.SetText("YOUR A NOOB");
    }
    if(score >= 5)
    {
        _message.SetText("YOUR A SURVIVOR!");
    }
    if(score >= 10)
    {
        _message.SetText("YOUR A BEAST");
    }
    if(score >= 15)
    {
        _message.SetText("YOUR THE BEST OF THE BEST");
    }
    if(score >= 20)
    {
        _message.SetText("YOUR A GOD!!");
    }
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

void FailState::Update(GameManager* mgr)
{
    sf::View view = mgr->GetView();
    _scoreString.SetPosition(mgr->ConvertCoords(200, 200, &view));
    _failImage.SetPosition(mgr->ConvertCoords(0,0, &view));
    _message.SetPosition(mgr->ConvertCoords(200, 270, &view));


}
void FailState::Render(GameManager* mgr)
{
    if(_flicker.GetElapsedTime() >= 0.05f)
    {
        _message.SetColor(sf::Color(_rand.Random(0, 255), _rand.Random(0, 255),_rand.Random(0, 255)));
        _flicker.Reset();
    }
    mgr->Draw(_failImage);
    mgr->Draw(_scoreString);
    mgr->Draw(_message);
}
