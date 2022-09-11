#pragma once


#include <cstdint>
#include <string>


namespace AllegroFlare
{
   class SystemInfo
   {
   private:

   protected:


   public:
      SystemInfo();
      ~SystemInfo();

      std::string allegro_flare_version();
      std::string allegro_version();
      uint32_t num_available_threads();
      bool num_available_threads_are_known();
      std::string get_processor_type();
      std::string get_sysname();
      std::string get_version();
      std::string get_release();
      std::string get_hostname();
      std::string get_machine();
      std::string operating_system();
   };
}



