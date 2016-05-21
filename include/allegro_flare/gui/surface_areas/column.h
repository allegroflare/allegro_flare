#ifndef __UI_COLLISION_COLUMN_HEADER
#define __UI_COLLISION_COLUMN_HEADER




#include <allegro_flare/gui/surface_area.h>




class UISurfaceAreaColumn : public UISurfaceArea
{
public:
   UISurfaceAreaColumn(float x, float w);

   void draw_bounding_area();
   bool collides(float x, float y);
};




#endif
