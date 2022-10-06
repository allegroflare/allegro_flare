

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
   , memory({})
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


void Delay::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "Delay" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   float frequency = memory.get_frequency(); // same as "samples per second"
   int samples_needed = (int)(frequency * delay_sec);
   memory.set_sample_count(samples_needed);
   memory.initialize();
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
   float wet = 0.8;
   float dry = 1.0;

   // process by channel
   for (int i=0; i<samples; i++)
   {
      int pos = i*2; // 2 == channel_count;
      fbuf[pos+0] = fbuf[pos+0];
      fbuf[pos+1] = fbuf[pos+1];
      
      // write the current memory sample + (existing buffer * dry) to the delay buffer
      //memory.set_sample_at(pos, fbuf);

      // (int pos = i*channel_count)
   }

   //memcpy(processing_buffer, fbuf, samples * channel_count);
   // write the signal data to the delay buffer

   return;
}


} // namespace AudioProcessing
} // namespace AllegroFlare


