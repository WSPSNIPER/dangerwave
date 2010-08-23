#include "SwarmState.h"
#include "GameManager.h"
int state = OUT_OF_ROUND;
SwarmState* SwarmState::_instance = NULL;

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
_tree(2, 640, 480),
_bullets(BulletManager::GetInst())
{
    _player = new Player(100, 100, "images/player.png");
    _manager->Add(_player);
    srand((unsigned)time(NULL));
    _pressText.SetPosition(300, 200);
    _pressText.SetText("Press P To Start The Round");

    _timerText2.SetPosition(2.f,10.f);
    _scoreText2.SetPosition(2.f,30.f);
    _levelText2.SetPosition(2.f,50.f);
    _timerText.SetPosition(100.f,10.f);
    _scoreText.SetPosition(100.f,30.f);
    _levelText.SetPosition(100.f,50.f);

    _timerText2.SetText("time:");
    _scoreText2.SetText("score:");
    _levelText2.SetText("level:");
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
            }
        }
    }
}

void SwarmState::SpawnFood(int amnt)
{
    for(int i =0; i < amnt; i++)
    {
        _manager->Add(new Food((int)rand() % 600, (int)rand() % 400, 10, "images/food.png"));
    }
    _scoreGoal = amnt;
}

void SwarmState::SpawnWave(int amnt)
{
    for(int i = 0; i < amnt; i++)
    {
        _manager->Add(new Entity((int)rand() % 600, (int)rand() % 400, 32, 32, "images/enemy.png"));
    }
}

void SwarmState::StartRound(int level)
{
    SpawnWave(2*(level+1)+5);
    SpawnFood(10);

    _timer.Reset();
    _score = 0;
    _player->SetScore(0);
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
    if(state == OUT_OF_ROUND)
    {
        mgr->Draw(_pressText);
    }
}

void SwarmState::UpdateText()
{
    char buffer[33];
    _scoreText.SetText(itoa(_score, buffer, 10));
    _levelText.SetText(itoa(_currentLevel, buffer, 10));
    _timerText.SetText(itoa((int)_timer.GetElapsedTime(), buffer, 10));

}

void SwarmState::Update(GameManager* mgr)
{
    _score = _player->GetScore();

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
        }
        else if(_score >= _scoreGoal)
        {
            state = OUT_OF_ROUND;
            _manager->Clear();
        }
    }
}
