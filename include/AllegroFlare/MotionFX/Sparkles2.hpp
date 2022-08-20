#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Timeline/ActorManager.hpp>
#include <allegro5/allegro_font.h>
#include <string>
#include <vector>


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
         float time;

      public:
         Sparkles2(AllegroFlare::BitmapBin* bitmap_bin=nullptr, float x=0.0f, float y=0.0f, float time=0.0);
         ~Sparkles2();

         void set_x(float x);
         void set_y(float y);
         void set_time(float time);
         float get_x();
         float get_y();
         float get_time();
         void initialize();
         std::vector<std::string> build_friend_star_script_lines(float rotation=0.0f);
         void render();
         ALLEGRO_BITMAP* obtain_star_bitmap();
      };
   }
}



