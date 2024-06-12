

#include <AllegroFlare/SoftwareKeyboard/SoftwareKeyboard.hpp>

#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Interpolators.hpp>
#include <AllegroFlare/UsefulPHP.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace SoftwareKeyboard
{


SoftwareKeyboard::SoftwareKeyboard(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::FontBin* font_bin, std::string font_name, int font_size)
   : event_emitter(event_emitter)
   , font_bin(font_bin)
   , font_name(font_name)
   , font_size(font_size)
   , keys({})
   , cursor_pos(0)
   , cursor_destination({})
   , cursor_size_destination(80, 80)
   , cursor_reposition_multiplier(DEFAULT_CURSOR_REPOSITION_MULTIPLIER)
   , show_rectangle_outline_on_keys(false)
   , keyboard_placement({})
   , prompt_text("Enter your name")
   , result_string({})
   , num_permitted_chars(12)
   , event_to_emit_on_pressing_submit_key(DEFAULT_EVENT_TO_EMIT_ON_PRESSING_SUBMIT_KEY)
   , on_submit_callback_func()
   , on_submit_callback_func_user_data(nullptr)
   , cursor_location({})
   , cursor_size(80, 80)
   , showing_input_error_frame(false)
   , input_error_frame_error_messages({})
   , bonk_sound_effect_identifier(DEFAULT_BONK_SOUND_EFFECT_IDENTIFIER)
   , key_click_sound_effect_identifier(DEFAULT_KEY_CLICK_SOUND_EFFECT_IDENTIFIER)
   , erase_sound_effect_identifier(DEFAULT_ERASE_SOUND_EFFECT_IDENTIFIER)
   , initialized(false)
{
}


SoftwareKeyboard::~SoftwareKeyboard()
{
}


void SoftwareKeyboard::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


void SoftwareKeyboard::set_font_name(std::string font_name)
{
   this->font_name = font_name;
}


void SoftwareKeyboard::set_font_size(int font_size)
{
   this->font_size = font_size;
}


void SoftwareKeyboard::set_prompt_text(std::string prompt_text)
{
   this->prompt_text = prompt_text;
}


void SoftwareKeyboard::set_result_string(std::string result_string)
{
   this->result_string = result_string;
}


void SoftwareKeyboard::set_num_permitted_chars(std::size_t num_permitted_chars)
{
   this->num_permitted_chars = num_permitted_chars;
}


void SoftwareKeyboard::set_event_to_emit_on_pressing_submit_key(std::string event_to_emit_on_pressing_submit_key)
{
   this->event_to_emit_on_pressing_submit_key = event_to_emit_on_pressing_submit_key;
}


void SoftwareKeyboard::set_on_submit_callback_func(std::function<void(AllegroFlare::SoftwareKeyboard::SoftwareKeyboard*, void*)> on_submit_callback_func)
{
   this->on_submit_callback_func = on_submit_callback_func;
}


void SoftwareKeyboard::set_on_submit_callback_func_user_data(void* on_submit_callback_func_user_data)
{
   this->on_submit_callback_func_user_data = on_submit_callback_func_user_data;
}


void SoftwareKeyboard::set_input_error_frame_error_messages(std::vector<std::string> input_error_frame_error_messages)
{
   this->input_error_frame_error_messages = input_error_frame_error_messages;
}


void SoftwareKeyboard::set_bonk_sound_effect_identifier(std::string bonk_sound_effect_identifier)
{
   this->bonk_sound_effect_identifier = bonk_sound_effect_identifier;
}


void SoftwareKeyboard::set_key_click_sound_effect_identifier(std::string key_click_sound_effect_identifier)
{
   this->key_click_sound_effect_identifier = key_click_sound_effect_identifier;
}


void SoftwareKeyboard::set_erase_sound_effect_identifier(std::string erase_sound_effect_identifier)
{
   this->erase_sound_effect_identifier = erase_sound_effect_identifier;
}


AllegroFlare::EventEmitter* SoftwareKeyboard::get_event_emitter() const
{
   return event_emitter;
}


AllegroFlare::FontBin* SoftwareKeyboard::get_font_bin() const
{
   return font_bin;
}


std::string SoftwareKeyboard::get_font_name() const
{
   return font_name;
}


int SoftwareKeyboard::get_font_size() const
{
   return font_size;
}


float SoftwareKeyboard::get_cursor_reposition_multiplier() const
{
   return cursor_reposition_multiplier;
}


std::string SoftwareKeyboard::get_prompt_text() const
{
   return prompt_text;
}


std::string SoftwareKeyboard::get_result_string() const
{
   return result_string;
}


std::size_t SoftwareKeyboard::get_num_permitted_chars() const
{
   return num_permitted_chars;
}


std::string SoftwareKeyboard::get_event_to_emit_on_pressing_submit_key() const
{
   return event_to_emit_on_pressing_submit_key;
}


std::function<void(AllegroFlare::SoftwareKeyboard::SoftwareKeyboard*, void*)> SoftwareKeyboard::get_on_submit_callback_func() const
{
   return on_submit_callback_func;
}


void* SoftwareKeyboard::get_on_submit_callback_func_user_data() const
{
   return on_submit_callback_func_user_data;
}


bool SoftwareKeyboard::get_showing_input_error_frame() const
{
   return showing_input_error_frame;
}


std::vector<std::string> SoftwareKeyboard::get_input_error_frame_error_messages() const
{
   return input_error_frame_error_messages;
}


std::string SoftwareKeyboard::get_bonk_sound_effect_identifier() const
{
   return bonk_sound_effect_identifier;
}


std::string SoftwareKeyboard::get_key_click_sound_effect_identifier() const
{
   return key_click_sound_effect_identifier;
}


std::string SoftwareKeyboard::get_erase_sound_effect_identifier() const
{
   return erase_sound_effect_identifier;
}


bool SoftwareKeyboard::get_initialized() const
{
   return initialized;
}


tsl::ordered_map<std::string, AllegroFlare::SoftwareKeyboard::KeyboardKey> &SoftwareKeyboard::get_keys_ref()
{
   return keys;
}


void SoftwareKeyboard::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::set_font_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::set_font_bin]: error: guard \"(!initialized)\" not met");
   }
   this->font_bin = font_bin;
   return;
}

