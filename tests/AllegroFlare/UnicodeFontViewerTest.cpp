
#include <gtest/gtest.h>

#include <AllegroFlare/UnicodeFontViewer.hpp>


TEST(AllegroFlare_UnicodeFontViewerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::UnicodeFontViewer unicode_font_viewer;
}


TEST(AllegroFlare_UnicodeFontViewerTest, run__returns_the_expected_response)
{
   AllegroFlare::UnicodeFontViewer unicode_font_viewer;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, unicode_font_viewer.run());
}

