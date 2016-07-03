#ifndef __UI_COLLISION_BITMAP_ALPHA_HEADER
#define __UI_COLLISION_BITMAP_ALPHA_HEADER




#include <allegro_flare/gui/surface_area.h>




class UISurfaceAreaBitmapAlpha : public UISurfaceArea
{
private:
   ALLEGRO_BITMAP *bitmap;

public:
   UISurfaceAreaBitmapAlpha(float x, float y, ALLEGRO_BITMAP *bitmap);

   void draw_bounding_area();
   bool collides(float x, float y);
};




#endif
