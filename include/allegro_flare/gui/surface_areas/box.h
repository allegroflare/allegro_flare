#ifndef __UI_COLLISION_BOX_HEADER
#define __UI_COLLISION_BOX_HEADER




#include <allegro_flare/gui/surface_areas/surface_area_base.h>




class UISurfaceAreaBox : public UISurfaceAreaBase
{
public:
   UISurfaceAreaBox(float x, float y, float w, float h);
   ~UISurfaceAreaBox();

   void draw_bounding_area();
   bool collides(float x, float y);
};




#endif
