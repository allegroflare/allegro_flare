

#include <AllegroFlare/Version.hpp>


#include <allegro5/allegro.h>
#include <sstream>


namespace AllegroFlare
{


std::string Version::get_allegro_version_string()
{
   uint32_t version = al_get_allegro_version();
   int major = version >> 24;
   int minor = (version >> 16) & 255;
   int revision = (version >> 8) & 255;
   int release = version & 255;

   std::stringstream str;
   str << major << '.' << minor << '.' << revision << " - release " << release;
   return str.str();
}



std::string Version::get_allegro_flare_version_string()
{
   return ALLEGRO_FLARE_VERSION;
}



} // namespace AllegroFlare




