

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
   // TODO
   initialized = true;
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


