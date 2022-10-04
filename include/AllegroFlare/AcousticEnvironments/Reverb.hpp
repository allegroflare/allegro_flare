#pragma once


#include <AllegroFlare/AcousticEnvironments/Base.hpp>
#include <allegro5/allegro_audio.h>
#include <cstddef>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace AcousticEnvironments
   {
      class Reverb : public AllegroFlare::AcousticEnvironments::Base
      {
      public:
         static constexpr char* TYPE = "AcousticEnvironments/Reverb";
         static constexpr int PROCESSING_BUFFER_INITIAL_SIZE = 2048;

      private:
         std::string property;
         ALLEGRO_MIXER* master_mixer;
         ALLEGRO_MIXER* reverb_mixer;
         ALLEGRO_AUDIO_DEPTH reverb_mixer_depth;
         std::size_t reverb_mixer_depth_size;
         unsigned int reverb_mixer_frequency;
         ALLEGRO_CHANNEL_CONF reverb_mixer_channel_configuration;
         std::size_t reverb_mixer_channel_count;
         bool initialized;
         std::vector<float> processing_buffer;
         std::vector<float> swap_buffer;

      protected:


      public:
         Reverb(std::string property="[unset-property]");
         ~Reverb();

         std::string get_property() const;
         ALLEGRO_AUDIO_DEPTH get_reverb_mixer_depth() const;
         std::size_t get_reverb_mixer_depth_size() const;
         unsigned int get_reverb_mixer_frequency() const;
         ALLEGRO_CHANNEL_CONF get_reverb_mixer_channel_configuration() const;
         std::size_t get_reverb_mixer_channel_count() const;
         ALLEGRO_MIXER* get_reverb_mixer();
         static void mixer_postprocess_callback(void* buf=nullptr, unsigned int samples=0, void* data=nullptr);
         void initialize();
      };
   }
}



