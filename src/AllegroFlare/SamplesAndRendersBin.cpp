

#include <AllegroFlare/SamplesAndRendersBin.hpp>

#include <AllegroFlare/AudioWaveformRenderer.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


SamplesAndRendersBin::SamplesAndRendersBin()
   : AllegroFlare::Bin<std::string, std::pair<ALLEGRO_SAMPLE*, ALLEGRO_BITMAP*>>("AllegroFlare/SampleAndRendersBin")
   , samples_to_bitmaps_map({})
{
}


SamplesAndRendersBin::~SamplesAndRendersBin()
{
}


bool SamplesAndRendersBin::validate()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[SamplesAndRendersBin::validate]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SamplesAndRendersBin::validate: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_audio_installed()))
   {
      std::stringstream error_message;
      error_message << "[SamplesAndRendersBin::validate]: error: guard \"al_is_audio_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SamplesAndRendersBin::validate: error: guard \"al_is_audio_installed()\" not met");
   }
   if (!(al_is_acodec_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[SamplesAndRendersBin::validate]: error: guard \"al_is_acodec_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SamplesAndRendersBin::validate: error: guard \"al_is_acodec_addon_initialized()\" not met");
   }
   // TODO: Add guards on audio
   return true;
}

ALLEGRO_BITMAP* SamplesAndRendersBin::find_render_by_sample(ALLEGRO_SAMPLE* sample)
{
   if (samples_to_bitmaps_map.find(sample) == samples_to_bitmaps_map.end()) return nullptr;
   return samples_to_bitmaps_map[sample];
}

std::pair<ALLEGRO_SAMPLE*, ALLEGRO_BITMAP*> SamplesAndRendersBin::load_data(std::string identifier)
{
   if (!(validate()))
   {
      std::stringstream error_message;
      error_message << "[SamplesAndRendersBin::load_data]: error: guard \"validate()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SamplesAndRendersBin::load_data: error: guard \"validate()\" not met");
   }
   // Load the sample
   ALLEGRO_SAMPLE *sample = al_load_sample((get_path() + identifier).c_str());

   if (!sample)
   {
      AllegroFlare::Logger::throw_error(
            "AllegroFlare::SampleAndRendersBinxx",
            "Could not load sample by identifier \"" + identifier
               + "\" while looking in \"" + get_path()
               + "\" while working in \"" + std::filesystem::current_path().string() + "\"."
         );
   }

   // Create a bitmap from the sample
   ALLEGRO_STATE previous_render_state;
   al_store_state(&previous_render_state, ALLEGRO_STATE_TARGET_BITMAP);
   ALLEGRO_BITMAP *render = al_create_bitmap(512, 64); // TODO: Create a dynamically sized bitmap
                                                       // TODO: Put the samples on a sprite sheet
                                                       // TODO: Consider adding more settings for width/height
   AllegroFlare::AudioWaveformRenderer renderer(sample);
   al_set_target_bitmap(render);
   renderer.draw_waveform(render);
   al_restore_state(&previous_render_state);

   samples_to_bitmaps_map[sample] = render;

   return std::pair<ALLEGRO_SAMPLE*, ALLEGRO_BITMAP*>(sample, render);
}

void SamplesAndRendersBin::destroy_data(std::pair<ALLEGRO_SAMPLE*, ALLEGRO_BITMAP*> sample_and_render)
{
   if (sample_and_render.first) al_destroy_sample(sample_and_render.first);
   if (sample_and_render.second) al_destroy_bitmap(sample_and_render.second);
   samples_to_bitmaps_map.erase(sample_and_render.first);
   return;
}


} // namespace AllegroFlare


