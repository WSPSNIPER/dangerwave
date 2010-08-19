#ifndef _AI_H_
#define _AI_H_

#include "Entity.h"
#include "Trig.h"
#include "LuaManager.h"
using namespace cell;
/**************************************************************************************************
* @class AI
* this is a class for lua that basically will make the AI scripting
* easier lol
***************************************************************************************************/
class AI
{
    AI();

public:
    virtual ~AI();
    static AI *GetInst();

    int GetMaxRange() const     { return m_range; }
    void SetMaxRange(int range) { m_range = range; }

    // cant use vectors cause then i would have to give them to lua :(
    bool InRange(int x1, int y1, int x2, int y2);
    bool InView(float x1, float y1, float x2, float y2, float facingAngle = 0.f);

private:
    static AI *m_instance;
    int m_range;
};

extern void ExportAI(AI*);

#endif // _AI_H_
