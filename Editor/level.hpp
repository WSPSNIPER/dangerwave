#include <string>
class Tile
{
public:

    Tile():
        w(32),  h(32),
        s_x(0), s_y(0),
        x(0),   y(0),
        flag(0),effect(0),
        rendered(false)
    {

    }


    //picture or sprite instance;

    // mouldes to load sprite;

    int w,h; //sets the size of the tile;
    int s_x,s_y; // finds the coords on the sprite sheet.
    int x, y; //tile's coordinates

    int flag;// int for flags such as solid or not
    int effect; // flag for effects suchs as translucent

    bool rendered;

    string tilesheet; //used to get the sprite sheet of the current tile.
};

class Config
{
public:
    Config(string file);
    int x,y;
    string File;
};

class Level
{
    sf::Sprite draw;

public:
    int ofs_x, ofs_y, x, y, z;

    int x_coord, y_coord, layer, strip_x, strip_y, hieght, width, tile_count, h, w;

    void Draw(sf::Image &image,sf::RenderWindow &Window);

    void Load_Map(std::string load); //loads

    void Save_Map(std::string save, int H, int W); //saves

    void Create_Tiles(int X, int Y, int Z); //creates tiles. basically an empty plane

    void Clear_Tiles();

    void SetFlag(int f);

    bool edited;

    string LuaScript;

    ~Level();

    Tile tile[3][100][100]; // "..." [:(]
};
