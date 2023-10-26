
#include <gtest/gtest.h>

#include <AllegroFlare/DialogSystem/Scenes/Basic.hpp>


TEST(AllegroFlare_DialogSystem_Scenes_BasicTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogSystem::Scenes::Basic basic;
}


TEST(AllegroFlare_DialogSystem_Scenes_BasicTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogSystem/Scenes/Basic",
     AllegroFlare::DialogSystem::Scenes::Basic::TYPE
   );
}


TEST(AllegroFlare_DialogSystem_Scenes_BasicTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogSystem::Scenes::Basic basic;
   EXPECT_EQ(AllegroFlare::DialogSystem::Scenes::Basic::TYPE, basic.get_type());
}


