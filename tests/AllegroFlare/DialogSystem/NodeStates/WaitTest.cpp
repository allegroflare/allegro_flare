
#include <gtest/gtest.h>

#include <AllegroFlare/DialogSystem/NodeStates/Wait.hpp>


TEST(AllegroFlare_DialogSystem_NodeStates_WaitTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogSystem::NodeStates::Wait wait;
}


TEST(AllegroFlare_DialogSystem_NodeStates_WaitTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogSystem/NodeStates/Wait",
     AllegroFlare::DialogSystem::NodeStates::Wait::TYPE
   );
}


TEST(AllegroFlare_DialogSystem_NodeStates_WaitTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogSystem::NodeStates::Wait wait;
   EXPECT_EQ(AllegroFlare::DialogSystem::NodeStates::Wait::TYPE, wait.get_type());
}


