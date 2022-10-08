

#include <AllegroFlare/AudioProcessing/AllPass.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace AudioProcessing
{


AllPass::AllPass(float offset_sec, float decay)
   : offset_sec(offset_sec)
   , decay(decay)
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


float AllPass::get_decay() const
{
   return decay;
}


AllegroFlare::AudioDataBlock &AllPass::get_data_block_ref()
{
   return data_block;
}


void AllPass::set_offset_sec(float offset_sec)
{
   data_block.set_sample_count(data_block.get_frequency() * offset_sec);
   return;
}

ALLEGRO_MIXER* AllPass::get_al_mixer()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "AllPass" << "::" << "get_al_mixer" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   return mixer.get_mixer();
}

void AllPass::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "AllPass" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   // initialize the mixer
   // DEBUG:
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
      error_message << "AllPass" << "::" << "mixer_postprocess_callback" << ": error: " << "guard \"data\" not met";
      throw std::runtime_error(error_message.str());
   }
   float *fbuf = (float *)buf;
   AllegroFlare::AudioProcessing::AllPass *all_pass= static_cast<AllegroFlare::AudioProcessing::AllPass*>(data);
   AllegroFlare::AudioDataBlock &data_block = all_pass->get_data_block_ref();
   float wet = 1.0; //all_pass->decay;
   float dry = 1.0;
   int channel_count = all_pass->mixer.get_channel_count();

   //int sample_offset = 256;
   //static std::pair<float, float> delayed_sample = {0, 0};

   float allPassGain = 1.0;

   for (int i=0; i<samples; i++)
   {
      int bufpos = i * 2;

      //float delayOutput = allPassDelayedSample;
      std::pair<float, float> delayOutput = data_block.get_sample_at(i+1);

      //float feedBack = delayOutput * allPassGain;
      std::pair<float, float> feedBack = std::pair<float, float>(
         delayOutput.first * allPassGain,
         delayOutput.second * allPassGain
      );

      //float delayInput = inSamp + feedBack;
      std::pair<float, float> delayInput = std::pair<float, float>(
         fbuf[bufpos+0] + feedBack.first,
         fbuf[bufpos+1] + feedBack.second
      );

      //float feedForward = delayInput * -allPassGain;
      std::pair<float, float> feedForward = std::pair<float, float>(
         delayInput.first * -allPassGain,
         delayInput.second * -allPassGain
      );

      //allPassDelayedSample = delayInput;
      data_block.set_sample_at(i-1, delayInput.first, delayInput.second);

      //return delayOutput + feedForward;
      fbuf[bufpos+0] = delayOutput.first + feedForward.first;
      fbuf[bufpos+1] = delayOutput.second + feedForward.second;
   }
   data_block.move_sample_head_position_by(samples);

   return;
}


} // namespace AudioProcessing
} // namespace AllegroFlare


