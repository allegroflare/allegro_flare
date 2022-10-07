#pragma once


#include <AllegroFlare/AudioDataBlock.hpp>
#include <AllegroFlare/AudioMixer.hpp>
#include <allegro5/allegro_audio.h>


namespace AllegroFlare
{
   namespace AudioProcessing
   {
      class Delay
      {
      private:
         float delay_sec;
         float decay;
         AllegroFlare::AudioMixer mixer;
         AllegroFlare::AudioDataBlock data_block;
         bool initialized;

      protected:


      public:
         Delay(float delay_sec=1.0, float decay=0.8);
         ~Delay();

         float get_delay_sec() const;
         float get_decay() const;
         AllegroFlare::AudioDataBlock &get_data_block_ref();
         void set_delay_sec(float delay_sec=1.0f);
         ALLEGRO_MIXER* get_al_mixer();
         void initialize();
         static void mixer_postprocess_callback(void* buf=nullptr, unsigned int samples=0, void* data=nullptr);
      };
   }
}



