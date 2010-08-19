#include <SFML/Graphics.hpp>

#include <SFML/System.hpp>
#include <iostream>
#include "EntityManager.h"
#include "Player.h"
#include "GameManager.h"
#include "TestState.h"
#include "QuadTree.h"
#include <fstream>
using namespace std; // just because im cool :)
int main()
{
    GameManager game(640, 480, 32, "Game");

    game.SetFramerateLimit(60);
    game.PushState(TestState::GetInst());
    game.Init();
    while(game.IsOpened())
    {
        game.HandleEvents();
        game.Update();
        game.Render();
    }
    game.Cleanup();
    return EXIT_SUCCESS;
}
