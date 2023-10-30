
#include <gtest/gtest.h>

#include <AllegroFlare/GameConfigurations/Base.hpp>


class GameConfigurationsBaseTestClass : public AllegroFlare::GameConfigurations::Base
{
public:
   GameConfigurationsBaseTestClass()
      : AllegroFlare::GameConfigurations::Base("GameConfigurationsBaseTestClass")
   {}
};


TEST(AllegroFlare_GameConfigurations_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::GameConfigurations::Base base;
}


TEST(AllegroFlare_GameConfigurations_BaseTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/GameConfigurations/Base",
     AllegroFlare::GameConfigurations::Base::TYPE
   );
}


TEST(AllegroFlare_GameConfigurations_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::GameConfigurations::Base base;
   EXPECT_EQ(AllegroFlare::GameConfigurations::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_GameConfigurations_BaseTest, derived_classes_will_have_the_expected_type)
{
   GameConfigurationsBaseTestClass test_class;
   EXPECT_EQ("GameConfigurationsBaseTestClass", test_class.get_type());
}


