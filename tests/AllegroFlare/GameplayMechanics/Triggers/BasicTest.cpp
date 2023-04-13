
#include <gtest/gtest.h>

#include <AllegroFlare/GameplayMechanics/Triggers/Basic.hpp>


TEST(AllegroFlare_GameplayMechanics_Triggers_BasicTest, can_be_created_without_blowing_up)
{
   AllegroFlare::GameplayMechanics::Triggers::Basic basic;
}


TEST(AllegroFlare_GameplayMechanics_Triggers_BasicTest, TYPE__has_the_expected_value)
{
   EXPECT_EQ("AllegroFlare/GameplayMechanics/Triggers/Basic", AllegroFlare::GameplayMechanics::Triggers::Basic::TYPE);
}


TEST(AllegroFlare_GameplayMechanics_Triggers_BasicTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::GameplayMechanics::Triggers::Basic basic;
   EXPECT_EQ(AllegroFlare::GameplayMechanics::Triggers::Basic::TYPE, basic.get_type());
}


