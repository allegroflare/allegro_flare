

#include <AllegroFlare/Prototypes/MindDive/Hypersync.hpp>

#include <allegro5/allegro_acodec.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace MindDive
{


Hypersync::Hypersync(ALLEGRO_EVENT_QUEUE* event_queue)
   : event_queue(event_queue)
   , audio_stream(nullptr)
   , audio_voice(nullptr)
   , audio_mixer(nullptr)
   , initialized(false)
{
}


Hypersync::~Hypersync()
{
}


ALLEGRO_EVENT_QUEUE* Hypersync::get_event_queue() const
{
   return event_queue;
}


void Hypersync::set_event_queue(ALLEGRO_EVENT_QUEUE* event_queue)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Hypersync" << "::" << "set_event_queue" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   this->event_queue = event_queue;
   return;
}

void Hypersync::start()
{
   al_register_event_source(event_queue, al_get_audio_stream_event_source(audio_stream));
   if (!al_attach_audio_stream_to_mixer(audio_stream, audio_mixer))
   {
      throw std::runtime_error("boobaz");
   }

   return;
}

void Hypersync::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "Hypersync" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(al_is_audio_installed()))
   {
      std::stringstream error_message;
      error_message << "Hypersync" << "::" << "initialize" << ": error: " << "guard \"al_is_audio_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(al_is_acodec_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "Hypersync" << "::" << "initialize" << ": error: " << "guard \"al_is_acodec_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(event_queue))
   {
      std::stringstream error_message;
      error_message << "Hypersync" << "::" << "initialize" << ": error: " << "guard \"event_queue\" not met";
      throw std::runtime_error(error_message.str());
   }
   audio_voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
   if (!audio_voice) throw std::runtime_error("could not create voice!!");

   audio_mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
   if (!al_attach_mixer_to_voice(audio_mixer, audio_voice))
   {
      throw std::runtime_error("could not attach mixer to voice");
   }

   std::string filename = "/Users/markoates/Repos/allegro_flare/bin/data/samples/music_tracks/some-jamzz-04.ogg";
   //std::string filename = "/Users/markoates/Repos/allegro_flare/bin/data/samples/music_tracks/skate2.ogg";

   audio_stream = al_load_audio_stream(filename.c_str(), 4, 2048);
   if (!audio_stream) throw std::runtime_error("could not load stream!!");

   al_set_audio_stream_playmode(audio_stream, ALLEGRO_PLAYMODE_ONCE);

   initialized = true;
   return;
}

void Hypersync::destruct()
{
   if (audio_mixer)
   {
      // TODO: sort out this destruction
      //al_detach_voice(audio_voice);
      //al_destroy_mixer(audio_mixer);
   }
   if (audio_voice)
   {
      al_destroy_voice(audio_voice);
   }
   if (audio_stream)
   {
      al_unregister_event_source(event_queue, al_get_audio_stream_event_source(audio_stream));
      al_destroy_audio_stream(audio_stream);
   }
   return;
}


} // namespace MindDive
} // namespace Prototypes
} // namespace AllegroFlare


