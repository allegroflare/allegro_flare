#pragma once



#include <iostream>
#include <vector>

#include <allegro5/allegro.h>
#include <AllegroFlare/Vec2D.hpp>



namespace AllegroFlare
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

      int width;
      int height;
      ALLEGRO_BITMAP *surface;
      ALLEGRO_BITMAP *light_bitmap;
      std::vector<AllegroFlare::Vec2D> points;
      bool initialized;

      void update_surface();

   public:
      ShadowMask(int width=1, int height=1, ALLEGRO_BITMAP *light_bitmap=nullptr);
      ~ShadowMask();

      void initialize();
      void add_point(float x, float y);
      void clear_points();
      void draw();
   };
}




