
#include <gtest/gtest.h>

#include <AllegroFlare/SamplesAndRendersBin.hpp>
#include <AllegroFlare/DeploymentEnvironment.hpp>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>


static bool save_bitmap_to_test_snapshots(std::string filename, ALLEGRO_BITMAP* bitmap)
{
   // Requires image_addon to be initialized
   return al_save_bitmap(("./tmp/test_snapshots/" + filename).c_str(), bitmap);
}


TEST(AllegroFlare_SamplesAndRendersBinTest, can_be_created_without_blowing_up)
{
   AllegroFlare::SamplesAndRendersBin sample_renders_bin;
}


TEST(AllegroFlare_SamplesAndRendersBinTest, load_data__will_load_the_data_as_expected)
{
   AllegroFlare::DeploymentEnvironment deployment_environment(AllegroFlare::DeploymentEnvironment::ENVIRONMENT_TEST);
   al_init();
   al_install_audio();
   al_reserve_samples(8);
   al_init_acodec_addon();
   al_init_image_addon();

   AllegroFlare::SamplesAndRendersBin sample_renders_bin;
   sample_renders_bin.set_full_path(deployment_environment.get_data_folder_path() + "samples/music_tracks/");
   std::string sample_identifier = "test-bips-130bpm-01.ogg";
   std::pair<ALLEGRO_SAMPLE*, ALLEGRO_BITMAP*> loaded_data = sample_renders_bin.load_data(sample_identifier);

   ASSERT_NE(nullptr, loaded_data.first);
   ASSERT_NE(nullptr, loaded_data.second);

   ASSERT_EQ(true, save_bitmap_to_test_snapshots("load_data.png", loaded_data.second));

   al_shutdown_image_addon();
   al_uninstall_audio();
   al_uninstall_system();
}


