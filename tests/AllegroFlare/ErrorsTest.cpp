
#include <gtest/gtest.h>

#include <AllegroFlare/Errors.hpp>


TEST(AllegroFlare_ErrorsTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Errors errors;
}


TEST(AllegroFlare_ErrorsTest, run__returns_the_expected_response)
{
   AllegroFlare::Errors errors;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, errors.run());
}


