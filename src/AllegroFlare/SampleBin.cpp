

#include <AllegroFlare/SampleBin.hpp>

#include <allegro5/allegro_acodec.h>


namespace AllegroFlare
{
   SampleBin::SampleBin()
      : Bin<std::string, ALLEGRO_SAMPLE *>()
   {}


   SampleBin::~SampleBin()
   {
      clear();
   }


   bool SampleBin::validate()
   {
      // TODO investigate why this line does not return the output error regardless if acodec has not be initialized
      if (!al_is_acodec_addon_initialized())
      {
         std::cout << "[SampleBin::validate] not properly initialized (requires al_init_acodec_addon()). "
                   << " Will crash probably crash." << std::endl;
         return false;
      }
      return true;
   }


   ALLEGRO_SAMPLE *SampleBin::load_data(std::string identifier)
   {
      validate();
      return al_load_sample(identifier.c_str());
   }


   void SampleBin::destroy_data(ALLEGRO_SAMPLE *sample)
   {
      al_destroy_sample(sample);
   }
}


