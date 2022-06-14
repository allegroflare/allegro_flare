
#include <gtest/gtest.h>

#include <AllegroFlare/FontBravura.hpp>


TEST(AllegroFlare_FontBravuraTest, can_be_created_without_blowing_up)
{
   AllegroFlare::FontBravura font_bravura;
}


TEST(AllegroFlare_FontBravuraTest, run__returns_the_expected_response)
{
   AllegroFlare::FontBravura font_bravura;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, font_bravura.run());
}

