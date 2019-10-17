#ifndef __UI_COLLISION_AREA_HEADER
#define __UI_COLLISION_AREA_HEADER




#include <allegro_flare/placement2d.h>




class UISurfaceAreaBase
{
public:
   placement2d placement;
   UISurfaceAreaBase(float x, float y, float w, float h);
   virtual ~UISurfaceAreaBase();

   virtual void draw_bounding_area() = 0;
   virtual bool collides(float x, float y) = 0;
};




#endif
