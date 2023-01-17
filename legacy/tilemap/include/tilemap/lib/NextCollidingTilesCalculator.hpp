#pragma once


#include <framework/vec2i.hpp>
#include <vector>


class NextCollidingTilesCalculator
{
public:
   enum axis_t
   {
      X_AXIS,
      Y_AXIS,
   };

private:
   axis_t axis;
   float element_x;
   float element_y;
   float element_w;
   float element_h;
   float element_velocity_x;
   float element_velocity_y;

public:
   NextCollidingTilesCalculator(NextCollidingTilesCalculator::axis_t axis, float element_x, float element_y, float element_w, float element_h, float element_velocity_x, float element_velocity_y);
   ~NextCollidingTilesCalculator();

   std::vector<vec2i> next_colliding_tiles();
};


