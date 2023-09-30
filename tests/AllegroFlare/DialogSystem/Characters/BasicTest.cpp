
#include <gtest/gtest.h>

#include <AllegroFlare/DialogSystem/Characters/Basic.hpp>


TEST(AllegroFlare_DialogSystem_Characters_BasicTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogSystem::Characters::Basic basic;
}


TEST(AllegroFlare_DialogSystem_Characters_BasicTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogSystem/Characters/Basic",
     AllegroFlare::DialogSystem::Characters::Basic::TYPE
   );
}


TEST(AllegroFlare_DialogSystem_Characters_BasicTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogSystem::Characters::Basic basic;
   EXPECT_EQ(AllegroFlare::DialogSystem::Characters::Basic::TYPE, basic.get_type());
}


