

#include <AllegroFlare/Elements/Text.hpp>

#include <allegro5/allegro.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


Text::Text(AllegroFlare::FontBin* font_bin, std::string text, ALLEGRO_COLOR color)
   : AllegroFlare::Elements::Base()
   , font_bin(font_bin)
   , text(text)
   , color(color)
{
}


Text::~Text()
{
}


void Text::set_text(std::string text)
{
   this->text = text;
}


void Text::set_color(ALLEGRO_COLOR color)
{
   this->color = color;
}


std::string Text::get_text() const
{
   return text;
}


ALLEGRO_COLOR Text::get_color() const
{
   return color;
}


void Text::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Text::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error(error_message.str());
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Text::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error(error_message.str());
   }
   fit_placement_width_and_height_to_text();

   get_placement_ref().start_transform();
   al_draw_text(obtain_font(), color, 0, 0, 0, text.c_str());
   get_placement_ref().restore_transform();
   return;
}

void Text::fit_placement_width_and_height_to_text()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Text::fit_placement_width_and_height_to_text]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error(error_message.str());
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Text::fit_placement_width_and_height_to_text]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error(error_message.str());
   }
   float width = al_get_text_width(obtain_font(), text.c_str());
   float height = al_get_font_line_height(obtain_font());
   get_placement_ref().size.x = width;
   get_placement_ref().size.y = height;
   return;
}

ALLEGRO_FONT* Text::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Text::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error(error_message.str());
   }
   return font_bin->auto_get("DroidSans.ttf -48");
}


} // namespace Elements
} // namespace AllegroFlare


