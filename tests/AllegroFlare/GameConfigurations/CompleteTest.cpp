
#include <gtest/gtest.h>

#include <AllegroFlare/GameConfigurations/Complete.hpp>


class GameConfigurationsBaseTestClass : public AllegroFlare::GameConfigurations::Complete
{
public:
   GameConfigurationsBaseTestClass()
      : AllegroFlare::GameConfigurations::Complete("GameConfigurationsBaseTestClass")
   {}
};


TEST(AllegroFlare_GameConfigurations_CompleteTest, can_be_created_without_blowing_up)
{
   AllegroFlare::GameConfigurations::Complete complete;
}


TEST(AllegroFlare_GameConfigurations_CompleteTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/GameConfigurations/Complete",
     AllegroFlare::GameConfigurations::Complete::TYPE
   );
}


TEST(AllegroFlare_GameConfigurations_CompleteTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::GameConfigurations::Complete complete;
   EXPECT_EQ(AllegroFlare::GameConfigurations::Complete::TYPE, complete.get_type());
}


TEST(AllegroFlare_GameConfigurations_CompleteTest, derived_classes_will_have_the_expected_type)
{
   GameConfigurationsBaseTestClass test_class;
   EXPECT_EQ("GameConfigurationsBaseTestClass", test_class.get_type());
}


