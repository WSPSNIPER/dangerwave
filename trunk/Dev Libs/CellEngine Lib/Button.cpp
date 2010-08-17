#include "Button.h"

using namespace cell;

Button::Button(float x, float y, float w, float h, std::string lua_script, std::string text)
:
_ui(UIState::GetInst()),
_lua(LuaManager::GetInst()),
_rect(x,y,x+w,y+h)
{

    _textStr = text;
    _luaScript = lua_script;
    _luaUpdate = true;
    _font.LoadFromFile("system.ttf", 20);
    _text.SetFont(_font);

    _text.SetText(_textStr);
	_text.SetCenter((_text.GetRect().Left + (_text.GetRect().Right - _text.GetRect().Left)/2),
					(_text.GetRect().Top + (_text.GetRect().Bottom - _text.GetRect().Top)/2));

    _text.SetScale(0.45f,0.45f);

    SetPosition(x, y);
}


void Button::Render(sf::RenderWindow& window)
{
    window.Draw(_button);
	if(Hovering())
		window.Draw(_hoverRect);
	window.Draw(_text);
}


void Button::SetPosition(float x, float y)
{
    _rect.Left = x;
    _rect.Right = x + _rect.GetWidth();
    _rect.Top = y;
    _rect.Bottom = y + _rect.GetHeight();
    _button = sf::Shape::Rectangle(_rect.Left, _rect.Top, _rect.Right, _rect.Bottom, sf::Color(200, 200, 200));

	_hoverRect = sf::Shape::Rectangle(_rect.Left, _rect.Top, _rect.Right, _rect.Bottom, sf::Color(0,0,200,60));

	_text.SetPosition(_rect.Left + _rect.GetWidth()/2, _rect.Top + _rect.GetHeight()/2);
}


void Button::Update()
{
    if(_luaUpdate)
    {
        if(Clicked())
        {
            _lua->DoFile(_luaScript);
            _ui->itemActive = 2;
        }
    }
}

bool Button::Clicked()
{
    return (
		_ui->mouseX >= _rect.Left   &&
		_ui->mouseX <= _rect.Right  &&
		_ui->mouseY >= _rect.Top    &&
		_ui->mouseY <= _rect.Bottom &&
		_ui->mouseDown              &&
		_ui->itemActive <= 1          // only allow one click a click (lol)
			);
}

bool Button::Hovering()
{
    return (
		_ui->mouseX >= _rect.Left   &&
		_ui->mouseX <= _rect.Right  &&
		_ui->mouseY >= _rect.Top    &&
		_ui->mouseY <= _rect.Bottom
			);
}

void Button::SetText(std::string text)
{
    _text.SetText(text);
}
/// ahh all the constructors set up
