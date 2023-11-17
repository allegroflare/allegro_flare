
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/DialogBoxStyles.hpp>


TEST(AllegroFlare_Elements_DialogBoxStylesTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxStyles dialog_box_styles;
}


TEST(AllegroFlare_Elements_DialogBoxStylesTest, run__returns_the_expected_response)
{
   AllegroFlare::Elements::DialogBoxStyles dialog_box_styles;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, dialog_box_styles.run());
}


