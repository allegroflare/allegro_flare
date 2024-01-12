#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace UI
      {
         class SliderToggle
         {
         private:
            AllegroFlare::FontBin* font_bin;
            float x;
            float y;
            float width;
            float height;
            bool onoff;
            int font_size;
            std::string on_text;
            std::string off_text;
            ALLEGRO_FONT* obtain_font(float _font_size=-34);

         protected:


         public:
            SliderToggle(AllegroFlare::FontBin* font_bin=nullptr, float x=0.0f, float y=0.0f, float width=220.0f, float height=60.0f, bool onoff=true, int font_size=-34);
            ~SliderToggle();

            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_x(float x);
            void set_y(float y);
            void set_width(float width);
            void set_height(float height);
            void set_onoff(bool onoff);
            void set_font_size(int font_size);
            void set_on_text(std::string on_text);
            void set_off_text(std::string off_text);
            AllegroFlare::FontBin* get_font_bin() const;
            float get_x() const;
            float get_y() const;
            float get_width() const;
            float get_height() const;
            bool get_onoff() const;
            int get_font_size() const;
            std::string get_on_text() const;
            std::string get_off_text() const;
            void render();
            void draw_pill(std::string text="[unset-text]", float x=1920/2, float y=1080/3, float w=140, float h=60, ALLEGRO_COLOR box_color=ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0}, ALLEGRO_COLOR text_color=ALLEGRO_COLOR{0.0, 0.0, 0.0, 1.0}, float _font_size=-34);
         };
      }
   }
}



