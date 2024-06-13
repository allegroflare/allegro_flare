

#include <AllegroFlare/AudioProcessing/AudioMixer.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace AudioProcessing
{


AudioMixer::AudioMixer()
   : parent_mixer(nullptr)
   , mixer(nullptr)
   , audio_depth(ALLEGRO_AUDIO_DEPTH_FLOAT32)
   , audio_depth_size(0)
   , frequency(0)
   , channel_configuration(ALLEGRO_CHANNEL_CONF_2)
   , channel_count(0)
   , initialized(false)
{
}


AudioMixer::~AudioMixer()
{
}


ALLEGRO_AUDIO_DEPTH AudioMixer::get_audio_depth() const
{
   return audio_depth;
}


std::size_t AudioMixer::get_audio_depth_size() const
{
   return audio_depth_size;
}


unsigned int AudioMixer::get_frequency() const
{
   return frequency;
}


ALLEGRO_CHANNEL_CONF AudioMixer::get_channel_configuration() const
{
   return channel_configuration;
}


std::size_t AudioMixer::get_channel_count() const
{
   return channel_count;
}


ALLEGRO_MIXER* AudioMixer::get_mixer()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AudioProcessing::AudioMixer::get_mixer]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AudioProcessing::AudioMixer::get_mixer]: error: guard \"initialized\" not met");
   }
   return mixer;
}

void AudioMixer::validate_configuration()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AudioProcessing::AudioMixer::validate_configuration]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AudioProcessing::AudioMixer::validate_configuration]: error: guard \"initialized\" not met");
   }
   // validate configuration
   if (audio_depth != ALLEGRO_AUDIO_DEPTH_FLOAT32)
   {
      std::stringstream error_message;
      error_message << "AllegroFlare::AudioProcessing::AudioMixer::validate_configuration: error: "
                    << "expecting audio_depth of the passed AcousticEnvironments::Reverb to be "
                    << "ALLEGRO_AUDIO_DEPTH_FLOAT32 but it is not.";
      throw std::runtime_error(error_message.str());
   }
   if (channel_configuration != ALLEGRO_CHANNEL_CONF_2)
   {
      std::stringstream error_message;
      error_message << "AllegroFlare::AudioProcessing::AudioMixer::validate_configuration: error: "
                    << "expecting channel_configuration of to be "
                    << "ALLEGRO_CHANNEL_CONF_2 but it is not.";
      throw std::runtime_error(error_message.str());
   }
   if (frequency != 44100)
   {
      std::stringstream error_message;
      error_message << "AllegroFlare::AudioProcessing::AudioMixer::validate_configuration: error: "
                    << "expecting frequency to be 44100 but it is not.";
      throw std::runtime_error(error_message.str());
   }

   return;
}

void AudioMixer::initialize()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AudioProcessing::AudioMixer::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AudioProcessing::AudioMixer::initialize]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_audio_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AudioProcessing::AudioMixer::initialize]: error: guard \"al_is_audio_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AudioProcessing::AudioMixer::initialize]: error: guard \"al_is_audio_installed()\" not met");
   }
   if (!(al_get_default_mixer()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AudioProcessing::AudioMixer::initialize]: error: guard \"al_get_default_mixer()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AudioProcessing::AudioMixer::initialize]: error: guard \"al_get_default_mixer()\" not met");
   }
   // set the parent_mixer provided by allegro
   parent_mixer = al_get_default_mixer();
   if (!parent_mixer)
   {
      std::stringstream error_message;
      error_message << "AllegroFlare::AcousticEnvironments::Reverb::initialize error: "
                    << "there was an error getting the parent_mixer from allegro.";
      throw std::runtime_error(error_message.str());
   }

   // create our mixer with properties that match the parent_mixer
   audio_depth = al_get_mixer_depth(parent_mixer);
   frequency = al_get_mixer_frequency(parent_mixer);
   channel_configuration = al_get_mixer_channels(parent_mixer);
   mixer = al_create_mixer(frequency, audio_depth, channel_configuration);
   if (!mixer)
   {
      std::stringstream error_message;
      error_message << "AllegroFlare::AcousticEnvironments::Reverb::initialize error: "
                    << "there was an error creating the mixer.";
      throw std::runtime_error(error_message.str());
   }

   bool mixer_attachment_was_successful = al_attach_mixer_to_mixer(mixer, parent_mixer);
   if (!mixer_attachment_was_successful)
   {
      std::stringstream error_message;
      error_message << "AllegroFlare::AcousticEnvironments::Reverb::initialize error: "
                    << "there was an error attaching the mixer to the parent_mixer.";
      throw std::runtime_error(error_message.str());
   }

   // store some properties locally
   audio_depth_size = al_get_audio_depth_size(audio_depth);
   channel_count = al_get_channel_count(channel_configuration);

   initialized = true;
   return;
}

void AudioMixer::set_postprocess_callback(void (*callback)(void*, unsigned int, void*) /*callback*/, void* user_data)
{
   bool mixer_postprocess_callback_setup_was_successful =
      al_set_mixer_postprocess_callback(mixer, callback, user_data);
   if (!mixer_postprocess_callback_setup_was_successful)
   {
      std::stringstream error_message;
      error_message << "AllegroFlare::AudioProcessing::AudioMixer::set_postprocess_callback error: "
                    << "there was an error setting up the mixer postprocess callback.";
      throw std::runtime_error(error_message.str());
   }
   return;
}


} // namespace AudioProcessing
} // namespace AllegroFlare


