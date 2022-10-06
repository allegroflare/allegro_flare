

#include <AllegroFlare/AudioDataBlock.hpp>

#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


AudioDataBlock::AudioDataBlock(ALLEGRO_AUDIO_DEPTH depth_type)
   : block({})
   , depth_type(depth_type)
   , depth_type_size(al_get_audio_depth_size(depth_type))
   , frequency(44100)
   , channel_configuration(ALLEGRO_CHANNEL_CONF_2)
   , channel_count(al_get_channel_count(ALLEGRO_CHANNEL_CONF_2))
   , sample_count(2048)
   , head(0)
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


std::size_t AudioDataBlock::get_sample_count() const
{
   return sample_count;
}


void AudioDataBlock::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "AudioDataBlock" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   block.resize(sample_count * channel_count);
   initialized = true;
}

void AudioDataBlock::set_sample_count(std::size_t sample_count)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "AudioDataBlock" << "::" << "set_sample_count" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!((sample_count > 0)))
   {
      std::stringstream error_message;
      error_message << "AudioDataBlock" << "::" << "set_sample_count" << ": error: " << "guard \"(sample_count > 0)\" not met";
      throw std::runtime_error(error_message.str());
   }
   this->sample_count = sample_count;
   return;
}

float AudioDataBlock::get_sample_at(int sample_position, int channel_t)
{
   sample_position = clamp_loop_sample_position(head + sample_position);

   return block[(sample_position * channel_count) + channel_t];
}

void AudioDataBlock::set_sample_at(int sample_position, int channel_t, float value)
{
   sample_position = clamp_loop_sample_position(head + sample_position);

   block[(sample_position * channel_count) + channel_t] = value;
}

void AudioDataBlock::set_sample_at(int sample_position, float left_channel_value, float right_channel_value)
{
   sample_position = clamp_loop_sample_position(head + sample_position);

   block[sample_position + CHANNEL_LEFT] = left_channel_value;
   block[sample_position + CHANNEL_RIGHT] = right_channel_value;
}

std::pair<float, float> AudioDataBlock::get_sample_at(int sample_position, float left_channel_value, float right_channel_value)
{
   sample_position = clamp_loop_sample_position(head + sample_position);

   return std::pair<float, float>{
      block[(sample_position * channel_count) + CHANNEL_LEFT],
      block[(sample_position * channel_count) + CHANNEL_RIGHT],
   };
}

int AudioDataBlock::clamp_loop_sample_position(int sample_position)
{
   while (sample_position >= sample_count) sample_position -= sample_count;
   while (sample_position < 0) sample_position += sample_count;
   return sample_position;
}


} // namespace AllegroFlare


