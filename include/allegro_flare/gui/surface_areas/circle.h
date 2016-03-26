#ifndef FGUI_COLLISION_CIRCLE_HEADER
#define FGUI_COLLISION_CIRCLE_HEADER




#include <allegro_flare/gui/surface_area.h>




class FGUISurfaceAreaCircle : public FGUISurfaceArea
{
public:
   FGUISurfaceAreaCircle(float x, float y, float r);

   void draw_bounding_area();
   bool collides(float x, float y);
};




#endif
