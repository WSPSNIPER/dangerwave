#include"headers.hpp"
#include"button.hpp"

Button::Button(int s_x, int s_y, int s_h, int s_w,
               sf::Color,sf::Font font, int size, string text)
{
    x = s_x;
    y = s_y;
    h = s_h;
    w = s_w;

    name = text;
    Size = size;

    Rect = sf::Shape::Rectangle(x,y,x + w,y + h,sf::Color(255,0,0),0.f,sf::Color(255,0,0));

    Text_font = font;


}

void Button::Draw(sf::RenderWindow &Window)
{
    Text.SetFont(Text_font);

    Text.SetSize(Size);

    Text.SetText(name);

    Text.SetX(x + 1.f);

    Text.SetY(y + 1.f);

    Window.Draw(Rect);
    Window.Draw(Text);
}
