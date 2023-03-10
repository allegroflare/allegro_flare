

#include <AllegroFlare/Elements/Button.hpp>

#include <AllegroFlare/Clock.hpp>
#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Interpolators.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <algorithm>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


Button::Button(AllegroFlare::FontBin* font_bin)
   : font_bin(font_bin)
   , text("START")
   , text_font_name("Inter-Medium.ttf")
   , text_font_size(-28)
   , started_at(0)
   , x(0)
   , y(0)
{
}


Button::~Button()
{
}


void Button::set_text(std::string text)
{
   this->text = text;
}


void Button::set_text_font_name(std::string text_font_name)
{
   this->text_font_name = text_font_name;
}


void Button::set_text_font_size(int text_font_size)
{
   this->text_font_size = text_font_size;
}


void Button::set_started_at(float started_at)
{
   this->started_at = started_at;
}


void Button::set_x(float x)
{
   this->x = x;
}


void Button::set_y(float y)
{
   this->y = y;
}


std::string Button::get_text() const
{
   return text;
}


std::string Button::get_text_font_name() const
{
   return text_font_name;
}


int Button::get_text_font_size() const
{
   return text_font_size;
}


float Button::get_started_at() const
{
   return started_at;
}


float Button::get_x() const
{
   return x;
}


float Button::get_y() const
{
   return y;
}


void Button::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Button::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Button::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Button::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Button::render: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(al_is_ttf_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Button::render]: error: guard \"al_is_ttf_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Button::render: error: guard \"al_is_ttf_addon_initialized()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Button::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Button::render: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Button::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Button::render: error: guard \"font_bin\" not met");
   }
   // TODO: use these positions in tests
   //float x = 1920-400;
   //float y = 1080-300;
   float age = infer_age();
   ALLEGRO_FONT *button_font = obtain_button_font();
   ALLEGRO_COLOR button_color = AllegroFlare::Color::PaleGreen;
   //std::string text = "NEXT >";
   //if (at_last_advance)
   //{
      //button_color = AllegroFlare::Color::LemonChiffon;
      //text = "FINISH";
   //}
   float text_width = al_get_text_width(button_font, text.c_str());
   float text_height = al_get_font_line_height(button_font);
   ALLEGRO_COLOR button_text_color = button_color;
   float button_frame_opacity = ((1.5 - fmod(age, 1.5)) / 1.5) * 0.75 + 0.25;
   ALLEGRO_COLOR button_frame_color = AllegroFlare::color::mix(
         button_color, AllegroFlare::Color::Transparent, 1.0 - button_frame_opacity);
   float thickness = 4.0f;
   float roundness = thickness * 1.5;
   float padding_x = 32.0f;
   float padding_y = 12.0f;
   AllegroFlare::Placement2D button_place;
   button_place.position.x = x;
   button_place.position.y = y;

   float reveal_duration = 0.6f;
   if (age < reveal_duration)
   {
      // modify params by the reveal animation offsets
      float normalized_time = std::max(0.0f, std::min(1.0f, age / reveal_duration));
      float inv_normalized_time = 1.0 - normalized_time;
      float reveal_y_offset = 30;
      //float reveal_opacity = 0.5;
      //ALLEGRO_COLOR reveal_color = AllegroFlare::Color::Indigo;
      ALLEGRO_COLOR reveal_color = AllegroFlare::Color::Transparent;

      button_text_color = AllegroFlare::color::mix(
            reveal_color, button_text_color, normalized_time);
      button_frame_color = AllegroFlare::color::mix(
            reveal_color, button_frame_color, normalized_time);
      button_place.position.y += reveal_y_offset * AllegroFlare::interpolator::tripple_fast_out(inv_normalized_time);
   }

   button_place.start_transform();

   // draw the cursor outline
   al_draw_rounded_rectangle(
      -padding_x,
      -padding_y,
      text_width+padding_x,
      text_height+padding_y,
      roundness,
      roundness,
      button_frame_color,
      thickness
   );

   // draw the text
   al_draw_text(button_font, button_text_color, text_width/2, 0, ALLEGRO_ALIGN_CENTER, text.c_str());

   button_place.restore_transform();

   return;
}

float Button::infer_age()
{
   AllegroFlare::Clock clock;
   return clock.real_world_time_since(started_at);
}

ALLEGRO_FONT* Button::obtain_button_font()
{
   std::stringstream composite_font_str;
   composite_font_str << text_font_name << " " << text_font_size;
   return font_bin->auto_get(composite_font_str.str());
}


} // namespace Elements
} // namespace AllegroFlare


