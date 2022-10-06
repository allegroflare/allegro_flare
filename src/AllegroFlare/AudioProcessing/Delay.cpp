

#include <AllegroFlare/AudioProcessing/Delay.hpp>

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


} // namespace AudioProcessing
} // namespace AllegroFlare


