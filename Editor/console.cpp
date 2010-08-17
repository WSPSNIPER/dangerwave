#include"headers.hpp"
#include"console.hpp"

void Console::set_text(string text)
{
    Text.SetText(text);
}

void Console::clear()
{
    //set_text("");
    //cout<<" buffer :"<<buffer<<"."<<endl;
    //cout<<" final :"<<entered<<"."<<endl;
    buffer.clear();
}

void Console::set_entering(bool enter)
{
    entering = enter;
}

bool Console::is_entering()
{
    return entering;
}

string Console::get_text()
{
    return entered;
}

void Console::delete_letter()
{
    buffer.erase(buffer.length(), 1);
}

char Console::get_typed(sf::Event &event)
{
    return (char)event.Text.Unicode;
}

void Console::add_letter(char text)
{
    buffer.insert(buffer.end(),text);
}

void Console::update(sf::Event &event)
{
    if(entering)
    {
        entered = buffer;
        Text.SetText(buffer);
        if(event.Type == sf::Event::KeyReleased)
        {
            if(event.Key.Code == sf::Key::Delete || event.Key.Code == sf::Key::Back)
            {
                delete_letter();
            }
            else if(event.Key.Code == sf::Key::Return)
            {
                entering = false;
            }
            else if(event.Key.Code == sf::Key::Escape)
            {
                //clear();
                entering = false;
            }
        }
        if(event.Type == sf::Event::TextEntered && event.Key.Code != sf::Key::Back && event.Key.Code != sf::Key::Delete)
        {
            add_letter(get_typed(event));
        }

        else if(event.Type == sf::Event::Closed)
        {
            entering = false;
        }
    }
}

void Console::Draw(sf::RenderWindow &Window)
{
    if(entering)
    {
        Text.SetText(entered);
        Window.Draw(Rect);
        Window.Draw(Text);
    }

}

sf::String Console::GetText()
{
    return Text;
}

Console::Console(int text_size,int o_x, int o_y, int o_h, int o_w, sf::Font &o_font)
{
    x = o_x;
    y = o_y;
    h = o_h;
    w = o_w;

    Text_font = o_font;
    Text.SetSize(text_size);
    Text.SetFont(Text_font);
    Text.SetPosition(x,y);
    Text.SetColor(sf::Color(0,0,0,255));
    entering = false;
    Rect = sf::Shape::Rectangle(x,y,x + w,y + h,sf::Color(255,0,0),0.f,sf::Color(255,0,0));
}
