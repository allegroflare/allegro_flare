#pragma once


#include <AllegroFlare/Camera2D.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Timer.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace MindDive
      {
         namespace Hud
         {
            class Hud
            {
            private:
               AllegroFlare::FontBin* font_bin;
               AllegroFlare::Timer* timer;
               std::string slate_text;
               ALLEGRO_BITMAP* backbuffer_sub_bitmap;
               bool initialized;
               AllegroFlare::Camera2D camera;
               void render_stopwatch();
               void render_slate();
               ALLEGRO_FONT* obtain_font();

            protected:


            public:
               Hud(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::Timer* timer=nullptr, std::string slate_text="-- WIN --");
               ~Hud();

               void set_font_bin(AllegroFlare::FontBin* font_bin);
               void set_timer(AllegroFlare::Timer* timer);
               AllegroFlare::FontBin* get_font_bin() const;
               AllegroFlare::Timer* get_timer() const;
               void initialize();
               void render();
            };
         }
      }
   }
}



