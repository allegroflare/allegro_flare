

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


Hypersync::Hypersync(std::string song_filename, float song_bpm)
   : song_filename(song_filename)
   , song_bpm(song_bpm)
   , timer({})
   , audio_stream(nullptr)
   , audio_voice(nullptr)
   , audio_mixer(nullptr)
   , initialized(false)
   , stream_is_attached(false)
   , MIN_SONG_BPM(20.0f)
   , latency_sec(0.140f)
{
}


Hypersync::~Hypersync()
{
}


std::string Hypersync::get_song_filename() const
{
   return song_filename;
}


float Hypersync::get_song_bpm() const
{
   return song_bpm;
}


void Hypersync::TODO()
{
   // TODO:
   // - investigate calculating the amount of latency needed, you might consume stream
   //   filling events, size of buffer, etc.
   // - add a "reset" option
   // - permit changing the song and bpm after initialization (which will implicitly stop stream and reset the timer)
   return;
}

void Hypersync::set_song_filename(std::string song_filename)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::Hypersync::set_song_filename]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::Hypersync::set_song_filename]: error: guard \"(!initialized)\" not met");
   }
   this->song_filename = song_filename;
   return;
}

void Hypersync::set_song_bpm(float song_bpm)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::Hypersync::set_song_bpm]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::Hypersync::set_song_bpm]: error: guard \"(!initialized)\" not met");
   }
   if (!((song_bpm >= MIN_SONG_BPM)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::Hypersync::set_song_bpm]: error: guard \"(song_bpm >= MIN_SONG_BPM)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::Hypersync::set_song_bpm]: error: guard \"(song_bpm >= MIN_SONG_BPM)\" not met");
   }
   this->song_bpm = song_bpm;
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
   float beat = (seconds * (song_bpm / 60.0));
   return ((int)beat) % 4 + 1;
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
      error_message << "[AllegroFlare::Prototypes::MindDive::Hypersync::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::Hypersync::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_audio_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::Hypersync::initialize]: error: guard \"al_is_audio_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::Hypersync::initialize]: error: guard \"al_is_audio_installed()\" not met");
   }
   if (!(al_is_acodec_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::Hypersync::initialize]: error: guard \"al_is_acodec_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::Hypersync::initialize]: error: guard \"al_is_acodec_addon_initialized()\" not met");
   }
   audio_voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
   if (!audio_voice) throw std::runtime_error("could not create voice!!");

   audio_mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
   if (!al_attach_mixer_to_voice(audio_mixer, audio_voice))
   {
      throw std::runtime_error("could not attach mixer to voice");
   }

   audio_stream = al_load_audio_stream(song_filename.c_str(), 4, 2048);
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
      al_destroy_audio_stream(audio_stream);
   }
   return;
}


} // namespace MindDive
} // namespace Prototypes
} // namespace AllegroFlare


