#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Screens/TitleScreen.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <cstddef>
#include <cstdint>
#include <functional>
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
         enum State
         {
            STATE_UNDEF = 0,
            STATE_REVEALING,
            STATE_AWAITING_USER_INPUT,
            STATE_MENU_OPTION_IS_CHOSEN,
            STATE_FINISHED,
         };
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::BitmapBin* bitmap_bin;
         std::size_t surface_width;
         std::size_t surface_height;
         std::string title_text;
         std::string copyright_text;
         std::string title_bitmap_name;
         std::string title_font_name;
         std::string menu_font_name;
         std::string copyright_font_name;
         ALLEGRO_COLOR title_text_color;
         ALLEGRO_COLOR menu_text_color;
         ALLEGRO_COLOR menu_selector_color;
         ALLEGRO_COLOR menu_selector_outline_color;
         ALLEGRO_COLOR menu_selected_text_color;
         ALLEGRO_COLOR copyright_text_color;
         float menu_selector_outline_stroke_thickness;
         int title_font_size;
         int menu_font_size;
         int copyright_font_size;
         std::vector<std::pair<std::string, std::string>> menu_options;
         std::function<void(AllegroFlare::Screens::TitleScreen*, void*)> on_menu_choice_callback_func;
         void* on_menu_choice_callback_func_user_data;
         std::function<void(AllegroFlare::Screens::TitleScreen*, void*)> on_finished_callback_func;
         void* on_finished_callback_func_user_data;
         float title_position_x;
         float title_position_y;
         float menu_position_x;
         float menu_position_y;
         int cursor_position;
         std::string menu_move_sound_effect_identifier;
         bool menu_move_sound_effect_enabled;
         std::string menu_select_option_sound_effect_identifier;
         bool menu_select_option_sound_effect_enabled;
         float menu_option_selection_to_activation_delay;
         float reveal_duration;
         float reveal_started_at;
         bool showing_menu;
         bool showing_copyright;
         uint32_t state;
         bool state_is_busy;
         float state_changed_at;
         bool menu_option_chosen;
         float menu_option_chosen_at;
         bool menu_option_activated;
         void move_cursor_up();
         void move_cursor_down();
         void select_menu_option();
         ALLEGRO_FONT* obtain_title_font();
         ALLEGRO_FONT* obtain_menu_font();
         ALLEGRO_FONT* obtain_copyright_font();
         ALLEGRO_BITMAP* obtain_title_bitmap();
         bool menu_is_empty();
         bool menu_has_items();

      protected:


      public:
         TitleScreen(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, std::size_t surface_width=1920, std::size_t surface_height=1080, std::string title_text="Untitled Game", std::string copyright_text="© Copyright 2024", std::string title_bitmap_name="", std::string title_font_name="Inter-Regular.ttf", std::string menu_font_name="Inter-Regular.ttf", std::string copyright_font_name="Inter-Regular.ttf", ALLEGRO_COLOR title_text_color=ALLEGRO_COLOR{1, 1, 1, 1}, ALLEGRO_COLOR menu_text_color=ALLEGRO_COLOR{1, 1, 1, 1}, ALLEGRO_COLOR menu_selector_color=ALLEGRO_COLOR{1, 1, 1, 1}, ALLEGRO_COLOR menu_selector_outline_color=ALLEGRO_COLOR{0, 0, 0, 0}, ALLEGRO_COLOR menu_selected_text_color=ALLEGRO_COLOR{0, 0, 0, 1}, ALLEGRO_COLOR copyright_text_color=ALLEGRO_COLOR{0.4f, 0.42f, 0.48f, 0.6f}, float menu_selector_outline_stroke_thickness=2.0f, int title_font_size=-80, int menu_font_size=-38, int copyright_font_size=-28);
         virtual ~TitleScreen();

         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
         void set_surface_width(std::size_t surface_width);
         void set_surface_height(std::size_t surface_height);
         void set_title_text(std::string title_text);
         void set_copyright_text(std::string copyright_text);
         void set_title_bitmap_name(std::string title_bitmap_name);
         void set_title_font_name(std::string title_font_name);
         void set_menu_font_name(std::string menu_font_name);
         void set_copyright_font_name(std::string copyright_font_name);
         void set_title_text_color(ALLEGRO_COLOR title_text_color);
         void set_menu_text_color(ALLEGRO_COLOR menu_text_color);
         void set_menu_selector_color(ALLEGRO_COLOR menu_selector_color);
         void set_menu_selector_outline_color(ALLEGRO_COLOR menu_selector_outline_color);
         void set_menu_selected_text_color(ALLEGRO_COLOR menu_selected_text_color);
         void set_copyright_text_color(ALLEGRO_COLOR copyright_text_color);
         void set_menu_selector_outline_stroke_thickness(float menu_selector_outline_stroke_thickness);
         void set_title_font_size(int title_font_size);
         void set_menu_font_size(int menu_font_size);
         void set_copyright_font_size(int copyright_font_size);
         void set_on_menu_choice_callback_func(std::function<void(AllegroFlare::Screens::TitleScreen*, void*)> on_menu_choice_callback_func);
         void set_on_menu_choice_callback_func_user_data(void* on_menu_choice_callback_func_user_data);
         void set_on_finished_callback_func(std::function<void(AllegroFlare::Screens::TitleScreen*, void*)> on_finished_callback_func);
         void set_on_finished_callback_func_user_data(void* on_finished_callback_func_user_data);
         void set_title_position_x(float title_position_x);
         void set_title_position_y(float title_position_y);
         void set_menu_position_x(float menu_position_x);
         void set_menu_position_y(float menu_position_y);
         void set_menu_move_sound_effect_identifier(std::string menu_move_sound_effect_identifier);
         void set_menu_move_sound_effect_enabled(bool menu_move_sound_effect_enabled);
         void set_menu_select_option_sound_effect_identifier(std::string menu_select_option_sound_effect_identifier);
         void set_menu_select_option_sound_effect_enabled(bool menu_select_option_sound_effect_enabled);
         void set_menu_option_selection_to_activation_delay(float menu_option_selection_to_activation_delay);
         void set_reveal_duration(float reveal_duration);
         std::size_t get_surface_width() const;
         std::size_t get_surface_height() const;
         std::string get_title_text() const;
         std::string get_copyright_text() const;
         std::string get_title_bitmap_name() const;
         std::string get_title_font_name() const;
         std::string get_menu_font_name() const;
         std::string get_copyright_font_name() const;
         ALLEGRO_COLOR get_title_text_color() const;
         ALLEGRO_COLOR get_menu_text_color() const;
         ALLEGRO_COLOR get_menu_selector_color() const;
         ALLEGRO_COLOR get_menu_selector_outline_color() const;
         ALLEGRO_COLOR get_menu_selected_text_color() const;
         ALLEGRO_COLOR get_copyright_text_color() const;
         float get_menu_selector_outline_stroke_thickness() const;
         int get_title_font_size() const;
         int get_menu_font_size() const;
         int get_copyright_font_size() const;
         std::vector<std::pair<std::string, std::string>> get_menu_options() const;
         std::function<void(AllegroFlare::Screens::TitleScreen*, void*)> get_on_menu_choice_callback_func() const;
         void* get_on_menu_choice_callback_func_user_data() const;
         std::function<void(AllegroFlare::Screens::TitleScreen*, void*)> get_on_finished_callback_func() const;
         void* get_on_finished_callback_func_user_data() const;
         float get_title_position_x() const;
         float get_title_position_y() const;
         float get_menu_position_x() const;
         float get_menu_position_y() const;
         int get_cursor_position() const;
         std::string get_menu_move_sound_effect_identifier() const;
         bool get_menu_move_sound_effect_enabled() const;
         std::string get_menu_select_option_sound_effect_identifier() const;
         bool get_menu_select_option_sound_effect_enabled() const;
         float get_menu_option_selection_to_activation_delay() const;
         float get_reveal_duration() const;
         void TODO();
         void set_font_name(std::string font_name="[unset-font_name]");
         void set_state(uint32_t state=STATE_UNDEF, bool override_if_busy=false);
         void update(float time_now=al_get_time());
         static bool is_valid_state(uint32_t state=STATE_UNDEF);
         float infer_age(float time_of_event=0, float time_now=al_get_time());
         float infer_reveal_age(float time_now=al_get_time());
         float infer_reveal_age_n(float time_now=al_get_time());
         void show_menu();
         virtual void on_activate() override;
         void skip_to_title();
         void set_menu_options(std::vector<std::pair<std::string, std::string>> menu_options={});
         virtual void activate_current_selected_menu_option();
         bool processing_user_input();
         bool is_state(uint32_t possible_state=STATE_UNDEF);
         virtual void primary_timer_func() override;
         void render();
         void draw_title();
         void draw_copyright_text();
         static void draw_cursor_box(float x=0.0f, float y=0.0f, float width=1.0f, float height=1.0f, ALLEGRO_COLOR fill_color=ALLEGRO_COLOR{1, 1, 1, 1}, ALLEGRO_COLOR outline_color=ALLEGRO_COLOR{1, 1, 1, 1}, float outline_stroke_thickness=1.0f, bool menu_option_chosen=false, float menu_option_chosen_at=0.0f, float menu_option_selection_to_activation_delay=1.0f, float time_now=al_get_time());
         void draw_menu();
         std::string infer_current_menu_option_value();
         std::string infer_current_menu_option_label();
         void play_menu_move_sound_effect();
         void play_menu_select_option_sound_effect();
         virtual void joy_button_down_func(ALLEGRO_EVENT* ev=nullptr) override;
         virtual void joy_axis_func(ALLEGRO_EVENT* ev=nullptr) override;
         virtual void virtual_control_button_down_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
         static std::vector<std::pair<std::string, std::string>> build_default_menu_options();
      };
   }
}



