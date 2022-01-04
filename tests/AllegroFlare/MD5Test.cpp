
#include <gtest/gtest.h>

#include <AllegroFlare/MD5.hpp>

TEST(AllegroFlare_MD5Test, can_be_created_without_blowing_up)
{
   AllegroFlare::MD5 md5;
}

TEST(AllegroFlare_MD5Test, run__returns_the_expected_response)
{
   AllegroFlare::MD5 md5;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, md5.run());
}
