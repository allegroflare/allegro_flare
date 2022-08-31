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
            std::string current_page_text;
            float width;
            float height;
            float text_padding_x;
            float text_padding_y;
            int num_revealed_characters;
            bool is_finished;
            bool page_is_finished;
            float page_finished_at;
            bool at_last_page;
            float age;
            void draw_special_state_empty_text(float width=1, float height=1);
            void draw_action_text(std::string text="[unset-action-text]", float width=1, float height=1);
            std::string concat_text(std::string source_text="", int length=0);
            ALLEGRO_FONT* obtain_dialog_font();

         protected:


         public:
            BasicRenderer(AllegroFlare::FontBin* font_bin=nullptr, std::string current_page_text="[unset-current_page_text]", float width=(1920/2.0f), float height=(1080/5.0f), float text_padding_x=52.0f, float text_padding_y=40.0f, int num_revealed_characters=999, bool is_finished=false, bool page_is_finished=false, float page_finished_at=0.0f, bool at_last_page=false, float age=999.0f);
            ~BasicRenderer();

            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_current_page_text(std::string current_page_text);
            void set_width(float width);
            void set_height(float height);
            void set_text_padding_x(float text_padding_x);
            void set_text_padding_y(float text_padding_y);
            void set_num_revealed_characters(int num_revealed_characters);
            void set_is_finished(bool is_finished);
            void set_page_is_finished(bool page_is_finished);
            void set_page_finished_at(float page_finished_at);
            void set_at_last_page(bool at_last_page);
            void set_age(float age);
            AllegroFlare::FontBin* get_font_bin() const;
            std::string get_current_page_text() const;
            float get_width() const;
            float get_height() const;
            float get_text_padding_x() const;
            float get_text_padding_y() const;
            int get_num_revealed_characters() const;
            bool get_is_finished() const;
            bool get_page_is_finished() const;
            float get_page_finished_at() const;
            bool get_at_last_page() const;
            float get_age() const;
            void render();
            void draw_styled_revealed_text(float max_width=1, std::string text="[unset-text]", int num_revealed_characters=999);
         };
      }
   }
}



