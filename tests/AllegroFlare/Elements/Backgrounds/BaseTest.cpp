
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/Backgrounds/Base.hpp>


TEST(AllegroFlare_Elements_Backgrounds_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::Backgrounds::Base base;
}


TEST(AllegroFlare_Elements_Backgrounds_BaseTest, has_the_expected_type)
{
   AllegroFlare::Elements::Backgrounds::Base base_background;
   EXPECT_EQ("AllegroFlare/Elements/Backgrounds/Base", base_background.get_type());
}


