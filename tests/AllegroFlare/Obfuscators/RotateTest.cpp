
#include <gtest/gtest.h>

#include <AllegroFlare/Obfuscators/Rotate.hpp>


TEST(AllegroFlare_Obfuscators_RotateTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Obfuscators::Rotate rotate;
}


TEST(AllegroFlare_Obfuscators_RotateTest, run__returns_the_expected_response)
{
   AllegroFlare::Obfuscators::Rotate rotate;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, rotate.run());
}


