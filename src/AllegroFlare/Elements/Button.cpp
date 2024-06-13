

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
   , text_font_name("Inter-Regular.ttf")
   , text_font_size(-28)
   , core_color(AllegroFlare::Color::PaleGreen)
   , started_at(0.0f)
   , x(0.0f)
   , y(0.0f)
   , padding_x(32.0f)
   , padding_y(12.0f)
   , alignment_strategy(AllegroFlare::Elements::Button::Alignments::ALIGNED_AT_TEXT_ORIGIN)
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


void Button::set_core_color(ALLEGRO_COLOR core_color)
{
   this->core_color = core_color;
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


void Button::set_padding_x(float padding_x)
{
   this->padding_x = padding_x;
}


void Button::set_padding_y(float padding_y)
{
   this->padding_y = padding_y;
}


void Button::set_alignment_strategy(AllegroFlare::Elements::Button::Alignments alignment_strategy)
{
   this->alignment_strategy = alignment_strategy;
}


AllegroFlare::FontBin* Button::get_font_bin() const
{
   return font_bin;
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


ALLEGRO_COLOR Button::get_core_color() const
{
   return core_color;
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


float Button::get_padding_x() const
{
   return padding_x;
}


float Button::get_padding_y() const
{
   return padding_y;
}


AllegroFlare::Elements::Button::Alignments Button::get_alignment_strategy() const
{
   return alignment_strategy;
}


void Button::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   // TODO: consider a mechanism that flags width/height as dirty
   this->font_bin = font_bin;
   return;
}

float Button::infer_box_width()
{
   ALLEGRO_FONT *button_font = obtain_button_font();
   float text_width = al_get_text_width(button_font, text.c_str());
   return text_width + padding_x * 2;
}

float Button::infer_box_height()
{
   ALLEGRO_FONT *button_font = obtain_button_font();
   float text_height = al_get_font_line_height(button_font);
   return text_height + padding_y * 2;
}

void Button::align_to_center()
{
   alignment_strategy = AllegroFlare::Elements::Button::Alignments::CENTERED;
   return;
}

void Button::align_to_right_centered()
{
   alignment_strategy = AllegroFlare::Elements::Button::Alignments::RIGHT_CENTERED;
   return;
}

void Button::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Button::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Button::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Button::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Button::render]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(al_is_ttf_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Button::render]: error: guard \"al_is_ttf_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Button::render]: error: guard \"al_is_ttf_addon_initialized()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Button::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Button::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Button::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Button::render]: error: guard \"font_bin\" not met");
   }
   float age = infer_age();
   ALLEGRO_FONT *button_font = obtain_button_font();
   ALLEGRO_COLOR button_text_color = core_color;
   float button_frame_opacity = ((1.5 - fmod(age, 1.5)) / 1.5) * 0.75 + 0.25;
   ALLEGRO_COLOR button_frame_color = AllegroFlare::color::mix(
         core_color, AllegroFlare::Color::Transparent, 1.0 - button_frame_opacity);
   float thickness = 4.0f;
   float roundness = thickness * 1.5;

   AllegroFlare::Placement2D button_placement = build_button_placement_based_on_alignment_strategy();

   float reveal_duration = 0.6f;
   if (age < reveal_duration)
   {
      // modify params by the reveal animation offsets
      float normalized_time = std::max(0.0f, std::min(1.0f, age / reveal_duration));
      float inv_normalized_time = 1.0 - normalized_time;
      float reveal_y_offset = 30;
      ALLEGRO_COLOR reveal_color = AllegroFlare::Color::Transparent;

      button_text_color = AllegroFlare::color::mix(
            reveal_color, button_text_color, normalized_time);
      button_frame_color = AllegroFlare::color::mix(
            reveal_color, button_frame_color, normalized_time);
      button_placement.position.y += reveal_y_offset * AllegroFlare::interpolator::tripple_fast_out(inv_normalized_time);
   }

   button_placement.start_transform();

   // draw the cursor outline
   al_draw_rounded_rectangle(
      0,
      0,
      infer_box_width(),
      infer_box_height(),
      roundness,
      roundness,
      button_frame_color,
      thickness
   );

   // draw the text
   al_draw_text(button_font, button_text_color, padding_x, padding_y, ALLEGRO_ALIGN_LEFT, text.c_str());

   button_placement.restore_transform();

   return;
}

AllegroFlare::Placement2D Button::build_button_placement_based_on_alignment_strategy()
{
   AllegroFlare::Placement2D result;
   switch (alignment_strategy)
   {
      case AllegroFlare::Elements::Button::Alignments::ALIGNED_AT_TEXT_ORIGIN:
         result.position.x = x - padding_x;
         result.position.y = y - padding_y;
      break;

      case AllegroFlare::Elements::Button::Alignments::CENTERED:
         result.position.x = x;
         result.position.y = y;
         result.size.x = infer_box_width();
         result.size.y = infer_box_height();
         result.align.x = 0.5;
         result.align.y = 0.5;
      break;

      case AllegroFlare::Elements::Button::Alignments::RIGHT_CENTERED:
         result.position.x = x;
         result.position.y = y;
         result.size.x = infer_box_width();
         result.size.y = infer_box_height();
         result.align.x = 1.0;
         result.align.y = 0.5;
      break;

      default:
         // TODO: Replace with AllegroFlare::Logger error
         throw std::runtime_error("Elements/Button::build_button_placement_based_on_alignment_strategy: error: "
                     "Unhandled Alignments type"
                  );
      break;
   }
   return result;
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


