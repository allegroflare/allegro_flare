

#include <AllegroFlare/InputDiagrams/KeyboardKey.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace InputDiagrams
{


KeyboardKey::KeyboardKey(AllegroFlare::FontBin* font_bin, std::string keyboard_key_str, ALLEGRO_COLOR color)
   : font_bin(font_bin)
   , keyboard_key_str(keyboard_key_str)
   , color(color)
{
}


KeyboardKey::~KeyboardKey()
{
}


void KeyboardKey::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void KeyboardKey::set_keyboard_key_str(std::string keyboard_key_str)
{
   this->keyboard_key_str = keyboard_key_str;
}


void KeyboardKey::set_color(ALLEGRO_COLOR color)
{
   this->color = color;
}


AllegroFlare::FontBin* KeyboardKey::get_font_bin()
{
   return font_bin;
}


std::string KeyboardKey::get_keyboard_key_str()
{
   return keyboard_key_str;
}


ALLEGRO_COLOR KeyboardKey::get_color()
{
   return color;
}


void KeyboardKey::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "KeyboardKey" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "KeyboardKey" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_ttf_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "KeyboardKey" << "::" << "render" << ": error: " << "guard \"al_is_ttf_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_primitives_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "KeyboardKey" << "::" << "render" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   ALLEGRO_FONT *font = obtain_font();
   float padding_x = 6;
   float padding_y = 5;
   float roundness = 6;
   float line_thickness = 1.5;

   al_draw_rounded_rectangle(0, 0, 100, 40, roundness, roundness, color, line_thickness);
   al_draw_text(font, color, padding_x, padding_y, 0, keyboard_key_str.c_str());

   return;
}

ALLEGRO_FONT* KeyboardKey::obtain_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "KeyboardKey" << "::" << "obtain_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   std::string font_name = "Inter-Medium.ttf";
   int font_size = -20;

   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << font_size;
   return font_bin->auto_get(composite_font_str.str());
}
} // namespace InputDiagrams
} // namespace AllegroFlare


