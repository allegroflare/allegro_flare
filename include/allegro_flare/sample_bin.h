#ifndef __AF_SAMPLE_BIN_HEADER
#define __AF_SAMPLE_BIN_HEADER




#include <allegro5/allegro_audio.h>
#include <allegro_flare/bin.h>




class SampleBin : public Bin<ALLEGRO_SAMPLE *>
{
public:
   SampleBin(std::string directory="data/samples");
   ~SampleBin();
   ALLEGRO_SAMPLE *load_data(std::string identifier);
   void destroy_data(ALLEGRO_SAMPLE *sample);
};




#endif
