

#include <AllegroFlare/Elements/DialogBoxNameTag.hpp>

#include <AllegroFlare/Elements/DialogBoxFrame.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


DialogBoxNameTag::DialogBoxNameTag(AllegroFlare::FontBin* font_bin, std::string name, float width, float height)
   : font_bin(font_bin)
   , name(name)
   , width(width)
   , height(height)
{
}


DialogBoxNameTag::~DialogBoxNameTag()
{
}


float DialogBoxNameTag::get_width() const
{
   return width;
}


float DialogBoxNameTag::get_height() const
{
   return height;
}


void DialogBoxNameTag::render()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxNameTag::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxNameTag::render]: error: guard \"font_bin\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxNameTag::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxNameTag::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxNameTag::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxNameTag::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_get_current_display()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxNameTag::render]: error: guard \"al_get_current_display()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxNameTag::render]: error: guard \"al_get_current_display()\" not met");
   }
   ALLEGRO_COLOR fill_color = al_color_html("ffffff");
   al_draw_filled_rectangle(0, 0, width, height, fill_color);
   //AllegroFlare::Elements::DialogBoxFrame(width, height).render();
   draw_text();
   return;
}

void DialogBoxNameTag::draw_text()
{
   ALLEGRO_FONT* font = obtain_dialog_font();
   ALLEGRO_COLOR text_color = al_color_html("000000");
   al_draw_text(
      font,
      text_color,
      width/2,
      height/2 - al_get_font_line_height(font)/2 - 2,
      ALLEGRO_ALIGN_CENTER,
      name.c_str()
   );
   return;
}

ALLEGRO_FONT* DialogBoxNameTag::obtain_dialog_font()
{
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxNameTag::obtain_dialog_font]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxNameTag::obtain_dialog_font]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(al_is_ttf_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxNameTag::obtain_dialog_font]: error: guard \"al_is_ttf_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxNameTag::obtain_dialog_font]: error: guard \"al_is_ttf_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxNameTag::obtain_dialog_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxNameTag::obtain_dialog_font]: error: guard \"font_bin\" not met");
   }
   static const std::string FONT_IDENTIFIER = "Inter-Medium.ttf -36";
   ALLEGRO_FONT* result_font = font_bin->operator[](FONT_IDENTIFIER);
   return result_font;
}


} // namespace Elements
} // namespace AllegroFlare


