#ifndef FGUI_COLLISION_ROW_HEADER
#define FGUI_COLLISION_ROW_HEADER




#include <allegro_flare/gui/surface_area.h>




class FGUISurfaceAreaRow : public FGUISurfaceArea
{
public:
   FGUISurfaceAreaRow(float y, float h);

   void draw_bounding_area();
   bool collides(float x, float y);
};





#endif