void SoftwareKeyboard::reset()
{
   reset_with_defaults("", "");
   return;
}

void SoftwareKeyboard::reset_with_defaults(std::string initial_result_string, std::string initial_cursor_position_over_key_name)
{
   // TODO: Test this method
   cursor_destination = {0, 0};
   cursor_size_destination = {80, 80};
   cursor_location = cursor_destination;
   cursor_size = cursor_size_destination;
   showing_input_error_frame = false;
   // TODO: add showing_input_error_frame_at and set to 0.0f here
   input_error_frame_error_messages.clear();
   // TODO: add input_error_frame_error_messages_at and set to 0.0f here
   cursor_pos = 0;
   // TODO: Modify this to position the cursor instantly and silently
   // TODO: Test this
   if (!initial_cursor_position_over_key_name.empty())
   {
      jump_cursor_pos_to_index_of_key_name(initial_cursor_position_over_key_name);
      update_cursor_destination();
      cursor_location = cursor_destination;
   }
   // TODO: test this clear
   result_string = initial_result_string;
   return;
}

void SoftwareKeyboard::set_cursor_reposition_multiplier(float cursor_reposition_multiplier)
{
   if (!((cursor_reposition_multiplier > 0.1f)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::set_cursor_reposition_multiplier]: error: guard \"(cursor_reposition_multiplier > 0.1f)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::set_cursor_reposition_multiplier]: error: guard \"(cursor_reposition_multiplier > 0.1f)\" not met");
   }
   if (!((cursor_reposition_multiplier <= 1.0f)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::set_cursor_reposition_multiplier]: error: guard \"(cursor_reposition_multiplier <= 1.0f)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::set_cursor_reposition_multiplier]: error: guard \"(cursor_reposition_multiplier <= 1.0f)\" not met");
   }
   this->cursor_reposition_multiplier = cursor_reposition_multiplier;
   return;
}

void SoftwareKeyboard::set_keys(tsl::ordered_map<std::string, AllegroFlare::SoftwareKeyboard::KeyboardKey> keys)
{
   this->keys = keys;
   cursor_pos = 0;
   update_cursor_destination();
   return;
}

void SoftwareKeyboard::set_keyboard_dimensions(float width, float height)
{
   keyboard_placement.size.x = width;
   keyboard_placement.size.y = height;
   return;
}

void SoftwareKeyboard::set_keyboard_position(float x, float y)
{
   keyboard_placement.position.x = x;
   keyboard_placement.position.y = y;
   return;
}

void SoftwareKeyboard::initialize()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::initialize]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::initialize]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::initialize]: error: guard \"font_bin\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::initialize]: error: guard \"event_emitter\" not met");
   }
   keyboard_placement.position.x = 1920/2;
   keyboard_placement.position.y = 1080/2;
   initialized = true;
   return;
}

void SoftwareKeyboard::press_key_under_cursor()
{
   if (keys.empty()) return;
   int i=0;
   for (auto &key_dictionary_element : keys)
   {
      if (cursor_pos == i)
      {
         press_key_by_name(key_dictionary_element.first);
         return;
      }
      i++;
   }
   return;
   return;
}

void SoftwareKeyboard::press_key_by_name(std::string name)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::press_key_by_name]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::press_key_by_name]: error: guard \"initialized\" not met");
   }
   bool this_change_should_dismiss_the_input_error_frame = false;

   if (!key_exists(name))
   {
      // TODO: make this sound effect an option, or, output a warning
      emit_bonk_sound_effect();
      return;
   }
   AllegroFlare::SoftwareKeyboard::KeyboardKey &key = keys[name];

   std::string string_to_append = "";

   if (name == "SPACE")
   {
      if (result_string.empty())
      {
         // do nothing. E.g. do not allow starting a name with a space
         show_input_error_frame({ "cannot start with a space" });
         emit_bonk_sound_effect();
      }
      else if (result_string.back() == ' ')
      {
         // do nothing. E.g. do not allow multiple sequential spaces in a name
         show_input_error_frame({ "cannot have multiple spaces" });
         emit_bonk_sound_effect();
      }
      else
      {
         string_to_append = " ";
         this_change_should_dismiss_the_input_error_frame = true;
      }
   }
   else if (name == "BACKSPACE")
   {
      if (result_string.empty())
      {
         emit_bonk_sound_effect();
         this_change_should_dismiss_the_input_error_frame = true;
      }
      else
      {
         result_string.pop_back();
         emit_erase_sound_effect();
         this_change_should_dismiss_the_input_error_frame = true;
      }
   }
   else if (name == "SUBMIT")
   {
      // TODO: Work out logic to infer if the input error frame shoudl be dismissed or not
      //this_change_should_dismiss_the_input_error_frame = true;
      validate_and_submit_form(); // TODO: Split this into two functions
     // TODO: Emit keypress sound
   }
   else
   {
      // assume the "name" of the key is the same as the character we want to append
      this_change_should_dismiss_the_input_error_frame = true;
      string_to_append = name;
   }

   // append string, or bonk if at limit
   if (!string_to_append.empty())
   {
      if (result_string.size() >= num_permitted_chars)
      {
         emit_bonk_sound_effect();
         this_change_should_dismiss_the_input_error_frame = true;
      }
      else
      {
         // TODO: ensure concating "string_to_append" will not result in a result_string that is longer than limit
         result_string += string_to_append;
         emit_key_click_sound_effect();
         this_change_should_dismiss_the_input_error_frame = true;
      }
   }

   jump_cursor_pos_to_index_of_key_name(name);
   update_cursor_destination();
   key.set_last_pressed_at(al_get_time());
   if (this_change_should_dismiss_the_input_error_frame) clear_input_error_frame();
   return;
}

