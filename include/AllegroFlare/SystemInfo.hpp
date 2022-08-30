#pragma once


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
      unsigned int num_available_threads();
      bool num_available_threads_are_known();
      std::string operating_system();
   };
}



