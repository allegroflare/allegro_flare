

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
   , timer({})
   , audio_stream(nullptr)
   , audio_voice(nullptr)
   , audio_mixer(nullptr)
   , initialized(false)
   , stream_is_attached(false)
   , song_bpm(130.0f)
   , latency_sec(0.065f)
{
}


Hypersync::~Hypersync()
{
}


ALLEGRO_EVENT_QUEUE* Hypersync::get_event_queue() const
{
   return event_queue;
}


void Hypersync::TODO()
{
   // TODO: investigate calculating the amount of latency needed.
   // - you might consume stream filling events, size of buffer, etc.
   return;
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

float Hypersync::get_timer_seconds()
{
   return get_timer_microseconds() * 0.000001f;
}

float Hypersync::get_timer_milliseconds()
{
   return get_timer_microseconds() * 0.001f;
}

float Hypersync::get_timer_microseconds()
{
   float time_with_latency = timer.get_elapsed_time_microseconds() - (latency_sec * 1000000);
   if (time_with_latency < 0) return 0;
   return time_with_latency;
}

int Hypersync::get_beat_num(float seconds)
{
   float beat = (seconds * (song_bpm / 60.0) + 1);
   return ((int)beat) % 4;
}

int Hypersync::get_measure_num(float seconds)
{
   float beat = (seconds * (song_bpm / 60.0));
   return ((int)beat) / 4;
}

std::string Hypersync::build_beat_clock_str()
{
   float seconds = get_timer_seconds();
   std::stringstream result;
   result << get_measure_num(seconds) << ":" << get_beat_num(seconds);
   return result.str();
}

void Hypersync::start()
{
   if (!stream_is_attached)
   {
      al_register_event_source(event_queue, al_get_audio_stream_event_source(audio_stream));
      if (!al_attach_audio_stream_to_mixer(audio_stream, audio_mixer))
      {
         throw std::runtime_error("boobaz");
      }
      timer.start();
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
   float song_bpm = 130.0f;
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
      if (stream_is_attached)
      {
         // TODO: sort out this destruction
         al_detach_voice(audio_voice);
         al_destroy_mixer(audio_mixer);
      }
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


