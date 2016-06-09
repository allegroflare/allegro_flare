#ifndef __UI_COLLISION_AREA_HEADER
#define __UI_COLLISION_AREA_HEADER




#include <allegro_flare/placement2d.h>




class UISurfaceArea
{
public:
   placement2d placement;
   UISurfaceArea(float x, float y, float w, float h);
   virtual ~UISurfaceArea();

   virtual void draw_bounding_area() = 0;
   virtual bool collides(float x, float y) = 0;
};




#endif