void SoftwareKeyboard::show_input_error_frame(std::vector<std::string> input_error_frame_error_messages)
{
   showing_input_error_frame = true;
   set_input_error_frame_error_messages(input_error_frame_error_messages);
   // TODO: add showing_input_error_frame_at and set here
   return;
}

void SoftwareKeyboard::clear_input_error_frame()
{
   showing_input_error_frame = false;
   clear_input_error_frame_error_messages();
   // TODO: add showing_input_error_frame_at and set to 0.0f here
   return;
}

void SoftwareKeyboard::clear_input_error_frame_error_messages()
{
   input_error_frame_error_messages.clear();
   return;
}

bool SoftwareKeyboard::has_input_error_frame_error_messages()
{
   return (!input_error_frame_error_messages.empty());
}

void SoftwareKeyboard::validate_and_submit_form()
{
   std::string sanitized_string = result_string;
   sanitized_string = AllegroFlare::php::trim(sanitized_string);
      
   if (sanitized_string.empty())
   {
      // TODO: show some error feedback that a name must be entered
      show_input_error_frame({ "cannot be blank" });
      emit_bonk_sound_effect();
   }
   else
   {
      // emit the event
      event_emitter->emit_game_event(AllegroFlare::GameEvent(event_to_emit_on_pressing_submit_key));

      // call the callback
      if (on_submit_callback_func) on_submit_callback_func(this, on_submit_callback_func_user_data);
   }

   return;
}

void SoftwareKeyboard::update_cursor_destination()
{
   if (keys.empty()) return;
   int i=0;
   for (auto &key_dictionary_element : keys)
   {
      if (cursor_pos == i)
      {
         // NOTE: this key_dictionary_element is the current cursor selected key
         auto &key = key_dictionary_element.second;
         cursor_destination.x = key.get_x();
         cursor_destination.y = key.get_y();
         cursor_size_destination.x = key.get_width();
         cursor_size_destination.y = key.get_height();
         return;
      }
      i++;
   }
   return;
}

std::string SoftwareKeyboard::infer_current_key_name()
{
   if (keys.empty()) return "";
   int i=0;
   for (auto &key_dictionary_element : keys)
   {
      if (cursor_pos == i)
      {
         return key_dictionary_element.first;
      }
      i++;
   }
   return ""; // TODO: cout warning
}

void SoftwareKeyboard::jump_cursor_pos_to_index_of_key_name(std::string name)
{
   // TODO: logic for this function
   int i=0;
   for (auto &key_dictionary_element : keys)
   {
      if (name == key_dictionary_element.first)
      {
         // NOTE: this key_dictionary_element is the named key we're looking for
         cursor_pos = i;
         return;
      }
      i++;
   }
   return;
}

void SoftwareKeyboard::increment_cursor_pos()
{
   if (keys.empty())
   {
      emit_bonk_sound_effect();
      return;
   }
   cursor_pos++;
   while (cursor_pos >= keys.size()) cursor_pos -= keys.size();
   update_cursor_destination();
   return;
}

void SoftwareKeyboard::decrement_cursor_pos()
{
   if (keys.empty())
   {
      emit_bonk_sound_effect();
      return;
   }
   cursor_pos--;
   while (cursor_pos < 0) cursor_pos += keys.size();
   update_cursor_destination();
   return;
}

void SoftwareKeyboard::draw_result_string_and_boxes()
{
   float box_width = 50;
   float box_height = 90;
   float box_spacing_x = 10;
   float calculated_width = calculate_spaced_elements_width(num_permitted_chars, box_width, box_spacing_x);
   float x = 1920/2 - calculated_width / 2;
   float y = 1920/12*2 - 120;
   ALLEGRO_COLOR box_color = AllegroFlare::color::color(ALLEGRO_COLOR{0.25, 0.25, 0.25, 0.25}, 0.5);

   float x_cursor = x;
   ALLEGRO_FONT *result_text_font = obtain_result_text_font();
   float font_hline_height = al_get_font_line_height(result_text_font) * 0.5;
   for (int i=0; i<num_permitted_chars; i++)
   {
      // draw box
      al_draw_filled_rectangle(x_cursor, y, x_cursor+box_width, y+box_height, box_color);

      std::string this_char = " ";
      if (i < result_string.size())
      {
         this_char[0] = result_string[i];
         al_draw_text(
            result_text_font,
            ALLEGRO_COLOR{1, 1, 1, 1},
            x_cursor + box_width * 0.5,
            y + box_height*0.5 - font_hline_height,
            ALLEGRO_ALIGN_CENTER,
            this_char.c_str()
         );
      }

      if (i == result_string.size())
      {
         std::string current_key_name = infer_current_key_name();

         // draw the character that is currently selected by the cursor
         // TODO: Add this (show_currently_selected_character_in_the_input_box) as a configurable option
         // TODO: Add visual test for this option
         bool show_currently_selected_character_in_the_input_box = false;
         if (show_currently_selected_character_in_the_input_box)
         {
            if (current_key_name == "BACKSPACE") current_key_name = "<";
            if (current_key_name.size() == 1)
            {
               ALLEGRO_COLOR cursor_color = build_cursor_color();
               al_draw_text(
                  result_text_font,
                  cursor_color,
                  x_cursor + box_width * 0.5,
                  y + box_height*0.5 - font_hline_height,
                  ALLEGRO_ALIGN_CENTER,
                  current_key_name.c_str()
               );
            }
         }

         // TODO: Add these (drawing_cursor_box, drawing_cursor_underline) as configurable options
         // TODO: Add visual test for these options
         bool drawing_cursor_box = false;
         bool drawing_cursor_underline = true;

         // TODO: remove this validation if (drawing_cursor_box, drawing_cursor_underline) are added as options
         if (drawing_cursor_box == drawing_cursor_underline)
         {
            throw std::runtime_error("cannot draw both or neither");
         }

         if (!(current_key_name == "SUBMIT" || current_key_name == "<"))
         {
            if (drawing_cursor_box)
            {
               // draw the text input cursor (box)
               draw_cursor_rectangle(x_cursor, y, box_width, box_height);
            }
            if (drawing_cursor_underline)
            {
               // draw the text input cursor (underline)
               draw_cursor_underline(x_cursor, y, box_width, box_height);
            }
         }
      }

      x_cursor += (box_width + box_spacing_x);
   }

   if (showing_input_error_frame)
   {
      float frame_padding = 12.0f;
      draw_input_error_frame(
         x-frame_padding,
         y-frame_padding,
         calculated_width+frame_padding*2,
         box_height+frame_padding*2
      );
   }

   return;
}

