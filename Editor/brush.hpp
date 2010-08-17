
class Brush
{
public:
    int Tile, Set, Mode;

    sf::Image Tile_set;
    sf::Sprite tile;
    Brush()
    {
        Tile = 0;
    }

    void Draw_Selected(sf::RenderWindow &Window);
};
