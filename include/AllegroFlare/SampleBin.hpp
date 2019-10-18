#pragma once


#include <allegro5/allegro_audio.h>
#include <AllegroFlare/Bin.hpp>


namespace AllegroFlare
{
   class SampleBin : public Bin<std::string, ALLEGRO_SAMPLE *>
   {
   public:
      SampleBin();
      ~SampleBin();
      ALLEGRO_SAMPLE *load_data(std::string identifier);
      void destroy_data(ALLEGRO_SAMPLE *sample);
   };
}


