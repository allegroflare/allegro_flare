#ifndef FGUI_COLLISION_AREA_HEADER
#define FGUI_COLLISION_AREA_HEADER




#include <allegro_flare/placement2d.h>




class FGUISurfaceArea
{
public:
   placement2d placement;
   FGUISurfaceArea(float x, float y, float w, float h);
   virtual ~FGUISurfaceArea();

   virtual void draw_bounding_area() = 0;
   virtual bool collides(float x, float y) = 0;
};





#endif
