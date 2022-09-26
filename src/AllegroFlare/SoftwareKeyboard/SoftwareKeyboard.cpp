

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
   , initialized(false)
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

void SoftwareKeyboard::update_cursor_placement()
{
   if (keys.empty()) return;
   int i=0;
   for (auto &key_dictionary_element : keys)
   {
      if (cursor_pos == i)
      {
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
   update_cursor_placement();
   return;
}

void SoftwareKeyboard::decrement_cursor_pos()
{
   if (keys.empty()) return; // TODO: play bonk sound
   cursor_pos--;
   while (cursor_pos < 0) cursor_pos += keys.size();
   update_cursor_placement();
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
   int i=0;
   ALLEGRO_FONT *font = obtain_font();
   float font_hline_height = al_get_font_line_height(font) / 2;
   for (auto &key_dictionary_element : keys)
   {
      auto &key = key_dictionary_element.second;
      al_draw_rectangle(key.get_x(), key.get_y(), key.get_x2(), key.get_y2(), ALLEGRO_COLOR{1, 1, 1, 1}, 2.0);
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
   float x_spacing = 90;
   float y_spacing = 90;
   std::unordered_map<std::string, AllegroFlare::SoftwareKeyboard::KeyboardKey> result = {
     { "A", { "A", 100+x_spacing*0, 100+y_spacing*0, 80, 80 } },
     { "B", { "B", 100+x_spacing*1, 100+y_spacing*0, 80, 80 } },
     { "C", { "C", 100+x_spacing*2, 100+y_spacing*0, 80, 80 } },
     { "D", { "D", 100+x_spacing*3, 100+y_spacing*0, 80, 80 } },
     { "E", { "E", 100+x_spacing*4, 100+y_spacing*0, 80, 80 } },
     { "F", { "F", 100+x_spacing*5, 100+y_spacing*0, 80, 80 } },

     { "G", { "G", 100+x_spacing*0, 100+y_spacing*1, 80, 80 } },
   };
   return result;
}


} // namespace SoftwareKeyboard
} // namespace AllegroFlare


