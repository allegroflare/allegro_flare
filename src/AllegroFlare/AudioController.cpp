

#include <AllegroFlare/AudioController.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{


AudioController::AudioController(AllegroFlare::SampleBin* sample_bin, std::map<std::string, AllegroFlare::AudioRepositoryElement> sound_effect_elements, std::map<std::string, AllegroFlare::AudioRepositoryElement> music_track_elements)
   : sample_bin(sample_bin)
   , sound_effects_identifier_prefix("sound_effects/")
   , music_tracks_identifier_prefix("music_tracks/")
   , sound_effect_elements(sound_effect_elements)
   , music_track_elements(music_track_elements)
   , sound_effects({})
   , music_tracks({})
   , current_music_track_identifier("")
   , global_volume(0.1)
   , output_loading_debug_to_cout(true)
   , initialized(false)
{
}


AudioController::~AudioController()
{
}


bool AudioController::get_initialized()
{
   return initialized;
}


void AudioController::initialize()
{
   if (!((!initialized)))
      {
         std::stringstream error_message;
         error_message << "AudioController" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(sample_bin))
      {
         std::stringstream error_message;
         error_message << "AudioController" << "::" << "initialize" << ": error: " << "guard \"sample_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (output_loading_debug_to_cout) std::cout << "Loading assets in AudioController... " << std::endl;
   if (output_loading_debug_to_cout) std::cout << "sound_effects:" << std::endl;
   for (auto &sound_effect_element : sound_effect_elements)
   {
      std::string identifier = sound_effect_element.first;
      std::string filename = sound_effect_element.second.get_filename();
      bool loop = sound_effect_element.second.get_loop();

      std::string asset_key = sound_effects_identifier_prefix + filename;

      if (output_loading_debug_to_cout) std::cout << "- asset_key: " << asset_key << std::endl;

      ALLEGRO_SAMPLE *sample = sample_bin->auto_get(asset_key);
      Sound *sound = new Sound(sample);
      sound->loop(loop);
      sound->volume(global_volume);

      // TODO manage case where identifier already exists for this record

      sound_effects[identifier] = sound;
   }
   if (output_loading_debug_to_cout) std::cout << "music_tracks:" << std::endl;
   for (auto &music_track_element : music_track_elements)
   {
      std::string identifier = music_track_element.first;
      std::string filename = music_track_element.second.get_filename();
      bool loop = music_track_element.second.get_loop();

      std::string asset_key = music_tracks_identifier_prefix + filename;

      if (output_loading_debug_to_cout) std::cout << "- asset_key: " << asset_key << std::endl;

      ALLEGRO_SAMPLE *sample = sample_bin->auto_get(asset_key);
      Sound *sound = new Sound(sample);
      sound->loop(loop);
      sound->volume(global_volume);

      // TODO manage case where identifier already exists for this record

      music_tracks[identifier] = sound;
   }

   initialized = true;
   return;
}

void AudioController::destruct()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "AudioController" << "::" << "destruct" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   stop_all();
   for (auto &sound_effect : sound_effects) delete sound_effect.second;
   for (auto &music_track : music_tracks) delete music_track.second;
   return;
}

void AudioController::stop_all()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "AudioController" << "::" << "stop_all" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   stop_all_sound_effects();
   stop_all_music();
   return;
}

void AudioController::stop_all_music()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "AudioController" << "::" << "stop_all_music" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   for (auto &music_track : music_tracks) music_track.second->stop();
   current_music_track_identifier = "";
   return;
}

void AudioController::stop_all_sound_effects()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "AudioController" << "::" << "stop_all_sound_effects" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   for (auto &sound_effect : sound_effects) sound_effect.second->stop();
   return;
}

void AudioController::set_global_volume(float volume)
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "AudioController" << "::" << "set_global_volume" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   for (auto &sound_effect : sound_effects) sound_effect.second->volume(global_volume);
   for (auto &music_track : music_tracks) music_track.second->volume(global_volume);
   return;
}

void AudioController::play_sound_effect_by_identifier(std::string identifier)
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "AudioController" << "::" << "play_sound_effect_by_identifier" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   Sound *sound = find_sound_effect_by_identifier(identifier);
   if (sound) sound->play();
   return;
}

void AudioController::play_music_track_by_identifier(std::string identifier)
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "AudioController" << "::" << "play_music_track_by_identifier" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (identifier == current_music_track_identifier) return; // NOTE: GUARD COULD BE IMPROVED
   stop_all_music();
   Sound *sound = find_music_track_by_identifier(identifier);
   if (sound) sound->play();
   return;
}

AllegroFlare::Sound* AudioController::find_sound_effect_by_identifier(std::string identifier)
{
   std::map<std::string, AllegroFlare::Sound*>::iterator it = sound_effects.find(identifier);
   if (it == sound_effects.end())
   {
      std::cout << "AudioController::play_sound_effect_by_identifier() error: "
         << "unable to find element with identifier \""
         << identifier
         << "\""
         << std::endl;
      return nullptr;
   }
   return it->second;
}

AllegroFlare::Sound* AudioController::find_music_track_by_identifier(std::string identifier)
{
   std::map<std::string, Sound*>::iterator it = music_tracks.find(identifier);
   if (it == sound_effects.end())
   {
      std::cout << "AudioController::play_music_track_by_identifier() error: "
         << "unable to find element with identifier \""
         << identifier
         << "\""
         << std::endl;
      return nullptr;
   }
   return it->second;
}
} // namespace AllegroFlare


