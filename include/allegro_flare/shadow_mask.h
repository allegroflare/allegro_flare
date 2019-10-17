#ifndef __ALLEGRO_FLARE_SHADOW_MASK_HEADER
#define __ALLEGRO_FLARE_SHADOW_MASK_HEADER




#include <iostream>
#include <vector>

#include <allegro5/allegro.h>




namespace allegro_flare
{
   class ShadowMask
   {
   private:
      class point2d
      {
      public:
         float x;
         float y;
         point2d(float x, float y);
      };

      ALLEGRO_BITMAP *surface;
      ALLEGRO_BITMAP *light_bitmap;
      std::vector<point2d> points;

      void update_surface();

   public:
      ShadowMask(int width, int height, ALLEGRO_BITMAP *light_bitmap);
      ~ShadowMask();

      // Adds a light point to the mask.
      void add_point(float x, float y);

      // Removes all the light points from the mask.
      void clear_points();

      // Draws the mask to the screen.
      void draw();
   };
}




#endif
