#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace DialogBoxRenderers
      {
         class BasicRenderer
         {
         private:
            AllegroFlare::FontBin* font_bin;
            float width;
            float height;
            std::string current_page_text;
            int num_revealed_characters;
            bool is_finished;

         public:
            BasicRenderer(AllegroFlare::FontBin* font_bin=nullptr, float width=1.0f, float height=1.0f, std::string current_page_text="[unset-current_page_text]", int num_revealed_characters=999, bool is_finished=false);
            ~BasicRenderer();

            void render();
            void draw_special_state_empty_text(float width=1, float height=1);
            void draw_action_text(std::string text="[unset-action-text]", float width=1, float height=1);
            void draw_styled_revealed_text(float max_width=1, std::string text="[unset-text]", int num_revealed_characters=999);
            std::string concat_text(std::string source_text="", int length=0);
            ALLEGRO_FONT* obtain_dialog_font();
         };
      }
   }
}



