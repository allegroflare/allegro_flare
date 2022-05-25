
#include <gtest/gtest.h>

#include <AllegroFlare/Timeline/ScriptLoader.hpp>


TEST(AllegroFlare_Timeline_ScriptLoaderTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Timeline::ScriptLoader script_loader;
}


TEST(AllegroFlare_Timeline_ScriptLoaderTest, run__returns_the_expected_response)
{
   AllegroFlare::Timeline::ScriptLoader script_loader;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, script_loader.run());
}