ALLEGRO_COLOR SoftwareKeyboard::build_cursor_color()
{
   ALLEGRO_COLOR color_a = al_color_name("aquamarine");
   ALLEGRO_COLOR color_b = AllegroFlare::color::transparent;
   float speed_multiplier = 0.9;
   float mix_factor = AllegroFlare::interpolator::slow_in(fmod(al_get_time() * speed_multiplier, 1.0));
   return AllegroFlare::color::mix(color_a, color_b, 0.7 * mix_factor);
}

ALLEGRO_COLOR SoftwareKeyboard::build_input_error_frame_color()
{
   ALLEGRO_COLOR color_a = al_color_name("crimson");
   ALLEGRO_COLOR color_b = al_color_name("darkred");
   float speed_multiplier = 0.9;
   float mix_factor = AllegroFlare::interpolator::slow_in(fmod(al_get_time() * speed_multiplier, 1.0));
   return AllegroFlare::color::mix(color_a, color_b, 0.7 * mix_factor);
}

void SoftwareKeyboard::draw_cursor_rectangle(float x, float y, float w, float h)
{
   ALLEGRO_COLOR color = build_cursor_color();
   float roundness = 8;
   float thickness = 6.0;

   al_draw_rounded_rectangle(x, y, x + w, y + h, roundness, roundness, color, thickness);
   return;
}

void SoftwareKeyboard::draw_cursor_underline(float x, float y, float w, float h)
{
   ALLEGRO_COLOR color = build_cursor_color();
   float thickness = 6.0;

   // TODO: Consider adding rounded line caps
   al_draw_line(x, y+h, x+w, y+h, color, thickness);
   return;
}

void SoftwareKeyboard::draw_input_error_frame(float x, float y, float w, float h)
{
   ALLEGRO_COLOR color = build_input_error_frame_color();
   float roundness = 8;
   float thickness = 6.0;

   al_draw_rounded_rectangle(x, y, x + w, y + h, roundness, roundness, color, thickness);

   // Draw the messages
   bool there_are_error_messages = !input_error_frame_error_messages.empty();
   if (there_are_error_messages)
   {
      ALLEGRO_COLOR error_messages_text_color = al_color_name("crimson");
      ALLEGRO_FONT *error_messages_font = obtain_error_messages_font();
      std::string comma_joined_error_messages = join(input_error_frame_error_messages, ", ");
      al_draw_text(
         error_messages_font,
         error_messages_text_color,
         x+w,
         y+h,
         ALLEGRO_ALIGN_RIGHT,
         comma_joined_error_messages.c_str()
      );
   }

   return;
}

void SoftwareKeyboard::draw_cursor()
{
   draw_cursor_rectangle(cursor_location.x, cursor_location.y, cursor_size.x, cursor_size.y);
   return;
}

void SoftwareKeyboard::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::render]: error: guard \"initialized\" not met");
   }
   // this is a soft "update" here to update the live-moving cursor location
   cursor_location = (cursor_destination - cursor_location) * cursor_reposition_multiplier + cursor_location;
   cursor_size = (cursor_size_destination - cursor_size) * cursor_reposition_multiplier + cursor_size;

   keyboard_placement.start_transform();

   // draw backfill and frame
   draw_keyboard_backfill_and_frame();

   // draw keys
   float time_now = al_get_time();
   ALLEGRO_FONT *font = obtain_keyboard_font();
   ALLEGRO_FONT *prompt_text_font = obtain_prompt_text_font();
   float font_hline_height = al_get_font_line_height(font) / 2;
   for (auto &key_dictionary_element : keys)
   {
      ALLEGRO_COLOR key_color = ALLEGRO_COLOR{1, 1, 1, 1};
      auto &key = key_dictionary_element.second;
      float pressed_age = time_now - key.get_last_pressed_at();
      float motion_duration = 0.6;
      float y_offset = 0.0f;
      if (pressed_age <= motion_duration)
      {
         float normalized_effect_time = pressed_age / motion_duration;
         float inv_normalized_effect_time = 1.0 - normalized_effect_time;
         float fast_curve = inv_normalized_effect_time * inv_normalized_effect_time;
         ALLEGRO_COLOR color_a = al_color_name("aquamarine");
         ALLEGRO_COLOR color_b = key_color;
         key_color = AllegroFlare::color::mix(color_a, color_b, 1.0 - fast_curve);
         y_offset = 8 * inv_normalized_effect_time * inv_normalized_effect_time;
      }

      if (show_rectangle_outline_on_keys)
      {
         al_draw_rectangle(
            key.get_x(),
            key.get_y(),
            key.get_x2(),
            key.get_y2(),
            ALLEGRO_COLOR{0.5, 0.5, 0.5, 0.5},
            1.0
         );
      }
      al_draw_text(
         font,
         key_color,
         key.get_center(),
         key.get_middle() - font_hline_height + y_offset,
         ALLEGRO_ALIGN_CENTER,
         key.get_label().c_str()
      );
   }

   // draw cursor
   draw_cursor();

   keyboard_placement.restore_transform();

   // draw the result string
   draw_result_string_and_boxes();

   // draw the prompt string
   al_draw_text(
      prompt_text_font,
      ALLEGRO_COLOR{1, 1, 1, 1},
      1920/2, // TODO: make this positioning dynamic
      1080/7*1-85, // TODO: make this positioning dynamic
      ALLEGRO_ALIGN_CENTER,
      prompt_text.c_str()
   );

   return;
}

