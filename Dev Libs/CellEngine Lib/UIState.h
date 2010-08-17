#ifndef _UI_STATE_H__
#define _UI_STATE_H__

#include "LuaManager.h"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
namespace cell
{
    class  UIState
    {
        private:
            UIState();
            static UIState* _instance;

        public:
            ~UIState();
            static UIState* GetInst();

            void Update(sf::Event &event);

            int mouseX, mouseY;
            bool mouseDown;
            int itemHot, itemActive;

    };
}


#endif
