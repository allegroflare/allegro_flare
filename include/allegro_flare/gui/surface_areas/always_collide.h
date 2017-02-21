#pragma once




#include <allegro_flare/gui/surface_areas/surface_area_base.h>




class UISurfaceAreaAlwaysCollide : public UISurfaceAreaBase
{
public:
   UISurfaceAreaAlwaysCollide(float x, float y, float w, float h);
   ~UISurfaceAreaAlwaysCollide();

   void draw_bounding_area();
   bool collides(float x, float y);
};




