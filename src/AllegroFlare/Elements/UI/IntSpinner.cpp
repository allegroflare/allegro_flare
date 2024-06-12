

#include <AllegroFlare/Elements/UI/IntSpinner.hpp>

#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace UI
{


IntSpinner::IntSpinner(AllegroFlare::FontBin* font_bin, float x, float y, float width, float height, int font_size)
   : font_bin(font_bin)
   , x(x)
   , y(y)
   , width(width)
   , height(height)
   , font_size(font_size)
   , number(1920)
   , state(STATE_UNDEF)
   , state_is_busy(false)
   , state_changed_at(0.0f)
{
}


IntSpinner::~IntSpinner()
{
}


void IntSpinner::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void IntSpinner::set_x(float x)
{
   this->x = x;
}


void IntSpinner::set_y(float y)
{
   this->y = y;
}


void IntSpinner::set_width(float width)
{
   this->width = width;
}


void IntSpinner::set_height(float height)
{
   this->height = height;
}


void IntSpinner::set_font_size(int font_size)
{
   this->font_size = font_size;
}


void IntSpinner::set_number(int number)
{
   this->number = number;
}


AllegroFlare::FontBin* IntSpinner::get_font_bin() const
{
   return font_bin;
}


float IntSpinner::get_x() const
{
   return x;
}


float IntSpinner::get_y() const
{
   return y;
}


float IntSpinner::get_width() const
{
   return width;
}


float IntSpinner::get_height() const
{
   return height;
}


int IntSpinner::get_font_size() const
{
   return font_size;
}


int IntSpinner::get_number() const
{
   return number;
}


uint32_t IntSpinner::get_state() const
{
   return state;
}


void IntSpinner::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::UI::IntSpinner::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::UI::IntSpinner::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::UI::IntSpinner::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::UI::IntSpinner::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::UI::IntSpinner::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::UI::IntSpinner::render]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::UI::IntSpinner::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::UI::IntSpinner::render]: error: guard \"font_bin\" not met");
   }
   // Draw the number
   std::stringstream ss;
   ss << number;

   ALLEGRO_COLOR number_text_color = is_state(STATE_DISABLED)
                                   ? ALLEGRO_COLOR{0.29, 0.29, 0.29, 0.29}
                                   : ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0};
   draw_centered_text(ss.str(), x + width / 2, y + height / 2, number_text_color, font_size);

   // Outter box
   ALLEGRO_COLOR outer_box_color = is_state(STATE_ACTIVE_FOCUS)
                                 ? ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0}
                                 : ALLEGRO_COLOR{0.40, 0.40, 0.40, 0.40};
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

   if (is_state(STATE_ACTIVE_FOCUS))
   {
      // Draw triangles
      float triangle_padding = 12;
      float triangle_width = 40;
      float triangle_height = 20;
      float c_x = x+width*0.5 - triangle_width * 0.5;

      // Draw triangle up
      float ty = y - triangle_height - triangle_padding;
      draw_triangle_up(c_x, ty, triangle_width, triangle_height, ALLEGRO_COLOR{1, 1, 1, 1});

      // Draw triangle down
      float tdy = y + height + triangle_padding;
      draw_triangle_down(c_x, tdy, triangle_width, triangle_height, ALLEGRO_COLOR{1, 1, 1, 1});
   }

   return;
}

void IntSpinner::draw_centered_text(std::string text, float x, float y, ALLEGRO_COLOR text_color, float _font_size)
{
   ALLEGRO_FONT *font = obtain_font(_font_size);
   float text_height = al_get_font_line_height(font);
   float center_x = int(x);
   float center_y = int(y - text_height/2);
   float inner_box_roundness = 10.0f;

   al_draw_text(font, text_color, center_x, center_y, ALLEGRO_ALIGN_CENTER, text.c_str());
}

void IntSpinner::draw_triangle_right(float x, float y, float width, float height, ALLEGRO_COLOR color)
{
   x -= width;
   y -= height * 0.5;
   al_draw_filled_triangle(x, y, x+width, y+height*0.5, x, y+height, color);
   return;
}

void IntSpinner::draw_triangle_up(float x, float y, float width, float height, ALLEGRO_COLOR color)
{
   al_draw_filled_triangle(x, y+height, x+width*0.5, y, x+width, y+height, color);
   return;
}

void IntSpinner::draw_triangle_down(float x, float y, float width, float height, ALLEGRO_COLOR color)
{
   al_draw_filled_triangle(x, y, x+width, y, x+width*0.5, y+height, color);
   return;
}

void IntSpinner::set_state(uint32_t state, bool override_if_busy)
{
   if (!(is_valid_state(state)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::UI::IntSpinner::set_state]: error: guard \"is_valid_state(state)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::UI::IntSpinner::set_state]: error: guard \"is_valid_state(state)\" not met");
   }
   if (this->state == state) return;
   if (!override_if_busy && state_is_busy) return;
   uint32_t previous_state = this->state;

   switch (state)
   {
      case STATE_ENABLED:
      break;

      case STATE_DISABLED:
      break;

      case STATE_ACTIVE_FOCUS:
      break;

      default:
         throw std::runtime_error("weird error");
      break;
   }

   this->state = state;
   state_changed_at = al_get_time();

   return;
}

void IntSpinner::update_state(float time_now)
{
   if (!(is_valid_state(state)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::UI::IntSpinner::update_state]: error: guard \"is_valid_state(state)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::UI::IntSpinner::update_state]: error: guard \"is_valid_state(state)\" not met");
   }
   float age = infer_current_state_age(time_now);

   switch (state)
   {
      case STATE_ENABLED:
      break;

      case STATE_DISABLED:
      break;

      case STATE_ACTIVE_FOCUS:
      break;

      default:
         throw std::runtime_error("weird error");
      break;
   }

   return;
}

bool IntSpinner::is_valid_state(uint32_t state)
{
   std::set<uint32_t> valid_states =
   {
      STATE_ENABLED,
      STATE_DISABLED,
      STATE_ACTIVE_FOCUS,
   };
   return (valid_states.count(state) > 0);
}

bool IntSpinner::is_state(uint32_t possible_state)
{
   return (state == possible_state);
}

float IntSpinner::infer_current_state_age(float time_now)
{
   return (time_now - state_changed_at);
}

ALLEGRO_FONT* IntSpinner::obtain_font(float _font_size)
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::UI::IntSpinner::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::UI::IntSpinner::obtain_font]: error: guard \"font_bin\" not met");
   }
   std::stringstream ss;
   ss << "Inter-Medium.ttf " << _font_size;
   return font_bin->auto_get(ss.str().c_str());
}


} // namespace UI
} // namespace Elements
} // namespace AllegroFlare


