#include "SwarmState.h"
#include "GameManager.h"
#include "FailState.h"
int state = OUT_OF_ROUND;
int status = PASS;
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
_tree(2, 700, 500),
_bullets(BulletManager::GetInst()),
_enemyCount(0)
{
    _player = new Player(320, 240, "images/player.png");
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

    _timerText2.SetText("time:");
    _scoreText2.SetText("score:");
    _levelText2.SetText("level:");
    _music.OpenFromFile("sounds/game_music.ogg");

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
            }
        }
    }
}

void SwarmState::SpawnFood(int amnt)
{
    for(int i =0; i < amnt; i++)
    {
        _manager->Add(new Food(_rand.Random(40, 600), _rand.Random(40, 400), 10, "images/food.png"));
    }
    _scoreGoal = amnt;
}

void SwarmState::SpawnWave(int amnt)
{
    for(int i = 0; i < amnt; i++)
    {
        _manager->Add(new Enemy(_rand.Random(40, 600), _rand.Random(40, 400)));
    }
}

void SwarmState::StartRound(int level)
{

    SpawnWave(12);
    SpawnFood(10);
    amount = 12;


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
/// make the scoring about seeing how long you can last the wave.
void SwarmState::Update(GameManager* mgr)
{
    if(_spawnTimer.GetElapsedTime() >= 20.f)
    {
        SpawnWave(12);
    }
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
            status = FAIL;
            mgr->PushState(FailState::GetInst());
        }
        else if(_score >= _scoreGoal)
        {
            state = OUT_OF_ROUND;
            _manager->Clear();
            _music.Pause();
        }
        else if(_manager->GetVector().size() == 1)
        {
            state = OUT_OF_ROUND;
            _manager->Clear();
            _music.Pause();

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
