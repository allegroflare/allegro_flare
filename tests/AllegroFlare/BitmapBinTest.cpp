
#include <gtest/gtest.h>

#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/DeploymentEnvironment.hpp>


TEST(AllegroFlare_BitmapBinTest, can_be_crated_without_blowing_up)
{
   AllegroFlare::BitmapBin bitmap_bin;
}


TEST(AllegroFlare_BitmapBinTest, validate__without_the_image_addon_initialized__outputs_an_error)
{
   AllegroFlare::BitmapBin bitmap_bin;

   testing::internal::CaptureStdout();
   bitmap_bin.validate();
   std::string output = testing::internal::GetCapturedStdout();
   std::string expected_cerr_output = "\x1B[1;31m"
                                      "[AllegroFlare::BitmapBin::validate] not properly initialized "
                                      "(requires al_init_image_addon()).  Will crash probably crash."
                                      "\x1B[0m"
                                      "\n";
   ASSERT_EQ(expected_cerr_output, output);
}


TEST(AllegroFlare_BitmapBinTest, DISABLED__destroy_data__after_shutdown__will_throw_an_error)
   // TODO: This test works, but will crash when bitmap_bin is destroyed at the end of the test. Will need to find
   // alternative technique to test without illiciting an actual crash
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string fixture_path = deployment_environment.get_data_folder_path();

   AllegroFlare::BitmapBin bitmap_bin;
   bitmap_bin.set_full_path(fixture_path + "bitmaps/");

   al_init();
   al_init_image_addon();

   //ALLEGRO_BITMAP *bitmap =
   bitmap_bin.preload("commissioner-01.gif");
   //EXPECT_NE(nullptr, bitmap);

   al_uninstall_system();

   EXPECT_THROW_WITH_MESSAGE(
      bitmap_bin.destroy("commissioner-01.gif"),
      std::runtime_error,
      "foo"
   );
}


TEST(AllegroFlare_BitmapBinTest, build_standard_path__will_return_a_string_for_the_folder_where_the_assets_are_located)
{
   AllegroFlare::DeploymentEnvironment deployment_environment(AllegroFlare::DeploymentEnvironment::ENVIRONMENT_TEST);

   std::string expected_path = "tests/fixtures/bitmaps/";
   std::string actual_path =
      AllegroFlare::BitmapBin::build_standard_path(deployment_environment.get_data_folder_path());

   EXPECT_EQ(expected_path, actual_path);
}


