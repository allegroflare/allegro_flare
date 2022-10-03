

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
   , initialized(false)
{
}


Reverb::~Reverb()
{
}


std::string Reverb::get_property() const
{
   return property;
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

   std::cout << "Callback on \"" << reverb_environment->get_type() << "\"" << std::endl;

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
   reverb_mixer = al_create_mixer(
      al_get_mixer_frequency(master_mixer),
      al_get_mixer_depth(master_mixer), 
      al_get_mixer_channels(master_mixer)
   );
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

   initialized = true;
   return;
}


} // namespace AcousticEnvironments
} // namespace AllegroFlare


