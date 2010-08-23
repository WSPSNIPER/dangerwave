#include "SwarmState.h"
#include "GameManager.h"
#include "FailState.h"
#include "Trig.h"
int state = OUT_OF_ROUND;
int status = PASS;
bool setup = false;
SwarmState* SwarmState::_instance = NULL;


// listinging to chelsea grin and bring me the horizion and programming my ass off to meet the
// dead line lol
SwarmState* SwarmState::GetInst()
{
    if(!_instance)
        _instance = new SwarmState;
    return _instance;
}

SwarmState::SwarmState()
:
_scoreGoal(0),
_score(0),
_currentLevel(0),
_player(0),
_level("maps/island2.map", "images/tiles.png"),
_manager(EntityManager::GetInst()),
_images(ImageManager::GetInst()),
_tree(2, _level.GetWidth()*32, _level.GetHeight()*32),
_enemyCount(0)
{
    std::cout << _level.GetHeight() << std::endl;
    _player = new Player(320, 240, &_view, "images/player.png");
    _manager->Add(_player);
    srand((unsigned)time(NULL));
    _pressText.SetPosition(150, 200);
    _pressText.SetText("Press P To Start The Round");

    _timerText2.SetPosition(2.f,10.f);
    _scoreText2.SetPosition(2.f,30.f);
    _levelText2.SetPosition(2.f,50.f);
    _timerText.SetPosition(100.f,10.f);
    _scoreText.SetPosition(100.f,30.f);
    _levelText.SetPosition(100.f,50.f);
    _message.SetPosition(2.f, 80.f);

    _message.SetText("START THE GAME ALREADY");

    _timerText2.SetText("time:");
    _scoreText2.SetText("score:");
    _levelText2.SetText("level:");
    _music.OpenFromFile("sounds/game_music.ogg");

    _health = _player->GetHealthBar();

}
SwarmState::~SwarmState()
{
    if(_instance)
        delete _instance;
}
void SwarmState::Init()
{
    _rand.SetSeed((unsigned)time(NULL));
}

void SwarmState::Cleanup()
{
}

void SwarmState::HandleEvents(GameManager* mgr)
{
    const sf::Input& input = mgr->GetInput();
    while(mgr->GetEvent(_event))
    {
        cell::UIState::GetInst()->Update(_event);
        if(_event.Type == sf::Event::Closed)
        {
            mgr->Close();
        }
        if(state == OUT_OF_ROUND)
        {
            if(input.IsKeyDown(sf::Key::P))
            {
                StartRound(_currentLevel);
                state = IN_ROUND;
                _currentLevel++;
                _music.Play();
                _spawnTimer.Reset();
                _scoreTimer.Reset();
            }
        }
    }
}

void SwarmState::SpawnFood(int amnt)
{
    for(int i =0; i < amnt; i++)
    {
        _manager->Add(new Food(_rand.Random(40, (_level.GetWidth()*32) - 50), _rand.Random(40, (_level.GetHeight()*32) - 50), 10, "images/food.png"));
    }
    _scoreGoal = amnt;
}

void SwarmState::SpawnWave(int amnt)
{
    for(int i = 0; i < amnt; i++)
    {
        _manager->Add(new Enemy(_rand.Random(40, (_level.GetWidth()*32) - 50), _rand.Random(40, (_level.GetHeight()*32)- 50)));
    }
}

void SwarmState::StartRound(int level)
{

    SpawnWave(50);
    SpawnFood(20);
    amount = 12;


    _timer.Reset();
}

void SwarmState::Render(GameManager* mgr)
{

    _level.Render(*mgr);
    _manager->Render(*mgr);
    mgr->Draw(_scoreText);
    mgr->Draw(_timerText);
    mgr->Draw(_levelText);
    mgr->Draw(_scoreText2);
    mgr->Draw(_timerText2);
    mgr->Draw(_levelText2);
    mgr->Draw(_health);
    mgr->Draw(_message);
    if(state == OUT_OF_ROUND)
    {
        mgr->Draw(_pressText);
    }
}

void SwarmState::UpdateMsg()
{
    if(_score == 0)
    {
        _message.SetText("SUPER NOOB");
    }
    if(_score >= 1)
    {
        _message.SetText("NOOB");
    }
    if(_score >= 5)
    {
        _message.SetText("Surviving!");
    }
    if(_score >= 10)
    {
        _message.SetText("Beast!");
    }
    if(_score >= 15)
    {
        _message.SetText("The Best of the Best!");
    }
    if(_score >= 20)
    {
        _message.SetText("GOD!!!");
    }
}

void SwarmState::UpdateText()
{
    UpdateMsg();
    if(_scoreTimer.GetElapsedTime() >= 10)
    {
        _score++;
        score++;
        _scoreTimer.Reset();
    }
    if(_spawnTimer.GetElapsedTime() >= 20.f)
    {
        SpawnWave(30);
        SpawnFood(30);
        _spawnTimer.Reset();
    }
    char buffer[33];
    _scoreText.SetText(itoa(_score, buffer, 10));
    _levelText.SetText(itoa(_currentLevel, buffer, 10));
    _timerText.SetText(itoa((int)_timer.GetElapsedTime(), buffer, 10));



}
/// make the scoring about seeing how long you can last the wave.
void SwarmState::Update(GameManager* mgr)
{
    _timerText2.SetPosition(mgr->ConvertCoords(2.f,10.f, &_view));
    _scoreText2.SetPosition(mgr->ConvertCoords(2.f,30.f, &_view));
    _levelText2.SetPosition(mgr->ConvertCoords(2.f,50.f, &_view));
    _timerText.SetPosition(mgr->ConvertCoords(100.f,10.f, &_view));
    _scoreText.SetPosition(mgr->ConvertCoords(100.f,30.f, &_view));
    _levelText.SetPosition(mgr->ConvertCoords(100.f,50.f, &_view));
    _message.SetPosition(mgr->ConvertCoords(2.f, 80.f, &_view));

    if(_player->GetHp() > 50)
        _health = sf::Shape::Rectangle(mgr->ConvertCoords(520, 20, &_view),
                                       mgr->ConvertCoords(520+_player->GetHp(), 40, &_view),
                                       sf::Color(20, 230, 30));
    else
        _health = sf::Shape::Rectangle(mgr->ConvertCoords(520, 20, &_view),
                                       mgr->ConvertCoords(520+_player->GetHp(), 40, &_view),
                                       sf::Color(230, 20, 30));
    if(!setup)
    {
        _view = mgr->GetDefaultView();
        _player->SetView(&_view);
        mgr->SetView(_view);
        setup = true;
    }


    _manager->Update();
    UpdateText();
    if(state == IN_ROUND)
    {

        _tree.Update(_manager);
        _tree.CheckCollisions();
        if(_timer.GetElapsedTime() >= TIME_LIMIT)
        {
            state = OUT_OF_ROUND;
            _manager->Clear();
            status = FAIL;
            mgr->PushState(FailState::GetInst());
        }

        else if(_player->Dead())
        {
            state = OUT_OF_ROUND;
            _manager->Clear();
            status = FAIL;
            mgr->PushState(FailState::GetInst());
        }
        std::cout << _manager->GetVector().size() << std::endl;
    }
}
