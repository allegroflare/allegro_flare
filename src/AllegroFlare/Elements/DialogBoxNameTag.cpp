

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


DialogBoxNameTag::DialogBoxNameTag(AllegroFlare::FontBin* font_bin, std::string name, float width, float height, ALLEGRO_COLOR background_color, float background_opacity, ALLEGRO_COLOR text_color, float opacity)
   : font_bin(font_bin)
   , name(name)
   , width(width)
   , height(height)
   , background_color(background_color)
   , background_opacity(background_opacity)
   , text_color(text_color)
   , opacity(opacity)
{
}


DialogBoxNameTag::~DialogBoxNameTag()
{
}


void DialogBoxNameTag::set_background_color(ALLEGRO_COLOR background_color)
{
   this->background_color = background_color;
}


void DialogBoxNameTag::set_background_opacity(float background_opacity)
{
   this->background_opacity = background_opacity;
}


void DialogBoxNameTag::set_text_color(ALLEGRO_COLOR text_color)
{
   this->text_color = text_color;
}


void DialogBoxNameTag::set_opacity(float opacity)
{
   this->opacity = opacity;
}


float DialogBoxNameTag::get_width() const
{
   return width;
}


float DialogBoxNameTag::get_height() const
{
   return height;
}


ALLEGRO_COLOR DialogBoxNameTag::get_background_color() const
{
   return background_color;
}


float DialogBoxNameTag::get_background_opacity() const
{
   return background_opacity;
}


ALLEGRO_COLOR DialogBoxNameTag::get_text_color() const
{
   return text_color;
}


float DialogBoxNameTag::get_opacity() const
{
   return opacity;
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
   //ALLEGRO_COLOR fill_color = al_color_html("ffffff");
   ALLEGRO_COLOR final_background_color = ALLEGRO_COLOR{
      background_color.r * opacity * background_opacity, 
      background_color.g * opacity * background_opacity, 
      background_color.b * opacity * background_opacity, 
      background_color.a * opacity * background_opacity
   };
   al_draw_filled_rectangle(0, 0, width, height, final_background_color);
   //AllegroFlare::Elements::DialogBoxFrame(width, height).render();
   draw_text();
   return;
}

void DialogBoxNameTag::draw_text()
{
   ALLEGRO_FONT* font = obtain_dialog_font();
   ALLEGRO_COLOR final_text_color = ALLEGRO_COLOR{
      text_color.r * opacity, 
      text_color.g * opacity, 
      text_color.b * opacity, 
      text_color.a * opacity
   };
   //ALLEGRO_COLOR text_color = al_color_html("000000");
   al_draw_text(
      font,
      text_color,
      width/2,
      height/2 - al_get_font_line_height(font)/2,
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