void SoftwareKeyboard::draw_keyboard_backfill_and_frame()
{
   ALLEGRO_COLOR backfill_color = AllegroFlare::color::color(al_color_html("303030"), 0.3);
   ALLEGRO_COLOR border_color = AllegroFlare::color::color(al_color_html("ffffff"), 0.8);
   float roundness = 6.0f;
   float border_thickness = 6.0f;
   float border_padding = border_thickness * 1.75f;
   float extra_padding_x = 60;
   float extra_padding_y = 40;

   al_draw_filled_rounded_rectangle(
      0 - extra_padding_x,
      0 - extra_padding_y,
      keyboard_placement.size.x + extra_padding_x,
      keyboard_placement.size.y + extra_padding_y,
      roundness,
      roundness,
      backfill_color
   );
   al_draw_rounded_rectangle(
      0 - border_padding - extra_padding_x,
      0 - border_padding - extra_padding_y,
      keyboard_placement.size.x + border_padding + extra_padding_x,
      keyboard_placement.size.y + border_padding + extra_padding_y,
      roundness,
      roundness,
      border_color,
      border_thickness
   );
   return;
}

bool SoftwareKeyboard::key_exists(std::string identifier)
{
   return (keys.count(identifier) >= 1);
}

void SoftwareKeyboard::emit_bonk_sound_effect()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::emit_bonk_sound_effect]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::emit_bonk_sound_effect]: error: guard \"initialized\" not met");
   }
   event_emitter->emit_play_sound_effect_event(bonk_sound_effect_identifier);
   return;
}

void SoftwareKeyboard::emit_key_click_sound_effect()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::emit_key_click_sound_effect]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::emit_key_click_sound_effect]: error: guard \"initialized\" not met");
   }
   event_emitter->emit_play_sound_effect_event(key_click_sound_effect_identifier);
   return;
}

void SoftwareKeyboard::emit_erase_sound_effect()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::emit_erase_sound_effect]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::emit_erase_sound_effect]: error: guard \"initialized\" not met");
   }
   event_emitter->emit_play_sound_effect_event(erase_sound_effect_identifier);
   return;
}

ALLEGRO_FONT* SoftwareKeyboard::obtain_keyboard_font()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::obtain_keyboard_font]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::obtain_keyboard_font]: error: guard \"initialized\" not met");
   }
   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << font_size;
   return font_bin->auto_get(composite_font_str.str());
}

ALLEGRO_FONT* SoftwareKeyboard::obtain_prompt_text_font()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::obtain_prompt_text_font]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::obtain_prompt_text_font]: error: guard \"initialized\" not met");
   }
   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << (font_size - 23);
   return font_bin->auto_get(composite_font_str.str());
}

ALLEGRO_FONT* SoftwareKeyboard::obtain_result_text_font()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::obtain_result_text_font]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::obtain_result_text_font]: error: guard \"initialized\" not met");
   }
   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << (font_size - 20);
   return font_bin->auto_get(composite_font_str.str());
}

ALLEGRO_FONT* SoftwareKeyboard::obtain_error_messages_font()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::obtain_error_messages_font]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::obtain_error_messages_font]: error: guard \"initialized\" not met");
   }
   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << (font_size);
   return font_bin->auto_get(composite_font_str.str());
}

AllegroFlare::Vec2D SoftwareKeyboard::calculate_boilerplate_keyboard_dimensions()
{
   float x_spacing = 65;
   float y_spacing = 70;
   float column_spacing = 450;
   return AllegroFlare::Vec2D(column_spacing * 2 + x_spacing * 6, 500);
}

