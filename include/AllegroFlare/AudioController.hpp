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

   public:
      AudioController(AllegroFlare::SampleBin& sample_bin=get_dummy_sample_bin_ref(), std::map<std::string, AllegroFlare::AudioRepositoryElement> sound_effect_elements={}, std::map<std::string, AllegroFlare::AudioRepositoryElement> music_track_elements={});
      ~AudioController();

      static AllegroFlare::SampleBin &get_dummy_sample_bin_ref();
      std::string run();
   };
}



