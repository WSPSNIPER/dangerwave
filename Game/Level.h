#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "Player.h"
#include <string>
#include <fstream>
/**************************************************************************************************
* @class Level
* the level loads a map into the engine
***************************************************************************************************/
class Tile
{
public:
    int w,
        h,
        s_x,
        s_y,
        x,
        y;

    int flag;// int for flags such as solid or not
    int effect; // flag for effects suchs as translucent
    sf::Sprite image;
};
class Level
{
    public:
        Level(std::string file, std::string imageDir = "");
        Level();
        ~Level();

        void Load(std::string file, std::string imageDir = "");
        void Render(sf::RenderWindow& window);
        void SetUp();

    private:
        Tile m_tile[3][100][100];
        int m_count, m_width, m_height;
        std::string m_dir;

};


#endif // _LEVEL_H_
