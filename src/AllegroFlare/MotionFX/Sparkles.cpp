

#include <AllegroFlare/MotionFX/Sparkles.hpp>

#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace MotionFX
{


Sparkles::Sparkles(AllegroFlare::FontBin* font_bin, float x, float y)
   : font_bin(font_bin)
   , x(x)
   , y(y)
   , particles({})
   , created_at(0)
   , initialized(false)
   , main_star_placement({})
{
}


Sparkles::~Sparkles()
{
}


void Sparkles::set_x(float x)
{
   this->x = x;
}


void Sparkles::set_y(float y)
{
   this->y = y;
}


void Sparkles::set_created_at(float created_at)
{
   this->created_at = created_at;
}


float Sparkles::get_x() const
{
   return x;
}


float Sparkles::get_y() const
{
   return y;
}


float Sparkles::get_created_at() const
{
   return created_at;
}


bool Sparkles::get_initialized() const
{
   return initialized;
}


void Sparkles::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MotionFX::Sparkles::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MotionFX::Sparkles::initialize]: error: guard \"(!initialized)\" not met");
   }
   static const float TAU = 6.28318531;
   float num_particles = 7;
   float distance = 80;
          // distance,   rotation,   opacity,    color
   particles = {
      { distance, TAU / 7.0 * 0, 1.0, AllegroFlare::Color::Gold },
      { distance, TAU / 7.0 * 1, 1.0, AllegroFlare::Color::Gold },
      { distance, TAU / 7.0 * 2, 1.0, AllegroFlare::Color::Gold },
      { distance, TAU / 7.0 * 3, 1.0, AllegroFlare::Color::Gold },
      { distance, TAU / 7.0 * 4, 1.0, AllegroFlare::Color::Gold },
      { distance, TAU / 7.0 * 5, 1.0, AllegroFlare::Color::Gold },
      { distance, TAU / 7.0 * 6, 1.0, AllegroFlare::Color::Gold },
   };

   main_star_placement = Placement2D(x, y, 0, 0);

   initialized = true;
   return;
}

void Sparkles::update()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MotionFX::Sparkles::update]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MotionFX::Sparkles::update]: error: guard \"initialized\" not met");
   }
   float rotation_speed = -0.04;

   // update the main star
   main_star_placement.rotation += (rotation_speed * 0.5);

   // update the particles
   for (auto &particle : particles)
   {
      float &particle_rotation = std::get<1>(particle);
      particle_rotation += rotation_speed;
   }
   return;
}

void Sparkles::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MotionFX::Sparkles::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MotionFX::Sparkles::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MotionFX::Sparkles::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MotionFX::Sparkles::render]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MotionFX::Sparkles::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MotionFX::Sparkles::render]: error: guard \"initialized\" not met");
   }
   ALLEGRO_COLOR star_color = AllegroFlare::Color::Gold;

   // draw the main star
   main_star_placement.start_transform();
   draw_centered_unicode_character(obtain_icon_font(), star_color, 0, 0);
   main_star_placement.restore_transform();

   // draw the particle stars
   for (auto &particle : particles)
   {
      float distance = std::get<0>(particle);
      float rotation = std::get<1>(particle);
      float opacity = std::get<2>(particle);
      ALLEGRO_COLOR color = std::get<3>(particle);

      float final_x = sin(rotation) * distance;
      float final_y = cos(rotation) * distance;

      draw_centered_unicode_character(obtain_mini_icon_font(), color, x + final_x, y + final_y);
   }

   return;
}

void Sparkles::is_finished()
{
   return;
}

float Sparkles::infer_age()
{
   return al_get_time() - created_at;
}

ALLEGRO_FONT* Sparkles::obtain_icon_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MotionFX::Sparkles::obtain_icon_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MotionFX::Sparkles::obtain_icon_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("fa-solid-900.ttf -50");
}

ALLEGRO_FONT* Sparkles::obtain_mini_icon_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MotionFX::Sparkles::obtain_mini_icon_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MotionFX::Sparkles::obtain_mini_icon_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("fa-solid-900.ttf -30");
}

void Sparkles::draw_centered_unicode_character(ALLEGRO_FONT* font, ALLEGRO_COLOR color, int x, int y, uint32_t icon, int flags)
{
   static ALLEGRO_USTR *ustr = NULL;
   if (!ustr) ustr = al_ustr_new("");
   al_ustr_set_chr(ustr, 0, icon);
   float width = al_get_ustr_width(font, ustr);
   float height = al_get_font_line_height(font);
   al_draw_ustr(font, color, x-width*0.5, y-height*0.5, flags, ustr);
   return;
}


} // namespace MotionFX
} // namespace AllegroFlare


