#include "AI.h"
#include "Trig.h"

void ExportAI(AI* a)
{
    cell::LuaManager *manager = cell::LuaManager::GetInst();
    luabind::module(manager->GetState())
    [
        luabind::class_<AI>("AI")
        .def("SetMaxRange", &AI::SetMaxRange)
        .def("GetMaxRange", &AI::GetMaxRange)
        .def("InRange",     &AI::InRange)
        .def("InView",      &AI::InView) // functions to export to lua
    ];
    manager->SetGlobal("ai", a);
}

AI *AI::m_instance = NULL;
AI *AI::GetInst()
{
    if(!m_instance)
    {
        m_instance = new AI;
    }
    return m_instance;
}

AI::AI()
{
    m_range = 100;
}

AI::~AI()
{
    if(m_instance)
        delete m_instance;
}
// too much code... too little time!
/// @todo factor in distance to the in view algorithem :/
bool AI::InView(float x1, float y1, float x2, float y2, float facingAngle)
{
    if(InRange(x1, y1, x2, y2))
    {
        const sf::Vector2f x(x1, y1);
        const sf::Vector2f y(x2, y2);
        float angle = cell::VectorMath::GetAngle(x, y);
        return facingAngle <= angle +20 && facingAngle <= angle-20; // too little time and too
        // lazy to factor in distance so this will work just not perfect... be my guest to make it
        // perfect :)
    }
    return false;
}

bool AI::InRange(int x1, int y1, int x2, int y2)
{
    if(x1 > x2)
    {
        if(y1 > y2)
        {
            return x2 >= x1 - m_range && y2 >= y1 - m_range;

        }
        else
        {
            return x2 >= x1 - m_range && y1 >= y2 - m_range;
        }
    }
    else
    {
        if(y1 > y2)
        {
            return x1 >= x2 - m_range && y2 >= y1 - m_range;
        }
        else
        {
            return x1 >= x2 - m_range && y1 >= y2 - m_range;
        }
    }
}
