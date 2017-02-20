#pragma once




#include <allegro_flare/gui/surface_areas/surface_area_base.h>




class UISurfaceAreaNeverCollide : public UISurfaceAreaBase
{
public:
   UISurfaceAreaNeverCollide(float x, float y, float w, float h);
   ~UISurfaceAreaNeverCollide();

   void draw_bounding_area();
   bool collides(float x, float y);
};




