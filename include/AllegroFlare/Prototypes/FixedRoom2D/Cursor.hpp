#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <allegro5/allegro.h>
#include <cstdint>
#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace FixedRoom2D
      {
         class Cursor
         {
         private:
            AllegroFlare::FontBin* font_bin;
            float x;
            float y;
            AllegroFlare::Placement2D icon_offset_placement;
            AllegroFlare::Placement2D info_text_offset_placement;
            std::string info_text;
            int info_text_flags;
            uint32_t icon_character_num;
            float cursor_last_set_at;
            void draw_unicode_character(ALLEGRO_FONT* font=nullptr, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, uint32_t icon=61444, int flags=0);
            ALLEGRO_FONT* obtain_cursor_font();
            ALLEGRO_FONT* obtain_info_text_font();
            void draw_cursor();
            void draw_info_text();

         protected:


         public:
            Cursor(AllegroFlare::FontBin* font_bin=nullptr);
            ~Cursor();

            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_x(float x);
            void set_y(float y);
            void set_info_text(std::string info_text);
            float get_x() const;
            float get_y() const;
            std::string get_info_text() const;
            void draw();
            void update();
            void move(float distance_x=0.0f, float distance_y=0.0f);
            bool clamp(float min_x=0.0f, float min_y=0.0f, float max_x=1920.0f, float max_y=1080.0f);
            void move_to(float x=0.0f, float y=0.0f);
            void clear_info_text();
            void set_cursor_to_pointer();
            void set_cursor_to_grab();
         };
      }
   }
}



