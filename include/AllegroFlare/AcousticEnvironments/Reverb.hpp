#pragma once


#include <AllegroFlare/AcousticEnvironments/Base.hpp>
#include <allegro5/allegro_audio.h>
#include <string>


namespace AllegroFlare
{
   namespace AcousticEnvironments
   {
      class Reverb : public AllegroFlare::AcousticEnvironments::Base
      {
      public:
         static constexpr char* TYPE = "AcousticEnvironments/Reverb";

      private:
         std::string property;
         ALLEGRO_MIXER* master_mixer;
         bool initialized;

      protected:


      public:
         Reverb(std::string property="[unset-property]");
         ~Reverb();

         std::string get_property() const;
         void initialize();
      };
   }
}



