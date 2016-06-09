#ifndef __UI_COLLISION_ROW_HEADER
#define __UI_COLLISION_ROW_HEADER




#include <allegro_flare/gui/surface_area.h>




class UISurfaceAreaRow : public UISurfaceArea
{
public:
   UISurfaceAreaRow(float y, float h);

   void draw_bounding_area();
   bool collides(float x, float y);
};




#endif
