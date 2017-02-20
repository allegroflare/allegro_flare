#ifndef __UI_COLLISION_CIRCLE_HEADER
#define __UI_COLLISION_CIRCLE_HEADER




#include <allegro_flare/gui/surface_areas/surface_area_base.h>




class UISurfaceAreaCircle : public UISurfaceAreaBase
{
public:
   UISurfaceAreaCircle(float x, float y, float r);

   void draw_bounding_area();
   bool collides(float x, float y);
};




#endif
