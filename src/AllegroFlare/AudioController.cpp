

#include <AllegroFlare/AudioController.hpp>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
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
#include <AllegroFlare/TerminalColors.hpp>


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
   , global_volume(1.0)
   , output_loading_debug_to_cout(true)
   , initialized(false)
   , music_tracks_loaded(false)
   , sound_effects_loaded(false)
{
}


AudioController::~AudioController()
{
}


bool AudioController::get_initialized()
{
   return initialized;
}


bool AudioController::get_music_tracks_loaded()
{
   return music_tracks_loaded;
}


bool AudioController::get_sound_effects_loaded()
{
   return sound_effects_loaded;
}


void AudioController::initialize()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "AudioController" << "::" << "initialize" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_audio_installed()))
      {
         std::stringstream error_message;
         error_message << "AudioController" << "::" << "initialize" << ": error: " << "guard \"al_is_audio_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_acodec_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "AudioController" << "::" << "initialize" << ": error: " << "guard \"al_is_acodec_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
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

   destruct_all_sound_effects();
   load_sound_effects();

   if (output_loading_debug_to_cout) std::cout << "music_tracks:" << std::endl;

   destruct_all_music_tracks();
   load_music_tracks();

   std::cout << "[AllegroFlare::AudioController::load()] finished." << std::endl;

   initialized = true;
   return;
}

void AudioController::set_and_load_sound_effect_elements(std::map<std::string, AllegroFlare::AudioRepositoryElement> sound_effect_elements)
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "AudioController" << "::" << "set_and_load_sound_effect_elements" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   destruct_all_sound_effects();

   this->sound_effect_elements = sound_effect_elements;
   load_sound_effects();
   return;
}

void AudioController::set_and_load_music_track_elements(std::map<std::string, AllegroFlare::AudioRepositoryElement> music_track_elements)
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "AudioController" << "::" << "set_and_load_music_track_elements" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   destruct_all_music_tracks();

   this->music_track_elements = music_track_elements;
   load_music_tracks();
   return;
}

void AudioController::load_sound_effects()
{
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

   return;
}

void AudioController::load_music_tracks()
{
   destruct_all_music_tracks();

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

   return;
}

void AudioController::destruct()
{
   destruct_all_sound_effects();
   destruct_all_music_tracks();
   return;
}

void AudioController::destruct_all()
{
   destruct_all_sound_effects();
   destruct_all_music_tracks();
   return;
}

void AudioController::destruct_all_sound_effects()
{
   stop_all_sound_effects();
   for (auto &sound_effect : sound_effects) delete sound_effect.second;
   return;
}

void AudioController::destruct_all_music_tracks()
{
   stop_all_music_tracks();
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
   stop_all_music_tracks();
   return;
}

void AudioController::stop_all_music_tracks()
{
   for (auto &music_track : music_tracks) music_track.second->stop();
   current_music_track_identifier = "";
   return;
}

void AudioController::stop_all_sound_effects()
{
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
   stop_all_music_tracks();
   Sound *sound = find_music_track_sound_object_by_identifier(identifier);
   if (sound) sound->play();
   return;
}

AllegroFlare::Sound* AudioController::find_sound_effect_by_identifier(std::string identifier)
{
   std::map<std::string, AllegroFlare::Sound*>::iterator it = sound_effects.find(identifier);
   if (it == sound_effects.end())
   {
      std::cout
         << AllegroFlare::TerminalColors::RED
         << "AudioController::find_sound_effect_by_identifier() error: "
         << "unable to find element with identifier \""
         << identifier
         << "\""
         << AllegroFlare::TerminalColors::DEFAULT
         << std::endl;
      return nullptr;
   }
   return it->second;
}

AllegroFlare::Sound* AudioController::find_music_track_sound_object_by_identifier(std::string identifier)
{
   std::map<std::string, Sound*>::iterator it = music_tracks.find(identifier);
   if (it == music_tracks.end())
   {
      std::cout << "[AudioController::find_music_track_sound_object_by_identifier] error: "
                << "unable to find element with identifier \"" << identifier << "\"" << std::endl;
      return nullptr;
   }
   return it->second;
}

bool AudioController::music_track_element_exists(std::string identifier)
{
   return (music_track_elements.count(identifier) > 0);
}

AllegroFlare::AudioRepositoryElement AudioController::find_music_track_repository_element_by_identifier(std::string identifier)
{
   std::map<std::string, AudioRepositoryElement>::iterator it = music_track_elements.find(identifier);
   if (it == music_track_elements.end())
   {
      std::cout << "[AudioController::find_music_track_repository_element_by_identifier] error: "
                << "unable to find element with identifier \"" << identifier << "\"" << std::endl;
      return {};
   }
   return it->second;
}

void AudioController::dump_to_cout()
{
   for (auto &sound_effect_element : sound_effect_elements)
   {
      std::string identifier = sound_effect_element.first;
      std::string filename = sound_effect_element.second.get_filename();
      bool loop = sound_effect_element.second.get_loop();
      
      std::cout << "{ identifier: \"" << identifier << "\", source: \"" << filename << "\" }" << std::endl;
   }
   for (auto &music_track_element : music_track_elements)
   {
      std::string identifier = music_track_element.first;
      std::string filename = music_track_element.second.get_filename();
      bool loop = music_track_element.second.get_loop();
      
      std::cout << "{ identifier: \"" << identifier << "\", source: \"" << filename << "\" }" << std::endl;
   }
}
} // namespace AllegroFlare


