#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Choice.hpp>
#include <AllegroFlare/Elements/ListBoxRenderer.hpp>
#include <AllegroFlare/Elements/SelectionCursorBox.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <string>
#include <tuple>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace DialogBoxRenderers
      {
         class ChoiceRenderer
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
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::Elements::DialogBoxes::Choice* choice_dialog_box;
            AllegroFlare::Elements::SelectionCursorBox* selection_cursor_box;
            float width;
            float height;
            std::string font_name;
            int font_size;
            float text_padding_x;
            float text_padding_y;
            ALLEGRO_COLOR border_color;
            ALLEGRO_COLOR text_color;
            ALLEGRO_COLOR background_color;
            ALLEGRO_COLOR label_color;
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
            void draw_special_state_empty_text(float width=1, float height=1);
            std::string concat_text(std::string source_text="", int length=0);
            std::string obtain_choice_dialog_box_prompt();
            std::vector<std::pair<std::string, std::string>> obtain_choice_dialog_box_options();
            std::vector<std::string> obtain_choice_dialog_box_option_labels();
            int obtain_choice_dialog_box_cursor_position();
            ALLEGRO_FONT* obtain_dialog_font();

         protected:


         public:
            ChoiceRenderer(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::Elements::DialogBoxes::Choice* choice_dialog_box=nullptr, AllegroFlare::Elements::SelectionCursorBox* selection_cursor_box=nullptr, float width=(1920/2.0f), float height=(1080/5.0f), std::string font_name=DEFAULT_FONT_NAME, int font_size=DEFAULT_FONT_SIZE, float text_padding_x=52.0f, float text_padding_y=40.0f, int num_revealed_characters=999, bool is_finished=false, bool page_is_finished=false, float page_finished_at=0.0f, bool at_last_page=false, float age=999.0f, bool showing_speaking_character_name=false, std::string speaking_character_name="");
            ~ChoiceRenderer();

            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void set_choice_dialog_box(AllegroFlare::Elements::DialogBoxes::Choice* choice_dialog_box);
            void set_selection_cursor_box(AllegroFlare::Elements::SelectionCursorBox* selection_cursor_box);
            void set_width(float width);
            void set_height(float height);
            void set_font_name(std::string font_name);
            void set_font_size(int font_size);
            void set_text_padding_x(float text_padding_x);
            void set_text_padding_y(float text_padding_y);
            void set_border_color(ALLEGRO_COLOR border_color);
            void set_text_color(ALLEGRO_COLOR text_color);
            void set_background_color(ALLEGRO_COLOR background_color);
            void set_label_color(ALLEGRO_COLOR label_color);
            void set_num_revealed_characters(int num_revealed_characters);
            void set_is_finished(bool is_finished);
            void set_page_is_finished(bool page_is_finished);
            void set_page_finished_at(float page_finished_at);
            void set_at_last_page(bool at_last_page);
            void set_age(float age);
            void set_showing_speaking_character_name(bool showing_speaking_character_name);
            void set_speaking_character_name(std::string speaking_character_name);
            AllegroFlare::FontBin* get_font_bin() const;
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            AllegroFlare::Elements::DialogBoxes::Choice* get_choice_dialog_box() const;
            AllegroFlare::Elements::SelectionCursorBox* get_selection_cursor_box() const;
            float get_width() const;
            float get_height() const;
            std::string get_font_name() const;
            int get_font_size() const;
            float get_text_padding_x() const;
            float get_text_padding_y() const;
            ALLEGRO_COLOR get_border_color() const;
            ALLEGRO_COLOR get_text_color() const;
            ALLEGRO_COLOR get_background_color() const;
            ALLEGRO_COLOR get_label_color() const;
            int get_num_revealed_characters() const;
            bool get_is_finished() const;
            bool get_page_is_finished() const;
            float get_page_finished_at() const;
            bool get_at_last_page() const;
            float get_age() const;
            bool get_showing_speaking_character_name() const;
            std::string get_speaking_character_name() const;
            void render_speaking_character_name_tag();
            void render();
            std::tuple<float, float, float, float> calculate_dimensions_of_current_selection();
            static void helper__reposition_selection_cursor_box_dimensions_to(AllegroFlare::Elements::SelectionCursorBox* selection_cursor_box=nullptr, std::tuple<float, float, float, float> dimensions={});
            static void helper__set_selection_cursor_box_dimensions_to(AllegroFlare::Elements::SelectionCursorBox* selection_cursor_box=nullptr, std::tuple<float, float, float, float> dimensions={});
            float get_left_indent();
            AllegroFlare::Elements::ListBoxRenderer build_list_box_renderer();
            void draw_choices_with_cursor_and_current_selection();
            void draw_styled_revealed_text(float max_width=1, std::string text="[unset-text]", int num_revealed_characters=999);
         };
      }
   }
}



