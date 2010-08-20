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
    if(img != "" && img != m_dir)
    {
        m_dir = img;
        SetUp();
    }

    ifstream Load(file.c_str());
    std::string temp = "";
    int x, y, layer, x_coord, y_coord, strip_x, strip_y, w, h;
    if(Load.is_open())
    {
        while(Load>>temp)
        {
            if(temp == "MapX")
            {
                Load>>x;
            }
            if(temp == "MapY")
            {
                Load>>y;
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
                m_tile[layer][x_coord / w][y_coord / h].image.SetSubRect(sf::IntRect(strip_x, strip_y, strip_x+w, strip_y+h));
                m_height = y_coord / h;
                m_width = x_coord / w;
            }
        }
    }
}

void Level::SetUp()
{
    for(size_t l = 0; l < 3; l++)
    {
        for(size_t x = 0; x < m_width; x++)
        {
            for(size_t y = 0; y < m_height; y++)
            {
                m_tile[l][x][y].image.SetImage(cell::ImageManager::GetInst()->GetImage(m_dir));
            }
        }
    }
}


void Level::Render(sf::RenderWindow& window)
{
    for(size_t l = 0; l < 3; l++)
    {
        for(size_t x = 0; x < m_width; x++)
        {
            for(size_t y = 0; y < m_height; y++)
            {
                window.Draw(m_tile[l][x][y].image);
            }
        }
    }
}
