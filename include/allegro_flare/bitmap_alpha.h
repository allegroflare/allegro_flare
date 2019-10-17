#pragma once




#include <allegro_flare/surface_area_base.h>




class UISurfaceAreaBitmapAlpha : public UISurfaceAreaBase
{
private:
   ALLEGRO_BITMAP *bitmap;
   float alpha_threshold;

public:
   UISurfaceAreaBitmapAlpha(float x, float y, ALLEGRO_BITMAP *bitmap);

   void draw_bounding_area();
   bool collides(float x, float y);
   void set_alpha_threshold(float threshold=0.001);
   float get_alpha_threshold();
   ALLEGRO_BITMAP *get_surface_area_bitmap();
};




#endif
