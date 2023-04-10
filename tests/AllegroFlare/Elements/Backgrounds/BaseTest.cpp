
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/Backgrounds/Base.hpp>


TEST(AllegroFlare_Elements_Backgrounds_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::Backgrounds::Base base;
}


TEST(AllegroFlare_Elements_Backgrounds_BaseTest, TYPE__has_the_expected_value)
{
   EXPECT_EQ("AllegroFlare/Elements/Backgrounds/Base", AllegroFlare::Elements::Backgrounds::Base::TYPE);
}


TEST(AllegroFlare_Elements_Backgrounds_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::Backgrounds::Base base_background;
   EXPECT_EQ(AllegroFlare::Elements::Backgrounds::Base::TYPE, base_background.get_type());
}


