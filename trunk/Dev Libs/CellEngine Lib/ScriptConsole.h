#ifndef _SCRIPT_CONSOLE_H_
#define _SCRIPT_CONSOLE_H_

#include "LuaManager.h"
#include "CellGui.h"
#include <fstream>

#include "SFML/System.hpp"


// this class is a singleton that allows the user to write and save scripts (parts of)  in game

// if i feel creative add multiple lines with a vector of lines


namespace cell
{
    class ScriptConsole
    {
        private:
            ScriptConsole();
            static ScriptConsole *_instance;
        public:
            static ScriptConsole *GetInst();
            ~ScriptConsole();

            void Render(sf::RenderWindow& window);

            std::string GetText();
            char GetTypedChar(sf::Event &event);

            void AddChar(char c);
            void BackSpace();

            void SetText(std::string text);

            void PopOn(){ _pop = true; }   // pushes it on to the screen ( too lazy to work on them yet )
            void PopOff(){_pop = false;}  // pops the box off the screen

            void SaveEvent();

            bool IsPopped() { return _pop;}

            void Execute();

            void Update(sf::Event& event);

        private:
        // i know what you are thinking, why the ( _ ) before the var
        // well because i like all the private members to be at the bottom of the list in auto code completion
        // plus i like to know when somthing is a member and i usto use ( m_ )
        // i dont know but i like it now :)
            LuaManager*     _lua;
            sf::String      _string;


            cell::Button     _saveConversation;
            cell::Button     _quit;
            cell::Button     _saveEvent;

            bool            _pop;

            sf::Font        _font;
            sf::Shape       _rect; // a transparent rect that will be to script box

    };

}


#endif // _SCRIPT_CONSOLE_H_
