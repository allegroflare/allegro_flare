#pragma once


#include <string>


#define ALLEGRO_FLARE_VERSION "0.8.11wip"


namespace AllegroFlare
{
   class Version
   {
   public:
      std::string get_allegro_version_string();
      std::string get_allegro_flare_version_string();
      std::string get_cpp_version_string();
   };
} // namespace AllegroFlare


