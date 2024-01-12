

#include <AllegroFlare/Elements/UI/SliderToggle.hpp>

#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace UI
{


SliderToggle::SliderToggle(AllegroFlare::FontBin* font_bin, float x, float y, float width, float height, bool onoff, int font_size)
   : font_bin(font_bin)
   , x(x)
   , y(y)
   , width(width)
   , height(height)
   , onoff(onoff)
   , font_size(font_size)
   , on_text("ON")
   , off_text("OFF")
{
}


SliderToggle::~SliderToggle()
{
}


void SliderToggle::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void SliderToggle::set_x(float x)
{
   this->x = x;
}


void SliderToggle::set_y(float y)
{
   this->y = y;
}


void SliderToggle::set_width(float width)
{
   this->width = width;
}


void SliderToggle::set_height(float height)
{
   this->height = height;
}


void SliderToggle::set_onoff(bool onoff)
{
   this->onoff = onoff;
}


void SliderToggle::set_font_size(int font_size)
{
   this->font_size = font_size;
}


void SliderToggle::set_on_text(std::string on_text)
{
   this->on_text = on_text;
}


void SliderToggle::set_off_text(std::string off_text)
{
   this->off_text = off_text;
}


AllegroFlare::FontBin* SliderToggle::get_font_bin() const
{
   return font_bin;
}


float SliderToggle::get_x() const
{
   return x;
}


float SliderToggle::get_y() const
{
   return y;
}


float SliderToggle::get_width() const
{
   return width;
}


float SliderToggle::get_height() const
{
   return height;
}


bool SliderToggle::get_onoff() const
{
   return onoff;
}


int SliderToggle::get_font_size() const
{
   return font_size;
}


std::string SliderToggle::get_on_text() const
{
   return on_text;
}


std::string SliderToggle::get_off_text() const
{
   return off_text;
}


void SliderToggle::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[SliderToggle::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SliderToggle::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[SliderToggle::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SliderToggle::render: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[SliderToggle::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SliderToggle::render: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[SliderToggle::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SliderToggle::render: error: guard \"font_bin\" not met");
   }
   float padding = 6;
   float pill_width = 112;
   float pill_height = 46;
   float pill_y = y + height/2 - pill_height/2;

   float on_x = x + padding; //width / 4 - pill_width / 2;
   float off_x = x + width - padding - pill_width; /// 4 * 3 - pill_width / 2;

   if (onoff) // when "on"
   {
      ALLEGRO_COLOR on_box_color = ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0};
      ALLEGRO_COLOR on_text_color = ALLEGRO_COLOR{0.0, 0.0, 0.0, 1.0};
      ALLEGRO_COLOR off_box_color = ALLEGRO_COLOR{0.0, 0.0, 0.0, 0.0};
      ALLEGRO_COLOR off_text_color = ALLEGRO_COLOR{0.53, 0.53, 0.53, 0.53};

      draw_pill("ON", on_x, pill_y, pill_width, pill_height, on_box_color, on_text_color, font_size);
      draw_pill("OFF", off_x, pill_y, pill_width, pill_height, off_box_color, off_text_color, font_size);
   }
   else // when "off"
   {
      //3c3d3d
      ALLEGRO_COLOR on_box_color = ALLEGRO_COLOR{0.0, 0.0, 0.0, 0.0};
      ALLEGRO_COLOR on_text_color = ALLEGRO_COLOR{0.24, 0.24, 0.24, 0.24};
      ALLEGRO_COLOR off_box_color = ALLEGRO_COLOR{0.24, 0.24, 0.24, 0.24};
      ALLEGRO_COLOR off_text_color = ALLEGRO_COLOR{0.53, 0.53, 0.53, 0.53};

      draw_pill("ON", on_x, pill_y, pill_width, pill_height, on_box_color, on_text_color, font_size);
      draw_pill("OFF", off_x, pill_y, pill_width, pill_height, off_box_color, off_text_color, font_size);
   }

   // outter box
   ALLEGRO_COLOR outer_box_color = ALLEGRO_COLOR{0.40, 0.40, 0.40, 0.40};
   float outer_box_roundness = 10.0f;
   float outer_box_thickness = 3.0f;
   al_draw_rounded_rectangle(
      x,
      y,
      x+width,
      y+height,
      outer_box_roundness,
      outer_box_roundness,
      outer_box_color,
      outer_box_thickness
   );

   return;
}

void SliderToggle::draw_pill(std::string text, float x, float y, float w, float h, ALLEGRO_COLOR box_color, ALLEGRO_COLOR text_color, float _font_size)
{
   ALLEGRO_FONT *font = obtain_font(_font_size);
   float text_height = al_get_font_line_height(font);
   float center_x = int(x + w / 2);
   float center_y = int(y - text_height/2 + h/2);
   float inner_box_roundness = 10.0f;

   al_draw_filled_rounded_rectangle(
      x, y, x+w, y+h,
      inner_box_roundness,
      inner_box_roundness,
      box_color
   );
   al_draw_text(font, text_color, center_x, center_y, ALLEGRO_ALIGN_CENTER, text.c_str());
}

ALLEGRO_FONT* SliderToggle::obtain_font(float _font_size)
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[SliderToggle::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SliderToggle::obtain_font: error: guard \"font_bin\" not met");
   }
   std::stringstream ss;
   ss << "Inter-Medium.ttf " << _font_size;
   return font_bin->auto_get(ss.str().c_str());
}


} // namespace UI
} // namespace Elements
} // namespace AllegroFlare


