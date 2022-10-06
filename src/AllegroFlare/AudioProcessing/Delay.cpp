

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

   // initialize the memory
   float frequency = memory.get_frequency(); // same as "samples per second"
   int samples_needed = (int)(frequency * delay_sec);
   memory.set_sample_count(samples_needed);
   memory.initialize();

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
   float wet = 0.8;
   float dry = 1.0;
   int channel_count = delay->mixer.get_channel_count();

   for (int i=0; i<(samples * channel_count); i += channel_count)
   {
      fbuf[i+0] = fbuf[i+0];
      fbuf[i+1] = fbuf[i+1];
      
      // TODO: write the current memory sample, existing buffer, dry, wet into the memory buffer
      //memory.set_sample_at(i, fbuf[i+0], fbuf[i+1]);
   }

   return;
}


} // namespace AudioProcessing
} // namespace AllegroFlare


