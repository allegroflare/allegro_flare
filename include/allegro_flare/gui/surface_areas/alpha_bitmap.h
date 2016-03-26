#ifndef FGUI_COLLISION_BITMAP_HEADER
#define FGUI_COLLISION_BITMAP_HEADER




#include <allegro_flare/gui/surface_area.h>




class FGUISurfaceAreaBitmap : public FGUISurfaceArea
{
private:
   ALLEGRO_BITMAP *bitmap;
public:
   FGUISurfaceAreaBitmap(float x, float y, ALLEGRO_BITMAP *bitmap);

   void draw_bounding_area();
   bool collides(float x, float y);
};




#endif
