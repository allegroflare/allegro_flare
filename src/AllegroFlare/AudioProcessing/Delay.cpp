

#include <AllegroFlare/AudioProcessing/Delay.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace AudioProcessing
{


Delay::Delay(float delay_sec, float decay)
   : delay_sec(delay_sec)
   , decay(decay)
   , mixer({})
   , data_block({})
   , initialized(false)
{
}


Delay::~Delay()
{
}


float Delay::get_delay_sec() const
{
   return delay_sec;
}


float Delay::get_decay() const
{
   return decay;
}


AllegroFlare::AudioDataBlock &Delay::get_data_block_ref()
{
   return data_block;
}


void Delay::set_delay_sec(float delay_sec)
{
   data_block.set_sample_count(data_block.get_frequency() * delay_sec);
   // DEBUG:
   return;
}

ALLEGRO_MIXER* Delay::get_al_mixer()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Delay" << "::" << "get_al_mixer" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   return mixer.get_mixer();
}

void Delay::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "Delay" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   // initialize the mixer
   mixer.initialize();

   // initialize the data_block
   float frequency = data_block.get_frequency(); // same as "samples per second"
   int samples_needed = (int)(frequency * delay_sec);
   data_block.set_sample_count(samples_needed);
   data_block.initialize();

   // attach the
   mixer.set_postprocess_callback(mixer_postprocess_callback, this);

   // set initialized
   initialized = true;
   return;
}

void Delay::mixer_postprocess_callback(void* buf, unsigned int samples, void* data)
{
   if (!(data))
   {
      std::stringstream error_message;
      error_message << "Delay" << "::" << "mixer_postprocess_callback" << ": error: " << "guard \"data\" not met";
      throw std::runtime_error(error_message.str());
   }
   float *fbuf = (float *)buf;
   AllegroFlare::AudioProcessing::Delay *delay = static_cast<AllegroFlare::AudioProcessing::Delay*>(data);
   AllegroFlare::AudioDataBlock &data_block = delay->get_data_block_ref();
   float wet = 0.8;
   float dry = 1.0;
   int channel_count = delay->mixer.get_channel_count();

   for (int i=0; i<(samples * channel_count); i += channel_count)
   {
      // TODO: figure out how to offset the buffer to repeat sound at delay_sec intervals

      fbuf[i+0] = fbuf[i+0] * dry + data_block.get_sample_at(i/channel_count, 0) * wet;
      fbuf[i+1] = fbuf[i+1] * dry + data_block.get_sample_at(i/channel_count, 1) * wet;

      data_block.set_sample_at(i-1, fbuf[i+0], fbuf[i+1]);
   }

   return;
}


} // namespace AudioProcessing
} // namespace AllegroFlare


