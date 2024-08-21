
#include <gtest/gtest.h>

#include <AllegroFlare/Screens/Gameplay.hpp>
#include <AllegroFlare/Testing/WithAllegroFlareFrameworksFullFixture.hpp>


class AllegroFlare_Screens_GameplayTest : public ::testing::Test {};
class AllegroFlare_Screens_GameplayTestWithAllegroFlareFrameworksFullFixture :
   public AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture
{
public:
   //AllegroFlare_Screens_GameplayTestWithAllegroRenderingFixture
};


TEST_F(AllegroFlare_Screens_GameplayTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::Gameplay gameplay;
}


TEST_F(AllegroFlare_Screens_GameplayTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ("AllegroFlare/Screens/Gameplay", AllegroFlare::Screens::Gameplay::TYPE);
}


TEST_F(AllegroFlare_Screens_GameplayTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Screens::Gameplay gameplay;
   EXPECT_EQ(AllegroFlare::Screens::Gameplay::TYPE, gameplay.get_type());
}


TEST_F(AllegroFlare_Screens_GameplayTestWithAllegroFlareFrameworksFullFixture, will_work_in_a_framework_context)
{
   AllegroFlare::Screens::Gameplay gameplay;
   framework_register_and_activate_screen("gameplay", &gameplay);
   framework_run_loop();
}


