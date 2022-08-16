#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Timeline/ActorManager.hpp>
#include <allegro5/allegro_font.h>


namespace AllegroFlare
{
   namespace MotionFX
   {
      class Sparkles2
      {
      private:
         AllegroFlare::BitmapBin* bitmap_bin;
         float x;
         float y;
         AllegroFlare::Timeline::ActorManager actor_manager;
         bool initialized;

      public:
         Sparkles2(AllegroFlare::BitmapBin* bitmap_bin=nullptr, float x=0.0f, float y=0.0f);
         ~Sparkles2();

         void set_x(float x);
         void set_y(float y);
         float get_x();
         float get_y();
         void initialize();
         void update();
         void render();
         ALLEGRO_BITMAP* obtain_star_bitmap();
      };
   }
}



