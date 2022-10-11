#pragma once


#include <AllegroFlare/Elements/Backgrounds/Base.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <cstdint>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace Backgrounds
      {
         class IconPattern : public AllegroFlare::Elements::Backgrounds::Base
         {
         private:
            AllegroFlare::FontBin* font_bin;
            ALLEGRO_COLOR background_color;
            uint32_t icon_a;
            uint32_t icon_b;
            std::string font_awesome_font_name;
            float time;

         protected:


         public:
            IconPattern(AllegroFlare::FontBin* font_bin=nullptr);
            virtual ~IconPattern();

            void set_background_color(ALLEGRO_COLOR background_color);
            ALLEGRO_COLOR get_background_color() const;
            virtual void update() override;
            virtual void render() override;
            void draw_unicode_character(ALLEGRO_FONT* font=nullptr, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, int32_t icon=61444, int flags=0, float x=0.0f, float y=0.0f);
            ALLEGRO_FONT* obtain_font_awesome_font();
         };
      }
   }
}



