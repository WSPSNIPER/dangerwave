class Tileset
{
    Tile **tile;

    int x_amount, y_amount, h, w;

    sf::Sprite sprite;

public:
    Tileset(int x_num, int y_num, int W, int H, sf::Sprite &Temp);
    ~Tileset();

    void Create();
};
