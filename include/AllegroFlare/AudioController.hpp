#pragma once


#include <AllegroFlare/AudioController.hpp>
#include <AllegroFlare/AudioRepositoryElement.hpp>
#include <AllegroFlare/SampleBin.hpp>
#include <AllegroFlare/Sound.hpp>
#include <map>
#include <string>


namespace AllegroFlare
{
   class AudioController
   {
   public:

      enum RecordExistsBehavior
      {
         UNDEF = 0,
         OVERWRITE_WITHOUT_WARNING,
         OVERWRITE_WITH_WARNING,
         SKIP_WITHOUT_WARNING,
         SKIP_WITH_WARNING,
         THROW,
      };
   private:
      AllegroFlare::SampleBin* sample_bin;
      std::string sound_effects_identifier_prefix;
      std::string music_tracks_identifier_prefix;
      std::map<std::string, AllegroFlare::AudioRepositoryElement> sound_effect_elements;
      std::map<std::string, AllegroFlare::AudioRepositoryElement> music_track_elements;
      std::map<std::string, AllegroFlare::Sound*> sound_effects;
      std::map<std::string, AllegroFlare::Sound*> music_tracks;
      std::string current_music_track_identifier;
      float global_volume;
      bool output_loading_debug_to_cout;
      bool initialized;
      void load_sound_effects();
      void load_music_tracks();
      void destruct_all();
      void destruct_all_sound_effects();
      void destruct_all_music_tracks();
      void stop_all_sound_effects();
      bool sound_effect_exists(std::string identifier="[unset-identifier]");
      bool music_track_exists(std::string identifier="[unset-identifier]");
      bool sound_effect_element_exists(std::string identifier="a-sound-effect-identifier-that-is-not-set");
      AllegroFlare::Sound* find_sound_effect_sound_object_by_identifier(std::string identifier="a-sound-effect-identifier-that-is-not-set");
      AllegroFlare::AudioRepositoryElement find_sound_effect_element_by_identifier(std::string identifier="a-sound-effect-identifier-that-is-not-set");
      AllegroFlare::Sound* find_music_track_sound_object_by_identifier(std::string identifier="a-music-track-identifier-that-is-not-set");
      bool music_track_element_exists(std::string identifier="a-music-track-identifier-that-is-not-set");
      AllegroFlare::AudioRepositoryElement find_music_track_element_by_identifier(std::string identifier="a-music-track-identifier-that-is-not-set");

   protected:


   public:
      AudioController(AllegroFlare::SampleBin* sample_bin=nullptr, std::map<std::string, AllegroFlare::AudioRepositoryElement> sound_effect_elements={}, std::map<std::string, AllegroFlare::AudioRepositoryElement> music_track_elements={});
      ~AudioController();

      bool get_initialized() const;
      void initialize();
      void set_and_load_sound_effect_elements(std::map<std::string, AllegroFlare::AudioRepositoryElement> sound_effect_elements={});
      void add_and_load_sound_effect_elements(std::map<std::string, AllegroFlare::AudioRepositoryElement> sound_effect_elements_to_add={}, AllegroFlare::AudioController::RecordExistsBehavior record_exists_behavior=AllegroFlare::AudioController::RecordExistsBehavior::THROW);
      void set_and_load_music_track_elements(std::map<std::string, AllegroFlare::AudioRepositoryElement> music_track_elements={});
      void destruct();
      void stop_all();
      void stop_all_music_tracks();
      void set_global_volume(float volume=0.1);
      void play_sound_effect(std::string identifier="a-sound-effect-identifier-that-is-not-set");
      void stop_sound_effect(std::string identifier="a-sound-effect-identifier-that-is-not-set");
      void play_music_track(std::string identifier="a-music-track-identifier-that-is-not-set");
      void dump_to_cout();
   };
}



