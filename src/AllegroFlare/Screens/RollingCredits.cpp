

#include <AllegroFlare/Screens/RollingCredits.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Screens
{


RollingCredits::RollingCredits(AllegroFlare::FontBin* font_bin, AllegroFlare::Elements::RollingCredits::RollingCredits rolling_credits_component, float surface_width, float surface_height)
   : AllegroFlare::Screens::Base("RollingCredits")
   , font_bin(font_bin)
   , rolling_credits_component(rolling_credits_component)
   , surface_width(surface_width)
   , surface_height(surface_height)
   , y_offset(0.0f)
   , y_speed(2.0f)
   , initialized(false)
{
}


RollingCredits::~RollingCredits()
{
}


void RollingCredits::set_surface_width(float surface_width)
{
   this->surface_width = surface_width;
}


void RollingCredits::set_surface_height(float surface_height)
{
   this->surface_height = surface_height;
}


void RollingCredits::set_y_offset(float y_offset)
{
   this->y_offset = y_offset;
}


void RollingCredits::set_y_speed(float y_speed)
{
   this->y_speed = y_speed;
}


AllegroFlare::Elements::RollingCredits::RollingCredits RollingCredits::get_rolling_credits_component()
{
   return rolling_credits_component;
}


float RollingCredits::get_surface_width()
{
   return surface_width;
}


float RollingCredits::get_surface_height()
{
   return surface_height;
}


float RollingCredits::get_y_offset()
{
   return y_offset;
}


float RollingCredits::get_y_speed()
{
   return y_speed;
}


AllegroFlare::Elements::RollingCredits::RollingCredits &RollingCredits::get_rolling_credits_component_ref()
{
   return rolling_credits_component;
}


float &RollingCredits::get_y_offset_ref()
{
   return y_offset;
}


float &RollingCredits::get_y_speed_ref()
{
   return y_speed;
}


void RollingCredits::on_activate()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "RollingCredits" << "::" << "on_activate" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   y_offset = 0;
   return;
}

void RollingCredits::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (!((!initialized)))
      {
         std::stringstream error_message;
         error_message << "RollingCredits" << "::" << "set_font_bin" << ": error: " << "guard \"(!initialized)\" not met";
         throw std::runtime_error(error_message.str());
      }
   this->font_bin = font_bin;
   return;
}

void RollingCredits::set_sections(std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> sections)
{
   rolling_credits_component.set_sections(sections);
   return;
}

void RollingCredits::initialize()
{
   if (!((!initialized)))
      {
         std::stringstream error_message;
         error_message << "RollingCredits" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "RollingCredits" << "::" << "initialize" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   rolling_credits_component.set_font_bin(font_bin);
   rolling_credits_component.initialize();
   return;
}

void RollingCredits::update()
{
   y_offset += y_speed;
   return;
}

void RollingCredits::render()
{
   rolling_credits_component.set_y_offset(y_offset);
   rolling_credits_component.render();
   return;
}

void RollingCredits::primary_timer_func()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "RollingCredits" << "::" << "primary_timer_func" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "RollingCredits" << "::" << "primary_timer_func" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   update();
   render();
   return;
}
} // namespace Screens
} // namespace AllegroFlare


