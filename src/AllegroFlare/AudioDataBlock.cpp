

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

float AudioDataBlock::get_sample_at(int position, int channel_t)
{
   return block[position + channel_t];
}

void AudioDataBlock::set_sample_at(int position, int channel_t, float value)
{
   block[position + channel_t] = value;
}

void AudioDataBlock::set_sample_at(int position, float left_channel_value, float right_channel_value)
{
   block[position + CHANNEL_LEFT] = left_channel_value;
   block[position + CHANNEL_RIGHT] = right_channel_value;
}


} // namespace AllegroFlare


