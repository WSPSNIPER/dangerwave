
#ifndef _SLOPE_H_
#define _SLOPE_H_
#include "Entity.h"

class Slope

{

   public:



   float Rise(float y1,float y2);



   float Run(float x1,float x2);



   sf::Vector2f RiseOverRun(sf::Vector2f First, sf::Vector2f Second);

};

typedef Slope _Slope;

#endif
