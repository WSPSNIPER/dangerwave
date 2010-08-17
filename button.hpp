
class Button
{
public:

    Button(int s_x, int s_y, int s_h, int s_w, sf::Color,sf::Font font, int size, string text);

    float x,y,h,w, Size;
    string name;
    sf::Shape Rect;
    sf::Color Text_Color;
    sf::Font Text_font;
    sf::String Text;

    void Draw(sf::RenderWindow &Window);
};
