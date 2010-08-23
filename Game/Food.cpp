#include "Food.h"

Food::Food(int x, int y, int heal, std::string image) :
cell::Entity(x, y, 16, 16, image)
{
    _healAmnt = heal;
    SetPosition(x,y);
    _type = FOOD;
}

Food::~Food()
{
    //dtor
}




void Food::Render(sf::RenderWindow& window)
{
    window.Draw(_sprite);
}

void Food::OnCollision(cell::Entity* e)
{
    if(e->GetType() == PLAYER)
    {
        Kill();
    }
}
