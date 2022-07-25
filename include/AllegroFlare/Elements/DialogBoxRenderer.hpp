#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      class DialogBoxRenderer
      {
      private:
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::Elements::DialogBoxes::Base* dialog_box;

      public:
         DialogBoxRenderer(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::Elements::DialogBoxes::Base* dialog_box=nullptr);
         ~DialogBoxRenderer();

         void render();
         void draw_special_state_empty_text(float width=1, float height=1);
         void draw_action_text(std::string text="[unset-action-text]", float width=1, float height=1);
         void draw_styled_revealed_text(float max_width=1);
         std::string obtain_dialog_box_text();
         int obtain_dialog_box_num_revealed_characters();
         std::string concat_text(std::string source_text="", int length=0);
         ALLEGRO_FONT* obtain_dialog_font();
      };
   }
}



