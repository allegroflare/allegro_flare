

#include <AllegroFlare/AudioController.hpp>



namespace AllegroFlare
{


AllegroFlare::SampleBin AudioController::dummy_sample_bin = {};


AudioController::AudioController(AllegroFlare::SampleBin& sample_bin, std::map<std::string, AllegroFlare::AudioRepositoryElement> sound_effect_elements, std::map<std::string, AllegroFlare::AudioRepositoryElement> music_track_elements)
   : sample_bin(sample_bin)
   , sound_effects_identifier_prefix("sound_effects/")
   , music_tracks_identifier_prefix("music_tracks/")
   , sound_effect_elements(sound_effect_elements)
   , music_track_elements(music_track_elements)
   , sound_effects({})
   , music_tracks({})
   , current_music_track_identifier("")
   , global_volume(0.1)
   , output_loading_debug_to_cout(false)
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


AllegroFlare::SampleBin &AudioController::get_dummy_sample_bin_ref()
{
   return dummy_sample_bin;
}


void AudioController::initialize()
{
   if (output_loading_debug_to_cout) std::cout << "Loading assets in AudioController... " << std::endl;
   if (output_loading_debug_to_cout) std::cout << "sound_effects:" << std::endl;
   for (auto &sound_effect_element : sound_effect_elements)
   {
      std::string identifier = sound_effect_element.first;
      std::string filename = sound_effect_element.second.get_filename();
      bool loop = sound_effect_element.second.get_loop();

      std::string asset_key = sound_effects_identifier_prefix + filename;

      if (output_loading_debug_to_cout) std::cout << "- asset_key: " << asset_key << std::endl;

      ALLEGRO_SAMPLE *sample = sample_bin.auto_get(asset_key);
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

      ALLEGRO_SAMPLE *sample = sample_bin.auto_get(asset_key);
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
   stop_all();
   for (auto &sound_effect : sound_effects) delete sound_effect.second;
   for (auto &music_track : music_tracks) delete music_track.second;
   return;
}

void AudioController::stop_all()
{
   // TODO
   return;
}

void AudioController::set_global_volume(float volume)
{
   // TODO
   return;
}

void AudioController::play_music_track_by_identifier(std::string identifier)
{
   // TODO
   return;
}

void AudioController::play_sound_effect_by_identifier(std::string identifier)
{
   // TODO
   return;
}
} // namespace AllegroFlare


