#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace DialogBoxRenderers
      {
         class InterparsableRenderer
         {
         public:
            static constexpr char* DEFAULT_FONT_NAME = (char*)"Inter-Regular.ttf";
            static constexpr int DEFAULT_FONT_SIZE = -36;

         private:
            AllegroFlare::FontBin* font_bin;
            std::string current_page_text_with_formatting;
            float width;
            float height;
            std::string font_name;
            int font_size;
            float text_padding_x;
            float text_padding_y;
            int num_revealed_characters;
            bool is_finished;
            bool page_is_finished;
            float page_finished_at;
            bool at_last_page;
            float age;
            bool showing_speaking_character_name;
            std::string speaking_character_name;
            void render_frame();
            void render_text();
            void render_speaking_character_name_tag();
            void render_button();
            void draw_special_state_empty_text(float width=1, float height=1);
            std::string concat_text(std::string source_text="", int length=0);
            std::vector<std::string> obtain_choice_dialog_box_option_labels();
            int obtain_choice_dialog_box_cursor_position();
            ALLEGRO_FONT* obtain_dialog_font();

         protected:


         public:
            InterparsableRenderer(AllegroFlare::FontBin* font_bin=nullptr, std::string current_page_text_with_formatting="[unset-current_page_text_with_formatting]", float width=(1920/2.0f), float height=(1080/5.0f), std::string font_name=DEFAULT_FONT_NAME, int font_size=DEFAULT_FONT_SIZE, float text_padding_x=52.0f, float text_padding_y=40.0f, int num_revealed_characters=999, bool is_finished=false, bool page_is_finished=false, float page_finished_at=0.0f, bool at_last_page=false, float age=999.0f, bool showing_speaking_character_name=false, std::string speaking_character_name="");
            ~InterparsableRenderer();

            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_current_page_text_with_formatting(std::string current_page_text_with_formatting);
            void set_width(float width);
            void set_height(float height);
            void set_font_name(std::string font_name);
            void set_font_size(int font_size);
            void set_text_padding_x(float text_padding_x);
            void set_text_padding_y(float text_padding_y);
            void set_num_revealed_characters(int num_revealed_characters);
            void set_is_finished(bool is_finished);
            void set_page_is_finished(bool page_is_finished);
            void set_page_finished_at(float page_finished_at);
            void set_at_last_page(bool at_last_page);
            void set_age(float age);
            void set_showing_speaking_character_name(bool showing_speaking_character_name);
            void set_speaking_character_name(std::string speaking_character_name);
            AllegroFlare::FontBin* get_font_bin() const;
            std::string get_current_page_text_with_formatting() const;
            float get_width() const;
            float get_height() const;
            std::string get_font_name() const;
            int get_font_size() const;
            float get_text_padding_x() const;
            float get_text_padding_y() const;
            int get_num_revealed_characters() const;
            bool get_is_finished() const;
            bool get_page_is_finished() const;
            float get_page_finished_at() const;
            bool get_at_last_page() const;
            float get_age() const;
            bool get_showing_speaking_character_name() const;
            std::string get_speaking_character_name() const;
            void render();
            void draw_choices_with_cursor_and_current_selection();
            void draw_speaking_character_name();
            std::vector<std::string> split_to_words(std::string text="[unset-text]");
            void draw_styled_revealed_text_with_formatting(float max_width=1, std::string text_with_formatting="[unset-text_with_formatting]", int num_revealed_characters=999);
         };
      }
   }
}



