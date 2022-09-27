

#include <AllegroFlare/SoftwareKeyboard/SoftwareKeyboard.hpp>

#include <AllegroFlare/Color.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace SoftwareKeyboard
{


SoftwareKeyboard::SoftwareKeyboard(AllegroFlare::FontBin* font_bin, std::string font_name, int font_size)
   : font_bin(font_bin)
   , font_name(font_name)
   , font_size(font_size)
   , keys({})
   , cursor_pos(0)
   , cursor_location({})
   , cursor_size(80, 80)
   , initialized(false)
   , show_rectangle_outline_on_keys(false)
   , keyboard_placement({})
   , prompt_text("Enter your name")
   , result_string({})
   , num_permitted_chars(12)
{
}


SoftwareKeyboard::~SoftwareKeyboard()
{
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


void SoftwareKeyboard::set_num_permitted_chars(int num_permitted_chars)
{
   this->num_permitted_chars = num_permitted_chars;
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


bool SoftwareKeyboard::get_initialized() const
{
   return initialized;
}


std::string SoftwareKeyboard::get_prompt_text() const
{
   return prompt_text;
}


std::string SoftwareKeyboard::get_result_string() const
{
   return result_string;
}


int SoftwareKeyboard::get_num_permitted_chars() const
{
   return num_permitted_chars;
}


std::unordered_map<std::string, AllegroFlare::SoftwareKeyboard::KeyboardKey> &SoftwareKeyboard::get_keys_ref()
{
   return keys;
}


void SoftwareKeyboard::TODO()
{
   // set num_permitted_chars to a non-negative type like size_t
   return;
}

void SoftwareKeyboard::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "SoftwareKeyboard" << "::" << "set_font_bin" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   this->font_bin = font_bin;
   return;
}

void SoftwareKeyboard::set_keys(std::unordered_map<std::string, AllegroFlare::SoftwareKeyboard::KeyboardKey> keys)
{
   this->keys = keys;
   cursor_pos = 0;
   update_cursor_location();
   return;
}

void SoftwareKeyboard::set_keyboard_dimentions(float width, float height)
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
      error_message << "SoftwareKeyboard" << "::" << "initialize" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "SoftwareKeyboard" << "::" << "initialize" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "SoftwareKeyboard" << "::" << "initialize" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "SoftwareKeyboard" << "::" << "initialize" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
   keyboard_placement.position.x = 1920/2;
   keyboard_placement.position.y = 1080/2;
   initialized = true;
   return;
}

void SoftwareKeyboard::press_key_by_name(std::string name)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "SoftwareKeyboard" << "::" << "press_key_by_name" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!key_exists(name)) return; // TODO: maybe cout a warning, or return false if key is not recognized
   AllegroFlare::SoftwareKeyboard::KeyboardKey &key = keys[name];

   // TODO: perform the action for the key
   std::string string_to_append = "";

   if (name == "SPACE") string_to_append = " ";
   else if (name == "BACKSPACE")
   {
      if (result_string.empty()) {} // TODO; play bonk sound
      else result_string.pop_back();
   }
   else if (name == "OK") {} // TODO: logic for this condition
   else
   {
      // NOTE: assume the "name" is the character we want to append
      string_to_append = name;
   }

   // append string, or bonk if at limit
   if (!string_to_append.empty())
   {
      if (result_string.size() >= num_permitted_chars)
      {
         // TODO: play bonk sound
      }
      else
      {
         // TODO: ensure concating "string_to_append" will not result in a result_string that is longer than limit
         result_string += string_to_append;
      }
   }

   jump_cursor_pos_to_index_of_key_name(name);
   update_cursor_location();
   key.set_last_pressed_at(al_get_time());
   return;
}

void SoftwareKeyboard::update_cursor_location()
{
   if (keys.empty()) return;
   int i=0;
   for (auto &key_dictionary_element : keys)
   {
      if (cursor_pos == i)
      {
         // NOTE: this key_dictionary_element is the current cursor selected key
         auto &key = key_dictionary_element.second;
         cursor_location.x = key.get_x();
         cursor_location.y = key.get_y();
         cursor_size.x = key.get_width();
         cursor_size.y = key.get_height();
      }
      i++;
   }
   return;
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
   if (keys.empty()) return; // TODO: play bonk sound
   cursor_pos++;
   while (cursor_pos >= keys.size()) cursor_pos -= keys.size();
   update_cursor_location();
   return;
}

