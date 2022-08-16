

#include <AllegroFlare/MotionFX/Sparkles.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace MotionFX
{


Sparkles::Sparkles(AllegroFlare::FontBin* font_bin)
   : font_bin(font_bin)
   , quote({})
   , created_at(0)
{
}


Sparkles::~Sparkles()
{
}


void Sparkles::set_created_at(float created_at)
{
   this->created_at = created_at;
}


float Sparkles::get_created_at()
{
   return created_at;
}


void Sparkles::update()
{
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
   return;
}

void Sparkles::is_finished()
{
   return;
}

ALLEGRO_FONT* Sparkles::obtain_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "Sparkles" << "::" << "obtain_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("Purista Medium.otf -32");
}
} // namespace MotionFX
} // namespace AllegroFlare


