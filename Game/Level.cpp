#include "Level.h"
#include <fstream>
#include "ImageManager.h"
using namespace std;
Level::Level(std::string file, std::string img)
{
    m_count = 0;
    Load(file, img);
}

Level::Level()
{
    m_dir = "";
    m_count = 0;
}

Level::~Level()
{
    //dtor
}


void Level::Load(std::string file, std::string img)
{


    ifstream Load(file.c_str());
    std::string temp = "";
    int x, y, layer, x_coord, y_coord, strip_x, strip_y, w, h, flag;
    flag = 0;
    if(Load.is_open())
    {
        while(Load>>temp)
        {
            if(temp == "MapX")
            {
                Load>>x;
                m_width = x;
            }
            if(temp == "MapY")
            {
                Load>>y;
                m_height = y;

            }
            if(temp == "Layer")
            {
                Load>>layer;
            }
            if(temp == "Tile")
            {
                Load>>m_count;
            }
            if(temp == "X")
            {
                Load>>x_coord;
            }
            if(temp == "Y")
            {
                Load>>y_coord;
            }
            if(temp == "Strip_x")
            {
                Load>>strip_x;
            }
            if(temp == "Strip_y")
            {
                Load>>strip_y;
            }
            if(temp == "Flag")
            {
                Load>>flag;
            }
            if(temp == "H")
            {
                Load>>h;
            }
            if(temp == "W")
            {
                Load>>w;
            }
            if(temp == "END")
            {
                m_tile[layer][x_coord / w][y_coord / h].x = x_coord;
                m_tile[layer][x_coord / w][y_coord / h].y = y_coord;
                m_tile[layer][x_coord / w][y_coord / h].s_x = strip_x;
                m_tile[layer][x_coord / w][y_coord / h].s_y = strip_y;
                m_tile[layer][x_coord / w][y_coord / h].h = h;
                m_tile[layer][x_coord / w][y_coord / h].w = w;
                if(strip_x >= 64)
                {
                    m_tile[layer][x_coord / w][y_coord / h].flag = 1;
                }
                else
                    m_tile[layer][x_coord / w][y_coord / h].flag = 0;
            }
        }
    }

    if(img != "")
    {
        m_dir = img;
        SetUp();
    }
    else
    {
        m_dir = "tiles.png";
        SetUp();
    }
}

void Level::SetUp()
{
    for(int l = 0; l < 3; l++)
    {
        for(int x = 0; x < m_width; x++)
        {
            for(int y = 0; y < m_height; y++)
            {
                m_tile[l][x][y].image.SetImage(cell::ImageManager::GetInst()->GetImage(m_dir));
                m_tile[l][x][y].image.SetSubRect(sf::IntRect(m_tile[l][x][y].s_x,
                                                             m_tile[l][x][y].s_y,
                                                             m_tile[l][x][y].s_x+m_tile[l][x][y].w,
                                                             m_tile[l][x][y].s_y+m_tile[l][x][y].h));
                m_tile[l][x][y].image.SetPosition((float)m_tile[l][x][y].x,
                                                  (float)m_tile[l][x][y].y);
            }
        }
    }
}


void Level::Render(sf::RenderWindow& window)//, EntityManager* mgr)
{
    for(int l = 0; l < 3; l++)
    {
        for(int x = 0; x < m_width; x++)
        {
            for(int y = 0; y < m_height; y++)
            {
                if(window.GetView().GetRect().Contains(x*32, y*32));
                window.Draw(m_tile[l][x][y].image);
            }
        }
    }
}
