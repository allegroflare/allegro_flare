#pragma once


#include <AllegroFlare/Elements/Base.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Timer.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      class Stopwatch : public AllegroFlare::Elements::Base
      {
      public:
         static constexpr char* DEFAULT_FONT_IDENTIFIER = (char*)"Inter-Regular.ttf";
         static constexpr int DEFAULT_FONT_SIZE = -74;

      private:
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::Timer* timer;
         std::string font_identifier;
         int font_size;
         ALLEGRO_COLOR color;
         std::string build_ellapsed_time_str();
         ALLEGRO_FONT* obtain_font();

      protected:


      public:
         Stopwatch(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::Timer* timer=nullptr, std::string font_identifier=DEFAULT_FONT_IDENTIFIER, int font_size=DEFAULT_FONT_SIZE, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
         ~Stopwatch();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_timer(AllegroFlare::Timer* timer);
         void set_font_identifier(std::string font_identifier);
         void set_font_size(int font_size);
         void set_color(ALLEGRO_COLOR color);
         AllegroFlare::FontBin* get_font_bin() const;
         AllegroFlare::Timer* get_timer() const;
         std::string get_font_identifier() const;
         int get_font_size() const;
         ALLEGRO_COLOR get_color() const;
         void fit_placement_width_and_height_to_stopwatch();
         void render();
      };
   }
}



