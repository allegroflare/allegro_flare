

#include <AllegroFlare/Elements/StoryboardPages/Image.hpp>

#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Interpolators.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace StoryboardPages
{


Image::Image(ALLEGRO_BITMAP* bitmap, std::string reveal_style, float duration_to_advance_sec)
   : AllegroFlare::Elements::StoryboardPages::Base("Image")
   , bitmap(bitmap)
   , reveal_style(reveal_style)
   , duration_to_advance_sec(duration_to_advance_sec)
   , started_at(0.0f)
{
}


Image::~Image()
{
}


void Image::set_bitmap(ALLEGRO_BITMAP* bitmap)
{
   this->bitmap = bitmap;
}


void Image::set_reveal_style(std::string reveal_style)
{
   this->reveal_style = reveal_style;
}


void Image::set_duration_to_advance_sec(float duration_to_advance_sec)
{
   this->duration_to_advance_sec = duration_to_advance_sec;
}


ALLEGRO_BITMAP* Image::get_bitmap() const
{
   return bitmap;
}


std::string Image::get_reveal_style() const
{
   return reveal_style;
}


float Image::get_duration_to_advance_sec() const
{
   return duration_to_advance_sec;
}


float Image::get_started_at() const
{
   return started_at;
}


void Image::start()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::StoryboardPages::Image::start]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::StoryboardPages::Image::start]: error: guard \"al_is_system_installed()\" not met");
   }
   started_at = al_get_time();
   set_finished(false);
   return;
}

void Image::update()
{
   if (infer_age() >= duration_to_advance_sec) set_finished(true);
   return;
}

void Image::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::StoryboardPages::Image::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::StoryboardPages::Image::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_get_current_display()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::StoryboardPages::Image::render]: error: guard \"al_get_current_display()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::StoryboardPages::Image::render]: error: guard \"al_get_current_display()\" not met");
   }
   if (!bitmap) return;

   AllegroFlare::Placement2D image_place;
   image_place.position.x = 1920/2;
   image_place.position.y = 1080/2;
   image_place.size.x = al_get_bitmap_width(bitmap);
   image_place.size.y = al_get_bitmap_height(bitmap);

   ALLEGRO_COLOR color{1, 1, 1, 1};

   modify_params_for_reveal(&image_place, &color);
   modify_params_for_hide(&image_place, &color);

   image_place.start_transform();
   al_draw_tinted_bitmap(bitmap, color, 0, 0, 0);
   image_place.restore_transform();

   return;
}

void Image::advance()
{
   set_finished(true);
   return;
}

float Image::infer_age()
{
   return al_get_time() - started_at;
}

void Image::modify_params_for_hide(AllegroFlare::Placement2D* place, ALLEGRO_COLOR* color)
{
   if (!(place))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::StoryboardPages::Image::modify_params_for_hide]: error: guard \"place\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::StoryboardPages::Image::modify_params_for_hide]: error: guard \"place\" not met");
   }
   if (!(color))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::StoryboardPages::Image::modify_params_for_hide]: error: guard \"color\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::StoryboardPages::Image::modify_params_for_hide]: error: guard \"color\" not met");
   }
   float age = infer_age();

   if (reveal_style == "fade")
   {
      float hide_duration = 0.6f;
      if (age > (duration_to_advance_sec - hide_duration))
      {
         float start_time = duration_to_advance_sec - hide_duration;
         float end_time = duration_to_advance_sec;
         float normalized_time = 1.0 - ((end_time - age) / hide_duration);

         //float normalized_time = std::max(0.0f, std::min(1.0f, age / hide_duration));
         //float normalized_time = 0.5;

         float inv_normalized_time = 1.0 - normalized_time;
         float hide_scale_offset = -0.1;

         //float reveal_opacity = 0.5;
         //ALLEGRO_COLOR reveal_color = AllegroFlare::Color::Indigo;
         ALLEGRO_COLOR hide_to_color = AllegroFlare::Color::Transparent;

         *color = AllegroFlare::color::mix(*color, hide_to_color, normalized_time);
         *color = AllegroFlare::color::mix(*color, hide_to_color, normalized_time);
         //place->scale.x = 1.0 + hide_scale_offset * AllegroFlare::interpolator::slow_in(normalized_time);
         //place->scale.y = 1.0 + hide_scale_offset * AllegroFlare::interpolator::slow_in(normalized_time);
       }
   }
   else if (reveal_style == "reveal")
   {
      float hide_duration = 0.6f;
      if (age > (duration_to_advance_sec - hide_duration))
      {
         float start_time = duration_to_advance_sec - hide_duration;
         float end_time = duration_to_advance_sec;
         float normalized_time = 1.0 - ((end_time - age) / hide_duration);

         //float normalized_time = std::max(0.0f, std::min(1.0f, age / hide_duration));
         //float normalized_time = 0.5;

         float inv_normalized_time = 1.0 - normalized_time;
         float hide_scale_offset = -0.1;

         //float reveal_opacity = 0.5;
         //ALLEGRO_COLOR reveal_color = AllegroFlare::Color::Indigo;
         ALLEGRO_COLOR hide_to_color = AllegroFlare::Color::Transparent;

         *color = AllegroFlare::color::mix(*color, hide_to_color, normalized_time);
         *color = AllegroFlare::color::mix(*color, hide_to_color, normalized_time);
         //place->scale.x = 1.0 + hide_scale_offset * AllegroFlare::interpolator::slow_in(normalized_time);
         //place->scale.y = 1.0 + hide_scale_offset * AllegroFlare::interpolator::slow_in(normalized_time);
       }
   }

   return;
}

