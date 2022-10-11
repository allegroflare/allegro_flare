#pragma once


#include <AllegroFlare/Camera2D.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Timer.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace TileDrive
      {
         namespace Hud
         {
            class Hud
            {
            private:
               AllegroFlare::FontBin* font_bin;
               AllegroFlare::Timer* timer;
               std::string slate_text;
               ALLEGRO_COLOR slate_text_color;
               ALLEGRO_BITMAP* backbuffer_sub_bitmap;
               bool initialized;
               AllegroFlare::Camera2D camera;
               void render_stopwatch();
               void render_slate();
               ALLEGRO_FONT* obtain_font();

            protected:


            public:
               Hud(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::Timer* timer=nullptr, std::string slate_text="", ALLEGRO_COLOR slate_text_color={1, 1, 1, 1});
               ~Hud();

               void set_font_bin(AllegroFlare::FontBin* font_bin);
               void set_timer(AllegroFlare::Timer* timer);
               void set_slate_text(std::string slate_text);
               void set_slate_text_color(ALLEGRO_COLOR slate_text_color);
               AllegroFlare::FontBin* get_font_bin() const;
               AllegroFlare::Timer* get_timer() const;
               std::string get_slate_text() const;
               ALLEGRO_COLOR get_slate_text_color() const;
               void show_win_slate();
               void show_die_slate();
               void show_ready_slate();
               void clear_slate();
               void initialize();
               void render();
            };
         }
      }
   }
}



