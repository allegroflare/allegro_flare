#pragma once




#include <allegro_flare/gui/surface_area.h>




class UISurfaceAreaAlwaysCollide : public UISurfaceArea
{
public:
   UISurfaceAreaAlwaysCollide(float x, float y, float w, float h);
   ~UISurfaceAreaAlwaysCollide();

   void draw_bounding_area();
   bool collides(float x, float y);
};




