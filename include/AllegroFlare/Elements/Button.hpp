#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      class Button
      {
      public:

         enum class Alignments
         {
            CENTERED = 0,
            ALIGNED_AT_TEXT_ORIGIN,
         };
      private:
         AllegroFlare::FontBin* font_bin;
         std::string text;
         std::string text_font_name;
         int text_font_size;
         ALLEGRO_COLOR core_color;
         float started_at;
         float x;
         float y;
         float padding_x;
         float padding_y;
         AllegroFlare::Elements::Button::Alignments alignment_strategy;
         ALLEGRO_FONT* obtain_button_font();

      protected:


      public:
         Button(AllegroFlare::FontBin* font_bin=nullptr);
         ~Button();

         void set_text(std::string text);
         void set_text_font_name(std::string text_font_name);
         void set_text_font_size(int text_font_size);
         void set_core_color(ALLEGRO_COLOR core_color);
         void set_started_at(float started_at);
         void set_x(float x);
         void set_y(float y);
         void set_padding_x(float padding_x);
         void set_padding_y(float padding_y);
         void set_alignment_strategy(AllegroFlare::Elements::Button::Alignments alignment_strategy);
         AllegroFlare::FontBin* get_font_bin() const;
         std::string get_text() const;
         std::string get_text_font_name() const;
         int get_text_font_size() const;
         ALLEGRO_COLOR get_core_color() const;
         float get_started_at() const;
         float get_x() const;
         float get_y() const;
         float get_padding_x() const;
         float get_padding_y() const;
         AllegroFlare::Elements::Button::Alignments get_alignment_strategy() const;
         void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
         float infer_box_width();
         float infer_box_height();
         void align_box_at_center();
         void render();
         AllegroFlare::Placement2D build_button_placement_based_on_alignment_strategy();
         float infer_age();
      };
   }
}



