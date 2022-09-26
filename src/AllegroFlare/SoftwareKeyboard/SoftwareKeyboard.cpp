

#include <AllegroFlare/SoftwareKeyboard/SoftwareKeyboard.hpp>

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


std::unordered_map<std::string, AllegroFlare::SoftwareKeyboard::KeyboardKey> &SoftwareKeyboard::get_keys_ref()
{
   return keys;
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
   keyboard_placement.position.x = 200;
   keyboard_placement.position.y = 200;
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
   if (!key_exists(name)) return; // TODO: maybe cout a warning
   AllegroFlare::SoftwareKeyboard::KeyboardKey &key = keys[name];
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
         auto &key = key_dictionary_element.second;
         cursor_location.x = key.get_x();
         cursor_location.y = key.get_y();
         // this key_dictionary_element is the current cursor selected key
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

void SoftwareKeyboard::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "SoftwareKeyboard" << "::" << "render" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   keyboard_placement.start_transform();
   // draw keys
   int i=0;
   ALLEGRO_FONT *font = obtain_font();
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
   return;
}

bool SoftwareKeyboard::key_exists(std::string identifier)
{
   return (keys.count(identifier) >= 1);
}

ALLEGRO_FONT* SoftwareKeyboard::obtain_font()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "SoftwareKeyboard" << "::" << "obtain_font" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << font_size;
   return font_bin->auto_get(composite_font_str.str());
}

std::unordered_map<std::string, AllegroFlare::SoftwareKeyboard::KeyboardKey> SoftwareKeyboard::build_boilerplate_keyboard_keys()
{
   float x_spacing = 70;
   float y_spacing = 90;
   float column_spacing = 600;
   std::unordered_map<std::string, AllegroFlare::SoftwareKeyboard::KeyboardKey> result = {
     { "A", { "A", x_spacing*0, 100+y_spacing*0, 80, 80 } },
     { "B", { "B", x_spacing*1, 100+y_spacing*0, 80, 80 } },
     { "C", { "C", x_spacing*2, 100+y_spacing*0, 80, 80 } },
     { "D", { "D", x_spacing*3, 100+y_spacing*0, 80, 80 } },
     { "E", { "E", x_spacing*4, 100+y_spacing*0, 80, 80 } },
     { "F", { "F", x_spacing*5, 100+y_spacing*0, 80, 80 } },

     { "a", { "a", 600+x_spacing*0, 100+y_spacing*0, 80, 80 } },
     { "b", { "b", 600+x_spacing*1, 100+y_spacing*0, 80, 80 } },
     { "c", { "c", 600+x_spacing*2, 100+y_spacing*0, 80, 80 } },
     { "d", { "d", 600+x_spacing*3, 100+y_spacing*0, 80, 80 } },
     { "e", { "e", 600+x_spacing*4, 100+y_spacing*0, 80, 80 } },
     { "f", { "f", 600+x_spacing*5, 100+y_spacing*0, 80, 80 } },

     { "G", { "G", x_spacing*0, 100+y_spacing*1, 80, 80 } },
     { "H", { "H", x_spacing*1, 100+y_spacing*1, 80, 80 } },
     { "I", { "I", x_spacing*2, 100+y_spacing*1, 80, 80 } },
     { "J", { "J", x_spacing*3, 100+y_spacing*1, 80, 80 } },
     { "K", { "K", x_spacing*4, 100+y_spacing*1, 80, 80 } },
     { "L", { "L", x_spacing*5, 100+y_spacing*1, 80, 80 } },
   };
   return result;
}


} // namespace SoftwareKeyboard
} // namespace AllegroFlare


