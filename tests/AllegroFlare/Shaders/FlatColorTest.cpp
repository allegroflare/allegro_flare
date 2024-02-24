
#include <gtest/gtest.h>

#include <AllegroFlare/Shaders/FlatColor.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Shaders_FlatColorTest: public ::testing::Test {};
class AllegroFlare_Shaders_FlatColorWithAllegroRenderingFixtureTest :
   public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


TEST_F(AllegroFlare_Shaders_FlatColorTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Shaders::FlatColor flat_color;
}


TEST_F(AllegroFlare_Shaders_FlatColorTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Shaders/FlatColor",
     AllegroFlare::Shaders::FlatColor::TYPE
   );
}


TEST_F(AllegroFlare_Shaders_FlatColorTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Shaders::FlatColor flat_color;
   EXPECT_EQ(AllegroFlare::Shaders::FlatColor::TYPE, flat_color.get_type());
}


TEST_F(AllegroFlare_Shaders_FlatColorWithAllegroRenderingFixtureTest, activate__does_not_blow_up)
{
   AllegroFlare::Shaders::FlatColor flat_color;
   flat_color.initialize();
   flat_color.activate();
}


// TODO: Add a render test with a bitmap render subject


