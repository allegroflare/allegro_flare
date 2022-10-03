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
         ALLEGRO_MIXER* reverb_mixer;
         bool initialized;

      protected:


      public:
         Reverb(std::string property="[unset-property]");
         ~Reverb();

         std::string get_property() const;
         static void mixer_postprocess_callback(void* buf=nullptr, unsigned int samples=0, void* data=nullptr);
         void initialize();
      };
   }
}



