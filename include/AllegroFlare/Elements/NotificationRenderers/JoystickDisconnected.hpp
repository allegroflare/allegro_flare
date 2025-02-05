#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <cstdint>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace NotificationRenderers
      {
         class JoystickDisconnected
         {
         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;
            float x;
            float y;
            float width;
            float height;
            float created_at;
            std::string name;
            void draw_achievement_box(std::string title="[unset-title]", std::string description="[unset-description]");
            ALLEGRO_FONT* obtain_item_title_font();
            ALLEGRO_FONT* obtain_item_description_font();
            ALLEGRO_FONT* obtain_icon_font();
            void draw_unicode_character(ALLEGRO_FONT* font=nullptr, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, int x=0, int y=0, uint32_t icon=61444, int flags=0);

         protected:


         public:
            JoystickDisconnected(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, float x=0.0f, float y=0.0f, float width=560.0f, float height=130.0f, float created_at=0.0f, std::string name="[unset-name]");
            ~JoystickDisconnected();

            void set_x(float x);
            void set_y(float y);
            void set_width(float width);
            void set_height(float height);
            void set_created_at(float created_at);
            void set_name(std::string name);
            float get_x() const;
            float get_y() const;
            float get_width() const;
            float get_height() const;
            float get_created_at() const;
            std::string get_name() const;
            void render();
         };
      }
   }
}



