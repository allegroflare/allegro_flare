#pragma once


#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <AllegroFlare/SoftwareKeyboard/KeyboardKey.hpp>
#include <AllegroFlare/SoftwareKeyboard/SoftwareKeyboard.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <cstddef>
#include <functional>
#include <lib/tsl/ordered_map.h>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace SoftwareKeyboard
   {
      class SoftwareKeyboard
      {
      public:
         static constexpr const char* DEFAULT_EVENT_TO_EMIT_ON_PRESSING_SUBMIT_KEY = (char*)"submit_software_keyboard";
         static constexpr const char* DEFAULT_BONK_SOUND_EFFECT_IDENTIFIER = (char*)"ui-input-bonk-01.ogg";
         static constexpr const char* DEFAULT_KEY_CLICK_SOUND_EFFECT_IDENTIFIER = (char*)"menu-click-01.ogg";
         static constexpr const char* DEFAULT_ERASE_SOUND_EFFECT_IDENTIFIER = (char*)"delete-item-01.ogg";
         static constexpr const char* DEFAULT_FONT_NAME = (char*)"Inter-Regular.ttf";
         static constexpr float DEFAULT_CURSOR_REPOSITION_MULTIPLIER = 0.6f;

      private:
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::FontBin* font_bin;
         std::string font_name;
         int font_size;
         tsl::ordered_map<std::string, AllegroFlare::SoftwareKeyboard::KeyboardKey> keys;
         int cursor_pos;
         AllegroFlare::Vec2D cursor_destination;
         AllegroFlare::Vec2D cursor_size_destination;
         float cursor_reposition_multiplier;
         bool show_rectangle_outline_on_keys;
         AllegroFlare::Placement2D keyboard_placement;
         std::string prompt_text;
         std::string result_string;
         std::size_t num_permitted_chars;
         std::string event_to_emit_on_pressing_submit_key;
         std::function<void(AllegroFlare::SoftwareKeyboard::SoftwareKeyboard*, void*)> on_submit_callback_func;
         void* on_submit_callback_func_user_data;
         AllegroFlare::Vec2D cursor_location;
         AllegroFlare::Vec2D cursor_size;
         bool showing_input_error_frame;
         std::vector<std::string> input_error_frame_error_messages;
         std::string bonk_sound_effect_identifier;
         std::string key_click_sound_effect_identifier;
         std::string erase_sound_effect_identifier;
         bool initialized;
         void validate_and_submit_form();
         void update_cursor_destination();
         std::string infer_current_key_name();
         void draw_result_string_and_boxes();
         ALLEGRO_COLOR build_cursor_color();
         ALLEGRO_COLOR build_input_error_frame_color();
         void draw_cursor_rectangle(float x=0.0f, float y=0.0f, float w=0.0f, float h=0.0f);
         void draw_cursor_underline(float x=0.0f, float y=0.0f, float w=0.0f, float h=0.0f);
         void draw_input_error_frame(float x=0.0f, float y=0.0f, float w=0.0f, float h=0.0f);
         void draw_cursor();
         void draw_keyboard_backfill_and_frame();
         void emit_bonk_sound_effect();
         void emit_key_click_sound_effect();
         void emit_erase_sound_effect();
         ALLEGRO_FONT* obtain_keyboard_font();
         ALLEGRO_FONT* obtain_prompt_text_font();
         ALLEGRO_FONT* obtain_result_text_font();
         ALLEGRO_FONT* obtain_error_messages_font();
         std::string join(std::vector<std::string> tokens={}, std::string delimiter=", ");

      protected:


      public:
         SoftwareKeyboard(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::FontBin* font_bin=nullptr, std::string font_name=DEFAULT_FONT_NAME, int font_size=-40);
         ~SoftwareKeyboard();

         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_font_name(std::string font_name);
         void set_font_size(int font_size);
         void set_prompt_text(std::string prompt_text);
         void set_result_string(std::string result_string);
         void set_num_permitted_chars(std::size_t num_permitted_chars);
         void set_event_to_emit_on_pressing_submit_key(std::string event_to_emit_on_pressing_submit_key);
         void set_on_submit_callback_func(std::function<void(AllegroFlare::SoftwareKeyboard::SoftwareKeyboard*, void*)> on_submit_callback_func);
         void set_on_submit_callback_func_user_data(void* on_submit_callback_func_user_data);
         void set_input_error_frame_error_messages(std::vector<std::string> input_error_frame_error_messages);
         void set_bonk_sound_effect_identifier(std::string bonk_sound_effect_identifier);
         void set_key_click_sound_effect_identifier(std::string key_click_sound_effect_identifier);
         void set_erase_sound_effect_identifier(std::string erase_sound_effect_identifier);
         AllegroFlare::EventEmitter* get_event_emitter() const;
         AllegroFlare::FontBin* get_font_bin() const;
         std::string get_font_name() const;
         int get_font_size() const;
         float get_cursor_reposition_multiplier() const;
         std::string get_prompt_text() const;
         std::string get_result_string() const;
         std::size_t get_num_permitted_chars() const;
         std::string get_event_to_emit_on_pressing_submit_key() const;
         std::function<void(AllegroFlare::SoftwareKeyboard::SoftwareKeyboard*, void*)> get_on_submit_callback_func() const;
         void* get_on_submit_callback_func_user_data() const;
         bool get_showing_input_error_frame() const;
         std::vector<std::string> get_input_error_frame_error_messages() const;
         std::string get_bonk_sound_effect_identifier() const;
         std::string get_key_click_sound_effect_identifier() const;
         std::string get_erase_sound_effect_identifier() const;
         bool get_initialized() const;
         tsl::ordered_map<std::string, AllegroFlare::SoftwareKeyboard::KeyboardKey> &get_keys_ref();
         void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
         void reset();
         void set_cursor_reposition_multiplier(float cursor_reposition_multiplier=DEFAULT_CURSOR_REPOSITION_MULTIPLIER);
         void set_keys(tsl::ordered_map<std::string, AllegroFlare::SoftwareKeyboard::KeyboardKey> keys={});
         void set_keyboard_dimensions(float width=1, float height=1);
         void set_keyboard_position(float x=0, float y=0);
         void initialize();
         void press_key_under_cursor();
         void press_key_by_name(std::string name="[unset-name]");
         void show_input_error_frame(std::vector<std::string> input_error_frame_error_messages={});
         void clear_input_error_frame();
         void clear_input_error_frame_error_messages();
         bool has_input_error_frame_error_messages();
         void jump_cursor_pos_to_index_of_key_name(std::string name="[unset-name]");
         void increment_cursor_pos();
         void decrement_cursor_pos();
         void render();
         bool key_exists(std::string identifier="[unset-identifier]");
         static AllegroFlare::Vec2D calculate_boilerplate_keyboard_dimensions();
         void move_cursor_down();
         void move_cursor_up();
         static tsl::ordered_map<std::string, AllegroFlare::SoftwareKeyboard::KeyboardKey> build_boilerplate_keyboard_keys();
         static float calculate_spaced_elements_width(int num_elements=0, float element_width=0.0f, float element_spacing=0.0f);
      };
   }
}



