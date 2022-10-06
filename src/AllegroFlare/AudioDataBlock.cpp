

#include <AllegroFlare/AudioDataBlock.hpp>




namespace AllegroFlare
{


AudioDataBlock::AudioDataBlock(ALLEGRO_AUDIO_DEPTH depth_type)
   : block({})
   , depth_type(depth_type)
   , depth_type_size(al_get_audio_depth_size(depth_type))
   , frequency(44100)
   , channel_configuration(ALLEGRO_CHANNEL_CONF_2)
   , channel_count(al_get_channel_count(ALLEGRO_CHANNEL_CONF_2))
   , initialized(false)
{
}


AudioDataBlock::~AudioDataBlock()
{
}


ALLEGRO_AUDIO_DEPTH AudioDataBlock::get_depth_type() const
{
   return depth_type;
}


std::size_t AudioDataBlock::get_depth_type_size() const
{
   return depth_type_size;
}


unsigned int AudioDataBlock::get_frequency() const
{
   return frequency;
}


ALLEGRO_CHANNEL_CONF AudioDataBlock::get_channel_configuration() const
{
   return channel_configuration;
}


std::size_t AudioDataBlock::get_channel_count() const
{
   return channel_count;
}


void AudioDataBlock::initialize()
{
   block.resize(SAMPLE_COUNT * channel_count);
   initialized = true;
}

float AudioDataBlock::get_sample_at(int sample_position, int channel_t)
{
   return block[(sample_position * channel_count) + channel_t];
}

void AudioDataBlock::set_sample_at(int sample_position, int channel_t, float value)
{
   in_place_clamp_loop_sample_position(&sample_position);

   block[(sample_position * channel_count) + channel_t] = value;
}

void AudioDataBlock::set_sample_at(int sample_position, float left_channel_value, float right_channel_value)
{
   in_place_clamp_loop_sample_position(&sample_position);

   block[sample_position + CHANNEL_LEFT] = left_channel_value;
   block[sample_position + CHANNEL_RIGHT] = right_channel_value;
}

std::pair<float, float> AudioDataBlock::get_sample_at(int sample_position, float left_channel_value, float right_channel_value)
{
   in_place_clamp_loop_sample_position(&sample_position);

   return std::pair<float, float>{
      block[(sample_position * channel_count) + CHANNEL_LEFT],
      block[(sample_position * channel_count) + CHANNEL_RIGHT],
   };
}

void AudioDataBlock::in_place_clamp_loop_sample_position(int* sample_position)
{
   while (*sample_position >= SAMPLE_COUNT) *sample_position -= SAMPLE_COUNT;
   while (*sample_position < 0) *sample_position += SAMPLE_COUNT;
   return ;
}


} // namespace AllegroFlare


