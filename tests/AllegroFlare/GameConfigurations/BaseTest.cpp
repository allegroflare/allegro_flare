
#include <gtest/gtest.h>

#include <AllegroFlare/GameConfigurations/Base.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Logger.hpp>


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


TEST(AllegroFlare_GameConfigurations_BaseTest, load_level_by_identifier__without_implementation__will_throw_an_error)
{
   GameConfigurationsBaseTestClass test_class;
   EXPECT_THROW_WITH_MESSAGE(
      test_class.load_level_by_identifier(),
      std::runtime_error,
      "[AllegroFlare::GameConfigurations::Base::load_level_by_identifier]: error: "
         "Not implemented in the base class. This method must be implemented in the derived class"
   );

   // TODO: Add similar tests for other methods that require override
}


