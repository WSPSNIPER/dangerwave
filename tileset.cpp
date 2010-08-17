#include"headers.hpp"
#include"level.hpp"
#include"tileset.hpp"

void Tileset::Create()
{
    tile = new Tile*[x_amount];
    for(int c = 0; c < y_amount; c++)
    {
        tile[c] = new Tile[y_amount];
    }
}

Tileset::~Tileset()
{
    delete [] tile;
}

Tileset::Tileset(int x_num, int y_num, int W, int H, sf::Sprite &Temp)
{
    h = H;
    w = W;

    sprite = Temp;

    x_amount = x_num;
    y_amount = y_num;

    for(int a = 0; a < y_num / H; a++)
    {

        for(int b = 0; b < x_num / W; b++)
        {
            tile[a][b].h = H;
            tile[a][b].w = W;
            tile[a][b].x = b * W;
            tile[a][b].y = a * H;
        }

    }

}
