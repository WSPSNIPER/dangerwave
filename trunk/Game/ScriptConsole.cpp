#include "ScriptConsole.h"
#include <iostream>
using namespace cell;

ScriptConsole *ScriptConsole::_instance = NULL;
ScriptConsole *ScriptConsole::GetInst()
{
    if(!_instance)
    {
        _instance = new ScriptConsole();
    }
    return _instance;
}

// how could this constructor get any messer :)
ScriptConsole::ScriptConsole()
    :
    _lua(LuaManager::GetInst()),

    _string("", sf::Font::GetDefaultFont(), 20),

    _saveConversation(0, 180, 125, 20, "scripts/save_con.lua",   "save conv"),
    _quit(          290, 180, 125, 20, "scripts/quit.lua",       "quit"),
    _saveEvent(     145, 180, 125, 20, "scripts/save_event.lua", "save event"),   /// tried to make it look neater but idk if it worked

    _pop(true)
{
//_font.LoadFromFile("system.ttf");
//_string.SetFont(_font);
    _rect = sf::Shape::Rectangle(0, 0, 640, 200, sf::Color(0, 25, 250, 50));
}

// ahhhhhh im sooo tired cant think
ScriptConsole::~ScriptConsole()
{
    if(_instance)
    {
        delete _instance;
    }
}


void ScriptConsole::Update(sf::Event& event)
{
    if(_pop)
    {
        _saveConversation.Update();
        _saveEvent.Update();
        _quit.Update();
        if(event.Type == sf::Event::TextEntered)
        {
            AddChar(GetTypedChar(event));
        }
        else if(event.Type == sf::Event::KeyPressed)
        {
            if(event.Key.Code == sf::Key::Back)
            {
                BackSpace();
            }
        }
    }
}

void ScriptConsole::AddChar(char c)
{
    SetText(GetText() + c);
}

void ScriptConsole::SetText(std::string text)
{
    _string.SetText(text.c_str());
}


std::string ScriptConsole::GetText()
{
    return (std::string)_string.GetText(); // retrun a std::string of the text because the text of sfml is stupid and you cant do shit with it
}

char ScriptConsole::GetTypedChar(sf::Event &event)
{
    return (char)event.Text.Unicode;    // have to return a char of the char becuase you cant use the Unicode ( sfml's gay idea )                                            // of creating a more abstract system, it would have been easer if you returned a char sfml
}

void ScriptConsole::BackSpace()
{
    std::string s = GetText(); // yet again i need to create a string because you cant do shit with sfml string lol
    if(s.size() > 1)
    {
        s.erase(s.size()-2, s.size()-1);
        SetText(s); // set the std::string back to sfml string so it can be rendered
    }
}

void ScriptConsole::SaveEvent()
{

}

void ScriptConsole::Execute()
{
}

void ScriptConsole::Render(sf::RenderWindow &window)
{
    if(_pop)
    {
        window.Draw(_rect);
        _saveConversation.Render(window);
        _saveEvent.Render(window);
        _quit.Render(window);
        window.Draw(_string);
    }
}
/// @TODO think about making support for multiple lines
