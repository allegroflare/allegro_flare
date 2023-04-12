
#include <gtest/gtest.h>

#include <AllegroFlare/VideoBin.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_VideoBinTest : public ::testing::Test{};
class AllegroFlare_VideoBinTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


TEST_F(AllegroFlare_VideoBinTest, can_be_created_without_blowing_up)
{
   AllegroFlare::VideoBin video_bin;
}


TEST_F(AllegroFlare_VideoBinTestWithAllegroRenderingFixture,
   DISABLED__load_data__will_load_data_from_the_expected_path)
{
   // TODO: Implement this test
   //al_init_video_addon();
   //AllegroFlare::VideoBin video_bin;
   //video_bin.set_full_path(get_fixtures_path() + "videos/");

   //std::string test_video_identifier = "file_example_OGG_480_1_7mg.ogg";
   //ALLEGRO_VIDEO* loaded_video = video_bin.load_data(test_video_identifier);
   //EXPECT_NE(nullptr, loaded_video);
   //al_shutdown_video_addon();
}