void Image::modify_params_for_reveal(AllegroFlare::Placement2D* place, ALLEGRO_COLOR* color)
{
   if (!(place))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::StoryboardPages::Image::modify_params_for_reveal]: error: guard \"place\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::StoryboardPages::Image::modify_params_for_reveal]: error: guard \"place\" not met");
   }
   if (!(color))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::StoryboardPages::Image::modify_params_for_reveal]: error: guard \"color\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::StoryboardPages::Image::modify_params_for_reveal]: error: guard \"color\" not met");
   }
   float age = infer_age();

   if (reveal_style == "reveal")
   {
      float reveal_duration = 0.8f;
      if (age < reveal_duration)
      {
         float normalized_time = std::max(0.0f, std::min(1.0f, age / reveal_duration));
         float inv_normalized_time = 1.0 - normalized_time;
         float reveal_scale_offset = 0.2;
         //float reveal_opacity = 0.5;
         //ALLEGRO_COLOR reveal_color = AllegroFlare::Color::Indigo;
         ALLEGRO_COLOR reveal_from_color = AllegroFlare::Color::Transparent;

         *color = AllegroFlare::color::mix(reveal_from_color, *color, normalized_time);
         *color = AllegroFlare::color::mix(reveal_from_color, *color, normalized_time);
         place->scale.x = 1.0 + reveal_scale_offset * AllegroFlare::interpolator::double_slow_in(inv_normalized_time);
         place->scale.y = 1.0 + reveal_scale_offset * AllegroFlare::interpolator::double_slow_in(inv_normalized_time);
       }
   }
   else if (reveal_style == "fade")
   {
      float reveal_duration = 0.8f;
      if (age < reveal_duration)
      {
         float normalized_time = std::max(0.0f, std::min(1.0f, age / reveal_duration));
         float inv_normalized_time = 1.0 - normalized_time;
         //float reveal_scale_offset = 0.2;
         //float reveal_opacity = 0.5;
         //ALLEGRO_COLOR reveal_color = AllegroFlare::Color::Indigo;
         ALLEGRO_COLOR reveal_from_color = AllegroFlare::Color::Transparent;

         *color = AllegroFlare::color::mix(reveal_from_color, *color, normalized_time);
         *color = AllegroFlare::color::mix(reveal_from_color, *color, normalized_time);
         //place->scale.x = 1.0 + reveal_scale_offset * AllegroFlare::interpolator::double_slow_in(inv_normalized_time);
         //place->scale.y = 1.0 + reveal_scale_offset * AllegroFlare::interpolator::double_slow_in(inv_normalized_time);
       }
   }

   return;
}


} // namespace StoryboardPages
} // namespace Elements
} // namespace AllegroFlare


