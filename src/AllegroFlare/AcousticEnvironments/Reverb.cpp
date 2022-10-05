

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
   , reverb_mixer_depth_size(0)
   , reverb_mixer_frequency(0)
   , reverb_mixer_channel_configuration(ALLEGRO_CHANNEL_CONF_2)
   , reverb_mixer_channel_count(0)
   , initialized(false)
   , processing_buffer({})
   , swap_buffer({})
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


std::size_t Reverb::get_reverb_mixer_depth_size() const
{
   return reverb_mixer_depth_size;
}


unsigned int Reverb::get_reverb_mixer_frequency() const
{
   return reverb_mixer_frequency;
}


ALLEGRO_CHANNEL_CONF Reverb::get_reverb_mixer_channel_configuration() const
{
   return reverb_mixer_channel_configuration;
}


std::size_t Reverb::get_reverb_mixer_channel_count() const
{
   return reverb_mixer_channel_count;
}


ALLEGRO_MIXER* Reverb::get_reverb_mixer()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Reverb" << "::" << "get_reverb_mixer" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   return reverb_mixer;
}

float Reverb::clamp_intensity(float val)
{
   if (val < -1) return -1;
   if (val > 1) return 1;
   return val;
}

void Reverb::mixer_postprocess_callback(void* buf, unsigned int samples, void* data)
{
   if (!(data))
   {
      std::stringstream error_message;
      error_message << "Reverb" << "::" << "mixer_postprocess_callback" << ": error: " << "guard \"data\" not met";
      throw std::runtime_error(error_message.str());
   }
   std::cout << "------------" << std::endl;
   //static int callback_count = 0;
   //callback_count++;

   AllegroFlare::AcousticEnvironments::Reverb *reverb_environment =
      static_cast<AllegroFlare::AcousticEnvironments::Reverb*>(data);

   // validate configuration
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
   if (samples != PROCESSING_BUFFER_INITIAL_SIZE)
   {
      std::stringstream error_message;
      error_message << "AllegroFlare::AcousticEnvironments::Reverb::mixer_postprocess_callback: error: "
                    << "expecting number of samples to of the passed data to be "
                    << PROCESSING_BUFFER_INITIAL_SIZE << " but it was not (" << samples << ").";
      throw std::runtime_error(error_message.str());
   }

   float *fbuf = (float *)buf;
   std::size_t depth_size = reverb_environment->get_reverb_mixer_depth_size();
   unsigned int channel_count = reverb_environment->get_reverb_mixer_channel_count();
   float *swap_buffer = reverb_environment->swap_buffer.data();
   float *processing_buffer = reverb_environment->processing_buffer.data();

   // output some debug data
   std::cout << "Callback on \"" << reverb_environment->get_type() << "\":" << std::endl
             << "  - samples: " << samples << std::endl
             << "  - depth_size: " << depth_size << std::endl
             << "  - channel_count: " << channel_count << std::endl
             << "  - first_sample_value: " << fbuf[0] << std::endl
             //<< "  - callback_count: " << callback_count << std::endl
             ;

   // capture the existing buffer into our processing_buffer
   //memcpy(swap_buffer, fbuf, samples * depth_size * channel_count);

   // TODO: process audio here

   //// process by float
   //for (int i=0; i<(samples * depth_size * channel_count); i++)
   //{
      //fbuf[i] = swap_buffer[i];
   //}

   //al_rest(0.5);
   //al_rest(0.2);

   // process by channel
   for (int i=0; i<(samples); i++)
   {
      fbuf[i * channel_count + 0] = fbuf[i * channel_count + 0] * 0.5; // * 0.5;
      fbuf[i * channel_count + 1] = fbuf[i * channel_count + 1] * 0.5; // * 0.5;
      //int buff_pos = i * channel_count;

      // left channel
      //fbuf[buff_pos + 0] = clamp_intensity(
                              //swap_buffer[buff_pos + 0]
                              //+ (processing_buffer[buff_pos + 0] * 0.8)
                           //);
      // right channel
      //fbuf[buff_pos + 1] = clamp_intensity(
                              //swap_buffer[buff_pos + 1]
                              //+ (processing_buffer[buff_pos + 1] * 0.8)
                           //);

      //if (fbuf[buff_pos + 0] > 1) std::cout << "+++++" << fbuf[buff_pos + 0] << std::endl;
      //if (fbuf[buff_pos + 0] < -1) std::cout << "-----" << fbuf[buff_pos + 0] << std::endl;
      //if (fbuf[buff_pos + 1] > 1) std::cout << "+++++" << fbuf[buff_pos + 0] << std::endl;
      //if (fbuf[buff_pos + 1] < -1) std::cout << "-----" << fbuf[buff_pos + 0] << std::endl;
   }

   //std::cout << std::flush;

   //al_rest(0.2);
   memcpy(processing_buffer, fbuf, samples * depth_size * channel_count);
   //memcpy(fbuf, processing_buffer, samples * depth_size * channel_count);

   std::cout << "++++++++++++++" << std::endl;
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
   reverb_mixer_depth_size = al_get_audio_depth_size(reverb_mixer_depth);
   reverb_mixer_channel_count = al_get_channel_count(reverb_mixer_channel_configuration);
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

    //setup the mixer callback
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
   processing_buffer.resize(PROCESSING_BUFFER_INITIAL_SIZE * 4 * 2, 0);
   swap_buffer.resize(PROCESSING_BUFFER_INITIAL_SIZE * 4 * 2, 0);

   initialized = true;
   return;
}


} // namespace AcousticEnvironments
} // namespace AllegroFlare


