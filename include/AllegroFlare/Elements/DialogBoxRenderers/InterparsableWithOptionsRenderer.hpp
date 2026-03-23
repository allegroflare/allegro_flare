#pragma once


#include <AllegroFlare/Elements/DialogBoxes/InterparsableWithOptions.hpp>
#include <AllegroFlare/Elements/ListBoxRenderer.hpp>
#include <AllegroFlare/Elements/SelectionCursorBox.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <string>
#include <tuple>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace DialogBoxRenderers
      {
         class InterparsableWithOptionsRenderer
         {
         public:
            static constexpr char* DEFAULT_FONT_NAME = (char*)"Inter-Regular.ttf";
            static constexpr int DEFAULT_FONT_SIZE = -36;
            static constexpr ALLEGRO_COLOR DEFAULT_BORDER_COLOR = ALLEGRO_COLOR{1, 1, 1, 1};
            static constexpr ALLEGRO_COLOR DEFAULT_BACKGROUND_COLOR = ALLEGRO_COLOR{0, 0, 0, 1};
            static constexpr ALLEGRO_COLOR DEFAULT_TEXT_COLOR = ALLEGRO_COLOR{1, 1, 1, 1};
            static constexpr ALLEGRO_COLOR DEFAULT_LABEL_COLOR = ALLEGRO_COLOR{0, 0, 0, 1};

         private:
            AllegroFlare::FontBin* font_bin;
            AllegroFlare::Elements::DialogBoxes::InterparsableWithOptions* choice_dialog_box;
            AllegroFlare::Elements::SelectionCursorBox* selection_cursor_box;
            float width;
            float height;
            std::string font_name;
            int font_size;
            ALLEGRO_COLOR border_color;
            ALLEGRO_COLOR text_color;
            ALLEGRO_COLOR background_color;
            ALLEGRO_COLOR label_color;
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
            bool hide_name_tag_if_empty;
            void render_frame(float opacity=1.0f);
            void render_text();
            void render_speaking_character_name_tag();
            void render_next_or_finished_button(float opacity=1.0f);
            void draw_special_state_empty_text(float width=1, float height=1);
            std::vector<std::string> obtain_choice_dialog_box_option_labels();
            int xxx__obtain_choice_dialog_box_cursor_position();
            int obtain_choice_dialog_box_cursor_position();
            ALLEGRO_FONT* obtain_dialog_font();

         protected:


         public:
            InterparsableWithOptionsRenderer(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::Elements::DialogBoxes::InterparsableWithOptions* choice_dialog_box=nullptr, AllegroFlare::Elements::SelectionCursorBox* selection_cursor_box=nullptr, float width=(1920/2.0f), float height=(1080/5.0f), std::string font_name=DEFAULT_FONT_NAME, int font_size=DEFAULT_FONT_SIZE, float text_padding_x=52.0f, float text_padding_y=40.0f, int num_revealed_characters=999, bool is_finished=false, bool page_is_finished=false, float page_finished_at=0.0f, bool at_last_page=false, float age=999.0f, bool showing_speaking_character_name=false, std::string speaking_character_name="");
            ~InterparsableWithOptionsRenderer();

            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_choice_dialog_box(AllegroFlare::Elements::DialogBoxes::InterparsableWithOptions* choice_dialog_box);
            void set_selection_cursor_box(AllegroFlare::Elements::SelectionCursorBox* selection_cursor_box);
            void set_width(float width);
            void set_height(float height);
            void set_font_name(std::string font_name);
            void set_font_size(int font_size);
            void set_border_color(ALLEGRO_COLOR border_color);
            void set_text_color(ALLEGRO_COLOR text_color);
            void set_background_color(ALLEGRO_COLOR background_color);
            void set_label_color(ALLEGRO_COLOR label_color);
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
            void set_hide_name_tag_if_empty(bool hide_name_tag_if_empty);
            AllegroFlare::FontBin* get_font_bin() const;
            AllegroFlare::Elements::DialogBoxes::InterparsableWithOptions* get_choice_dialog_box() const;
            AllegroFlare::Elements::SelectionCursorBox* get_selection_cursor_box() const;
            float get_width() const;
            float get_height() const;
            std::string get_font_name() const;
            int get_font_size() const;
            ALLEGRO_COLOR get_border_color() const;
            ALLEGRO_COLOR get_text_color() const;
            ALLEGRO_COLOR get_background_color() const;
            ALLEGRO_COLOR get_label_color() const;
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
            bool get_hide_name_tag_if_empty() const;
            void draw_rudimentary_triangle(float x=0.0f, float y=0.0f, float w=16.0f, float h=16.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, float opacity=1.0f);
            void render();
            static void helper__set_selection_cursor_box_dimensions_to(AllegroFlare::Elements::SelectionCursorBox* selection_cursor_box=nullptr, std::tuple<float, float, float, float> dimensions={});
            float get_left_indent();
            AllegroFlare::Elements::ListBoxRenderer build_list_box_renderer();
            void draw_choices_with_cursor_and_current_selection();
            void xx__draw_choices_with_cursor_and_current_selection();
            void draw_speaking_character_name();
         };
      }
   }
}



