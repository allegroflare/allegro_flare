
#include <gtest/gtest.h>

#include <AllegroFlare/Obfuscator.hpp>


TEST(AllegroFlare_ObfuscatorTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Obfuscator obfuscator;
}


TEST(AllegroFlare_ObfuscatorTest, run__returns_the_expected_response)
{
   AllegroFlare::Obfuscator obfuscator;
   std::string initial_string = "Hello World!";
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, obfuscator.encode(initial_string));
}


