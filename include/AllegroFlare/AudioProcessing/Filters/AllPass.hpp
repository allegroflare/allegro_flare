#pragma once


#include <AllegroFlare/AudioProcessing/AudioDataBlock.hpp>
#include <AllegroFlare/AudioProcessing/AudioMixer.hpp>
#include <allegro5/allegro_audio.h>


namespace AllegroFlare
{
   namespace AudioProcessing
   {
      namespace Filters
      {
         class AllPass
         {
         private:
            float offset_sec;
            float gain;
            float wet;
            float dry;
            AllegroFlare::AudioProcessing::AudioMixer mixer;
            AllegroFlare::AudioProcessing::AudioDataBlock data_block;
            bool initialized;

         protected:


         public:
            AllPass(float offset_sec=1.0, float gain=0.7, float wet=1.0, float dry=1.0);
            ~AllPass();

            float get_offset_sec() const;
            float get_gain() const;
            float get_wet() const;
            float get_dry() const;
            AllegroFlare::AudioProcessing::AudioDataBlock &get_data_block_ref();
            void set_offset_sec(float offset_sec=1.0f);
            void set_gain(float gain=1.0f);
            void set_wet(float wet=1.0f);
            void set_dry(float dry=1.0f);
            ALLEGRO_MIXER* get_al_mixer();
            void initialize();
            static void mixer_postprocess_callback(void* buf=nullptr, unsigned int samples=0, void* data=nullptr);
         };
      }
   }
}



