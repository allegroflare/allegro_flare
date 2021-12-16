#pragma once


#include <AllegroFlare/AudioRepositoryElement.hpp>
#include <AllegroFlare/SampleBin.hpp>
#include <AllegroFlare/Sound.hpp>
#include <map>
#include <string>


namespace AllegroFlare
{
   class AudioController
   {
   private:
      AllegroFlare::SampleBin& sample_bin;
      std::string sound_effects_identifier_prefix;
      std::string music_tracks_identifier_prefix;
      std::map<std::string, AllegroFlare::AudioRepositoryElement> sound_effect_elements;
      std::map<std::string, AllegroFlare::AudioRepositoryElement> music_track_elements;
      std::map<std::string, AllegroFlare::Sound*> sound_effects;
      std::map<std::string, AllegroFlare::Sound*> music_tracks;
      std::string current_music_track_identifier;
      float global_volume;
      bool output_loading_debug_to_cout;
      static AllegroFlare::SampleBin dummy_sample_bin;
      bool initialized;

   public:
      AudioController(AllegroFlare::SampleBin& sample_bin=get_dummy_sample_bin_ref(), std::map<std::string, AllegroFlare::AudioRepositoryElement> sound_effect_elements={}, std::map<std::string, AllegroFlare::AudioRepositoryElement> music_track_elements={});
      ~AudioController();

      bool get_initialized();
      static AllegroFlare::SampleBin &get_dummy_sample_bin_ref();
      void initialize();
      void destruct();
      void stop_all();
      void stop_all_music();
      void stop_all_sound_effects();
      void set_global_volume(float volume=0.1);
      void play_sound_effect_by_identifier(std::string identifier="a-sound-effect-identifier-that-is-not-set");
      void play_music_track_by_identifier(std::string identifier="a-music-track-identifier-that-is-not-set");
      AllegroFlare::Sound* find_sound_effect_by_identifier(std::string identifier="a-sound-effect-identifier-that-is-not-set");
      AllegroFlare::Sound* find_music_track_by_identifier(std::string identifier="a-music-track-identifier-that-is-not-set");
   };
}



