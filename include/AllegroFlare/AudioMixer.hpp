#pragma once


#include <allegro5/allegro_audio.h>
#include <cstddef>


namespace AllegroFlare
{
   class AudioMixer
   {
   private:
      ALLEGRO_MIXER* parent_mixer;
      ALLEGRO_MIXER* mixer;
      ALLEGRO_AUDIO_DEPTH audio_depth;
      std::size_t audio_depth_size;
      unsigned int frequency;
      ALLEGRO_CHANNEL_CONF channel_configuration;
      std::size_t channel_count;
      bool initialized;

   protected:


   public:
      AudioMixer();
      ~AudioMixer();

      ALLEGRO_AUDIO_DEPTH get_audio_depth() const;
      std::size_t get_audio_depth_size() const;
      unsigned int get_frequency() const;
      ALLEGRO_CHANNEL_CONF get_channel_configuration() const;
      std::size_t get_channel_count() const;
      ALLEGRO_MIXER* get_mixer();
      void validate_configuration();
      void initialize();
      void set_postprocess_callback(void (*callback)(void*, unsigned int, void*) /*callback*/=nullptr, void* user_data=nullptr);
   };
}



