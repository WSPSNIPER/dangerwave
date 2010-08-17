#ifndef _BUTTON_H
#define _BUTTON_H

#include "UIState.h"

namespace cell
{

    class  Button
    {
        public:
            Button( float x, float y, float w, float h, std::string lua_script = "", std::string text = "" );
            virtual ~Button() {}

            void SetPosition(float x, float y);
            void Render(sf::RenderWindow& window);
            void Update();

            void LetLuaUpdate(bool let) { _luaUpdate = let; }

            void Lock()     { _locked = true;   }
            void UnLock()   { _locked = false;  }

            inline bool Clicked();
            inline bool Hovering();
            inline bool Locked()    { return _locked; }

            void SetText(std::string text);
            float GetX() const { return _rect.Left;         }
            float GetY() const { return _rect.Top;          }
            float GetH() const { return _rect.GetHeight();  }
            float GetW() const { return _rect.GetWidth();   }

        private:
            sf::Font        _font;
            sf::Shape       _button;
            sf::Shape       _hoverRect;
            std::string     _textStr;
            std::string     _luaScript;
            sf::String      _text;
            bool            _locked;
            bool            _luaUpdate;
            sf::FloatRect   _rect;
            UIState*        _ui;
            LuaManager*     _lua;
    };
}
#endif
