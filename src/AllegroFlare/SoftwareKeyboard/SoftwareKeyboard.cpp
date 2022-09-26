

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


std::map<std::string, AllegroFlare::SoftwareKeyboard::KeyboardKey> &SoftwareKeyboard::get_keys_ref()
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


} // namespace SoftwareKeyboard
} // namespace AllegroFlare


