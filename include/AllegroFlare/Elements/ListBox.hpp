#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Choice.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      class ListBox
      {
      public:
         static constexpr char* DEFAULT_FONT_NAME = (char*)"Inter-Regular.ttf";
         static constexpr int DEFAULT_FONT_SIZE = -36;

      private:
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::Elements::DialogBoxes::Choice* choice_dialog_box;
         float width;
         float height;
         std::string font_name;
         int font_size;
         float text_padding_x;
         float text_padding_y;
         ALLEGRO_FONT* obtain_dialog_font();
         std::string obtain_choice_dialog_box_prompt();
         std::vector<std::pair<std::string, std::string>> obtain_choice_dialog_box_options();
         int obtain_choice_dialog_box_cursor_position();
         std::string concat_text(std::string source_text="", int length=0);

      protected:


      public:
         ListBox(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::Elements::DialogBoxes::Choice* choice_dialog_box=nullptr, float width=(1920/2.0f), float height=(1080/5.0f), std::string font_name=DEFAULT_FONT_NAME, int font_size=DEFAULT_FONT_SIZE, float text_padding_x=52.0f, float text_padding_y=40.0f);
         ~ListBox();

         void set_width(float width);
         void set_height(float height);
         void set_font_name(std::string font_name);
         void set_font_size(int font_size);
         void set_text_padding_x(float text_padding_x);
         void set_text_padding_y(float text_padding_y);
         float get_width() const;
         float get_height() const;
         std::string get_font_name() const;
         int get_font_size() const;
         float get_text_padding_x() const;
         float get_text_padding_y() const;
         void render();
         void draw_prompt_text();
         void draw_choices_with_cursor_and_current_selection(float start_y=0);
      };
   }
}



