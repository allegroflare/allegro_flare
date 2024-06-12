

#include <AllegroFlare/AudioProcessing/Filters/AllPass.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace AudioProcessing
{
namespace Filters
{


AllPass::AllPass(float offset_sec, float gain, float wet, float dry)
   : offset_sec(offset_sec)
   , gain(gain)
   , wet(wet)
   , dry(dry)
   , mixer()
   , data_block()
   , initialized(false)
{
}


AllPass::~AllPass()
{
}


float AllPass::get_offset_sec() const
{
   return offset_sec;
}


float AllPass::get_gain() const
{
   return gain;
}


float AllPass::get_wet() const
{
   return wet;
}


float AllPass::get_dry() const
{
   return dry;
}


AllegroFlare::AudioProcessing::AudioDataBlock &AllPass::get_data_block_ref()
{
   return data_block;
}


void AllPass::set_offset_sec(float offset_sec)
{
   // Sample count must be at minimum 1 sample (data_block.set_sample_count will throw an error in this case)
   // With a sample rate of 44100, this would be an offset_sec of 0.000022675736961
   data_block.set_sample_count(data_block.get_frequency() * offset_sec);
   return;
}

void AllPass::set_gain(float gain)
{
   if (!((gain >= 0.0f)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AudioProcessing::Filters::AllPass::set_gain]: error: guard \"(gain >= 0.0f)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AudioProcessing::Filters::AllPass::set_gain]: error: guard \"(gain >= 0.0f)\" not met");
   }
   if (!((gain <= 1.0f)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AudioProcessing::Filters::AllPass::set_gain]: error: guard \"(gain <= 1.0f)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AudioProcessing::Filters::AllPass::set_gain]: error: guard \"(gain <= 1.0f)\" not met");
   }
   this->gain = gain;
   return;
}

void AllPass::set_wet(float wet)
{
   if (!((wet >= 0.0f)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AudioProcessing::Filters::AllPass::set_wet]: error: guard \"(wet >= 0.0f)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AudioProcessing::Filters::AllPass::set_wet]: error: guard \"(wet >= 0.0f)\" not met");
   }
   if (!((wet <= 1.0f)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AudioProcessing::Filters::AllPass::set_wet]: error: guard \"(wet <= 1.0f)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AudioProcessing::Filters::AllPass::set_wet]: error: guard \"(wet <= 1.0f)\" not met");
   }
   this->wet = wet;
   return;
}

void AllPass::set_dry(float dry)
{
   if (!((dry >= 0.0f)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AudioProcessing::Filters::AllPass::set_dry]: error: guard \"(dry >= 0.0f)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AudioProcessing::Filters::AllPass::set_dry]: error: guard \"(dry >= 0.0f)\" not met");
   }
   if (!((dry <= 1.0f)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AudioProcessing::Filters::AllPass::set_dry]: error: guard \"(dry <= 1.0f)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AudioProcessing::Filters::AllPass::set_dry]: error: guard \"(dry <= 1.0f)\" not met");
   }
   this->dry = dry;
   return;
}

ALLEGRO_MIXER* AllPass::get_al_mixer()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AudioProcessing::Filters::AllPass::get_al_mixer]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AudioProcessing::Filters::AllPass::get_al_mixer]: error: guard \"initialized\" not met");
   }
   return mixer.get_mixer();
}

void AllPass::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AudioProcessing::Filters::AllPass::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AudioProcessing::Filters::AllPass::initialize]: error: guard \"(!initialized)\" not met");
   }
   // initialize the mixer
   mixer.initialize();

   // initialize the data_block
   data_block.initialize();
   float frequency = data_block.get_frequency(); // same as "samples per second"
   int samples_needed = (int)(frequency * offset_sec);
   data_block.set_sample_count(samples_needed);

   // attach the
   mixer.set_postprocess_callback(mixer_postprocess_callback, this);

   // set initialized
   initialized = true;
   return;
}

void AllPass::mixer_postprocess_callback(void* buf, unsigned int samples, void* data)
{
   if (!(data))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AudioProcessing::Filters::AllPass::mixer_postprocess_callback]: error: guard \"data\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AudioProcessing::Filters::AllPass::mixer_postprocess_callback]: error: guard \"data\" not met");
   }
   float *fbuf = (float *)buf;
   AllegroFlare::AudioProcessing::Filters::AllPass *all_pass= static_cast<AllegroFlare::AudioProcessing::Filters::AllPass*>(data);
   AllegroFlare::AudioProcessing::AudioDataBlock &data_block = all_pass->get_data_block_ref();
   int channel_count = all_pass->mixer.get_channel_count();
   float &gain = all_pass->gain;
   float &wet = all_pass->wet;
   float &dry = all_pass->dry;

   for (int i=0; i<samples; i++)
   {
      int bufpos = i * 2;

      // collect the now_sample to mix in a wet/dry mix
      std::pair<float, float> dry_sample = { fbuf[bufpos+0], fbuf[bufpos+1] };

      //float delayOutput = allPassDelayedSample;
      std::pair<float, float> delayOutput = data_block.get_sample_at(i-1);

      //float feedBack = delayOutput * allPassGain;
      std::pair<float, float> feedBack = std::pair<float, float>(
         delayOutput.first * gain,
         delayOutput.second * gain
      );

      //float delayInput = inSamp + feedBack;
      std::pair<float, float> delayInput = std::pair<float, float>(
         fbuf[bufpos+0] + feedBack.first,
         fbuf[bufpos+1] + feedBack.second
      );

      //float feedForward = delayInput * -allPassGain;
      std::pair<float, float> feedForward = std::pair<float, float>(
         delayInput.first * -gain,
         delayInput.second * -gain
      );

      //allPassDelayedSample = delayInput;
      data_block.set_sample_at(i-1, delayInput.first, delayInput.second);

      //return delayOutput + feedForward;
      fbuf[bufpos+0] = dry_sample.first * dry + (delayOutput.first + feedForward.first) * wet;
      fbuf[bufpos+1] = dry_sample.second * dry + (delayOutput.second + feedForward.second) * wet;
   }
   data_block.move_sample_head_position_by(samples);

   return;
}


} // namespace Filters
} // namespace AudioProcessing
} // namespace AllegroFlare


