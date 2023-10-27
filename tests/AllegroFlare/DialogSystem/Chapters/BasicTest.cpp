
#include <gtest/gtest.h>

#include <AllegroFlare/DialogSystem/Chapters/Basic.hpp>


TEST(AllegroFlare_DialogSystem_Chapters_BasicTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogSystem::Chapters::Basic basic;
}


TEST(AllegroFlare_DialogSystem_Chapters_BasicTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogSystem/Chapters/Basic",
     AllegroFlare::DialogSystem::Chapters::Basic::TYPE
   );
}


TEST(AllegroFlare_DialogSystem_Chapters_BasicTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogSystem::Chapters::Basic basic;
   EXPECT_EQ(AllegroFlare::DialogSystem::Chapters::Basic::TYPE, basic.get_type());
}