void SoftwareKeyboard::move_cursor_down()
{
   if (keys.empty()) return;

   std::map<std::string, std::string> up_move_destination_exceptions = {

      // row 1

      { "A", "G" },
      { "B", "H" },
      { "C", "I" },
      { "D", "J" },
      { "E", "K" },
      { "F", "L" },

      { "a", "g" },
      { "b", "h" },
      { "c", "i" },
      { "d", "j" },
      { "e", "k" },
      { "f", "l" },

      { "0", "6" },
      { "1", "7" },
      { "2", "8" },
      { "3", "9" },
      { "4", "." },
      { "5", "-" },

      // row 2

      { "G", "M" },
      { "H", "N" },
      { "I", "O" },
      { "J", "P" },
      { "K", "Q" },
      { "L", "R" },

      { "g", "m" },
      { "h", "n" },
      { "i", "o" },
      { "j", "p" },
      { "k", "q" },
      { "l", "r" },

      { "6", "BACKSPACE" },
      { "7", "BACKSPACE" },
      { "8", "BACKSPACE" },
      { "9", "SUBMIT" },
      { ".", "SUBMIT" },
      { "-", "SUBMIT" },

      // row 3

      { "M", "S" },
      { "N", "T" },
      { "O", "U" },
      { "P", "V" },
      { "Q", "W" },
      { "R", "X" },
          
      { "m", "s" },
      { "n", "t" },
      { "o", "u" },
      { "p", "v" },
      { "q", "w" },
      { "r", "x" },

      //{ "X", "X" },
      //{ "X", "X" },
      //{ "X", "X" },
      //{ "X", "X" },
      //{ "X", "X" },
      //{ "X", "X" },

      // row 4

      { "S", "Y" },
      { "T", "Z" },
      { "U", "C" },
      { "V", "D" },
      { "W", "E" },
      { "X", "F" },
          
      { "s", "y" },
      { "t", "z" },
      { "u", "SPACE" },
      { "v", "SPACE" },
      { "w", "SPACE" },
      { "x", "BACKSPACE" },

      //{ "X", "X" },
      //{ "X", "X" },
      //{ "X", "X" },
      //{ "X", "X" },
      //{ "X", "X" },
      //{ "X", "X" },

      // row 5

      { "Y", "A" },
      { "Z", "B" },
      //{ "X", "X" },
      //{ "X", "X" },
      //{ "X", "X" },
      //{ "X", "X" },

      { "y", "SPACE" },
      { "z", "SPACE" },
      //{ "X", "X" },
      //{ "X", "X" },
      //{ "X", "X" },
      //{ "X", "X" },

      //{ "X", "X" },
      //{ "X", "X" },
      //{ "X", "X" },
      //{ "X", "X" },
      //{ "X", "X" },
      //{ "X", "X" },

      // bottom row

      { "BACKSPACE", "0" },
      { "SPACE", "a" },
      { "SUBMIT", "4" },
   };

   std::string current_key_name = infer_current_key_name();
   if (current_key_name.empty()) return;

   if (keys.count(current_key_name) >= 1)
   {
      // key is found in the exception dictionary
      std::string key_name_to_move_to = up_move_destination_exceptions[current_key_name];
      if (keys.count(key_name_to_move_to) <= 0)
      {
         // TODO: test this condition
         std::stringstream error_message;
         error_message << "[AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::move_cursor_to_pos]: WARNING: "
                       << "Attempting to move cursor to key named \"" << key_name_to_move_to << "\" but it does "
                       << "not exist.";
         std::cout << error_message.str() << std::endl;
         return;
      }

      // move to the destination key and return
      jump_cursor_pos_to_index_of_key_name(key_name_to_move_to);
      update_cursor_destination();
      
      return;
   }


   return;
}

void SoftwareKeyboard::move_cursor_up()
{
   if (keys.empty()) return;

   std::map<std::string, std::string> up_move_destination_exceptions = {

      // row 1

      { "A", "Y" },
      { "B", "Z" },
      { "C", "U", },
      { "D", "V", },
      { "E", "W", },
      { "F", "X", },

      { "a", "SPACE" },
      { "b", "SPACE" },
      { "c", "SPACE" },
      { "d", "SPACE" },
      { "e", "SPACE" },
      { "f", "BACKSPACE" },

      { "0", "BACKSPACE" },
      { "1", "BACKSPACE" },
      { "2", "BACKSPACE" },
      { "3", "BACKSPACE" },
      { "4", "SUBMIT" },
      { "5", "SUBMIT" },

      // row 2

      { "G", "A", },
      { "H", "B", },
      { "I", "C", },
      { "J", "D", },
      { "K", "E", },
      { "L", "F", },
           
      { "g", "a", },
      { "h", "b", },
      { "i", "c", },
      { "j", "d", },
      { "k", "e", },
      { "l", "f", },
           
      { "6", "0", },
      { "7", "1", },
      { "8", "2", },
      { "9", "3", },
      { ".", "4", },
      { "-", "5", },

      // row 3

      { "M", "G", },
      { "N", "H", },
      { "O", "I", },
      { "P", "J", },
      { "Q", "K", },
      { "R", "L", },
           
      { "m", "g", },
      { "n", "h", },
      { "o", "i", },
      { "p", "j", },
      { "q", "k", },
      { "r", "l", },
           
      //{ "*", "6", },
      //{ "*", "7", },
      //{ "*", "8", },
      //{ "*", "9", },
      //{ "*", ".", },
      //{ "*", "-", },

      // row 4

      { "S", "M", },
      { "T", "N", },
      { "U", "O", },
      { "V", "P", },
      { "W", "Q", },
      { "X", "R", },
              
      { "s", "m", },
      { "t", "n", },
      { "u", "o", },
      { "v", "p", },
      { "w", "q", },
      { "x", "r", },

      //{ "X", "X" },
      //{ "X", "X" },
      //{ "X", "X" },
      //{ "X", "X" },
      //{ "X", "X" },
      //{ "X", "X" },

      // row 5

      { "Y", "S", },
      { "Z", "T", },
      //{ "C", "X" },
      //{ "D", "X" },
      //{ "E", "X" },
      //{ "F", "X" },
               
      { "y", "s", },
      { "z", "t", },
      //{ "*", "u", },
      //{ "*", "v", },
      //{ "*", "w", },
      //{ "*", "x", },

      //{ "X", "X" },
      //{ "X", "X" },
      //{ "X", "X" },
      //{ "X", "X" },
      //{ "X", "X" },
      //{ "X", "X" },

      // bottom row

      { "BACKSPACE", "6" },
      { "SPACE", "y" },
      { "SUBMIT", "." },
   };

   std::string current_key_name = infer_current_key_name();
   if (current_key_name.empty()) return;

   if (keys.count(current_key_name) >= 1)
   {
      // key is found in the exception dictionary
      std::string key_name_to_move_to = up_move_destination_exceptions[current_key_name];
      if (keys.count(key_name_to_move_to) <= 0)
      {
         // TODO: test this condition
         std::stringstream error_message;
         error_message << "[AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::move_cursor_to_pos]: WARNING: "
                       << "Attempting to move cursor to key named \"" << key_name_to_move_to << "\" but it does "
                       << "not exist.";
         std::cout << error_message.str() << std::endl;
         return;
      }

      // move to the destination key and return
      jump_cursor_pos_to_index_of_key_name(key_name_to_move_to);
      update_cursor_destination();
      
      return;
   }

   return;
}

