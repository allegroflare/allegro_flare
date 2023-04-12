
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


