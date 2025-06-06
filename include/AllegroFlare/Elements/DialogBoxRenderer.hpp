#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/DialogBoxStyles.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>
#include <AllegroFlare/Elements/SelectionCursorBox.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      class DialogBoxRenderer
      {
      public:
         static constexpr float DEFAULT_STANDARD_DIALOG_BOX_X = 1920/2.0f;
         static constexpr float DEFAULT_STANDARD_DIALOG_BOX_Y = 1080/8.0f*6;
         static constexpr float DEFAULT_STANDARD_DIALOG_BOX_WIDTH = 1920/2.0f;
         static constexpr float DEFAULT_STANDARD_DIALOG_BOX_HEIGHT = 1080/5.0f;
         static constexpr ALLEGRO_COLOR DEFAULT_STANDARD_DIALOG_BOX_FRAME_COLOR = ALLEGRO_COLOR{1, 1, 1, 1};
         static constexpr ALLEGRO_COLOR DEFAULT_STANDARD_DIALOG_BOX_BACKGROUND_COLOR = ALLEGRO_COLOR{0, 0, 0, 1};
         static constexpr ALLEGRO_COLOR DEFAULT_STANDARD_DIALOG_BOX_TEXT_COLOR = ALLEGRO_COLOR{1, 1, 1, 1};
         static constexpr ALLEGRO_COLOR DEFAULT_STANDARD_DIALOG_BOX_LABEL_COLOR = ALLEGRO_COLOR{0, 0, 0, 1};

      private:
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::Elements::DialogBoxes::Base* dialog_box;
         AllegroFlare::Elements::SelectionCursorBox* selection_cursor_box;
         std::string standard_dialog_box_font_name;
         int standard_dialog_box_font_size;
         float standard_dialog_box_x;
         float standard_dialog_box_y;
         float standard_dialog_box_width;
         float standard_dialog_box_height;
         ALLEGRO_COLOR standard_dialog_box_frame_color;
         ALLEGRO_COLOR standard_dialog_box_text_color;
         ALLEGRO_COLOR standard_dialog_box_background_color;
         ALLEGRO_COLOR standard_dialog_box_label_color;

      protected:


      public:
         DialogBoxRenderer(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::Elements::DialogBoxes::Base* dialog_box=nullptr, AllegroFlare::Elements::SelectionCursorBox* selection_cursor_box=nullptr, std::string standard_dialog_box_font_name=AllegroFlare::Elements::DialogBoxStyles::DEFAULT_FONT_NAME, int standard_dialog_box_font_size=AllegroFlare::Elements::DialogBoxStyles::DEFAULT_FONT_SIZE);
         ~DialogBoxRenderer();

         void set_standard_dialog_box_font_name(std::string standard_dialog_box_font_name);
         void set_standard_dialog_box_font_size(int standard_dialog_box_font_size);
         void set_standard_dialog_box_x(float standard_dialog_box_x);
         void set_standard_dialog_box_y(float standard_dialog_box_y);
         void set_standard_dialog_box_width(float standard_dialog_box_width);
         void set_standard_dialog_box_height(float standard_dialog_box_height);
         void set_standard_dialog_box_frame_color(ALLEGRO_COLOR standard_dialog_box_frame_color);
         void set_standard_dialog_box_text_color(ALLEGRO_COLOR standard_dialog_box_text_color);
         void set_standard_dialog_box_background_color(ALLEGRO_COLOR standard_dialog_box_background_color);
         void set_standard_dialog_box_label_color(ALLEGRO_COLOR standard_dialog_box_label_color);
         std::string get_standard_dialog_box_font_name() const;
         int get_standard_dialog_box_font_size() const;
         float get_standard_dialog_box_x() const;
         float get_standard_dialog_box_y() const;
         float get_standard_dialog_box_width() const;
         float get_standard_dialog_box_height() const;
         ALLEGRO_COLOR get_standard_dialog_box_frame_color() const;
         ALLEGRO_COLOR get_standard_dialog_box_text_color() const;
         ALLEGRO_COLOR get_standard_dialog_box_background_color() const;
         ALLEGRO_COLOR get_standard_dialog_box_label_color() const;
         void deps(int _ignore=AllegroFlare::Elements::DialogBoxStyles::DEFAULT_FONT_SIZE);
         void render();
      };
   }
}