tsl::ordered_map<std::string, AllegroFlare::SoftwareKeyboard::KeyboardKey> SoftwareKeyboard::build_boilerplate_keyboard_keys()
{
   float x_spacing = 65;
   float y_spacing = 70;
   float column_spacing = 450;
   AllegroFlare::Vec2D calculated_dimensions = calculate_boilerplate_keyboard_dimensions();

   float space_key_width = 330;
   float backspace_key_width = 330;
   float submit_key_width = 140;
   float right_edge = calculated_dimensions.x;

   tsl::ordered_map<std::string, AllegroFlare::SoftwareKeyboard::KeyboardKey> result = {
     // row 1

     { "A", { "A", x_spacing*0,                  y_spacing*0, 80, 80 } },
     { "B", { "B", x_spacing*1,                  y_spacing*0, 80, 80 } },
     { "C", { "C", x_spacing*2,                  y_spacing*0, 80, 80 } },
     { "D", { "D", x_spacing*3,                  y_spacing*0, 80, 80 } },
     { "E", { "E", x_spacing*4,                  y_spacing*0, 80, 80 } },
     { "F", { "F", x_spacing*5,                  y_spacing*0, 80, 80 } },

     { "a", { "a", column_spacing*1+x_spacing*0, y_spacing*0, 80, 80 } },
     { "b", { "b", column_spacing*1+x_spacing*1, y_spacing*0, 80, 80 } },
     { "c", { "c", column_spacing*1+x_spacing*2, y_spacing*0, 80, 80 } },
     { "d", { "d", column_spacing*1+x_spacing*3, y_spacing*0, 80, 80 } },
     { "e", { "e", column_spacing*1+x_spacing*4, y_spacing*0, 80, 80 } },
     { "f", { "f", column_spacing*1+x_spacing*5, y_spacing*0, 80, 80 } },

     { "0", { "0", column_spacing*2+x_spacing*0, y_spacing*0, 80, 80 } },
     { "1", { "1", column_spacing*2+x_spacing*1, y_spacing*0, 80, 80 } },
     { "2", { "2", column_spacing*2+x_spacing*2, y_spacing*0, 80, 80 } },
     { "3", { "3", column_spacing*2+x_spacing*3, y_spacing*0, 80, 80 } },
     { "4", { "4", column_spacing*2+x_spacing*4, y_spacing*0, 80, 80 } },
     { "5", { "5", column_spacing*2+x_spacing*5, y_spacing*0, 80, 80 } },

     // row 2

     { "G", { "G", x_spacing*0,                  y_spacing*1, 80, 80 } },
     { "H", { "H", x_spacing*1,                  y_spacing*1, 80, 80 } },
     { "I", { "I", x_spacing*2,                  y_spacing*1, 80, 80 } },
     { "J", { "J", x_spacing*3,                  y_spacing*1, 80, 80 } },
     { "K", { "K", x_spacing*4,                  y_spacing*1, 80, 80 } },
     { "L", { "L", x_spacing*5,                  y_spacing*1, 80, 80 } },

     { "g", { "g", column_spacing*1+x_spacing*0, y_spacing*1, 80, 80 } },
     { "h", { "h", column_spacing*1+x_spacing*1, y_spacing*1, 80, 80 } },
     { "i", { "i", column_spacing*1+x_spacing*2, y_spacing*1, 80, 80 } },
     { "j", { "j", column_spacing*1+x_spacing*3, y_spacing*1, 80, 80 } },
     { "k", { "k", column_spacing*1+x_spacing*4, y_spacing*1, 80, 80 } },
     { "l", { "l", column_spacing*1+x_spacing*5, y_spacing*1, 80, 80 } },

     { "6", { "6", column_spacing*2+x_spacing*0, y_spacing*1, 80, 80 } },
     { "7", { "7", column_spacing*2+x_spacing*1, y_spacing*1, 80, 80 } },
     { "8", { "8", column_spacing*2+x_spacing*2, y_spacing*1, 80, 80 } },
     { "9", { "9", column_spacing*2+x_spacing*3, y_spacing*1, 80, 80 } },
     { ".", { ".", column_spacing*2+x_spacing*4, y_spacing*1, 80, 80 } },
     { "-", { "-", column_spacing*2+x_spacing*5, y_spacing*1, 80, 80 } },

     // row 3

     { "M", { "M", x_spacing*0,                  y_spacing*2, 80, 80 } },
     { "N", { "N", x_spacing*1,                  y_spacing*2, 80, 80 } },
     { "O", { "O", x_spacing*2,                  y_spacing*2, 80, 80 } },
     { "P", { "P", x_spacing*3,                  y_spacing*2, 80, 80 } },
     { "Q", { "Q", x_spacing*4,                  y_spacing*2, 80, 80 } },
     { "R", { "R", x_spacing*5,                  y_spacing*2, 80, 80 } },

     { "m", { "m", column_spacing*1+x_spacing*0, y_spacing*2, 80, 80 } },
     { "n", { "n", column_spacing*1+x_spacing*1, y_spacing*2, 80, 80 } },
     { "o", { "o", column_spacing*1+x_spacing*2, y_spacing*2, 80, 80 } },
     { "p", { "p", column_spacing*1+x_spacing*3, y_spacing*2, 80, 80 } },
     { "q", { "q", column_spacing*1+x_spacing*4, y_spacing*2, 80, 80 } },
     { "r", { "r", column_spacing*1+x_spacing*5, y_spacing*2, 80, 80 } },

     //{ "~", { "~", column_spacing*2+x_spacing*0, y_spacing*2, 80, 80 } },
     //{ "~", { "~", column_spacing*2+x_spacing*1, y_spacing*2, 80, 80 } },
     //{ "~", { "~", column_spacing*2+x_spacing*2, y_spacing*2, 80, 80 } },
     //{ "~", { "~", column_spacing*2+x_spacing*3, y_spacing*2, 80, 80 } },
     //{ "~", { "~", column_spacing*2+x_spacing*4, y_spacing*2, 80, 80 } },
     //{ "~", { "~", column_spacing*2+x_spacing*5, y_spacing*2, 80, 80 } },

     // row 4

     { "S", { "S", x_spacing*0,                  y_spacing*3, 80, 80 } },
     { "T", { "T", x_spacing*1,                  y_spacing*3, 80, 80 } },
     { "U", { "U", x_spacing*2,                  y_spacing*3, 80, 80 } },
     { "V", { "V", x_spacing*3,                  y_spacing*3, 80, 80 } },
     { "W", { "W", x_spacing*4,                  y_spacing*3, 80, 80 } },
     { "X", { "X", x_spacing*5,                  y_spacing*3, 80, 80 } },

     { "s", { "s", column_spacing*1+x_spacing*0, y_spacing*3, 80, 80 } },
     { "t", { "t", column_spacing*1+x_spacing*1, y_spacing*3, 80, 80 } },
     { "u", { "u", column_spacing*1+x_spacing*2, y_spacing*3, 80, 80 } },
     { "v", { "v", column_spacing*1+x_spacing*3, y_spacing*3, 80, 80 } },
     { "w", { "w", column_spacing*1+x_spacing*4, y_spacing*3, 80, 80 } },
     { "x", { "x", column_spacing*1+x_spacing*5, y_spacing*3, 80, 80 } },

     //{ "x", { "x", column_spacing*2+x_spacing*0, y_spacing*3, 80, 80 } },
     //{ "x", { "x", column_spacing*2+x_spacing*1, y_spacing*3, 80, 80 } },
     //{ "x", { "x", column_spacing*2+x_spacing*2, y_spacing*3, 80, 80 } },
     //{ "x", { "x", column_spacing*2+x_spacing*3, y_spacing*3, 80, 80 } },
     //{ "x", { "x", column_spacing*2+x_spacing*4, y_spacing*3, 80, 80 } },
     //{ "x", { "x", column_spacing*2+x_spacing*5, y_spacing*3, 80, 80 } },

     // row 5

     { "Y", { "Y", x_spacing*0,                    y_spacing*4, 80, 80 } },
     { "Z", { "Z", x_spacing*1,                    y_spacing*4, 80, 80 } },
     //{ " ", { " ", x_spacing*2,                  y_spacing*4, 80, 80 } },
     //{ " ", { " ", x_spacing*3,                  y_spacing*4, 80, 80 } },
     //{ " ", { " ", x_spacing*4,                  y_spacing*4, 80, 80 } },
     //{ " ", { " ", x_spacing*5,                  y_spacing*4, 80, 80 } },

     { "y", { "y", column_spacing*1+x_spacing*0,  y_spacing*4, 80, 80 } },
     { "z", { "z", column_spacing*1+x_spacing*1,  y_spacing*4, 80, 80 } },
     //{ " ", { " ", column_spacing*1+x_spacing*2, y_spacing*4, 80, 80 } },
     //{ " ", { " ", column_spacing*1+x_spacing*3, y_spacing*4, 80, 80 } },
     //{ " ", { " ", column_spacing*1+x_spacing*4, y_spacing*4, 80, 80 } },
     //{ " ", { " ", column_spacing*1+x_spacing*5, y_spacing*4, 80, 80 } },

     //{ "x", { "x", column_spacing*2+x_spacing*0, y_spacing*3, 80, 80 } },
     //{ "x", { "x", column_spacing*2+x_spacing*1, y_spacing*3, 80, 80 } },
     //{ "x", { "x", column_spacing*2+x_spacing*2, y_spacing*3, 80, 80 } },
     //{ "x", { "x", column_spacing*2+x_spacing*3, y_spacing*3, 80, 80 } },
     //{ "x", { "x", column_spacing*2+x_spacing*4, y_spacing*3, 80, 80 } },
     //{ "x", { "x", column_spacing*2+x_spacing*5, y_spacing*3, 80, 80 } },

     // bottom row

     { "SPACE",     { "Space", right_edge - 900, calculated_dimensions.y-80, space_key_width, 80 } },
     { "BACKSPACE", { "Backspace", right_edge - (140+330+50), calculated_dimensions.y-80, backspace_key_width, 80 } },
     { "SUBMIT",    { "OK", right_edge - 140, calculated_dimensions.y-80, submit_key_width, 80 } },

   };
   return result;
}

float SoftwareKeyboard::calculate_spaced_elements_width(int num_elements, float element_width, float element_spacing)
{
   if (!((num_elements >= 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::calculate_spaced_elements_width]: error: guard \"(num_elements >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SoftwareKeyboardSoftwareKeyboard::calculate_spaced_elements_width]: error: guard \"(num_elements >= 0)\" not met");
   }
   // TODO: Test this function
   // TODO: Include this function in a new class that specializes in working with layouts

   // When there are no elements, return 0
   if (num_elements == 0) return 0;

   // Calculate the total width of the boxes and spacing
   float total_width = (num_elements * element_width) + ((num_elements - 1) * element_spacing);
   return total_width;
}

std::string SoftwareKeyboard::join(std::vector<std::string> tokens, std::string delimiter)
{
   std::stringstream result;
   bool last = false;

   for (unsigned i=0; i<tokens.size(); i++)
   {
      result << tokens[i];
      if (i == tokens.size()-1) last = true;
      if (!last) result << delimiter;
   }

   return result.str();
}


} // namespace SoftwareKeyboard
} // namespace AllegroFlare