void SoftwareKeyboard::decrement_cursor_pos()
{
   if (keys.empty()) return; // TODO: play bonk sound
   cursor_pos--;
   while (cursor_pos < 0) cursor_pos += keys.size();
   update_cursor_location();
   return;
}

void SoftwareKeyboard::draw_result_string_and_boxes()
{
   float box_width = 50;
   float box_height = 90;
   float box_spacing_x = 60;
   float calculated_width = num_permitted_chars * box_spacing_x; // TODO: this is not 100% accurate
   float x = 1920/2 - calculated_width / 2;
   float y = 1920/12*2 - 120;
   ALLEGRO_COLOR box_color = AllegroFlare::color::color(ALLEGRO_COLOR{0.7, 0.8, 0.8, 1.0}, 0.2);

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

      x_cursor += box_spacing_x;
   }


   return;
}

void SoftwareKeyboard::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "SoftwareKeyboard" << "::" << "render" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   keyboard_placement.start_transform();

   // draw backfill and frame
   draw_keyboard_backfill_and_frame();

   // draw keys
   int i=0;
   ALLEGRO_FONT *font = obtain_keyboard_font();
   ALLEGRO_FONT *prompt_text_font = obtain_prompt_text_font();
   float font_hline_height = al_get_font_line_height(font) / 2;
   for (auto &key_dictionary_element : keys)
   {
      auto &key = key_dictionary_element.second;
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
         ALLEGRO_COLOR{1, 1, 1, 1},
         key.get_center(),
         key.get_middle() - font_hline_height,
         ALLEGRO_ALIGN_CENTER,
         key.get_label().c_str()
      );
      i++;
   }

   // draw cursor
   al_draw_rectangle(
      cursor_location.x,
      cursor_location.y,
      cursor_location.x+cursor_size.x,
      cursor_location.y+cursor_size.y,
      ALLEGRO_COLOR{0.5, 1, 0.75, 1},
      4.0
   );

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

ALLEGRO_FONT* SoftwareKeyboard::obtain_keyboard_font()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "SoftwareKeyboard" << "::" << "obtain_keyboard_font" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
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
      error_message << "SoftwareKeyboard" << "::" << "obtain_prompt_text_font" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
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
      error_message << "SoftwareKeyboard" << "::" << "obtain_result_text_font" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << (font_size - 20);
   return font_bin->auto_get(composite_font_str.str());
}

AllegroFlare::Vec2D SoftwareKeyboard::calculate_boilerplate_keyboard_dimentions()
{
   float x_spacing = 65;
   float y_spacing = 70;
   float column_spacing = 450;
   return AllegroFlare::Vec2D(column_spacing * 2 + x_spacing * 6, 500);
}

std::unordered_map<std::string, AllegroFlare::SoftwareKeyboard::KeyboardKey> SoftwareKeyboard::build_boilerplate_keyboard_keys()
{
   float x_spacing = 65;
   float y_spacing = 70;
   float column_spacing = 450;
   AllegroFlare::Vec2D calculated_dimentions = calculate_boilerplate_keyboard_dimentions();

   float space_width = 330;
   float backspace_width = 330;
   float ok_width = 140;
   float right_edge = calculated_dimentions.x;

   std::unordered_map<std::string, AllegroFlare::SoftwareKeyboard::KeyboardKey> result = {
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

     { "SPACE",     { "Space", right_edge - 900, calculated_dimentions.y-80, 330, 80 } },
     { "BACKSPACE", { "Backspace", right_edge - (140+330+50), calculated_dimentions.y-80, 330, 80 } },
     { "OK",        { "OK", right_edge - 140, calculated_dimentions.y-80, 140, 80 } },

   };
   return result;
}


} // namespace SoftwareKeyboard
} // namespace AllegroFlare


