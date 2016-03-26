#ifndef FGUI_COLLISION_BOX_HEADER
#define FGUI_COLLISION_BOX_HEADER




#include <allegro_flare/gui/surface_area.h>




class FGUISurfaceAreaBox : public FGUISurfaceArea
{
public:
   FGUISurfaceAreaBox(float x, float y, float w, float h);
   ~FGUISurfaceAreaBox();

   void draw_bounding_area();
   bool collides(float x, float y);
};




#endif
