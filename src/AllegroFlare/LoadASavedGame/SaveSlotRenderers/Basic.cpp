

#include <AllegroFlare/LoadASavedGame/SaveSlotRenderers/Basic.hpp>

#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace LoadASavedGame
{
namespace SaveSlotRenderers
{


Basic::Basic(AllegroFlare::FontBin* font_bin, std::string save_name)
   : font_bin(font_bin)
   , x(1920/2)
   , y(1080/3)
   , width(1920/2)
   , height(1080/7)
   , save_name(save_name)
{
}


Basic::~Basic()
{
}


void Basic::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void Basic::set_x(float x)
{
   this->x = x;
}


void Basic::set_y(float y)
{
   this->y = y;
}


void Basic::set_width(float width)
{
   this->width = width;
}


void Basic::set_height(float height)
{
   this->height = height;
}


void Basic::set_save_name(std::string save_name)
{
   this->save_name = save_name;
}


float Basic::get_x() const
{
   return x;
}


float Basic::get_y() const
{
   return y;
}


float Basic::get_width() const
{
   return width;
}


float Basic::get_height() const
{
   return height;
}


std::string Basic::get_save_name() const
{
   return save_name;
}


void Basic::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Basic::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Basic::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic::render: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Basic::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic::render: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Basic::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic::render: error: guard \"font_bin\" not met");
   }
   //float x = 1920/2;
   //float y = 1080/3;
   ALLEGRO_FONT *font = obtain_font();
   float h_font_line_height = al_get_font_line_height(font)/2;
   //float text_width = al_get_text_width(font, quote.c_str());
   //float text_height = al_get_font_line_height(font);
   float h_text_width = width/2;
   float h_text_height = height/2;
   AllegroFlare::Vec2D padding = {0, 0};

   al_draw_rounded_rectangle(
      x-h_text_width - padding.x,
      y-h_text_height - padding.y,
      x+h_text_width + padding.x,
      y+h_text_height + padding.y,
      8.0f,
      8.0f,
      ALLEGRO_COLOR{1, 1, 1, 1},
      3.0f
   );
   al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, x, y-h_font_line_height, ALLEGRO_ALIGN_CENTER, save_name.c_str());
   return;
}

ALLEGRO_FONT* Basic::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Basic::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic::obtain_font: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Medium.ttf -26");
}


} // namespace SaveSlotRenderers
} // namespace LoadASavedGame
} // namespace AllegroFlare


