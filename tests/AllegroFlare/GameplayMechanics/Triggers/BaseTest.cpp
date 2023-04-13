
#include <gtest/gtest.h>

#include <AllegroFlare/GameplayMechanics/Triggers/Base.hpp>


class TriggersBaseTestClass : public AllegroFlare::GameplayMechanics::Triggers::Base
{
public:
   TriggersBaseTestClass()
      : AllegroFlare::GameplayMechanics::Triggers::Base("TriggersBaseTestClass")
   {}
};


TEST(AllegroFlare_GameplayMechanics_Triggers_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::GameplayMechanics::Triggers::Base base;
}


TEST(AllegroFlare_GameplayMechanics_Triggers_BaseTest, TYPE__has_the_expected_value)
{
   EXPECT_EQ("AllegroFlare/GameplayMechanics/Triggers/Base", AllegroFlare::GameplayMechanics::Triggers::Base::TYPE);
}


TEST(AllegroFlare_GameplayMechanics_Triggers_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::GameplayMechanics::Triggers::Base base;
   EXPECT_EQ(AllegroFlare::GameplayMechanics::Triggers::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_GameplayMechanics_Triggers_BaseTest, derived_classes_will_have_the_expected_type)
{
   TriggersBaseTestClass test_class;
   EXPECT_EQ("TriggersBaseTestClass", test_class.get_type());
}


