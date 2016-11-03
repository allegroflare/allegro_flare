#pragma once




#include <allegro_flare/gui/surface_area.h>




class UISurfaceAreaNeverCollide : public UISurfaceArea
{
public:
   UISurfaceAreaNeverCollide();
   ~UISurfaceAreaNeverCollide();

   void draw_bounding_area();
   bool collides(float x, float y);
};




