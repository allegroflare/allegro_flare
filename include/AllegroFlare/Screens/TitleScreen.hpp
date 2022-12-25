#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace Screens
   {
      class TitleScreen : public AllegroFlare::Screens::Base
      {
      private:
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::BitmapBin* bitmap_bin;
         std::string title_text;
         std::string copyright_text;
         std::string background_bitmap_name;
         std::string title_bitmap_name;
         std::string font_name;
         ALLEGRO_COLOR title_text_color;
         ALLEGRO_COLOR menu_text_color;
         ALLEGRO_COLOR menu_selector_color;
         ALLEGRO_COLOR menu_selected_text_color;
         ALLEGRO_COLOR copyright_text_color;
         int title_font_size;
         int menu_font_size;
         int copyright_font_size;
         std::vector<std::pair<std::string, std::string>> menu_options;
         float menu_position_x;
         float menu_position_y;
         int cursor_position;
         std::string menu_move_sound_effect_identifier;
         bool menu_move_sound_effect_enabled;
         std::string menu_select_option_sound_effect_identifier;
         bool menu_select_option_sound_effect_enabled;
         bool menu_option_activated;
         bool menu_option_chosen;
         float menu_option_chosen_at;
         float menu_option_selection_activation_delay;
         void move_cursor_up();
         void move_cursor_down();
         void select_menu_option();
         std::string infer_current_menu_option_value();
         std::string infer_current_menu_option_label();
         ALLEGRO_FONT* obtain_title_font();
         ALLEGRO_FONT* obtain_menu_font();
         ALLEGRO_FONT* obtain_copyright_font();
         ALLEGRO_BITMAP* obtain_background_bitmap();
         ALLEGRO_BITMAP* obtain_title_bitmap();
         bool menu_is_empty();
         bool menu_has_items();

      protected:


      public:
         TitleScreen(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, std::string title_text="Untitled Game", std::string copyright_text="Copyright 2022", std::string background_bitmap_name="", std::string title_bitmap_name="", std::string font_name="Inter-Medium.ttf", ALLEGRO_COLOR title_text_color=ALLEGRO_COLOR{1, 1, 1, 1}, ALLEGRO_COLOR menu_text_color=ALLEGRO_COLOR{1, 1, 1, 1}, ALLEGRO_COLOR menu_selector_color=ALLEGRO_COLOR{1, 1, 1, 1}, ALLEGRO_COLOR menu_selected_text_color=ALLEGRO_COLOR{0, 0, 0, 1}, ALLEGRO_COLOR copyright_text_color=ALLEGRO_COLOR{1, 1, 1, 1}, int title_font_size=-90, int menu_font_size=-48, int copyright_font_size=-32);
         virtual ~TitleScreen();

         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
         void set_title_text(std::string title_text);
         void set_copyright_text(std::string copyright_text);
         void set_background_bitmap_name(std::string background_bitmap_name);
         void set_title_bitmap_name(std::string title_bitmap_name);
         void set_font_name(std::string font_name);
         void set_title_text_color(ALLEGRO_COLOR title_text_color);
         void set_menu_text_color(ALLEGRO_COLOR menu_text_color);
         void set_menu_selector_color(ALLEGRO_COLOR menu_selector_color);
         void set_menu_selected_text_color(ALLEGRO_COLOR menu_selected_text_color);
         void set_copyright_text_color(ALLEGRO_COLOR copyright_text_color);
         void set_title_font_size(int title_font_size);
         void set_menu_font_size(int menu_font_size);
         void set_copyright_font_size(int copyright_font_size);
         void set_menu_position_x(float menu_position_x);
         void set_menu_position_y(float menu_position_y);
         void set_menu_move_sound_effect_identifier(std::string menu_move_sound_effect_identifier);
         void set_menu_move_sound_effect_enabled(bool menu_move_sound_effect_enabled);
         void set_menu_select_option_sound_effect_identifier(std::string menu_select_option_sound_effect_identifier);
         void set_menu_select_option_sound_effect_enabled(bool menu_select_option_sound_effect_enabled);
         std::string get_title_text() const;
         std::string get_copyright_text() const;
         std::string get_background_bitmap_name() const;
         std::string get_title_bitmap_name() const;
         std::string get_font_name() const;
         ALLEGRO_COLOR get_title_text_color() const;
         ALLEGRO_COLOR get_menu_text_color() const;
         ALLEGRO_COLOR get_menu_selector_color() const;
         ALLEGRO_COLOR get_menu_selected_text_color() const;
         ALLEGRO_COLOR get_copyright_text_color() const;
         int get_title_font_size() const;
         int get_menu_font_size() const;
         int get_copyright_font_size() const;
         std::vector<std::pair<std::string, std::string>> get_menu_options() const;
         float get_menu_position_x() const;
         float get_menu_position_y() const;
         int get_cursor_position() const;
         std::string get_menu_move_sound_effect_identifier() const;
         bool get_menu_move_sound_effect_enabled() const;
         std::string get_menu_select_option_sound_effect_identifier() const;
         bool get_menu_select_option_sound_effect_enabled() const;
         virtual void on_activate() override;
         void set_menu_options(std::vector<std::pair<std::string, std::string>> menu_options={});
         virtual void activate_menu_option(std::string menu_option_name="[unset-menu-option-name]");
         virtual void primary_timer_func() override;
         void render();
         void draw_background();
         void draw_title();
         void draw_copyright_text();
         void draw_menu();
         void play_menu_move_sound_effect();
         void play_menu_select_option_sound_effect();
         virtual void virtual_control_button_down_func(int player_num=0, int button_num=0, bool is_repeat=false) override;
         static std::vector<std::pair<std::string, std::string>> build_default_menu_options();
      };
   }
}



