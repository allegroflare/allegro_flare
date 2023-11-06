
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/Backgrounds/None.hpp>


TEST(AllegroFlare_Elements_Backgrounds_NoneTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::Backgrounds::None none;
}


TEST(AllegroFlare_Elements_Backgrounds_NoneTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Elements/Backgrounds/None",
     AllegroFlare::Elements::Backgrounds::None::TYPE
   );
}


TEST(AllegroFlare_Elements_Backgrounds_NoneTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::Backgrounds::None none;
   EXPECT_EQ(AllegroFlare::Elements::Backgrounds::None::TYPE, none.get_type());
}


