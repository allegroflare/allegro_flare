

#include <AllegroFlare/MotionFX/Sparkles.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <AllegroFlare/Color.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


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


float Sparkles::get_x()
{
   return x;
}


float Sparkles::get_y()
{
   return y;
}


float Sparkles::get_created_at()
{
   return created_at;
}


bool Sparkles::get_initialized()
{
   return initialized;
}


void Sparkles::initialize()
{
   if (!((!initialized)))
      {
         std::stringstream error_message;
         error_message << "Sparkles" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
         throw std::runtime_error(error_message.str());
      }
   static const float TAU = 6.28318531;
   float num_particles = 7;
          // distance,   rotation,   opacity,    color
   particles = {
      { 20, TAU / 7.0, 1.0, AllegroFlare::Color::Gold }
   };
   initialized = true;
   return;
}

void Sparkles::update()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Sparkles" << "::" << "update" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   // update the particles
   float rotation_speed = 0.02;
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
         error_message << "Sparkles" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "Sparkles" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Sparkles" << "::" << "render" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   ALLEGRO_COLOR star_color = AllegroFlare::Color::Gold;
   draw_centered_unicode_character(obtain_icon_font(), star_color, x, y);
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
         error_message << "Sparkles" << "::" << "obtain_icon_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("fa-solid-900.ttf -50");
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


