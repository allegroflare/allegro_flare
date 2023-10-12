
#include <gtest/gtest.h>

#include <AllegroFlare/DialogSystem/NodeStates/Base.hpp>


class NodeStatesBaseTestClass : public AllegroFlare::DialogSystem::NodeStates::Base
{
public:
   NodeStatesBaseTestClass()
      : AllegroFlare::DialogSystem::NodeStates::Base("NodeStatesBaseTestClass")
   {}
};


TEST(AllegroFlare_DialogSystem_NodeStates_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogSystem::NodeStates::Base base;
}


TEST(AllegroFlare_DialogSystem_NodeStates_BaseTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogSystem/NodeStates/Base",
     AllegroFlare::DialogSystem::NodeStates::Base::TYPE
   );
}


TEST(AllegroFlare_DialogSystem_NodeStates_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogSystem::NodeStates::Base base;
   EXPECT_EQ(AllegroFlare::DialogSystem::NodeStates::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_DialogSystem_NodeStates_BaseTest, derived_classes_will_have_the_expected_type)
{
   NodeStatesBaseTestClass test_class;
   EXPECT_EQ("NodeStatesBaseTestClass", test_class.get_type());
}


