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
            float text_padding_x;
            float text_padding_y;
            bool is_finished;
            bool page_is_finished;
            float page_finished_at;
            bool at_last_page;

         public:
            BasicRenderer(AllegroFlare::FontBin* font_bin=nullptr, float width=1.0f, float height=1.0f, std::string current_page_text="[unset-current_page_text]", int num_revealed_characters=999, float text_padding_x=55.0f, float text_padding_y=45.0f, bool is_finished=false, bool page_is_finished=false, float page_finished_at=0.0f, bool at_last_page=false);
            ~BasicRenderer();

            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_width(float width);
            void set_height(float height);
            void set_current_page_text(std::string current_page_text);
            void set_num_revealed_characters(int num_revealed_characters);
            void set_text_padding_x(float text_padding_x);
            void set_text_padding_y(float text_padding_y);
            void set_is_finished(bool is_finished);
            void set_page_is_finished(bool page_is_finished);
            void set_page_finished_at(float page_finished_at);
            void set_at_last_page(bool at_last_page);
            AllegroFlare::FontBin* get_font_bin();
            float get_width();
            float get_height();
            std::string get_current_page_text();
            int get_num_revealed_characters();
            float get_text_padding_x();
            float get_text_padding_y();
            bool get_is_finished();
            bool get_page_is_finished();
            float get_page_finished_at();
            bool get_at_last_page();
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



