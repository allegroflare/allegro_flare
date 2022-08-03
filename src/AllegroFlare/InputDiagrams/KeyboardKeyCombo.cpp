

#include <AllegroFlare/InputDiagrams/KeyboardKeyCombo.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <AllegroFlare/InputDiagrams/KeyboardKey.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace InputDiagrams
{


KeyboardKeyCombo::KeyboardKeyCombo(AllegroFlare::FontBin* font_bin, std::vector<std::string> keyboard_combo_tokens, ALLEGRO_COLOR color)
   : font_bin(font_bin)
   , keyboard_combo_tokens(keyboard_combo_tokens)
   , color(color)
{
}


KeyboardKeyCombo::~KeyboardKeyCombo()
{
}


void KeyboardKeyCombo::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void KeyboardKeyCombo::set_keyboard_combo_tokens(std::vector<std::string> keyboard_combo_tokens)
{
   this->keyboard_combo_tokens = keyboard_combo_tokens;
}


void KeyboardKeyCombo::set_color(ALLEGRO_COLOR color)
{
   this->color = color;
}


AllegroFlare::FontBin* KeyboardKeyCombo::get_font_bin()
{
   return font_bin;
}


std::vector<std::string> KeyboardKeyCombo::get_keyboard_combo_tokens()
{
   return keyboard_combo_tokens;
}


ALLEGRO_COLOR KeyboardKeyCombo::get_color()
{
   return color;
}


float KeyboardKeyCombo::get_keyboard_key_box_height()
{
   AllegroFlare::InputDiagrams::KeyboardKey keyboard_key;
   return keyboard_key.get_keyboard_key_box_height();
}

void KeyboardKeyCombo::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "KeyboardKeyCombo" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "KeyboardKeyCombo" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_ttf_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "KeyboardKeyCombo" << "::" << "render" << ": error: " << "guard \"al_is_ttf_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_primitives_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "KeyboardKeyCombo" << "::" << "render" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   AllegroFlare::InputDiagrams::KeyboardKey keyboard_key(font_bin);
   //float box_height = keyboard_key.get_keyboard_key_box_height();

   for (auto &keyboard_combo_token : keyboard_combo_tokens)
   {
      keyboard_key.set_keyboard_key_str(keyboard_combo_token);
      //keyboard_key.set_x = 
      keyboard_key.render();
   }
   return;
}

ALLEGRO_FONT* KeyboardKeyCombo::obtain_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "KeyboardKeyCombo" << "::" << "obtain_font" << ": error: " << "guard \"font_bin\" not met";
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


