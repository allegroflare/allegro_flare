#pragma once




#include <allegro_flare/gui/surface_area.h>




class UISurfaceAreaNeverCollide : public UISurfaceArea
{
public:
   UISurfaceAreaNeverCollide(float x, float y, float w, float h);
   ~UISurfaceAreaNeverCollide();

   void draw_bounding_area();
   bool collides(float x, float y);
};




