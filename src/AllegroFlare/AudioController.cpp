

#include <AllegroFlare/AudioController.hpp>

#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/TerminalColors.hpp>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


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
   , global_volume(1.0f)
   , output_loading_debug_to_cout(false)
   , initialized(false)
   , music_tracks_loaded(false)
   , sound_effects_loaded(false)
{
}


AudioController::~AudioController()
{
}


bool AudioController::get_initialized() const
{
   return initialized;
}


bool AudioController::get_music_tracks_loaded() const
{
   return music_tracks_loaded;
}


bool AudioController::get_sound_effects_loaded() const
{
   return sound_effects_loaded;
}


void AudioController::initialize()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AudioController::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AudioController::initialize: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_audio_installed()))
   {
      std::stringstream error_message;
      error_message << "[AudioController::initialize]: error: guard \"al_is_audio_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AudioController::initialize: error: guard \"al_is_audio_installed()\" not met");
   }
   if (!(al_is_acodec_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AudioController::initialize]: error: guard \"al_is_acodec_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AudioController::initialize: error: guard \"al_is_acodec_addon_initialized()\" not met");
   }
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AudioController::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AudioController::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(sample_bin))
   {
      std::stringstream error_message;
      error_message << "[AudioController::initialize]: error: guard \"sample_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AudioController::initialize: error: guard \"sample_bin\" not met");
   }
   // TODO: improve these couts
   if (output_loading_debug_to_cout) std::cout << "Loading assets in AudioController... " << std::endl;
   if (output_loading_debug_to_cout) std::cout << "sound_effects:" << std::endl;

   destruct_all_sound_effects();
   load_sound_effects();

   if (output_loading_debug_to_cout) std::cout << "music_tracks:" << std::endl;

   destruct_all_music_tracks();
   load_music_tracks();

   if (output_loading_debug_to_cout) std::cout << "[AllegroFlare::AudioController::load()] finished." << std::endl;

   initialized = true;
   return;
}

void AudioController::set_and_load_sound_effect_elements(std::map<std::string, AllegroFlare::AudioRepositoryElement> sound_effect_elements)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AudioController::set_and_load_sound_effect_elements]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AudioController::set_and_load_sound_effect_elements: error: guard \"initialized\" not met");
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
      error_message << "[AudioController::set_and_load_music_track_elements]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AudioController::set_and_load_music_track_elements: error: guard \"initialized\" not met");
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
      float volume = sound_effect_element.second.get_volume();

      std::string asset_key = sound_effects_identifier_prefix + filename;

      if (output_loading_debug_to_cout) std::cout << "- asset_key: " << asset_key << std::endl;

      ALLEGRO_SAMPLE *sample = sample_bin->auto_get(asset_key);
      Sound *sound = new Sound(sample);
      sound->initialize();
      sound->loop(loop);
      sound->volume(global_volume * volume);

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
      float volume = music_track_element.second.get_volume();

      std::string asset_key = music_tracks_identifier_prefix + filename;

      if (output_loading_debug_to_cout) std::cout << "- asset_key: " << asset_key << std::endl;

      ALLEGRO_SAMPLE *sample = sample_bin->auto_get(asset_key);
      Sound *sound = new Sound(sample);
      sound->initialize();
      sound->loop(loop);
      sound->volume(global_volume * volume);

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
      error_message << "[AudioController::stop_all]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AudioController::stop_all: error: guard \"initialized\" not met");
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
      error_message << "[AudioController::set_global_volume]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AudioController::set_global_volume: error: guard \"initialized\" not met");
   }
   // TODO: tweak this so that calling this function will not overwrite custom volumes
   // that exist on the repository elements
   for (auto &sound_effect : sound_effects) sound_effect.second->volume(global_volume);
   for (auto &music_track : music_tracks) music_track.second->volume(global_volume);
   return;
}

void AudioController::play_sound_effect(std::string identifier)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AudioController::play_sound_effect]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AudioController::play_sound_effect: error: guard \"initialized\" not met");
   }
   Sound *sound = find_sound_effect_sound_object_by_identifier(identifier);
   AudioRepositoryElement element = find_sound_effect_element_by_identifier(identifier);
   if (sound)
   {
      if (!sound->is_playing())
      {
         sound->play();
      }
      else // sound is currently playing, do some logic depending on what the configuration is
      {
         if (element.overplay_strategy_is_ignore())
         {
            // do nothing
         }
         else if (element.overplay_strategy_is_restart())
         {
            sound->stop();
            sound->play();
         }
      }
   }
   return;
}

void AudioController::play_music_track(std::string identifier)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AudioController::play_music_track]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AudioController::play_music_track: error: guard \"initialized\" not met");
   }
   Sound *sound = find_music_track_sound_object_by_identifier(identifier);
   AudioRepositoryElement element = find_music_track_element_by_identifier(identifier);
   if (sound)
   {
      if (!sound->is_playing())
      {
         stop_all_music_tracks();
         sound->play();
      }
      else // sound is currently playing, do some logic depending on what the configuration is
      {
         if (element.overplay_strategy_is_ignore())
         {
            // do nothing
         }
         else if (element.overplay_strategy_is_restart())
         {
            stop_all_music_tracks();
            sound->stop();
            sound->play();
         }
      }
   }
   return;
}

bool AudioController::sound_effect_element_exists(std::string identifier)
{
   return (sound_effect_elements.count(identifier) > 0);
}

AllegroFlare::Sound* AudioController::find_sound_effect_sound_object_by_identifier(std::string identifier)
{
   std::map<std::string, AllegroFlare::Sound*>::iterator it = sound_effects.find(identifier);
   if (it == sound_effects.end())
   {
      AllegroFlare::Logger::warn_from(
         "AllegroFlare::AudioController::find_sound_effect_sound_object_by_identifier",
         "Unable to find element with identifier \"" + identifier + "\"."
      );
      return nullptr;
   }
   return it->second;
}

AllegroFlare::AudioRepositoryElement AudioController::find_sound_effect_element_by_identifier(std::string identifier)
{
   std::map<std::string, AudioRepositoryElement>::iterator it = sound_effect_elements.find(identifier);
   if (it == sound_effect_elements.end())
   {
      AllegroFlare::Logger::warn_from(
         "AllegroFlare::AudioController::find_sound_effect_element_by_identifier",
         "Unable to find element with identifier \"" + identifier + "\"."
      );
      return {};
   }
   return it->second;
}

AllegroFlare::Sound* AudioController::find_music_track_sound_object_by_identifier(std::string identifier)
{
   std::map<std::string, Sound*>::iterator it = music_tracks.find(identifier);
   if (it == music_tracks.end())
   {
      AllegroFlare::Logger::warn_from(
         "AllegroFlare::AudioController::find_music_track_sound_object_by_identifier",
         "Unable to find element with identifier \"" + identifier + "\"."
      );
      return nullptr;
   }
   return it->second;
}

bool AudioController::music_track_element_exists(std::string identifier)
{
   return (music_track_elements.count(identifier) > 0);
}

AllegroFlare::AudioRepositoryElement AudioController::find_music_track_element_by_identifier(std::string identifier)
{
   std::map<std::string, AudioRepositoryElement>::iterator it = music_track_elements.find(identifier);
   if (it == music_track_elements.end())
   {
      AllegroFlare::Logger::warn_from(
         "AllegroFlare::AudioController::find_music_track_element_by_identifier",
         "Unable to find element with identifier \"" + identifier + "\"."
      );
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


