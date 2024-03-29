
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/WithAllegroFlareFrameworksFullFixture.hpp>


class TestClassFor_AllegroFlare_Testing_WithAllegroFlareFrameworksFullFixture
   : public AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture
{};


TEST_F(TestClassFor_AllegroFlare_Testing_WithAllegroFlareFrameworksFullFixture,
   get_test_name__will_return_the_name_of_the_test)
{
   std::string expected_test_name = "get_test_name__will_return_the_name_of_the_test";
   EXPECT_EQ(expected_test_name, get_test_name());
}


TEST_F(TestClassFor_AllegroFlare_Testing_WithAllegroFlareFrameworksFullFixture,
   get_test_suite_name__will_return_the_name_of_the_test)
{
   std::string expected_test_name = "TestClassFor_AllegroFlare_Testing_WithAllegroFlareFrameworksFullFixture";
   EXPECT_EQ(expected_test_name, get_test_suite_name());
}


TEST_F(TestClassFor_AllegroFlare_Testing_WithAllegroFlareFrameworksFullFixture,
   SetUp__will_set_the_frameworks_deployment_environment_to_test)
{
   EXPECT_EQ(true, get_framework_ref().is_deployment_environment_test());
}


TEST_F(TestClassFor_AllegroFlare_Testing_WithAllegroFlareFrameworksFullFixture,
   SetUp__will_set_the_bins_pointers_to_the_bins_of_the_framework)
{
   EXPECT_EQ(get_framework_bitmap_bin(), &get_framework_ref().get_bitmap_bin_ref());
   EXPECT_EQ(get_framework_font_bin(), &get_framework_ref().get_font_bin_ref());
   EXPECT_EQ(get_framework_model_bin(), &get_framework_ref().get_model_bin_ref());
   EXPECT_EQ(get_framework_sample_bin(), &get_framework_ref().get_sample_bin_ref());
   EXPECT_EQ(get_framework_video_bin(), &get_framework_ref().get_video_bin_ref());
}


TEST_F(TestClassFor_AllegroFlare_Testing_WithAllegroFlareFrameworksFullFixture,
   SetUp__will_set_the_framework_data_folder_path)
{
   EXPECT_EQ(get_framework_data_folder_path(), get_framework_ref().get_data_folder_path());
}


TEST_F(TestClassFor_AllegroFlare_Testing_WithAllegroFlareFrameworksFullFixture,
   SetUp__will_set_event_emitter_pointer_to_the_pointer_of_the_framework)
{
   EXPECT_EQ(get_framework_event_emitter(), &get_framework_ref().get_event_emitter_ref());
}


TEST_F(TestClassFor_AllegroFlare_Testing_WithAllegroFlareFrameworksFullFixture,
   SetUp__will_set_proifiler_pointer_to_the_pointer_of_the_framework)
{
   EXPECT_EQ(get_framework_profiler(), &get_framework_ref().get_profiler_ref());
}


TEST_F(TestClassFor_AllegroFlare_Testing_WithAllegroFlareFrameworksFullFixture,
   DISABLED__will_set_the_window_title_to_the_test_suite_name_and_test_name)
{
   // NOTE: cannot currently test this, Allegro5 does not currently have a al_get_window_title() feature
}


TEST_F(TestClassFor_AllegroFlare_Testing_WithAllegroFlareFrameworksFullFixture,
   DISABLED__with_a_test_name_prefixed_with_CAPTURE__will_save_a_screenshot_of_the_backbuffer_during_teardown)
{
   // NOTE: cannot currently test this, assertion would need to happen after teardown
}


TEST_F(TestClassFor_AllegroFlare_Testing_WithAllegroFlareFrameworksFullFixture,
   DISABLED__clear_display__will_clear_the_current_target_rendering_surface_to_an_eigengrau_color)
{
   // TODO
}


