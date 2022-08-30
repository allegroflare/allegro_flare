#pragma once


#include <cstdint>
#include <string>


namespace AllegroFlare
{
   class SystemInfo
   {
   private:

   public:
      SystemInfo();
      ~SystemInfo();

      std::string allegro_flare_version();
      std::string allegro_version();
      uint32_t num_available_threads();
      bool num_available_threads_are_known();
      std::string operating_system();
   };
}



