

#include <AllegroFlare/MotionFX/Sparkles2.hpp>
#include <AllegroFlare/Timeline/Actor2D.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace MotionFX
{


Sparkles2::Sparkles2(AllegroFlare::FontBin* font_bin, float x, float y)
   : font_bin(font_bin)
   , x(x)
   , y(y)
   , actor_manager({})
   , initialized(false)
{
}


Sparkles2::~Sparkles2()
{
}


void Sparkles2::set_x(float x)
{
   this->x = x;
}


void Sparkles2::set_y(float y)
{
   this->y = y;
}


float Sparkles2::get_x()
{
   return x;
}


float Sparkles2::get_y()
{
   return y;
}


void Sparkles2::initialize()
{
   if (!((!initialized)))
      {
         std::stringstream error_message;
         error_message << "Sparkles2" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
         throw std::runtime_error(error_message.str());
      }
   Timeline::Actor2D actor;

   initialized = true;
   return;
}

void Sparkles2::update()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "Sparkles2" << "::" << "update" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "Sparkles2" << "::" << "update" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Sparkles2" << "::" << "update" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   return;
}

void Sparkles2::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "Sparkles2" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "Sparkles2" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Sparkles2" << "::" << "render" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   return;
}
} // namespace MotionFX
} // namespace AllegroFlare


