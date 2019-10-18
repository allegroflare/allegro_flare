

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


   ALLEGRO_SAMPLE *SampleBin::load_data(std::string identifier)
   {
      return al_load_sample(identifier.c_str());
   }


   void SampleBin::destroy_data(ALLEGRO_SAMPLE *sample)
   {
      al_destroy_sample(sample);
   }
}


