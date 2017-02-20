#ifndef __UI_COLLISION_ROW_HEADER
#define __UI_COLLISION_ROW_HEADER




#include <allegro_flare/gui/surface_areas/surface_area_base.h>




class UISurfaceAreaRow : public UISurfaceAreaBase
{
public:
   UISurfaceAreaRow(float y, float h);

   void draw_bounding_area();
   bool collides(float x, float y);
};




#endif
