

#include <AllegroFlare/AudioProcessing/Filters/Delay.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace AudioProcessing
{
namespace Filters
{


Delay::Delay(float delay_sec, float decay)
   : delay_sec(delay_sec)
   , decay(decay)
   , mixer()
   , data_block()
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


AllegroFlare::AudioProcessing::AudioDataBlock &Delay::get_data_block_ref()
{
   return data_block;
}


void Delay::set_delay_sec(float delay_sec)
{
   data_block.set_sample_count(data_block.get_frequency() * delay_sec);
   return;
}

ALLEGRO_MIXER* Delay::get_al_mixer()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AudioProcessing::Filters::Delay::get_al_mixer]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AudioProcessing::Filters::Delay::get_al_mixer]: error: guard \"initialized\" not met");
   }
   return mixer.get_mixer();
}

void Delay::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AudioProcessing::Filters::Delay::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AudioProcessing::Filters::Delay::initialize]: error: guard \"(!initialized)\" not met");
   }
   // initialize the mixer
   mixer.initialize();

   // initialize the data_block
   data_block.initialize();
   float frequency = data_block.get_frequency(); // same as "samples per second"
   int samples_needed = (int)(frequency * delay_sec);
   data_block.set_sample_count(samples_needed);

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
      error_message << "[AllegroFlare::AudioProcessing::Filters::Delay::mixer_postprocess_callback]: error: guard \"data\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AudioProcessing::Filters::Delay::mixer_postprocess_callback]: error: guard \"data\" not met");
   }
   float *fbuf = (float *)buf;
   AllegroFlare::AudioProcessing::Filters::Delay *delay = static_cast<AllegroFlare::AudioProcessing::Filters::Delay*>(data);
   AllegroFlare::AudioProcessing::AudioDataBlock &data_block = delay->get_data_block_ref();
   float wet = delay->decay;
   float dry = 1.0;
   int channel_count = delay->mixer.get_channel_count();

   for (int i=0; i<samples; i++)
   {
      int bufpos = i * 2;

      float l_result = fbuf[bufpos+0] * dry + data_block.get_sample_at_mono(i, 0) * wet;
      float r_result = fbuf[bufpos+1] * dry + data_block.get_sample_at_mono(i, 1) * wet;

      data_block.set_sample_at(i-1, l_result, r_result);

      fbuf[bufpos+0] = l_result;
      fbuf[bufpos+1] = r_result;
   }
   data_block.move_sample_head_position_by(samples);

   return;
}


} // namespace Filters
} // namespace AudioProcessing
} // namespace AllegroFlare


