
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/GameConfigurations/Complete/SimpleConfiguration.hpp>


TEST(AllegroFlare_Testing_GameConfigurations_Complete_SimpleConfigurationTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Testing::GameConfigurations::Complete::SimpleConfiguration simple_configuration;
}


TEST(AllegroFlare_Testing_GameConfigurations_Complete_SimpleConfigurationTest, run__returns_the_expected_response)
{
   AllegroFlare::Testing::GameConfigurations::Complete::SimpleConfiguration simple_configuration;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, simple_configuration.run());
}


