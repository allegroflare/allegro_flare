

#include <AllegroFlare/AudioProcessing/AudioDataBlock.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace AudioProcessing
{


AudioDataBlock::AudioDataBlock()
   : block({})
   , sample_count(2048)
   , depth_type(ALLEGRO_AUDIO_DEPTH_FLOAT32)
   , depth_type_size(al_get_audio_depth_size(depth_type))
   , frequency(44100)
   , channel_configuration(ALLEGRO_CHANNEL_CONF_2)
   , channel_count(2)
   , sample_head_position(0)
   , initialized(false)
{
}


AudioDataBlock::~AudioDataBlock()
{
}


std::vector<float> AudioDataBlock::get_block() const
{
   return block;
}


std::size_t AudioDataBlock::get_sample_count() const
{
   return sample_count;
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


std::size_t AudioDataBlock::get_sample_head_position() const
{
   return sample_head_position;
}


std::vector<float> &AudioDataBlock::get_block_ref()
{
   return block;
}


void AudioDataBlock::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AudioProcessing::AudioDataBlock::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AudioProcessing::AudioDataBlock::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!((sample_count > 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AudioProcessing::AudioDataBlock::initialize]: error: guard \"(sample_count > 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AudioProcessing::AudioDataBlock::initialize]: error: guard \"(sample_count > 0)\" not met");
   }
   channel_count = al_get_channel_count(channel_configuration);
   block.resize(sample_count * channel_count, 0);
   initialized = true;
}

void AudioDataBlock::move_sample_head_position_by(std::size_t delta)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AudioProcessing::AudioDataBlock::move_sample_head_position_by]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AudioProcessing::AudioDataBlock::move_sample_head_position_by]: error: guard \"initialized\" not met");
   }
   sample_head_position += delta;
   while (sample_head_position >= sample_count) sample_head_position -= sample_count;
   return;
}

void AudioDataBlock::set_sample_count(std::size_t sample_count, bool clear)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AudioProcessing::AudioDataBlock::set_sample_count]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AudioProcessing::AudioDataBlock::set_sample_count]: error: guard \"initialized\" not met");
   }
   if (!((sample_count > 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AudioProcessing::AudioDataBlock::set_sample_count]: error: guard \"(sample_count > 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AudioProcessing::AudioDataBlock::set_sample_count]: error: guard \"(sample_count > 0)\" not met");
   }
   // TODO: permit this value to be set before initialization
   sample_head_position = 0;
   this->sample_count = sample_count;
   block.resize(sample_count * channel_count, 0);
   return;
}

std::size_t AudioDataBlock::get_block_size()
{
   return block.size();
}

float AudioDataBlock::get_sample_at_mono(int sample_position, int channel_t)
{
   sample_position = clamp_loop_sample_position(sample_head_position + sample_position);

   return block[(sample_position * channel_count) + channel_t];
}

void AudioDataBlock::set_sample_at_mono(int sample_position, int channel_t, float value)
{
   throw std::runtime_error("This feature is not fully built and would require a little development before use.");
   sample_position = clamp_loop_sample_position(sample_head_position + sample_position);

   block[(sample_position * channel_count) + channel_t] = value;
}

void AudioDataBlock::set_sample_at(int sample_position, float left_channel_value, float right_channel_value)
{
   sample_position = clamp_loop_sample_position(sample_head_position + sample_position);

   block[(sample_position * channel_count) + CHANNEL_LEFT] = left_channel_value;
   block[(sample_position * channel_count) + CHANNEL_RIGHT] = right_channel_value;
}

std::pair<float, float> AudioDataBlock::get_sample_at(int sample_position)
{
   sample_position = clamp_loop_sample_position(sample_head_position + sample_position);

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


} // namespace AudioProcessing
} // namespace AllegroFlare


