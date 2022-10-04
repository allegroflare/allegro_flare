

#include <AllegroFlare/AcousticEnvironments/Reverb.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace AcousticEnvironments
{


Reverb::Reverb(std::string property)
   : AllegroFlare::AcousticEnvironments::Base(AllegroFlare::AcousticEnvironments::Reverb::TYPE)
   , property(property)
   , master_mixer(nullptr)
   , reverb_mixer(nullptr)
   , reverb_mixer_depth(ALLEGRO_AUDIO_DEPTH_FLOAT32)
   , reverb_mixer_frequency(0)
   , reverb_mixer_channel_configuration(ALLEGRO_CHANNEL_CONF_2)
   , initialized(false)
   , processing_buffer({})
   , PROCESSING_BUFFER_INITIAL_SIZE(2048)
{
}


Reverb::~Reverb()
{
}


std::string Reverb::get_property() const
{
   return property;
}


ALLEGRO_AUDIO_DEPTH Reverb::get_reverb_mixer_depth() const
{
   return reverb_mixer_depth;
}


unsigned int Reverb::get_reverb_mixer_frequency() const
{
   return reverb_mixer_frequency;
}


ALLEGRO_CHANNEL_CONF Reverb::get_reverb_mixer_channel_configuration() const
{
   return reverb_mixer_channel_configuration;
}


void Reverb::mixer_postprocess_callback(void* buf, unsigned int samples, void* data)
{
   if (!(data))
   {
      std::stringstream error_message;
      error_message << "Reverb" << "::" << "mixer_postprocess_callback" << ": error: " << "guard \"data\" not met";
      throw std::runtime_error(error_message.str());
   }
   AllegroFlare::AcousticEnvironments::Reverb *reverb_environment =
      static_cast<AllegroFlare::AcousticEnvironments::Reverb*>(data);

   std::cout << "Callback on \"" << reverb_environment->get_type() << "\": "
             << "samples: " << samples
             << std::endl;

   if (reverb_environment->get_reverb_mixer_depth() != ALLEGRO_AUDIO_DEPTH_FLOAT32)
   {
      std::stringstream error_message;
      error_message << "AllegroFlare::AcousticEnvironments::Reverb::mixer_postprocess_callback: error: "
                    << "expecting reverb_mixer_depth of the passed AcousticEnvironments::Reverb to be "
                    << "ALLEGRO_AUDIO_DEPTH_FLOAT32 but it is not.";
      throw std::runtime_error(error_message.str());
   }
   if (reverb_environment->get_reverb_mixer_channel_configuration() != ALLEGRO_CHANNEL_CONF_2)
   {
      std::stringstream error_message;
      error_message << "AllegroFlare::AcousticEnvironments::Reverb::mixer_postprocess_callback: error: "
                    << "expecting reverb_mixer_depth of the passed AcousticEnvironments::Reverb to be "
                    << "ALLEGRO_CHANNEL_CONF_2 but it is not.";
      throw std::runtime_error(error_message.str());
   }
   if (reverb_environment->get_reverb_mixer_frequency() != 44100)
   {
      std::stringstream error_message;
      error_message << "AllegroFlare::AcousticEnvironments::Reverb::mixer_postprocess_callback: error: "
                    << "expecting reverb_mixer_depth of the passed AcousticEnvironments::Reverb to be "
                    << "44100 but it is not.";
      throw std::runtime_error(error_message.str());
   }

   // TODO: process audio here

   return;
}

void Reverb::initialize()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "Reverb" << "::" << "initialize" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(al_is_audio_installed()))
   {
      std::stringstream error_message;
      error_message << "Reverb" << "::" << "initialize" << ": error: " << "guard \"al_is_audio_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(al_get_default_mixer()))
   {
      std::stringstream error_message;
      error_message << "Reverb" << "::" << "initialize" << ": error: " << "guard \"al_get_default_mixer()\" not met";
      throw std::runtime_error(error_message.str());
   }
   // set the master_mixer provided by allegro
   master_mixer = al_get_default_mixer();
   if (!master_mixer)
   {
      std::stringstream error_message;
      error_message << "AllegroFlare::AcousticEnvironments::Reverb::initialize error: "
                    << "there was an error getting the master_mixer from allegro.";
      throw std::runtime_error(error_message.str());
   }

   // create our reverb mixer with properties that match the master_mixer
   reverb_mixer_depth = al_get_mixer_depth(master_mixer);
   reverb_mixer_frequency = al_get_mixer_frequency(master_mixer);
   reverb_mixer_channel_configuration = al_get_mixer_channels(master_mixer);
   reverb_mixer = al_create_mixer(reverb_mixer_frequency, reverb_mixer_depth, reverb_mixer_channel_configuration);
   if (!reverb_mixer)
   {
      std::stringstream error_message;
      error_message << "AllegroFlare::AcousticEnvironments::Reverb::initialize error: "
                    << "there was an error creating the reverb_mixer.";
      throw std::runtime_error(error_message.str());
   }

   bool mixer_attachment_was_successful = al_attach_mixer_to_mixer(reverb_mixer, master_mixer);
   if (!mixer_attachment_was_successful)
   {
      std::stringstream error_message;
      error_message << "AllegroFlare::AcousticEnvironments::Reverb::initialize error: "
                    << "there was an error attaching the reverb_mixer to the master_mixer.";
      throw std::runtime_error(error_message.str());
   }

   // setup the mixer callback
   bool mixer_postprocess_callback_setup_was_successful = al_set_mixer_postprocess_callback(
      reverb_mixer,
      AllegroFlare::AcousticEnvironments::Reverb::mixer_postprocess_callback,
      this
   );
   if (!mixer_postprocess_callback_setup_was_successful)
   {
      std::stringstream error_message;
      error_message << "AllegroFlare::AcousticEnvironments::Reverb::initialize error: "
                    << "there was an error setting up the mixer postprocess callback.";
      throw std::runtime_error(error_message.str());
   }

   // setup the processing buffer
   processing_buffer.resize(PROCESSING_BUFFER_INITIAL_SIZE, 0);

   initialized = true;
   return;
}


} // namespace AcousticEnvironments
} // namespace AllegroFlare


