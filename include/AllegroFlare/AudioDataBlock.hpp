#pragma once


#include <allegro5/allegro_audio.h>
#include <cstddef>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   class AudioDataBlock
   {
   public:
      static constexpr int CHANNEL_LEFT = 0;
      static constexpr int CHANNEL_RIGHT = 1;

   private:
      std::vector<float> block;
      std::size_t sample_count;
      ALLEGRO_AUDIO_DEPTH depth_type;
      std::size_t depth_type_size;
      unsigned int frequency;
      ALLEGRO_CHANNEL_CONF channel_configuration;
      std::size_t channel_count;
      std::size_t sample_head_position;
      bool initialized;
      int clamp_loop_sample_position(int sample_position=0);

   protected:


   public:
      AudioDataBlock(std::size_t sample_count=2048, ALLEGRO_AUDIO_DEPTH depth_type=ALLEGRO_AUDIO_DEPTH_FLOAT32);
      ~AudioDataBlock();

      std::vector<float> get_block() const;
      std::size_t get_sample_count() const;
      ALLEGRO_AUDIO_DEPTH get_depth_type() const;
      std::size_t get_depth_type_size() const;
      unsigned int get_frequency() const;
      ALLEGRO_CHANNEL_CONF get_channel_configuration() const;
      std::size_t get_channel_count() const;
      std::size_t get_sample_head_position() const;
      void initialize();
      void move_sample_head_position_by(std::size_t delta=0);
      void set_sample_count(std::size_t sample_count=2048, bool clear=false);
      std::size_t get_block_size();
      float get_sample_at(int sample_position=0, int channel_t=CHANNEL_LEFT);
      void set_sample_at_mono(int sample_position=0, int channel_t=CHANNEL_LEFT, float value=0.0f);
      void set_sample_at(int sample_position=0, float left_channel_value=0.0f, float right_channel_value=0.0f);
      std::pair<float, float> get_sample_at(int sample_position=0, float left_channel_value=0.0f, float right_channel_value=0.0f);
   };
}



